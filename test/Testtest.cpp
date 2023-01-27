#include <gtest/gtest.h>
#include "CasperClient.h"
#include "Types/GlobalStateKey.h"
#include "Types/PublicKey.h"
#include "Utils/CryptoUtil.h"
#include <sstream>
#include "Types/CLType.h"
#include "Types/CLConverter.h"

#include "ByteSerializers/DeployByteSerializer.h"
#include "gtest/gtest.h"

namespace Casper{

class CLValueTests : public ::testing::Test {
 protected:

    // CLValueTests() {
    //     // You can do set-up work for each test here.
    // }

    // ~CLValueTests() override {
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

    std::string encodeCLValue(const CLValue& clv)
    {
        auto clvBytes = ser.ToBytes(clv);
        return hexEncode(clvBytes);
    }

    CLValueByteSerializer ser;

};

TEST_F(CLValueTests, ByteSerializer_BoolFalse)
{
    auto clv = CLValue::Bool(false);
    EXPECT_EQ(encodeCLValue(clv), "010000000000");
}

TEST_F(CLValueTests, ByteSerializer_BoolTrue)
{
    auto clv = CLValue::Bool(true);
    EXPECT_EQ(encodeCLValue(clv), "010000000100");
}

TEST_F(CLValueTests, ByteSerializer_BoolFalseOption)
{
    auto clv = CLValue::Option(CLValue::Bool(false));
    EXPECT_EQ(encodeCLValue(clv), "0200000001000d00");
}

TEST_F(CLValueTests, ByteSerializer_BoolTrueOption)
{
    auto clv = CLValue::Option(CLValue::Bool(true));
    EXPECT_EQ(encodeCLValue(clv), "0200000001010d00");
}

TEST_F(CLValueTests, ByteSerializer_BoolOptionNone)
{
    auto clv = CLValue::OptionNone(CLTypeEnum::Bool);
    EXPECT_EQ(encodeCLValue(clv), "01000000000d00");
}

TEST_F(CLValueTests, ByteSerializer_Int32)
{
    auto clv = CLValue::I32(-10);
    EXPECT_EQ(encodeCLValue(clv), "04000000f6ffffff01");
}

TEST_F(CLValueTests, ByteSerializer_Int32Option)
{
    auto clv = CLValue::Option(CLValue::I32(-10));
    EXPECT_EQ(encodeCLValue(clv), "0500000001f6ffffff0d01");
}

TEST_F(CLValueTests, ByteSerializer_Int32OptionNone)
{
    auto clv = CLValue::OptionNone(CLTypeEnum::I32);
    EXPECT_EQ(encodeCLValue(clv), "01000000000d01");
}

TEST_F(CLValueTests, ByteSerializer_Int64)
{
    auto clv = CLValue::I64(-16);
    EXPECT_EQ(encodeCLValue(clv), "08000000f0ffffffffffffff02");
}

TEST_F(CLValueTests, ByteSerializer_Int64Option)
{
    auto clv =  CLValue::Option(CLValue::I64(-16));
    EXPECT_EQ(encodeCLValue(clv), "0900000001f0ffffffffffffff0d02");
}

TEST_F(CLValueTests, ByteSerializer_Int64OptionNone)
{
    auto clv = CLValue::OptionNone(CLTypeEnum::I64);
    EXPECT_EQ(encodeCLValue(clv), "01000000000d02");
}

TEST_F(CLValueTests, ByteSerializer_UInt8)
{
    auto clv = CLValue::U8(0x00);
    EXPECT_EQ(encodeCLValue(clv), "010000000003");

    clv = CLValue::U8(0x7F);
    EXPECT_EQ(encodeCLValue(clv), "010000007f03");
}

TEST_F(CLValueTests, ByteSerializer_UInt8Option)
{
    auto clv = CLValue::Option(CLValue::U8(0xFF));
    EXPECT_EQ(encodeCLValue(clv), "0200000001ff0d03");
}

TEST_F(CLValueTests, ByteSerializer_UInt8OptionNone)
{
    auto clv = CLValue::OptionNone(CLTypeEnum::U8);
    EXPECT_EQ(encodeCLValue(clv), "01000000000d03");
}

TEST_F(CLValueTests, ByteSerializer_UInt32)
{
    auto clv = CLValue::U32(UINT32_MAX);
    EXPECT_EQ(encodeCLValue(clv), "04000000ffffffff04");
}

TEST_F(CLValueTests, ByteSerializer_UInt32Option)
{
    auto clv = CLValue::Option(CLValue::U32(0));
    EXPECT_EQ(encodeCLValue(clv), "0500000001000000000d04");
}

TEST_F(CLValueTests, ByteSerializer_UInt32OptionNone)
{
    auto clv = CLValue::OptionNone(CLTypeEnum::U32);
    EXPECT_EQ(encodeCLValue(clv), "01000000000d04");
}

TEST_F(CLValueTests, ByteSerializer_UInt64)
{
    auto clv = CLValue::U64(UINT64_MAX);
    EXPECT_EQ(encodeCLValue(clv), "08000000ffffffffffffffff05");
}

TEST_F(CLValueTests, ByteSerializer_UInt64Option)
{
    auto clv = CLValue::Option(CLValue::U64(1));
    EXPECT_EQ(encodeCLValue(clv), "090000000101000000000000000d05");
}

TEST_F(CLValueTests, ByteSerializer_UInt64OptionNone)
{
    auto clv = CLValue::OptionNone(CLTypeEnum::U64);
    EXPECT_EQ(encodeCLValue(clv), "01000000000d05");
}

TEST_F(CLValueTests, ByteSerializer_UInt128)
{
    uint128_t tempVal = uint128_t(UINT64_MAX);
    auto clv = CLValue::U128(tempVal);
    EXPECT_EQ(encodeCLValue(clv), "0900000008ffffffffffffffff06");
}

TEST_F(CLValueTests, ByteSerializer_UInt128Option)
{
    uint128_t tempVal = u128FromHex("10FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF") - 1;
    auto clv = CLValue::Option(CLValue::U128(tempVal));
    EXPECT_EQ(encodeCLValue(clv), "120000000110feffffffffffffffffffffffffffffff0d06");
}

TEST_F(CLValueTests, ByteSerializer_UInt128OptionNone)
{
    auto clv = CLValue::OptionNone(CLTypeEnum::U128);
    EXPECT_EQ(encodeCLValue(clv), "01000000000d06");
}

TEST_F(CLValueTests, ByteSerializer_UInt256)
{
    uint256_t tempVal = uint256_t(UINT64_MAX);
    auto clv = CLValue::U256(tempVal);
    EXPECT_EQ(encodeCLValue(clv), "0900000008ffffffffffffffff07");
}

TEST_F(CLValueTests, ByteSerializer_UInt256Option)
{
    uint256_t tempVal = u256FromHex(
      "20FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF") - uint256_t(0x80);
    auto clv = CLValue::Option(CLValue::U256(tempVal));
    EXPECT_EQ(encodeCLValue(clv), "2200000001207fffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff0d07");
}

TEST_F(CLValueTests, ByteSerializer_UInt256OptionNone)
{
    auto clv = CLValue::OptionNone(CLTypeEnum::U256);
    EXPECT_EQ(encodeCLValue(clv), "01000000000d07");
}

TEST_F(CLValueTests, ByteSerializer_UInt512)
{
    uint512_t tempVal = uint512_t(UINT64_MAX);
    auto clv = CLValue::U512(tempVal);
    EXPECT_EQ(encodeCLValue(clv), "0900000008ffffffffffffffff08");
}

TEST_F(CLValueTests, ByteSerializer_UInt512Option)
{
    uint512_t tempVal = u512FromHex(
      "40FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF") - uint512_t(0x80);
    auto clv =  CLValue::Option(CLValue::U512(tempVal));
    EXPECT_EQ(encodeCLValue(clv), "4200000001407fffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff0d08");
}

TEST_F(CLValueTests, ByteSerializer_UInt512OptionNone)
{
    auto clv = CLValue::OptionNone(CLTypeEnum::U512);
    EXPECT_EQ(encodeCLValue(clv), "01000000000d08");
}

TEST_F(CLValueTests, ByteSerializer_Unit)
{
    auto clv = CLValue::Unit();
    EXPECT_EQ(encodeCLValue(clv), "0000000009");
}

TEST_F(CLValueTests, ByteSerializer_UnitOption)
{
    auto clv = CLValue::Option(CLValue::Unit());
    EXPECT_EQ(encodeCLValue(clv), "01000000010d09");
}

TEST_F(CLValueTests, ByteSerializer_UnitOptionNone)
{
    auto clv = CLValue::OptionNone(CLTypeEnum::Unit);
    EXPECT_EQ(encodeCLValue(clv), "01000000000d09");
}

TEST_F(CLValueTests, ByteSerializer_String)
{
    auto clv = CLValue::String("Hello, Casper!");
    EXPECT_EQ(encodeCLValue(clv), "120000000e00000048656c6c6f2c20436173706572210a");
}

TEST_F(CLValueTests, ByteSerializer_StringOption)
{
    auto clv = CLValue::Option(CLValue::String("Hello, Casper!"));
    EXPECT_EQ(encodeCLValue(clv), "13000000010e00000048656c6c6f2c20436173706572210d0a");

    clv = CLValue::Option(CLValue::String(""));
    EXPECT_EQ(encodeCLValue(clv), "0500000001000000000d0a");
}

TEST_F(CLValueTests, ByteSerializer_StringOptionNone)
{
    auto clv = CLValue::OptionNone(CLTypeEnum::String);
    EXPECT_EQ(encodeCLValue(clv), "01000000000d0a");
}

TEST_F(CLValueTests, ByteSerializer_URef)
{
    auto clv = CLValue::URef("uref-000102030405060708090a0b0c0d0e0f000102030405060708090a0b0c0d0e0f-007");
    EXPECT_EQ(encodeCLValue(clv), "21000000000102030405060708090a0b0c0d0e0f000102030405060708090a0b0c0d0e0f070c");
}

TEST_F(CLValueTests, ByteSerializer_URefOption)
{
    auto clv = CLValue::Option(CLValue::URef("uref-000102030405060708090a0b0c0d0e0f000102030405060708090a0b0c0d0e0f-007"));
    EXPECT_EQ(encodeCLValue(clv), "2200000001000102030405060708090a0b0c0d0e0f000102030405060708090a0b0c0d0e0f070d0c");
}


TEST_F(CLValueTests, ByteSerializer_URefOptionNone)
{
    auto clv = CLValue::OptionNone(CLTypeEnum::URef);
    EXPECT_EQ(encodeCLValue(clv), "01000000000d0c");
}

TEST_F(CLValueTests, ByteSerializer_Key)
{
    AccountHashKey tempVal{"account-hash-989ca079a5e446071866331468ab949483162588d57ec13ba6bb051f1e15f8b7"};
    auto clv = CLValue::Key(tempVal);
    EXPECT_EQ(encodeCLValue(clv), "2100000000989ca079a5e446071866331468ab949483162588d57ec13ba6bb051f1e15f8b70b");
}

TEST_F(CLValueTests, ByteSerializer_KeyOption)
{
    AccountHashKey tempVal{"account-hash-989ca079a5e446071866331468ab949483162588d57ec13ba6bb051f1e15f8b7"};
    auto clv = CLValue::Option(CLValue::Key(tempVal));
    EXPECT_EQ(encodeCLValue(clv), "220000000100989ca079a5e446071866331468ab949483162588d57ec13ba6bb051f1e15f8b70d0b");
}

TEST_F(CLValueTests, ByteSerializer_KeyOptionNone)
{
    auto clv = CLValue::OptionNone(CLTypeEnum::Key);
    EXPECT_EQ(encodeCLValue(clv), "01000000000d0b");
}

TEST_F(CLValueTests, ByteSerializer_PublicKey)
{
    auto tempVal = Casper::PublicKey::FromHexString("01381b36cd07Ad85348607ffE0fA3A2d033eA941D14763358eBEacE9C8aD3cB771");
    auto clv = CLValue::PublicKey(tempVal);
    EXPECT_EQ(encodeCLValue(clv), "2100000001381b36cd07ad85348607ffe0fa3a2d033ea941d14763358ebeace9c8ad3cb77116");
}


TEST_F(CLValueTests, ByteSerializer_PublicKeyOption)
{
    auto tempVal = Casper::PublicKey::FromHexString("01381b36cd07Ad85348607ffE0fA3A2d033eA941D14763358eBEacE9C8aD3cB771");
    auto clv = CLValue::Option(CLValue::PublicKey(tempVal));
    EXPECT_EQ(encodeCLValue(clv), "220000000101381b36cd07ad85348607ffe0fa3a2d033ea941d14763358ebeace9c8ad3cb7710d16");
}

TEST_F(CLValueTests, ByteSerializer_PublicKeyOptionNone)
{
    auto clv = CLValue::OptionNone(CLTypeEnum::PublicKey);
    EXPECT_EQ(encodeCLValue(clv), "01000000000d16");
}

TEST_F(CLValueTests, ByteSerializer_List)
{
    std::vector<CLValue> tempVal{CLValue::U32(1), CLValue::U32(2), CLValue::U32(3), CLValue::U32(4)};
    auto clv = CLValue::List(tempVal);
    EXPECT_EQ(encodeCLValue(clv), "1400000004000000010000000200000003000000040000000e04");

    clv = CLValue::EmptyList(CLType(CLTypeEnum::Key, CLTypeEnum::List));
    EXPECT_EQ(encodeCLValue(clv), "04000000000000000e0b");
}

TEST_F(CLValueTests, ByteSerializer_ListOption)
{
    std::vector<CLValue> tempVal{CLValue::U32(1), CLValue::U32(2), CLValue::U32(3), CLValue::U32(4)};
    auto clv = CLValue::Option(CLValue::List(tempVal));
    EXPECT_EQ(encodeCLValue(clv), "150000000104000000010000000200000003000000040000000d0e04");
}

TEST_F(CLValueTests, ByteSerializer_ListOptionNone)
{
    auto clv = CLValue::OptionNone(CLType(CLTypeEnum::U32, CLTypeEnum::List));
    EXPECT_EQ(encodeCLValue(clv), "01000000000d0e04");
}

TEST_F(CLValueTests, ByteSerializer_ByteArray)
{
    auto tempVal = hexDecode("0102030405060708");
    auto clv = CLValue::ByteArray(tempVal);
    EXPECT_EQ(encodeCLValue(clv), "0800000001020304050607080f08000000");
}

TEST_F(CLValueTests, ByteSerializer_ByteArrayOption)
{
    auto tempVal = hexDecode("0102030405060708");
    auto clv = CLValue::Option(CLValue::ByteArray(tempVal));
    EXPECT_EQ(encodeCLValue(clv), "090000000101020304050607080d0f08000000");
}

TEST_F(CLValueTests, ByteSerializer_ByteArrayOptionNone)
{
    auto clv = CLValue::OptionNone(CLType(32));
    EXPECT_EQ(encodeCLValue(clv), "01000000000d0f20000000");
}

TEST_F(CLValueTests, ByteSerializer_ResultOk)
{
    auto clv = CLValue::Ok(CLValue::U8(255), CLType(CLTypeEnum::String));
    EXPECT_EQ(encodeCLValue(clv), "0200000001ff10030a");
}

TEST_F(CLValueTests, ByteSerializer_ResultOkOption)
{
    auto clv = CLValue::Option(CLValue::Ok(CLValue::U8(255), CLType(CLTypeEnum::String)));
    EXPECT_EQ(encodeCLValue(clv), "030000000101ff0d10030a");

    clv = CLValue::Ok(CLValue::Unit(), CLType(CLTypeEnum::String));
    EXPECT_EQ(encodeCLValue(clv), "010000000110090a");
}

TEST_F(CLValueTests, ByteSerializer_ResultErr)
{
    auto clv = CLValue::Err(CLValue::String("Error!"), CLType(CLTypeEnum::Unit));
    EXPECT_EQ(encodeCLValue(clv), "0b00000000060000004572726f722110090a");
}

TEST_F(CLValueTests, ByteSerializer_ResultErrOption)
{
    auto clv = CLValue::Option(CLValue::Err(CLValue::String("Error!"), CLType(CLTypeEnum::Unit)));
    EXPECT_EQ(encodeCLValue(clv), "0c0000000100060000004572726f72210d10090a");
}

TEST_F(CLValueTests, ByteSerializer_ResultErrOptionNone)
{
    auto clv = CLValue::OptionNone(CLType(CLTypeEnum::U8), CLType(CLTypeEnum::String), CLTypeEnum::Result);
    EXPECT_EQ(encodeCLValue(clv), "01000000000d10030a");
}

TEST_F(CLValueTests, ByteSerializer_Map)
{
    std::map<CLValue, CLValue> tempVal{{CLValue::String("key1"), CLValue::U32(1)}, {CLValue::String("key2"), CLValue::U32(2)}};
    auto clv = CLValue::Map(tempVal);
    EXPECT_EQ(encodeCLValue(clv), "1c00000002000000040000006b65793101000000040000006b65793202000000110a04");
}

TEST_F(CLValueTests, ByteSerializer_MapOption)
{
    CLValue u32_1 = CLValue::U32(1);
    CLValue u32_2 = CLValue::U32(2);

    CLValue clv_key1 = CLValue::String("key1");
    CLValue clv_key2 = CLValue::String("key2");

    std::map<CLValue, CLValue> map_u32;
    map_u32.insert(std::make_pair(clv_key1, u32_1));
    map_u32.insert(std::make_pair(clv_key2, u32_2));

    auto clv = CLValue::Option(CLValue::Map(map_u32));
    EXPECT_EQ(encodeCLValue(clv), "1d0000000102000000040000006b65793101000000040000006b657932020000000d110a04");

}

TEST_F(CLValueTests, ByteSerializer_MapOptionNone)
{
    auto clv = CLValue::OptionNone(CLType(CLTypeEnum::String), CLType(CLTypeEnum::U32));
    EXPECT_EQ(encodeCLValue(clv), "01000000000d110a04");
}

TEST_F(CLValueTests, ByteSerializer_EmptyMap)
{
    auto clv = CLValue::EmptyMap(CLType(CLTypeEnum::String), CLType(CLTypeEnum::Key));
    EXPECT_EQ(encodeCLValue(clv), "0400000000000000110a0b");
}

TEST_F(CLValueTests, ByteSerializer_Tuple1)
{
    auto clv = CLValue::Tuple1(CLValue::U32(17));
    EXPECT_EQ(encodeCLValue(clv), "04000000110000001204");

    clv = CLValue::Tuple1(CLValue::String("ABCDE"));
    EXPECT_EQ(encodeCLValue(clv), "09000000050000004142434445120a");
}

TEST_F(CLValueTests, ByteSerializer_Tuple1Option)
{
    auto clv = CLValue::Option(CLValue::Tuple1(CLValue::String("ABCDE")));
    EXPECT_EQ(encodeCLValue(clv), "0a000000010500000041424344450d120a");
}

TEST_F(CLValueTests, ByteSerializer_Tuple1OptionNone)
{
    auto clv = CLValue::OptionNoneTuple1(CLTypeEnum::String);
    EXPECT_EQ(encodeCLValue(clv), "01000000000d120a");
}

TEST_F(CLValueTests, ByteSerializer_Tuple2)
{
    auto clv = CLValue::Tuple2(CLValue::U32(17), CLValue::U32(127));
    EXPECT_EQ(encodeCLValue(clv), "08000000110000007f000000130404");

    clv = CLValue::Tuple2(CLValue::U32(127), CLValue::String("ABCDE"));
    EXPECT_EQ(encodeCLValue(clv), "0d0000007f00000005000000414243444513040a");
}

TEST_F(CLValueTests, ByteSerializer_Tuple2Option)
{
    auto clv = CLValue::Option(CLValue::Tuple2(CLValue::U32(127), CLValue::String("ABCDE")));
    EXPECT_EQ(encodeCLValue(clv), "0e000000017f0000000500000041424344450d13040a");
}

TEST_F(CLValueTests, ByteSerializer_Tuple2OptionNone)
{
    auto clv = CLValue::OptionNoneTuple2(CLTypeEnum::U32, CLTypeEnum::String);
    EXPECT_EQ(encodeCLValue(clv), "01000000000d13040a");
}

TEST_F(CLValueTests, ByteSerializer_Tuple3)
{
    auto clv = CLValue::Tuple3(CLValue::U32(17), CLValue::U32(127), CLValue::U32(17));
    EXPECT_EQ(encodeCLValue(clv), "0c000000110000007f0000001100000014040404");

    clv = CLValue::Tuple3(CLValue::U32(127), CLValue::String("ABCDE"), CLValue::U32(127));
    EXPECT_EQ(encodeCLValue(clv), "110000007f0000000500000041424344457f00000014040a04");
}

TEST_F(CLValueTests, ByteSerializer_Tuple3Option)
{
    auto clv =  CLValue::Option(CLValue::Tuple3(CLValue::U32(127), CLValue::String("ABCDE"), CLValue::U32(127)));
    EXPECT_EQ(encodeCLValue(clv), "12000000017f0000000500000041424344457f0000000d14040a04");
}

TEST_F(CLValueTests, ByteSerializer_Tuple3OptionNone)
{
    auto clv = CLValue::OptionNoneTuple3(CLTypeEnum::U32, CLTypeEnum::String, CLTypeEnum::U32);
    EXPECT_EQ(encodeCLValue(clv), "01000000000d14040a04");
}

TEST_F(CLValueTests, ByteSerializer_Any)
{
    // TODO: Implement
    EXPECT_EQ(true, true);
}

}