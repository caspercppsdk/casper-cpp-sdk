#include "TestBase.hpp"

#include <cryptopp/osrng.h>

#include <chrono>

#include "ByteSerializers/GlobalStateKeyByteSerializer.h"
#include "TempFileHandler.hpp"
#include "Types/CLValue.h"
#include "Types/ED25519Key.h"
#include "Types/Secp256k1Key.h"
#include "data/TestSourceSecretKey.hpp"
#include "date/date.h"

#include <boost/variant/get.hpp>

namespace Casper
{
class ClientTests : public ::testing::Test
{
protected:
    // to store list inside map map["List"]: list_inner_type
    CLTypeRVA createContainerMap(std::string key, CLTypeRVA value)
    {
        std::map<std::string, CLTypeRVA> cl_map_type;
        cl_map_type[key] = value;
        CLTypeRVA rva = cl_map_type;
        return rva;
    }

    CLTypeRVA createOption(CLTypeRVA value)
    {
        return createContainerMap("Option", value);
    }

    CLTypeRVA createList(CLTypeRVA value)
    {
        return createContainerMap("List", value);
    }

    CLTypeRVA createMap(CLTypeRVA key, CLTypeRVA value)
    {
        std::map<CLTypeRVA, CLTypeRVA> cl_map_type;
        cl_map_type[key] = value;
        CLTypeRVA rva = cl_map_type;
        return rva;
    }

    CLTypeRVA createTuple1(CLTypeRVA value1)
    {
        std::vector<CLTypeRVA> cl_tuple1_type;
        cl_tuple1_type.push_back(value1);

        std::map<std::string, std::vector<CLTypeRVA>> cl_tuple_type;
        cl_tuple_type["Tuple1"] = cl_tuple1_type;
        CLTypeRVA rva = cl_tuple_type;

        return rva;
    }

    CLTypeRVA createTuple2(CLTypeRVA value1, CLTypeRVA value2)
    {
        std::vector<CLTypeRVA> cl_tuple2_type;
        cl_tuple2_type.push_back(value1);
        cl_tuple2_type.push_back(value2);

        std::map<std::string, std::vector<CLTypeRVA>> cl_tuple_type;
        cl_tuple_type["Tuple2"] = cl_tuple2_type;
        CLTypeRVA rva = cl_tuple_type;

        return rva;
    }

    CLTypeRVA createTuple3(CLTypeRVA value1, CLTypeRVA value2, CLTypeRVA value3)
    {
        std::vector<CLTypeRVA> cl_tuple3_type;
        cl_tuple3_type.push_back(value1);
        cl_tuple3_type.push_back(value2);
        cl_tuple3_type.push_back(value3);

        std::map<std::string, std::vector<CLTypeRVA>> cl_tuple_type;
        cl_tuple_type["Tuple3"] = cl_tuple3_type;
        CLTypeRVA rva = cl_tuple_type;

        return rva;
    }

    void threeWayCompare(CLTypeRVA rva)
    {
        // create a json from the initial type object
        nlohmann::json obj_to_json;
        to_json(obj_to_json, rva);

        // create a new type object object from the generated json
        CLTypeRVA json_to_obj;
        from_json(obj_to_json, json_to_obj);

        // create a new json from the generated CLType object
        nlohmann::json final_json;
        to_json(final_json, json_to_obj);

        // compare the final parsed json with the initial json
        EXPECT_EQ(obj_to_json, final_json);
    }

    bool compareString(const std::string& str1, const std::string& str2)
    {
        bool areEqual = StringUtil::toLower(str1) == StringUtil::toLower(str2);
        EXPECT_TRUE(areEqual);
        return areEqual;
    }

    /// test the serialization of a CLValue using a json file as input
    void clValue_with_jsonFile(std::string file_name)
    {
        // read the json file
        nlohmann::json input_json;
        try
            {
                std::string file_path = __FILE__;
                std::string dir_path = file_path.substr(0, file_path.rfind("/"));
                // std::cout << dir_path << std::endl;
                std::string file_path_name = dir_path + "/data/CLValue/" + file_name;
                std::ifstream ifs(file_path_name);
                input_json = nlohmann::json::parse(ifs);
        } catch (std::exception& e)
            {
                std::cout << "clValue_with_jsonFile: " << e.what() << std::endl;
        }

        // create a CLValue from the json
        CLValue generated_obj;
        from_json(input_json, generated_obj);

        // create a new json from the generated CLValue
        nlohmann::json generated_json;
        to_json(generated_json, generated_obj);

        // compare the final parsed json with the initial json
        compareString(generated_json.dump(), input_json.dump());
    }

    template <typename T>
    void globalStateKey_serialize(T key, std::string& expected_bytes_str)
    {
        GlobalStateKeyByteSerializer gsk_serializer;

        CBytes key_bytes = gsk_serializer.ToBytes(key);

        std::string bytes_str = CEP57Checksum::Encode(key_bytes);

        std::cout << std::endl << "key_bytes: " << key_bytes.size() << std::endl;
        std::cout << bytes_str << std::endl;

        compareString(expected_bytes_str, bytes_str);
    }
};
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
TEST_F(ClientTests, StringUtil_toLowert)
{
    EXPECT_EQ("hello world", StringUtil::toLower("Hello World"));
}

/// <summary>
/// Check the public key to account hash convert function
/// </summary>
TEST_F(ClientTests, publicKey_getAccountHash)
{
    Casper::PublicKey publicKey =
        Casper::PublicKey::FromHexString("01cd807fb41345d8dd5a61da7991e1468173acbee53920e4dfe0d28cb8825ac664");
    std::string accountHash = publicKey.GetAccountHash();
    std::string expectedAccountHash = "account-hash-"
                                      "998c5fd4e7b568bedd78e05555c83c61893dc5d8546ce0bec8b30e1c570f21aa";
    compareString(accountHash, expectedAccountHash);
}

/// map<String, List<PublicKey>>
TEST_F(ClientTests, CLType_Map_String_List_PublicKey)
{
    // String
    auto key_type = CLTypeEnum::String;

    // List<PublicKey>
    auto value_type = createList(CLTypeEnum::PublicKey);

    // map<String, List<PublicKey>>
    auto map_type = createMap(key_type, value_type);

    // assert that the serialization-deserialization is correct
    threeWayCompare(map_type);
}

/// List<String>
TEST_F(ClientTests, CLType_List_String)
{
    // List<String>
    CLTypeRVA list_type = createList(CLTypeEnum::String);

    // assert that the serialization-deserialization is correct
    threeWayCompare(list_type);
}

// TODO: Implement this test
void cltype_json_test()
{
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
TEST_F(ClientTests, CLType_Option_Bool)
{
    // Option<Bool>
    CLTypeRVA opt_type = createOption(CLTypeEnum::Bool);

    // assert that the serialization-deserialization is correct
    threeWayCompare(opt_type);
}

/// Option<List<Map<U64, U8>>>
TEST_F(ClientTests, CLType_Option_List_Map_U64_U8)
{
    // Option<List<Map<U64, U8>>>
    CLTypeRVA opt_type = createOption(createList(createMap(CLTypeEnum::U64, CLTypeEnum::U8)));

    // assert that the serialization-deserialization is correct
    threeWayCompare(opt_type);
}

/// Tuple1<Bool>
TEST_F(ClientTests, CLType_Tuple1_Bool)
{
    CLTypeRVA tuple1_type = createTuple1(CLTypeEnum::Unit);

    threeWayCompare(tuple1_type);
}

/// Tuple2<Bool, I32>
TEST_F(ClientTests, CLType_Tuple2_Bool_I32)
{
    auto elem1 = CLTypeEnum::Bool;
    auto elem2 = CLTypeEnum::I32;

    auto tuple2_type = createTuple2(elem1, elem2);

    threeWayCompare(tuple2_type);
}

/// Tuple2<U256, List<Any>>
TEST_F(ClientTests, CLType_Tuple2_U256_List_Any)
{
    auto elem1 = CLTypeEnum::U256;
    auto elem2 = createList(CLTypeEnum::Any);

    auto tuple2_type = createTuple2(elem1, elem2);

    threeWayCompare(tuple2_type);
}

TEST_F(ClientTests, CLType_Tuple3_I32_String_Option_U512)
{
    auto elem1 = CLTypeEnum::I32;
    auto elem2 = CLTypeEnum::String;
    auto elem3 = createOption(CLTypeEnum::U512);

    auto tuple3_type = createTuple3(elem1, elem2, elem3);

    threeWayCompare(tuple3_type);
}

TEST_F(ClientTests, CLType_JsonParse)
{
    std::string json_str = R"(
  {
    "bytes": "06da6662305f01",
    "parsed": "1508345276122",
    "cl_type": "U512"
  }
  )";

    nlohmann::json j = nlohmann::json::parse(json_str);
    CLValue cl;
    from_json(j, cl);

    EXPECT_EQ(boost::get<CLTypeEnum>(cl.cl_type.type), CLTypeEnum::U512);

    nlohmann::json j2;
    to_json(j2, cl);

    EXPECT_EQ(j2.dump(), j.dump());
}

TEST_F(ClientTests, CLValue_withJSON_BoolTrue)
{
    clValue_with_jsonFile("Bool-True.json");
}

TEST_F(ClientTests, CLValue_withJSON_BoolFalse)
{
    clValue_with_jsonFile("Bool-False.json");
}

TEST_F(ClientTests, CLValue_withJSON_I32)
{
    clValue_with_jsonFile("I32.json");
}

TEST_F(ClientTests, CLValue_withJSON_I64)
{
    clValue_with_jsonFile("I64.json");
}

TEST_F(ClientTests, CLValue_withJSON_U8)
{
    clValue_with_jsonFile("U8.json");
}

TEST_F(ClientTests, CLValue_withJSON_U32)
{
    clValue_with_jsonFile("U32.json");
}

TEST_F(ClientTests, CLValue_withJSON_U64)
{
    clValue_with_jsonFile("U64.json");
}

TEST_F(ClientTests, CLValue_withJSON_U128)
{
    clValue_with_jsonFile("U128.json");
}

TEST_F(ClientTests, CLValue_withJSON_U256)
{
    clValue_with_jsonFile("U256.json");
}

TEST_F(ClientTests, CLValue_withJSON_U256_2)
{
    clValue_with_jsonFile("U256-2.json");
}

TEST_F(ClientTests, CLValue_withJSON_U512)
{
    clValue_with_jsonFile("U512.json");
}

TEST_F(ClientTests, CLValue_withJSON_U512_0)
{
    clValue_with_jsonFile("U512-0.json");
}

TEST_F(ClientTests, CLValue_withJSON_Unit)
{
    clValue_with_jsonFile("Unit.json");
}

TEST_F(ClientTests, CLValue_withJSON_String)
{
    clValue_with_jsonFile("String.json");
}

TEST_F(ClientTests, CLValue_withJSON_URef)
{
    clValue_with_jsonFile("URef.json");
}

TEST_F(ClientTests, CLValue_withJSON_Key)
{
    clValue_with_jsonFile("Key.json");
}

TEST_F(ClientTests, CLValue_withJSON_PublicKey)
{
    clValue_with_jsonFile("PublicKey.json");
}

TEST_F(ClientTests, CLValue_withJSON_Option)
{
    clValue_with_jsonFile("Option.json");
}

TEST_F(ClientTests, CLValue_withJSON_OptionListKeyNULL)
{
    clValue_with_jsonFile("OptionListKey-NULL.json");
}

TEST_F(ClientTests, CLValue_withJSON_OptionU64NULL)
{
    clValue_with_jsonFile("OptionU64-NULL.json");
}

TEST_F(ClientTests, CLValue_withJSON_OptionU64)
{
    clValue_with_jsonFile("OptionU64.json");
}

TEST_F(ClientTests, CLValue_withJSON_List)
{
    clValue_with_jsonFile("List.json");
}

TEST_F(ClientTests, CLValue_withJSON_ListByteArray32)
{
    clValue_with_jsonFile("ListByteArray32.json");
}

TEST_F(ClientTests, CLValue_withJSON_ListOptionString)
{
    clValue_with_jsonFile("ListOptionString.json");
}

TEST_F(ClientTests, CLValue_withJSON_ListU8)
{
    clValue_with_jsonFile("ListU8.json");
}

TEST_F(ClientTests, CLValue_withJSON_ListU256)
{
    clValue_with_jsonFile("ListU256.json");
}

TEST_F(ClientTests, CLValue_withJSON_ByteArray)
{
    clValue_with_jsonFile("ByteArray.json");
}

// TODO: fix this test
// TEST_F(ClientTests, CLValue_withJSON_ResultOk)
// {
//     clValue_with_jsonFile("ResultOk.json");
// }

// TODO: fix this test
// TEST_F(ClientTests, CLValue_withJSON_ResultErr)
// {
//     clValue_with_jsonFile("ResultErr.json");
// }

TEST_F(ClientTests, CLValue_withJSON_Map)
{
    clValue_with_jsonFile("Map.json");
}

TEST_F(ClientTests, CLValue_withJSON_Tuple1)
{
    clValue_with_jsonFile("Tuple1.json");
}

TEST_F(ClientTests, CLValue_withJSON_Tuple2)
{
    clValue_with_jsonFile("Tuple2.json");
}

TEST_F(ClientTests, CLValue_withJSON_Tuple3)
{
    clValue_with_jsonFile("Tuple3.json");
}

TEST_F(ClientTests, CLValue_withJSON_Any)
{
    clValue_with_jsonFile("Any.json");
}

// void globalStateKey_serializer_test()
// {
//     /// ACCOUNT HASH TEST
//     AccountHashKey acc_key("account-hash-"
//                            "1b2d1d9069d21f916ab58be305c816b8f5258177d9cf29eee33728c4e934f094");

//     std::string expected_acc_bytes_str = "001b2d1d9069d21f916ab58be305c816b8f5258177d9cf29eee33728c4e934f094";

//     globalStateKey_serialize<AccountHashKey>(acc_key, expected_acc_bytes_str);

//     // HASH TEST
//     HashKey hash_key("hash-"
//                      "96053169b397360449b4de964200be449594ca93f252153f0a679b804e214a54");

//     std::string expected_hash_bytes_str = "0196053169b397360449b4de964200be449594ca93f252153f0a679b804e214a54";

//     globalStateKey_serialize<HashKey>(hash_key, expected_hash_bytes_str);

//     /// UREF TEST
//     URef uref_key("uref-e48935c79e96c490c01e1e8800de5ec5f4a857a57db0dcffed1e1e2b5d29b5e4-"
//                   "007");

//     std::string expected_uref_bytes_str = "02e48935c79e96c490c01e1e8800de5ec5f4a857a57db0dcffed1e1e2b5d29b5e407";

//     globalStateKey_serialize<URef>(uref_key, expected_uref_bytes_str);

//     // ERA INFO TEST
//     EraInfoKey era_info_key("era-2685");

//     std::string expected_era_bytes_str = "057d0a000000000000";
//     // TODO:
//     // globalStateKey_serialize<EraInfoKey>(era_info_key,
//     // expected_era_bytes_str);
// }

// // Executable Deploy Item Byte Serializer Tests //

// void publicKey_load_fromFileTest()
// {
//     std::cout << "\n";
//     /// Create a Private Key from pem file
//     // CryptoPP::AutoSeededRandomPool prng;

//     TempFileHandler fileHandler{sourceSecretKey, "sourceSecretKey"};

//     Casper::Secp256k1Key secp256k1Key(fileHandler.getPath());
//     std::cout << "private key: " << secp256k1Key.getPrivateKeyStr() << std::endl;
//     std::cout << "public key: " << secp256k1Key.getPublicKeyStr() << std::endl;

//     std::string message = "Do or do not. There is no try.";
//     std::string signature = secp256k1Key.sign(message);
//     std::cout << "signature: " << Casper::Secp256k1Key::signatureToString(signature) << std::endl;
//     // verify
//     bool is_valid = secp256k1Key.verify(message, signature);
//     std::cout << "Verification: " << std::boolalpha << is_valid << std::endl;
// }

// void ed25KeyTest()
// {
//     std::cout << "\n";
//     TempFileHandler fileHandler{sourceSecretKey, "sourceSecretKey"};

//     Ed25519Key ed_key(fileHandler.getPath());
//     std::cout << "ed_key.getPrivateKeyStr(): " << ed_key.getPrivateKeyStr() << std::endl;
//     std::cout << "ed_key.getPublicKeyStr(): " << ed_key.getPublicKeyStr() << std::endl;

//     std::string message = "e0a081fbf1ea9c716852df2bbfbfb1daecb9719f67c63c64cc49267d8038ebcf";
//     std::string signature = ed_key.sign(message);

//     std::cout << "in test verify: " << std::boolalpha << ed_key.verify(message, signature) << std::endl;
// }

} // namespace Casper