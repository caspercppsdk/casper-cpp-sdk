#include "Types/Deploy.h"

namespace Casper {

Deploy::Deploy(const DeployHeader& header_,
               const ExecutableDeployItem& payment_,
               const ExecutableDeployItem& session_) {
  CryptoPP::SecByteBlock body_hash = ComputeBodyHash(payment, session);

  this->header =
      DeployHeader(header_.account, header_.timestamp, header_.ttl,
                   header_.gas_price, CEP57Checksum::Encode(body_hash),
                   header_.dependencies, header_.chain_name);

  this->hash = CEP57Checksum::Encode(ComputeHeaderHash(this->header));
  this->payment = payment_;
  this->session = session_;
}

/// <summary>
/// Signs the deploy with a private key and adds a new Approval to it.
/// </summary>
void Deploy::Sign(KeyPair keyPair) {
  CryptoPP::SecByteBlock signature =
      keyPair.Sign(CryptoUtil::hexDecode(this->hash));

  this->approvals.emplace_back(
      keyPair.public_key,
      Signature::FromRawBytes(signature, keyPair.public_key.key_algorithm));
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
  CryptoPP::SecByteBlock computed_hash =
      ComputeBodyHash(this->payment, this->session);

  if (CryptoUtil::hexDecode(this->header.body_hash) != computed_hash) {
    message =
        "Computed Body Hash does not match value in deploy header. "
        "Expected: " +
        this->header.body_hash +
        "Computed: " + CEP57Checksum::Encode(computed_hash);
    return false;
  }

  computed_hash = ComputeHeaderHash(this->header);

  if (CryptoUtil::hexDecode(this->hash) != computed_hash) {
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
    if (!approval.signer.VerifySignature(CryptoUtil::hexDecode(this->hash),
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
  // TODO: Implement this !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

  // var serializer = new DeployByteSerializer();
  // return serializer.ToBytes(this).Length;
}

CryptoPP::SecByteBlock Deploy::ComputeBodyHash(ExecutableDeployItem payment,
                                               ExecutableDeployItem session) {
  /*
  var ms = new MemoryStream();
  var itemSerializer = new ExecutableDeployItemByteSerializer();

  ms.Write(itemSerializer.ToBytes(payment));
  ms.Write(itemSerializer.ToBytes(session));

  var bcBl2bdigest = new Org.BouncyCastle.Crypto.Digests.Blake2bDigest(256);
  var bBody = ms.ToArray();

  bcBl2bdigest.BlockUpdate(bBody, 0, bBody.Length);

  var hash = new byte[bcBl2bdigest.GetDigestSize()];
  bcBl2bdigest.DoFinal(hash, 0);

  return hash;
  */

  SecByteBlock hash;  // TODO : implement this !!!!!!!!!!!!!!!
  return hash;
}

CryptoPP::SecByteBlock Deploy::ComputeHeaderHash(DeployHeader header) {
  /*
var serializer = new DeployByteSerializer();
var bHeader = serializer.ToBytes(header);

var bcBl2bdigest = new Org.BouncyCastle.Crypto.Digests.Blake2bDigest(256);

bcBl2bdigest.BlockUpdate(bHeader, 0, bHeader.Length);

var hash = new byte[bcBl2bdigest.GetDigestSize()];
bcBl2bdigest.DoFinal(hash, 0);

return hash;
*/

  SecByteBlock hash;  // TODO : implement this !!!!!!!!!!!!!!!
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
    std::cout << "Error! Loading deploy file: " << file_name << std::endl;
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
