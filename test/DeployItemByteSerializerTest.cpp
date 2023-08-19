#define TEST_NO_MAIN 1
#include "CLValueByteSerializerTest.hpp"
#include "acutest.h"

namespace Casper
{

/// ModuleBytes Deploy Item Byte Serialization
void DeployItem_ByteSer_ModuleBytes_Test()
{
    ExecutableDeployItemByteSerializer ser;
    uint512_t amount = u512FromDec("1000");
    ModuleBytes module_bytes(amount);

    TEST_ASSERT(module_bytes.module_bytes.size() == 0);
    TEST_ASSERT(module_bytes.args.size() == 1);

    std::string expected_module_bytes_str = "00000000000100000006000000616d6f756e740300000002e80308";
    std::string actual_module_bytes_str = hexEncode(ser.ToBytes(module_bytes));
    std::cout << "module bytes: " << actual_module_bytes_str << std::endl;
    TEST_ASSERT(expected_module_bytes_str == actual_module_bytes_str);
}

/// StoredContractByHash Deploy Item Byte Serialization
void DeployItem_ByteSer_StoredContractByHash_Test()
{
    ExecutableDeployItemByteSerializer ser;
    Casper::HashKey hash_key("hash-0102030401020304010203040102030401020304010203040102030401020304");
    StoredContractByHash stored_contract_by_hash(hash_key.ToHexString(), "counter_inc");
    TEST_ASSERT(stored_contract_by_hash.hash == CEP57Checksum::Encode(hash_key.raw_bytes));
    TEST_ASSERT(stored_contract_by_hash.entry_point == "counter_inc");
    TEST_ASSERT(stored_contract_by_hash.args.size() == 0);

    std::string expected_stored_contract_by_hash_str =
        "0101020304010203040102030401020304010203040102030401020304010203040b0000"
        "00636f756e7465725f696e6300000000";

    std::string actual_stored_contract_by_hash_str = hexEncode(ser.ToBytes(stored_contract_by_hash));

    std::cout << "stored contract by hash: " << actual_stored_contract_by_hash_str << std::endl;

    TEST_ASSERT(expected_stored_contract_by_hash_str == actual_stored_contract_by_hash_str);
}

/// StoredContractByName Deploy Item Byte Serialization
void DeployItem_ByteSer_StoredContractByName_Test()
{
    ExecutableDeployItemByteSerializer ser;

    StoredContractByName stored_contract_by_name("counter", "counter_inc");

    TEST_ASSERT(stored_contract_by_name.name == "counter");
    TEST_ASSERT(stored_contract_by_name.entry_point == "counter_inc");
    TEST_ASSERT(stored_contract_by_name.args.size() == 0);

    std::string expected_stored_contract_by_name_str = "0207000000636f756e7465720b000000636f756e7465725f696e6300000000";

    std::string actual_stored_contract_by_name_str = hexEncode(ser.ToBytes(stored_contract_by_name));

    std::cout << "stored contract by name: " << actual_stored_contract_by_name_str << std::endl;

    TEST_ASSERT(expected_stored_contract_by_name_str == actual_stored_contract_by_name_str);
}

/// StoredVersionedContractByHash Deploy Item Byte Serialization
void DeployItem_ByteSer_StoredVersionedContractByHash_Test()
{
    ExecutableDeployItemByteSerializer ser;
    Casper::HashKey hash_key("hash-0102030401020304010203040102030401020304010203040102030401020304");
    StoredVersionedContractByHash stored_versioned_contract_by_hash(hash_key.ToHexString(), 1, "counter_inc");
    TEST_ASSERT(stored_versioned_contract_by_hash.hash == CEP57Checksum::Encode(hash_key.raw_bytes));
    TEST_ASSERT(stored_versioned_contract_by_hash.version == 1);
    TEST_ASSERT(stored_versioned_contract_by_hash.entry_point == "counter_inc");
    TEST_ASSERT(stored_versioned_contract_by_hash.args.size() == 0);

    std::string expected_stored_versioned_contract_by_hash_str =
        "030102030401020304010203040102030401020304010203040102030401020304010100"
        "00000b000000636f756e7465725f696e6300000000";

    std::string actual_stored_versioned_contract_by_hash_str =
        hexEncode(ser.ToBytes(stored_versioned_contract_by_hash));

    std::cout << "stored versioned contract by hash: " << actual_stored_versioned_contract_by_hash_str << std::endl;

    TEST_ASSERT(expected_stored_versioned_contract_by_hash_str == actual_stored_versioned_contract_by_hash_str);
}

/// StoredVersionedContractByName Deploy Item Byte Serialization
void DeployItem_ByteSer_StoredVersionedContractByName_Test()
{
    ExecutableDeployItemByteSerializer ser;
    Casper::StoredVersionedContractByName stored_v_contract("counter", 15, "counter_inc");
    TEST_ASSERT(stored_v_contract.name == "counter");
    TEST_ASSERT(stored_v_contract.version == 15);
    TEST_ASSERT(stored_v_contract.entry_point == "counter_inc");

    TEST_ASSERT(stored_v_contract.args.size() == 0);

    std::string expected_stored_v_contract_str =
        "0407000000636f756e746572010f0000000b000000636f756e7465725f696e630000000"
        "0";
    std::string actual_stored_v_contract_str = hexEncode(ser.ToBytes(stored_v_contract));
    std::cout << "stored versioned contract: " << actual_stored_v_contract_str << std::endl;
    TEST_ASSERT(expected_stored_v_contract_str == actual_stored_v_contract_str);
}

/// Transfer Deploy Item Byte Serialization
void DeployItem_ByteSer_Transfer_Test()
{
    ExecutableDeployItemByteSerializer ser;

    Casper::PublicKey pk =
        Casper::PublicKey::FromHexString("01027c04a0210afdf4a83328d57e8c2a12247a86d872fb53367f22a84b1b53d2a9");
    TransferDeployItem transfer_item(u512FromDec("15000000000"), AccountHashKey(pk), 12345u, true);

    TEST_ASSERT(transfer_item.args.size() == 3);

    std::string expected_transfer_item_str = "050300000006000000616d6f756e74060000000500d6117e030806000000746172676574"
                                             "200000007cfcb2fbdd0e747cabd0f8fe4d743179a764a8d7174ea6f0dfdb0c41fe1348b4"
                                             "0f20000000020000006964090000000139300000000000000d05";
    std::string actual_transfer_bytes = hexEncode(ser.ToBytes(transfer_item));

    std::cout << "transfer item: " << actual_transfer_bytes << std::endl;
    TEST_ASSERT(expected_transfer_item_str == actual_transfer_bytes);
}

} // namespace Casper