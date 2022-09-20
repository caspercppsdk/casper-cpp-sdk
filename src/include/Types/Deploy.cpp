#include "Types/Deploy.h"
#include "ByteSerializers/ExecutableDeployItemByteSerializer.h"
#include "ByteSerializers/DeployByteSerializer.h"

namespace Casper {

Deploy::Deploy(DeployHeader header, ExecutableDeployItem payment,
               ExecutableDeployItem session) {
  CBytes body_hash = ComputeBodyHash(payment, session);

  this->header = DeployHeader(header.account, header.timestamp, header.ttl,
                              header.gas_price, hexEncode(body_hash),
                              header.dependencies, header.chain_name);

  this->hash = hexEncode(ComputeHeaderHash(this->header));

  this->payment = payment;
  this->session = session;
}

/// <summary>
/// Signs the deploy with a private key and adds a new Approval to it.
/// </summary>
void Deploy::Sign(KeyPair keyPair) {
  CBytes signature = keyPair.Sign(CEP57Checksum::Decode(this->hash));

  this->approvals.emplace_back(
      keyPair.public_key,
      Signature::FromRawBytes(signature, keyPair.public_key.key_algorithm));
}

/// <summary>
/// Signs the deploy with a private key and adds a new Approval to it.
/// </summary>
void Deploy::Sign(Secp256k1Key& sec_key) {
  CBytes signature = sec_key.sign(CEP57Checksum::Decode(this->hash));

  std::string public_key_str = "02" + sec_key.getPublicKeyStr();
  this->approvals.emplace_back(
      Casper::PublicKey::FromHexString(public_key_str),
      Signature::FromRawBytes(signature, KeyAlgo::SECP256K1));
}

/// <summary>
/// Adds an approval to the deploy. No check is done to the approval signature.
/// </summary>
void Deploy::AddApproval(DeployApproval approval) {
  this->approvals.push_back(approval);
}

/// <summary>
/// Validates the body and header hashes in the deploy.
/// </summary>
/// <param name="message">output string with a validation error message if
/// validation fails. empty otherwise.</param> <returns>false if the validation
/// of hashes is not successful</returns>
bool Deploy::ValidateHashes(std::string& message) {
  CBytes computed_hash = ComputeBodyHash(this->payment, this->session);

  if (hexDecode(this->header.body_hash) != computed_hash) {
    message =
        "Computed Body Hash does not match value in deploy header. "
        "Expected: " +
        this->header.body_hash +
        "Computed: " + CEP57Checksum::Encode(computed_hash);
    return false;
  }

  computed_hash = ComputeHeaderHash(this->header);

  if (hexDecode(this->hash) != computed_hash) {
    message =
        "Computed Hash does not match value in deploy object. "
        "Expected: " +
        this->hash + "Computed: " + CEP57Checksum::Encode(computed_hash);
    return false;
  }

  message = "";
  return true;
}

/// <summary>
/// Verifies the signatures in the list of approvals.
/// </summary>
/// <param name="message">an output string with the signer which signature could
/// not be verified. empty if verification succeeds.</param> <returns>false if
/// the verification of a signature fails.</returns>
bool Deploy::VerifySignatures(std::string& message) {
  message = "";

  for (auto& approval : this->approvals) {
    if (!approval.signer.VerifySignature(hexDecode(this->hash),
                                         approval.signature.raw_bytes)) {
      message =
          "Error verifying signature with signer " + approval.signer.ToString();
      return false;
    }
  }

  return true;
}

/// <summary>
/// returns the number of bytes resulting from the binary serialization of the
/// Deploy.
/// </summary>
int Deploy::GetDeploySizeInBytes() const {
  DeployByteSerializer serializer;
  return serializer.ToBytes(*this).size();
}

CBytes Deploy::ComputeBodyHash(ExecutableDeployItem payment,
                               ExecutableDeployItem session) {
  CBytes sb;
  // std::cout << "ComputeBodyHash" << std::endl;
  ExecutableDeployItemByteSerializer itemSerializer;

  sb += itemSerializer.ToBytes(payment);
  sb += itemSerializer.ToBytes(session);
  // std::cout << "ComputeBodyHash2" << std::endl;

  CryptoPP::BLAKE2b bcBl2bdigest(32u);
  bcBl2bdigest.Update(sb, sb.size());
  // std::cout << "ComputeBodyHash3" << std::endl;

  CBytes hash(bcBl2bdigest.DigestSize());
  bcBl2bdigest.Final(hash);
  // std::cout << "ComputeBodyHash4" << std::endl;

  return hash;
}

CBytes Deploy::ComputeHeaderHash(DeployHeader header) {
  DeployByteSerializer serializer;

  nlohmann::json j;
  to_json(j, header);
  // std::cout << "ComputeHeaderHash header: \n";
  // std::cout << j.dump(2) << std::endl;

  CBytes bHeader = serializer.ToBytes(header);

  CryptoPP::BLAKE2b bcBl2bdigest(32u);

  bcBl2bdigest.Update(bHeader, bHeader.size());

  CBytes hash(bcBl2bdigest.DigestSize());
  bcBl2bdigest.Final(hash);

  return hash;
}

/// Loads the deploy from the given json object.
Deploy Deploy::loadFromJson(const nlohmann::json& input_json) {
  // create a Deploy from the json
  Casper::Deploy ret;
  Casper::from_json(input_json, ret);

  // create a new json from the generated Deploy
  nlohmann::json generated_json;
  Casper::to_json(generated_json, ret);

  // compare the final parsed json with the initial json
  assert(generated_json.dump(2) == input_json.dump(2));

  // return the generated Deploy
  return ret;
}

/// Load a Deploy from a json file with the given path and return it.
Deploy Deploy::loadFromFile(const std::string& file_name) {
  // read the json file
  nlohmann::json input_json;
  try {
    std::ifstream ifs(file_name);
    input_json = nlohmann::json::parse(ifs);
  } catch (std::exception& e) {
    SPDLOG_ERROR("Error! Loading deploy file: {}", file_name);
  }

  // create a Deploy from the json
  return loadFromJson(input_json);
}

/// Writes the deploy to the given file.
void Deploy::save(const std::string& filePath, uint8_t indent) const {
  // create a json from the Deploy
  nlohmann::json output_json;
  Casper::to_json(output_json, *this);

  // write the json to the file
  std::ofstream ofs(filePath);
  ofs << output_json.dump(indent);
}

nlohmann::json Deploy::toJson() const {
  nlohmann::json output_json;
  Casper::to_json(output_json, *this);
  return output_json;
}

std::string Deploy::toString(uint8_t indent) const {
  return this->toJson().dump(indent);
}

}  // namespace Casper
