#include "CasperClient.h"
#include "Types/GlobalStateKey.cpp"
#include "Types/PublicKey.h"
#include "Utils/CryptoUtil.h"
#include <sstream>
#include "Types/CLType.h"
#include "Types/CLConverter.h"

#include "ByteSerializers/GlobalStateKeyByteSerializer.h"

#include "Types/CLValue.h"
#include "date/date.h"
#include "Types/ED25519Key.h"
#include "Types/Secp256k1Key.h"
#include <cryptopp/osrng.h>
#include <chrono>

// Tests
#include "RpcTest.hpp"
#include "CLValueByteSerializerTest.hpp"
#include "DeployItemByteSerializerTest.hpp"

// Test Library
#include "acutest.h"
#include <boost/variant/get.hpp>

using namespace Casper;
/*
/// Helper function to print a result object
template <typename T>
void printResult(const T& result, const std::string& rpc_call_name,
                 int indent = 2) {
  std::cout << "-----------------------------------------------" << std::endl;
  std::cout << rpc_call_name << std::endl;

  nlohmann::json resultJSON;
  nlohmann::to_json(resultJSON, result);

  std::cout << resultJSON.dump(indent) << std::endl;
}
*/
/// <summary>
/// Check the Casper lower-case convert function
/// </summary>
void stringUtil_toLowerTest() {
  std::string str = "Hello World";
  std::string str_lower = "hello world";
  TEST_ASSERT(str_lower == StringUtil::toLower(str));
}

/// <summary>
/// Check the public key to account hash convert function
/// </summary>
void publicKey_getAccountHashTest() {
  Casper::PublicKey publicKey = Casper::PublicKey::FromHexString(
      "01cd807fb41345d8dd5a61da7991e1468173acbee53920e4dfe0d28cb8825ac664");

  std::string lower_case_account_hash = publicKey.GetAccountHash();

  std::string expected_account_hash =
      "account-hash-"
      "998c5fd4e7b568bedd78e05555c83c61893dc5d8546ce0bec8b30e1c570f21aa";
  std::cout << "lower_case_account_hash: " << lower_case_account_hash
            << std::endl;
  TEST_ASSERT(iequals(lower_case_account_hash, expected_account_hash));
}

// to store list inside map map["List"]: list_inner_type
CLTypeRVA createContainerMap(std::string key, CLTypeRVA value) {
  std::map<std::string, CLTypeRVA> cl_map_type;
  cl_map_type[key] = value;

  CLTypeRVA rva = cl_map_type;

  return rva;
}

CLTypeRVA createOption(CLTypeRVA value) {
  return createContainerMap("Option", value);
}

CLTypeRVA createList(CLTypeRVA value) {
  return createContainerMap("List", value);
}

CLTypeRVA createMap(CLTypeRVA key, CLTypeRVA value) {
  std::map<CLTypeRVA, CLTypeRVA> cl_map_type;
  cl_map_type[key] = value;

  CLTypeRVA rva = cl_map_type;

  return rva;
}

CLTypeRVA createTuple1(CLTypeRVA value1) {
  std::vector<CLTypeRVA> cl_tuple1_type;
  cl_tuple1_type.push_back(value1);

  std::map<std::string, std::vector<CLTypeRVA>> cl_tuple_type;
  cl_tuple_type["Tuple1"] = cl_tuple1_type;
  CLTypeRVA rva = cl_tuple_type;

  return rva;
}

CLTypeRVA createTuple2(CLTypeRVA value1, CLTypeRVA value2) {
  std::vector<CLTypeRVA> cl_tuple2_type;
  cl_tuple2_type.push_back(value1);
  cl_tuple2_type.push_back(value2);

  std::map<std::string, std::vector<CLTypeRVA>> cl_tuple_type;
  cl_tuple_type["Tuple2"] = cl_tuple2_type;
  CLTypeRVA rva = cl_tuple_type;

  return rva;
}

CLTypeRVA createTuple3(CLTypeRVA value1, CLTypeRVA value2, CLTypeRVA value3) {
  std::vector<CLTypeRVA> cl_tuple3_type;
  cl_tuple3_type.push_back(value1);
  cl_tuple3_type.push_back(value2);
  cl_tuple3_type.push_back(value3);

  std::map<std::string, std::vector<CLTypeRVA>> cl_tuple_type;
  cl_tuple_type["Tuple3"] = cl_tuple3_type;
  CLTypeRVA rva = cl_tuple_type;

  return rva;
}

bool threeWayCompare(CLTypeRVA rva) {
  // create a json from the initial type object
  nlohmann::json obj_to_json;
  to_json(obj_to_json, rva);

  std::cout << "json: " << obj_to_json.dump() << std::endl;

  // create a new type object object from the generated json
  CLTypeRVA json_to_obj;
  from_json(obj_to_json, json_to_obj);

  // create a new json from the generated CLType object
  nlohmann::json final_json;
  to_json(final_json, json_to_obj);

  std::cout << "final json: " << final_json.dump() << std::endl;

  // compare the final parsed json with the initial json
  bool result = obj_to_json == final_json;
  return result;
}

/// map<String, List<PublicKey>>
void cltype_test() {
  // String
  auto key_type = CLTypeEnum::String;

  // List<PublicKey>
  auto value_type = createList(CLTypeEnum::PublicKey);

  // map<String, List<PublicKey>>
  auto map_type = createMap(key_type, value_type);

  // assert that the serialization-deserialization is correct
  TEST_ASSERT(threeWayCompare(map_type));
}

/// List<String>
void cltype_str_list_test() {
  // List<String>
  CLTypeRVA list_type = createList(CLTypeEnum::String);

  // assert that the serialization-deserialization is correct
  TEST_ASSERT(threeWayCompare(list_type));
}

// TODO:
void cltype_json_test() {
  nlohmann::json j_map;

  j_map["cl_type"] = {{"Map", {{"key", "String"}, {"value", "String"}}}};

  nlohmann::json j_str_list;
  j_str_list["cl_type"] = {{"List", "String"}};

  /*
    std::cout << std::endl;
    std::cout << j_map.dump(2) << std::endl;

    std::cout << std::endl;
    std::cout << j_str_list.dump(2) << std::endl;
    */
}

/// Option<Bool>
void clType_option_test() {
  // Option<Bool>
  CLTypeRVA opt_type = createOption(CLTypeEnum::Bool);

  // assert that the serialization-deserialization is correct
  TEST_ASSERT(threeWayCompare(opt_type));
}

/// Option<List<Map<U64, U8>>>
void clType_option_recursiveTest() {
  // Option<List<Map<U64, U8>>>
  CLTypeRVA opt_type =
      createOption(createList(createMap(CLTypeEnum::U64, CLTypeEnum::U8)));

  // assert that the serialization-deserialization is correct
  TEST_ASSERT(threeWayCompare(opt_type));
}

/// Tuple1<Bool>
void clType_tuple1_test() {
  CLTypeRVA tuple1_type = createTuple1(CLTypeEnum::Unit);

  TEST_ASSERT(threeWayCompare(tuple1_type));
}

/// Tuple2<Bool, I32>
void clType_tuple2_test() {
  auto elem1 = CLTypeEnum::Bool;
  auto elem2 = CLTypeEnum::I32;

  auto tuple2_type = createTuple2(elem1, elem2);

  TEST_ASSERT(threeWayCompare(tuple2_type));
}

/// Tuple2<U256, List<Any>>
void clType_tuple2_recursiveTest() {
  auto elem1 = CLTypeEnum::U256;
  auto elem2 = createList(CLTypeEnum::Any);

  auto tuple2_type = createTuple2(elem1, elem2);

  TEST_ASSERT(threeWayCompare(tuple2_type));
}

void clType_tuple3_test() {
  auto elem1 = CLTypeEnum::I32;
  auto elem2 = CLTypeEnum::String;
  auto elem3 = createOption(CLTypeEnum::U512);

  auto tuple3_type = createTuple3(elem1, elem2, elem3);

  TEST_ASSERT(threeWayCompare(tuple3_type));
}

void clTypeParsed_test() {
  std::string json_str = R"(
  {
    "bytes": "06da6662305f01",
    "parsed": "1508345276122",
    "cl_type": "U512"
  }
  )";

  nlohmann::json j = nlohmann::json::parse(json_str);
  std::cout << std::endl << j.dump(2) << std::endl;
  CLValue cl;
  from_json(j, cl);

  TEST_ASSERT(boost::get<CLTypeEnum>(cl.cl_type.type) == CLTypeEnum::U512);

  nlohmann::json j2;
  to_json(j2, cl);
  std::cout << std::endl << j2.dump(2) << std::endl;

  TEST_ASSERT(j2.dump() == j.dump());
}

/// test the serialization of a CLValue using a json file as input
void clValue_with_jsonFile(std::string file_name) {
  // read the json file
  nlohmann::json input_json;
  try {
    std::string file_path = __FILE__;
    std::string dir_path = file_path.substr(0, file_path.rfind("/"));
    std::cout << dir_path << std::endl;
    std::string file_path_name = dir_path + "/data/CLValue/" + file_name;
    std::ifstream ifs(file_path_name);
    input_json = nlohmann::json::parse(ifs);
  } catch (std::exception& e) {
    std::cout << "clValue_with_jsonFile: " << e.what() << std::endl;
  }

  std::cout << std::endl << input_json.dump(2) << std::endl;

  // create a CLValue from the json
  CLValue generated_obj;
  from_json(input_json, generated_obj);

  // create a new json from the generated CLValue
  nlohmann::json generated_json;
  to_json(generated_json, generated_obj);

  std::cout << std::endl << generated_json.dump(2) << std::endl;

  // compare the final parsed json with the initial json
  TEST_ASSERT(iequals(generated_json.dump(), input_json.dump()));
}
void clValue_with_boolTrueTest() { clValue_with_jsonFile("Bool-True.json"); }

void clValue_with_boolFalseTest() { clValue_with_jsonFile("Bool-False.json"); }

void clValue_with_I32Test() { clValue_with_jsonFile("I32.json"); }

void clValue_with_I64Test() { clValue_with_jsonFile("I64.json"); }

void clValue_with_U8Test() { clValue_with_jsonFile("U8.json"); }

void clValue_with_U32Test() { clValue_with_jsonFile("U32.json"); }

void clValue_with_U64Test() { clValue_with_jsonFile("U64.json"); }

void clValue_with_U128Test() { clValue_with_jsonFile("U128.json"); }

void clValue_with_U256Test() { clValue_with_jsonFile("U256.json"); }

void clValue_with_U256_2Test() { clValue_with_jsonFile("U256-2.json"); }

void clValue_with_U512Test() { clValue_with_jsonFile("U512.json"); }

void clValue_with_U512_0Test() { clValue_with_jsonFile("U512-0.json"); }

void clValue_with_UnitTest() { clValue_with_jsonFile("Unit.json"); }

void clValue_with_StringTest() { clValue_with_jsonFile("String.json"); }

void clValue_with_URefTest() { clValue_with_jsonFile("URef.json"); }

void clValue_with_KeyTest() { clValue_with_jsonFile("Key.json"); }

void clValue_with_PublicKeyTest() { clValue_with_jsonFile("PublicKey.json"); }

void clValue_with_OptionTest() { clValue_with_jsonFile("Option.json"); }

void clValue_with_OptionListKeyNULLTest() {
  clValue_with_jsonFile("OptionListKey-NULL.json");
}

void clValue_with_OptionU64NULLTest() {
  clValue_with_jsonFile("OptionU64-NULL.json");
}

void clValue_with_OptionU64Test() { clValue_with_jsonFile("OptionU64.json"); }

void clValue_with_ListTest() { clValue_with_jsonFile("List.json"); }

void clValue_with_ListByteArray32Test() {
  clValue_with_jsonFile("ListByteArray32.json");
}

void clValue_with_ListOptionStringTest() {
  clValue_with_jsonFile("ListOptionString.json");
}

void clValue_with_ListU8Test() { clValue_with_jsonFile("ListU8.json"); }

void clValue_with_ListU256Test() { clValue_with_jsonFile("ListU256.json"); }

void clValue_with_ByteArrayTest() { clValue_with_jsonFile("ByteArray.json"); }

void clValue_with_ResultOkTest() { clValue_with_jsonFile("ResultOk.json"); }

void clValue_with_ResultErrTest() { clValue_with_jsonFile("ResultErr.json"); }

void clValue_with_MapTest() { clValue_with_jsonFile("Map.json"); }

void clValue_with_Tuple1Test() { clValue_with_jsonFile("Tuple1.json"); }

void clValue_with_Tuple2Test() { clValue_with_jsonFile("Tuple2.json"); }

void clValue_with_Tuple3Test() { clValue_with_jsonFile("Tuple3.json"); }

void clValue_with_AnyTest() { clValue_with_jsonFile("Any.json"); }

template <typename T>
void globalStateKey_serialize(T key, std::string& expected_bytes_str) {
  GlobalStateKeyByteSerializer gsk_serializer;

  CBytes key_bytes = gsk_serializer.ToBytes(key);

  std::string bytes_str = CEP57Checksum::Encode(key_bytes);

  std::cout << std::endl << "key_bytes: " << key_bytes.size() << std::endl;
  std::cout << bytes_str << std::endl;

  TEST_ASSERT(iequals(expected_bytes_str, bytes_str));
}

void globalStateKey_serializer_test() {
  /// ACCOUNT HASH TEST
  AccountHashKey acc_key(
      "account-hash-"
      "1b2d1d9069d21f916ab58be305c816b8f5258177d9cf29eee33728c4e934f094");

  std::string expected_acc_bytes_str =
      "001b2d1d9069d21f916ab58be305c816b8f5258177d9cf29eee33728c4e934f094";

  globalStateKey_serialize<AccountHashKey>(acc_key, expected_acc_bytes_str);

  // HASH TEST
  HashKey hash_key(
      "hash-"
      "96053169b397360449b4de964200be449594ca93f252153f0a679b804e214a54");

  std::string expected_hash_bytes_str =
      "0196053169b397360449b4de964200be449594ca93f252153f0a679b804e214a54";

  globalStateKey_serialize<HashKey>(hash_key, expected_hash_bytes_str);

  /// UREF TEST
  URef uref_key(
      "uref-e48935c79e96c490c01e1e8800de5ec5f4a857a57db0dcffed1e1e2b5d29b5e4-"
      "007");

  std::string expected_uref_bytes_str =
      "02e48935c79e96c490c01e1e8800de5ec5f4a857a57db0dcffed1e1e2b5d29b5e407";

  globalStateKey_serialize<URef>(uref_key, expected_uref_bytes_str);

  // ERA INFO TEST
  EraInfoKey era_info_key("era-2685");

  std::string expected_era_bytes_str = "057d0a000000000000";
  // TODO:
  // globalStateKey_serialize<EraInfoKey>(era_info_key,
  // expected_era_bytes_str);
}

// Executable Deploy Item Byte Serializer Tests //

void publicKey_load_fromFileTest() {
  std::cout << "\n";
  /// Create a Private Key from pem file
  // CryptoPP::AutoSeededRandomPool prng;

  Casper::Secp256k1Key secp256k1Key(privKeyPemFile);
  std::cout << "private key: " << secp256k1Key.getPrivateKeyStr() << std::endl;
  std::cout << "public key: " << secp256k1Key.getPublicKeyStr() << std::endl;

  std::string message = "Do or do not. There is no try.";
  std::string signature = secp256k1Key.sign(message);
  std::cout << "signature: "
            << Casper::Secp256k1Key::signatureToString(signature) << std::endl;
  // verify
  bool is_valid = secp256k1Key.verify(message, signature);
  std::cout << "Verification: " << std::boolalpha << is_valid << std::endl;
}

void ed25KeyTest() {
  std::cout << "\n";
  
  Ed25519Key ed_key(privKeyPemFile);
  std::cout << "ed_key.getPrivateKeyStr(): " << ed_key.getPrivateKeyStr()
            << std::endl;
  std::cout << "ed_key.getPublicKeyStr(): " << ed_key.getPublicKeyStr()
            << std::endl;

  std::string message =
      "e0a081fbf1ea9c716852df2bbfbfb1daecb9719f67c63c64cc49267d8038ebcf";
  std::string signature = ed_key.sign(message);

  std::cout << "in test verify: " << std::boolalpha
            << ed_key.verify(message, signature) << std::endl;
}

#define RPC_TEST 1
#define SER_DE_TEST 0
#define CL_TYPE_TEST 1
#define CL_VALUE_TEST 1
#define DEPLOY_ITEM_BYTE_SERIALIZER_TEST 1
#define CL_VALUE_BYTE_SERIALIZER_TEST 1
TEST_LIST = {

#if CL_VALUE_BYTE_SERIALIZER_TEST == 1
    {"CLValue_ByteSer_Bool_Test", CLValue_ByteSer_Bool_Test},
    {"CLValue_ByteSer_I32_Test", CLValue_ByteSer_I32_Test},
    {"CLValue_ByteSer_I64_Test", CLValue_ByteSer_I64_Test},
    {"CLValue_ByteSer_U8_Test", CLValue_ByteSer_U8_Test},
    {"CLValue_ByteSer_U32_Test", CLValue_ByteSer_U32_Test},
    {"CLValue_ByteSer_U64_Test", CLValue_ByteSer_U64_Test},
    {"CLValue_ByteSer_U128_Test", CLValue_ByteSer_U128_Test},
    {"CLValue_ByteSer_U256_Test", CLValue_ByteSer_U256_Test},
    {"CLValue_ByteSer_U512_Test", CLValue_ByteSer_U512_Test},
    {"CLValue_ByteSer_Unit_Test", CLValue_ByteSer_Unit_Test},
    {"CLValue_ByteSer_String_Test", CLValue_ByteSer_String_Test},
    {"CLValue_ByteSer_URef_Test", CLValue_ByteSer_URef_Test},
    {"CLValue_ByteSer_Key_Test", CLValue_ByteSer_Key_Test},
    {"CLValue_ByteSer_PublicKey_Test", CLValue_ByteSer_PublicKey_Test},
    {"CLValue_ByteSer_List_Test", CLValue_ByteSer_List_Test},
    {"CLValue_ByteSer_ByteArray_Test", CLValue_ByteSer_ByteArray_Test},
    {"CLValue_ByteSer_Result_Test", CLValue_ByteSer_Result_Test},
    {"CLValue_ByteSer_Map_Test", CLValue_ByteSer_Map_Test},
    {"CLValue_ByteSer_Tuple1_Test", CLValue_ByteSer_Tuple1_Test},
    {"CLValue_ByteSer_Tuple2_Test", CLValue_ByteSer_Tuple2_Test},
    {"CLValue_ByteSer_Tuple3_Test", CLValue_ByteSer_Tuple3_Test},
    {"CLValue_ByteSer_Any_Test", CLValue_ByteSer_Any_Test},
#endif

#if DEPLOY_ITEM_BYTE_SERIALIZER_TEST == 1
    {"ModuleBytes serialize", DeployItem_ByteSer_ModuleBytes_Test},
    {"StoredContractByHashSerialization",
     DeployItem_ByteSer_StoredContractByHash_Test},
    {"StoredContractByNameSerialization",
     DeployItem_ByteSer_StoredContractByName_Test},
    {"StoredVersionedContractByHashSerialization",
     DeployItem_ByteSer_StoredVersionedContractByHash_Test},
    {"StoredVersionedContractByNameSerialization",
     DeployItem_ByteSer_StoredVersionedContractByName_Test},
    {"TransferDeployItemSerialization", DeployItem_ByteSer_Transfer_Test},
#endif

    {"ED25519 Key Test", ed25KeyTest},
    {"PublicKey Load fromFile", publicKey_load_fromFileTest},
    {"getAccountHash checks internal PublicKey to AccountHash converter",
     publicKey_getAccountHashTest},
    {"toLower checks internal lower case converter", stringUtil_toLowerTest},
    {"gsk test", globalStateKey_serializer_test},

#if RPC_TEST == 1
    {"infoGetPeers checks node list size", infoGetPeers_Test},
    {"chainGetStateRootHash using Block height parameter",
     chainGetStateRootHash_with_blockHeightTest},
    {"chainGetStateRootHash using invalid Block height parameter",
     chainGetStateRootHash_with_invalidBlockHeightTest},
    {"chainGetStateRootHash using Block hash parameter",
     chainGetStateRootHash_with_blockHashTest},
    {"chainGetStateRootHash using empty Block hash parameter ",
     chainGetStateRootHash_with_emptyParameterTest},
    {"infoGetDeploy using Deploy hash parameter",
     infoGetDeploy_with_deployHashTest},
    {"infoGetDeploy using invalid Deploy hash parameter",
     infoGetDeploy_with_invalidDeployHashTest},
    {"infoGetStatus compares with a reference value",
     infoGetStatus_with_emptyParameterTest},
    {"chainGetBlockTransfers using Block hash parameter",
     chainGetBlockTransfers_with_blockHashTest},
    {"chainGetBlock using Block hash parameter",
     chainGetBlock_with_blockHashTest},
    {"chainGetEraInfoBySwitchBlock using Block hash parameter ",
     chainGetEraInfoBySwitchBlock_with_blockHashTest},
    {"stateGetItem using state root hash and key parameters ",
     stateGetItem_with_keyTest},
    {"stateGetItem using invalid state root hash and key parameters ",
     stateGetItem_with_invalidKeyTest},
    {"stateGetDictionaryItem using state root hash and dictionary key "
     " parameters ",
     stateGetDictionaryItem_with_keyTest},
    {"stateGetBalance compares with a reference value",
     stateGetBalance_with_urefTest},
    {"stateGetBalance using invalid URef and state root hash parameters ",
     stateGetBalance_with_invalidUrefTest},
    {"stateGetAuctionInfo using Block hash parameter (may take a while)",
     stateGetAuctionInfo_with_blockHashTest},
    {"PutDeploy RPC Call with a Stored Contract by Name",
     PutDeploy_StoredContractByName_Test},
    {"PutDeploy RPC Call with a Transfer", PutDeploy_Transfer_Test},
    {"PutDeploy RPC Call with a Stored Contract by Hash",
     PutDeploy_StoredContractByHash_Test},
#endif

#if SER_DE_TEST == 1
    {"Serialize - Bool", serializeBoolTest},
    {"Serialize - I32", serializeI32Test},
    {"Serialize - I64", serializeI64Test},
    {"Serialize - String", serializeStringTest},
    {"Serialize - U8", serializeU8Test},
    {"Serialize - U32", serializeU32Test},
    {"Serialize - U64", serializeU64Test},
    {"Serialize - U128", serializeU128Test},
    {"Serialize - U256", serializeU256Test},
    {"Serialize - U512", serializeU512Test},
    {"Serialize - ByteArray", serializeByteArrayTest},
    {"Serialize - Key", serializeKeyTest},
    {"Serialize - PublicKey", serializePublicKeyTest},
#endif

#if CL_TYPE_TEST == 1

    {"CLType", cltype_test},
    {"CLType json", cltype_json_test},
    {"CLType List<String>", cltype_str_list_test},
    {"CLValue parsed", clTypeParsed_test},

    {"CLType Tuple1", clType_tuple1_test},
    {"CLType Tuple2", clType_tuple2_test},
    {"CLType Tuple2 recursive", clType_tuple2_recursiveTest},
    {"CLType Tuple3", clType_tuple3_test},
    {"CLType Option", clType_option_test},
    {"CLType Option recursive", clType_option_recursiveTest},
#endif

#if CL_VALUE_TEST == 1
    {"CLValue using Bool expected false", clValue_with_boolFalseTest},
    {"CLValue using Bool expected true", clValue_with_boolTrueTest},
    {"CLValue using I32", clValue_with_I32Test},
    {"CLValue using I64", clValue_with_I64Test},
    {"CLValue using U8", clValue_with_U8Test},
    {"CLValue using U32", clValue_with_U32Test},
    {"CLValue using U64", clValue_with_U64Test},
    {"CLValue using U128", clValue_with_U128Test},
    {"CLValue using U256", clValue_with_U256Test},
    {"CLValue using U256-2", clValue_with_U256_2Test},
    {"CLValue using U512", clValue_with_U512Test},
    {"CLValue using U512-0", clValue_with_U512_0Test},
    {"CLValue using Unit", clValue_with_UnitTest},
    {"CLValue using String", clValue_with_StringTest},
    {"CLValue using URef", clValue_with_URefTest},
    {"CLValue using Key", clValue_with_KeyTest},
    //   {"CLValue using Account Key", clValue_with_accountKeyTest},
    //  {"CLValue using Hash Key", clValue_with_hashKeyTest},
    {"CLValue using PublicKey", clValue_with_PublicKeyTest},
    {"CLValue using Option", clValue_with_OptionTest},
    {"CLValue using Option<List<Key>> = NULL",
     clValue_with_OptionListKeyNULLTest},
    {"CLValue using Option<U64> = NULL", clValue_with_OptionU64NULLTest},
    {"CLValue using Option<U64>", clValue_with_OptionU64Test},
    {"CLValue using List", clValue_with_ListTest},
    {"CLValue using List<ByteArray:32>", clValue_with_ListByteArray32Test},
    {"CLValue using List<Option<String>>", clValue_with_ListOptionStringTest},
    {"CLValue using List<U8>", clValue_with_ListU8Test},
    {"CLValue using List<U256>", clValue_with_ListU256Test},
    {"CLValue using ByteArray", clValue_with_ByteArrayTest},
    //{"CLValue using ResultOk", clValue_with_ResultOkTest},
    //{"CLValue using ResultErr", clValue_with_ResultErrTest},
    {"CLValue using Map", clValue_with_MapTest},
    {"CLValue using Tuple1", clValue_with_Tuple1Test},
    {"CLValue using Tuple2", clValue_with_Tuple2Test},
    {"CLValue using Tuple3", clValue_with_Tuple3Test},
    {"CLValue using Any", clValue_with_AnyTest},

#endif

    {NULL, NULL}};
