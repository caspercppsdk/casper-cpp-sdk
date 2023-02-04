#include "TestBase.hpp"

#include "ByteSerializers/DeployByteSerializer.h"

namespace Casper {


class DeployItemTests : public ::testing::Test {
 protected:

    // DeployItemTests() {
    //     // You can do set-up work for each test here.
    // }

    // ~DeployItemTests() override {
    //     // You can do clean-up work that doesn't throw exceptions here.
    // }

    // // If the constructor and destructor are not enough for setting up
    // // and cleaning up each test, you can define the following methods:

    // void SetUp() override {
    //     // Code here will be called immediately after the constructor (right
    //     // before each test).
    // }

    // void TearDown() override {
    //     // Code here will be called immediately after each test (right
    //     // before the destructor).
    // }

    std::string encodeExecDepItem(const ExecutableDeployItem& execDepItem)
    {
        auto ediBytes = ser.ToBytes(execDepItem);
        return hexEncode(ediBytes);
    }

    ExecutableDeployItemByteSerializer ser;

};

/// ModuleBytes Deploy Item Byte Serialization
TEST_F(DeployItemTests, ByteSerializer_ModuleBytes)
{
    uint512_t amount = u512FromDec("1000");
    auto item = ModuleBytes(amount);

    EXPECT_EQ(item.module_bytes.size(), 0);
    EXPECT_EQ(item.args.size(), 1);

    EXPECT_EQ(encodeExecDepItem(item), "00000000000100000006000000616d6f756e740300000002e80308");
}

/// StoredContractByHash Deploy Item Byte Serialization
TEST_F(DeployItemTests, ByteSerializer_StoredContractByHash)
{
    Casper::HashKey hashKey(
      "hash-0102030401020304010203040102030401020304010203040102030401020304");
    auto item = StoredContractByHash(hashKey.ToHexString(), "counter_inc");

    EXPECT_EQ(item.hash, CEP57Checksum::Encode(hashKey.raw_bytes));
    EXPECT_EQ(item.entry_point, "counter_inc");
    EXPECT_EQ(item.args.size(), 0);

    EXPECT_EQ(encodeExecDepItem(item), "0101020304010203040102030401020304010203040102030401020304010203040b000000636f756e7465725f696e6300000000");
}

/// StoredContractByName Deploy Item Byte Serialization
TEST_F(DeployItemTests, ByteSerializer_StoredContractByName)
{
    auto item = StoredContractByName("counter", "counter_inc");

    EXPECT_EQ(item.name, "counter");
    EXPECT_EQ(item.entry_point, "counter_inc");
    EXPECT_EQ(item.args.size(), 0);

    EXPECT_EQ(encodeExecDepItem(item), "0207000000636f756e7465720b000000636f756e7465725f696e6300000000");
}

/// StoredVersionedContractByHash Deploy Item Byte Serialization
TEST_F(DeployItemTests, ByteSerializer_StoredVersionedContractByHash)
{
    Casper::HashKey hashKey(
      "hash-0102030401020304010203040102030401020304010203040102030401020304");
    auto item = StoredVersionedContractByHash(hashKey.ToHexString(), 1, "counter_inc");

    EXPECT_EQ(item.hash, CEP57Checksum::Encode(hashKey.raw_bytes));
    EXPECT_EQ(item.version, 1);
    EXPECT_EQ(item.entry_point, "counter_inc");
    EXPECT_EQ(item.args.size(), 0);

    EXPECT_EQ(encodeExecDepItem(item), "03010203040102030401020304010203040102030401020304010203040102030401010000000b000000636f756e7465725f696e6300000000");
}

/// StoredVersionedContractByName Deploy Item Byte Serialization
TEST_F(DeployItemTests, ByteSerializer_StoredVersionedContractByName)
{
    auto item = StoredVersionedContractByName("counter", 15, "counter_inc");

    EXPECT_EQ(item.name, "counter");
    EXPECT_EQ(item.version, 15);
    EXPECT_EQ(item.entry_point, "counter_inc");
    EXPECT_EQ(item.args.size(), 0);

    EXPECT_EQ(encodeExecDepItem(item), "0407000000636f756e746572010f0000000b000000636f756e7465725f696e6300000000");
}

/// Transfer Deploy Item Byte Serialization
TEST_F(DeployItemTests, ByteSerializer_Transfer)
{
    Casper::PublicKey pk = Casper::PublicKey::FromHexString(
      "01027c04a0210afdf4a83328d57e8c2a12247a86d872fb53367f22a84b1b53d2a9");
    TransferDeployItem item(u512FromDec("15000000000"), AccountHashKey(pk), 12345u, true);

    EXPECT_EQ(item.args.size(), 3);

    EXPECT_EQ(encodeExecDepItem(item), "050300000006000000616d6f756e74060000000500d6117e030806000000746172676574200000007cfcb2fbdd0e747cabd0f8fe4d743179a764a8d7174ea6f0dfdb0c41fe1348b40f20000000020000006964090000000139300000000000000d05");
}

}  // namespace Casper