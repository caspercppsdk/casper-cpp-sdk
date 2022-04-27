#define TEST_NO_MAIN 1
#include "CLValueByteSerializerTest.hpp"
#include "acutest.h"

namespace Casper {

/// Bool Byte Serialization
void CLValue_ByteSer_Bool_Test(void) {
  CLValueByteSerializer ser;

  // Bool False
  CLValue clv_bool_false = CLValue::Bool(false);
  std::string expected_bool_false = "010000000000";
  std::string actual_bool_false = hexEncode(ser.ToBytes(clv_bool_false));
  std::cout << "bool false: " << actual_bool_false << std::endl;
  TEST_ASSERT(expected_bool_false == actual_bool_false);

  // Bool True
  CLValue clv_bool_true = CLValue::Bool(true);
  std::string expected_bool_true = "010000000100";
  std::string actual_bool_true = hexEncode(ser.ToBytes(clv_bool_true));
  std::cout << "bool true: " << actual_bool_true << std::endl;
  TEST_ASSERT(expected_bool_true == actual_bool_true);

  // Optional Byte Serialization
  // Option False
  CLValue clv_opt_false = CLValue::Option(CLValue::Bool(false));
  std::string expected_opt_false = "0200000001000d00";
  std::string actual_opt_false = hexEncode(ser.ToBytes(clv_opt_false));
  std::cout << "optional false: " << actual_opt_false << std::endl;
  TEST_ASSERT(expected_opt_false == actual_opt_false);

  // Option True
  CLValue clv_opt_true = CLValue::Option(CLValue::Bool(true));
  std::string expected_opt_true = "0200000001010d00";
  std::string actual_opt_true = hexEncode(ser.ToBytes(clv_opt_true));
  std::cout << "optional true: " << actual_opt_true << std::endl;
  TEST_ASSERT(expected_opt_true == actual_opt_true);

  // Option None
  CLValue clv_opt_none = CLValue::OptionNone(CLTypeEnum::Bool);
  std::string expected_opt_none = "01000000000d00";
  std::string actual_opt_none = hexEncode(ser.ToBytes(clv_opt_none));
  std::cout << "optional none: " << actual_opt_none << std::endl;
  TEST_ASSERT(expected_opt_none == actual_opt_none);
}

/// I32 Byte Serialization
void CLValue_ByteSer_I32_Test(void) {
  CLValueByteSerializer ser;

  // I32
  CLValue clv_i32 = CLValue::I32(-10);
  std::string expected_i32 = "04000000f6ffffff01";
  std::string actual_i32 = hexEncode(ser.ToBytes(clv_i32));
  std::cout << "i32: " << actual_i32 << std::endl;
  TEST_ASSERT(expected_i32 == actual_i32);

  // Optional I32
  CLValue clv_opt_i32 = CLValue::Option(CLValue::I32(-10));
  std::string expected_opt_i32 = "0500000001f6ffffff0d01";
  std::string actual_opt_i32 = hexEncode(ser.ToBytes(clv_opt_i32));
  std::cout << "optional i32: " << actual_opt_i32 << std::endl;
  TEST_ASSERT(expected_opt_i32 == actual_opt_i32);

  // Optional None I32
  CLValue clv_opt_none_i32 = CLValue::OptionNone(CLTypeEnum::I32);
  std::string expected_opt_none_i32 = "01000000000d01";
  std::string actual_opt_none_i32 = hexEncode(ser.ToBytes(clv_opt_none_i32));
  std::cout << "optional none i32: " << actual_opt_none_i32 << std::endl;
  TEST_ASSERT(expected_opt_none_i32 == actual_opt_none_i32);
}

/// I64 Byte Serialization
void CLValue_ByteSer_I64_Test(void) {
  CLValueByteSerializer ser;

  // I64
  CLValue clv_i64 = CLValue::I64(-16);
  std::string expected_i64 = "08000000f0ffffffffffffff02";
  std::string actual_i64 = hexEncode(ser.ToBytes(clv_i64));
  std::cout << "i64: " << actual_i64 << std::endl;
  TEST_ASSERT(expected_i64 == actual_i64);

  // Optional I64
  CLValue clv_opt_i64 = CLValue::Option(CLValue::I64(-16));
  std::string expected_opt_i64 = "0900000001f0ffffffffffffff0d02";
  std::string actual_opt_i64 = hexEncode(ser.ToBytes(clv_opt_i64));
  std::cout << "optional i64: " << actual_opt_i64 << std::endl;
  TEST_ASSERT(expected_opt_i64 == actual_opt_i64);

  // Optional None I64
  CLValue clv_opt_none_i64 = CLValue::OptionNone(CLTypeEnum::I64);
  std::string expected_opt_none_i64 = "01000000000d02";
  std::string actual_opt_none_i64 = hexEncode(ser.ToBytes(clv_opt_none_i64));
  std::cout << "optional none i64: " << actual_opt_none_i64 << std::endl;
  TEST_ASSERT(expected_opt_none_i64 == actual_opt_none_i64);
}

// U8 Byte Serialization
void CLValue_ByteSer_U8_Test(void) {
  CLValueByteSerializer ser;

  // U8
  CLValue clv_u8 = CLValue::U8(0x00);
  std::string expected_u8 = "010000000003";
  std::string actual_u8 = hexEncode(ser.ToBytes(clv_u8));
  std::cout << "u8: " << actual_u8 << std::endl;
  TEST_ASSERT(expected_u8 == actual_u8);

  // U8 - 2
  CLValue clv_u8_2 = CLValue::U8(0x7F);
  std::string expected_u8_2 = "010000007f03";
  std::string actual_u8_2 = hexEncode(ser.ToBytes(clv_u8_2));
  std::cout << "u8_2: " << actual_u8_2 << std::endl;
  TEST_ASSERT(expected_u8_2 == actual_u8_2);

  // Optional U8
  CLValue clv_opt_u8 = CLValue::Option(CLValue::U8(0xFF));
  std::string expected_opt_u8 = "0200000001ff0d03";
  std::string actual_opt_u8 = hexEncode(ser.ToBytes(clv_opt_u8));
  std::cout << "optional u8: " << actual_opt_u8 << std::endl;
  TEST_ASSERT(expected_opt_u8 == actual_opt_u8);

  // Optional None U8
  CLValue clv_opt_none_u8 = CLValue::OptionNone(CLTypeEnum::U8);
  std::string expected_opt_none_u8 = "01000000000d03";
  std::string actual_opt_none_u8 = hexEncode(ser.ToBytes(clv_opt_none_u8));
  std::cout << "optional none u8: " << actual_opt_none_u8 << std::endl;
  TEST_ASSERT(expected_opt_none_u8 == actual_opt_none_u8);
}

/// U32 Byte Serialization
void CLValue_ByteSer_U32_Test(void) {
  CLValueByteSerializer ser;

  // U32
  CLValue clv_u32 = CLValue::U32(UINT32_MAX);
  std::string expected_u32 = "04000000ffffffff04";
  std::string actual_u32 = hexEncode(ser.ToBytes(clv_u32));
  std::cout << "u32: " << actual_u32 << std::endl;
  TEST_ASSERT(expected_u32 == actual_u32);

  // Optional U32
  CLValue clv_opt_u32 = CLValue::Option(CLValue::U32(0));
  std::string expected_opt_u32 = "0500000001000000000d04";
  std::string actual_opt_u32 = hexEncode(ser.ToBytes(clv_opt_u32));
  std::cout << "optional u32: " << actual_opt_u32 << std::endl;
  TEST_ASSERT(expected_opt_u32 == actual_opt_u32);

  // Optional None U32
  CLValue clv_opt_none_u32 = CLValue::OptionNone(CLTypeEnum::U32);
  std::string expected_opt_none_u32 = "01000000000d04";
  std::string actual_opt_none_u32 = hexEncode(ser.ToBytes(clv_opt_none_u32));
  std::cout << "optional none u32: " << actual_opt_none_u32 << std::endl;
  TEST_ASSERT(expected_opt_none_u32 == actual_opt_none_u32);
}

/// U64 Byte Serialization
void CLValue_ByteSer_U64_Test(void) {
  CLValueByteSerializer ser;

  // U64
  CLValue clv_u64 = CLValue::U64(UINT64_MAX);
  std::string expected_u64 = "08000000ffffffffffffffff05";
  std::string actual_u64 = hexEncode(ser.ToBytes(clv_u64));
  std::cout << "u64: " << actual_u64 << std::endl;
  TEST_ASSERT(expected_u64 == actual_u64);

  // Optional U64
  CLValue clv_opt_u64 = CLValue::Option(CLValue::U64(1));
  std::string expected_opt_u64 = "090000000101000000000000000d05";
  std::string actual_opt_u64 = hexEncode(ser.ToBytes(clv_opt_u64));
  std::cout << "optional u64: " << actual_opt_u64 << std::endl;
  TEST_ASSERT(expected_opt_u64 == actual_opt_u64);

  // Optional None U64
  CLValue clv_opt_none_u64 = CLValue::OptionNone(CLTypeEnum::U64);
  std::string expected_opt_none_u64 = "01000000000d05";
  std::string actual_opt_none_u64 = hexEncode(ser.ToBytes(clv_opt_none_u64));
  std::cout << "optional none u64: " << actual_opt_none_u64 << std::endl;
  TEST_ASSERT(expected_opt_none_u64 == actual_opt_none_u64);
}

/// U128 Byte Serialization
void CLValue_ByteSer_U128_Test(void) {
  CLValueByteSerializer ser;

  // U128
  uint128_t u128_val = uint128_t(UINT64_MAX);
  CLValue clv_u128 = CLValue::U128(u128_val);
  std::string actual_u128 = hexEncode(ser.ToBytes(clv_u128));
  std::cout << "u128: " << actual_u128 << std::endl;
  std::string expected_u128 = "0900000008ffffffffffffffff06";
  TEST_ASSERT(expected_u128 == actual_u128);

  // U128 Byte Serialization 2
  // Optional U128

  uint128_t u128_val_2 = u128FromHex("10FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF");
  u128_val_2 -= 1;

  CLValue clv_u128_2 = CLValue::Option(CLValue::U128(u128_val_2));
  std::string actual_u128_2 = hexEncode(ser.ToBytes(clv_u128_2));
  std::cout << "u128_2: " << actual_u128_2 << std::endl;
  std::string expected_u128_2 =
      "120000000110feffffffffffffffffffffffffffffff0d06";
  TEST_ASSERT(expected_u128_2 == actual_u128_2);

  // Optional None U128
  CLValue clv_opt_none_u128 = CLValue::OptionNone(CLTypeEnum::U128);
  std::string expected_opt_none_u128 = "01000000000d06";
  std::string actual_opt_none_u128 = hexEncode(ser.ToBytes(clv_opt_none_u128));
  std::cout << "optional none u128: " << actual_opt_none_u128 << std::endl;
  TEST_ASSERT(expected_opt_none_u128 == actual_opt_none_u128);
}

/// U256 Byte Serialization
void CLValue_ByteSer_U256_Test(void) {
  CLValueByteSerializer ser;

  // U256
  uint256_t u256_val = uint256_t(UINT64_MAX);
  CLValue clv_u256 = CLValue::U256(u256_val);
  std::string actual_u256 = hexEncode(ser.ToBytes(clv_u256));
  std::cout << "u256: " << actual_u256 << std::endl;
  std::string expected_u256 = "0900000008ffffffffffffffff07";
  TEST_ASSERT(expected_u256 == actual_u256);

  // Optional U256
  uint256_t u256_b_val_2 = u256FromHex(
      "20FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF");

  std::cout << "u256_b_val_2: " << u256_b_val_2 << std::endl;
  uint256_t subtract_val{0x80};
  u256_b_val_2 -= subtract_val;

  uint256_t u256_val_2(u256_b_val_2);

  CLValue clv_opt_u256 = CLValue::Option(CLValue::U256(u256_val_2));
  std::string expected_opt_u256 =
      "2200000001207fffffffffffffffffffffffffffffffffffffffffffffffffffffffffff"
      "ffff0d07";
  std::string actual_opt_u256 = hexEncode(ser.ToBytes(clv_opt_u256));
  std::cout << "optional u256: " << actual_opt_u256 << std::endl;
  TEST_ASSERT(expected_opt_u256 == actual_opt_u256);

  // Optional None U256
  CLValue clv_opt_none_u256 = CLValue::OptionNone(CLTypeEnum::U256);
  std::string expected_opt_none_u256 = "01000000000d07";
  std::string actual_opt_none_u256 = hexEncode(ser.ToBytes(clv_opt_none_u256));
  std::cout << "optional none u256: " << actual_opt_none_u256 << std::endl;
  TEST_ASSERT(expected_opt_none_u256 == actual_opt_none_u256);
}

/// U512 Byte Serialization
void CLValue_ByteSer_U512_Test(void) {
  CLValueByteSerializer ser;

  // U512 to bytes
  uint512_t u512_val = uint512_t(UINT64_MAX);
  CLValue clv_u512 = CLValue::U512(u512_val);
  std::string expected_u512 = "0900000008ffffffffffffffff08";
  std::string actual_u512 = hexEncode(ser.ToBytes(clv_u512));
  std::cout << "u512: " << actual_u512 << std::endl;
  std::cout << "u512 expected: " << expected_u512 << std::endl;

  TEST_ASSERT(expected_u512 == actual_u512);

  // Optional U512
  uint512_t u512_val_2 = u512FromHex(
      "40FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF"
      "FF"
      "FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF");

  uint512_t sub512_val{0x80};
  u512_val_2 -= sub512_val;

  CLValue clv_opt_u512 = CLValue::Option(CLValue::U512(u512_val_2));
  std::string expected_clv_opt_u512 =
      "4200000001407fffffffffffffffffffffffffffffffffffffffffffffffffffffffffff"
      "ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff0d0"
      "8";
  std::string actual_clv_opt_u512 = hexEncode(ser.ToBytes(clv_opt_u512));
  std::cout << "optional u512: " << actual_clv_opt_u512 << std::endl;
  std::cout << "optional u512 expected: " << expected_clv_opt_u512 << std::endl;
  TEST_ASSERT(expected_clv_opt_u512 == actual_clv_opt_u512);

  // Optional U512 None
  CLValue clv_opt_u512_none = CLValue::OptionNone(CLTypeEnum::U512);
  std::string expected_opt_u512_none = "01000000000d08";
  std::string actual_opt_u512_none = hexEncode(ser.ToBytes(clv_opt_u512_none));
  std::cout << "optional u512 none: " << actual_opt_u512_none << std::endl;
  TEST_ASSERT(expected_opt_u512_none == actual_opt_u512_none);
}

/// Unit Byte Serialization
void CLValue_ByteSer_Unit_Test(void) {
  CLValueByteSerializer ser;

  // Unit
  CLValue clv_unit = CLValue::Unit();
  std::string expected_unit = "0000000009";
  std::string actual_unit = hexEncode(ser.ToBytes(clv_unit));
  std::cout << "unit: " << actual_unit << std::endl;
  TEST_ASSERT(expected_unit == actual_unit);

  // Optional Unit
  CLValue clv_opt_unit = CLValue::Option(CLValue::Unit());
  std::string expected_opt_unit = "01000000010d09";
  std::string actual_opt_unit = hexEncode(ser.ToBytes(clv_opt_unit));
  std::cout << "optional unit: " << actual_opt_unit << std::endl;
  TEST_ASSERT(expected_opt_unit == actual_opt_unit);

  // Optional None Unit
  CLValue clv_opt_none_unit = CLValue::OptionNone(CLTypeEnum::Unit);
  std::string expected_opt_none_unit = "01000000000d09";
  std::string actual_opt_none_unit = hexEncode(ser.ToBytes(clv_opt_none_unit));
  std::cout << "optional none unit: " << actual_opt_none_unit << std::endl;
  TEST_ASSERT(expected_opt_none_unit == actual_opt_none_unit);
}

/// String Byte Serialization
void CLValue_ByteSer_String_Test(void) {
  CLValueByteSerializer ser;

  // String
  CLValue clv_str = CLValue::String("Hello, Casper!");
  std::string expected_str = "120000000e00000048656c6c6f2c20436173706572210a";
  std::string actual_str = hexEncode(ser.ToBytes(clv_str));
  std::cout << "string: " << actual_str << std::endl;
  TEST_ASSERT(expected_str == actual_str);

  // Optional String
  CLValue clv_opt_str = CLValue::Option(CLValue::String("Hello, Casper!"));
  std::string expected_opt_str =
      "13000000010e00000048656c6c6f2c20436173706572210d0a";
  std::string actual_opt_str = hexEncode(ser.ToBytes(clv_opt_str));
  std::cout << "optional string: " << actual_opt_str << std::endl;
  TEST_ASSERT(expected_opt_str == actual_opt_str);

  // Optional Empty String
  CLValue clv_opt_empty_str = CLValue::Option(CLValue::String(""));
  std::string expected_opt_empty_str = "0500000001000000000d0a";
  std::string actual_opt_empty_str = hexEncode(ser.ToBytes(clv_opt_empty_str));
  std::cout << "optional empty string: " << actual_opt_empty_str << std::endl;
  TEST_ASSERT(expected_opt_empty_str == actual_opt_empty_str);

  // Optional None String
  CLValue clv_opt_none_str = CLValue::OptionNone(CLTypeEnum::String);
  std::string expected_opt_none_str = "01000000000d0a";
  std::string actual_opt_none_str = hexEncode(ser.ToBytes(clv_opt_none_str));
  std::cout << "optional none string: " << actual_opt_none_str << std::endl;
  TEST_ASSERT(expected_opt_none_str == actual_opt_none_str);
}

/// URef Byte Serialization
void CLValue_ByteSer_URef_Test(void) {
  CLValueByteSerializer ser;

  CLValue uref_val = CLValue::URef(
      "uref-000102030405060708090a0b0c0d0e0f000102030405060708090a0b0c0d0e0f-"
      "007");

  std::string expected_uref =
      "21000000000102030405060708090a0b0c0d0e0f000102030405060708090a0b0c0d0e0f"
      "070c";

  std::string actual_uref = hexEncode(ser.ToBytes(uref_val));

  std::cout << "uref: " << actual_uref << std::endl;

  TEST_ASSERT(expected_uref == actual_uref);

  // Optional URef
  CLValue clv_opt_uref = CLValue::Option(CLValue::URef(
      "uref-000102030405060708090a0b0c0d0e0f000102030405060708090a0b0c0d0e0f-"
      "007"));
  std::string expected_opt_uref =
      "2200000001000102030405060708090a0b0c0d0e0f000102030405060708090a0b0c0d0e"
      "0f070d0c";

  std::string actual_opt_uref = hexEncode(ser.ToBytes(clv_opt_uref));

  std::cout << "optional uref: " << actual_opt_uref << std::endl;
  TEST_ASSERT(expected_opt_uref == actual_opt_uref);

  // Optional None URef
  CLValue clv_opt_none_uref = CLValue::OptionNone(CLTypeEnum::URef);
  std::string expected_opt_none_uref = "01000000000d0c";
  std::string actual_opt_none_uref = hexEncode(ser.ToBytes(clv_opt_none_uref));
  std::cout << "optional none uref: " << actual_opt_none_uref << std::endl;
  TEST_ASSERT(expected_opt_none_uref == actual_opt_none_uref);
}

/// Key Byte Serialization
void CLValue_ByteSer_Key_Test(void) {
  CLValueByteSerializer ser;

  // Account Hash
  AccountHashKey acc_key(
      "account-hash-"
      "989ca079a5e446071866331468ab949483162588d57ec13ba6bb051f1e15f8b7");

  CLValue clv_account_hash_key = CLValue::Key(acc_key);
  std::string expected_acc_key_str =
      "2100000000989ca079a5e446071866331468ab949483162588d57ec13ba6bb051f1e15f8"
      "b70b";
  std::string actual_acc_key_str = hexEncode(ser.ToBytes(clv_account_hash_key));
  std::cout << "account hash key: " << actual_acc_key_str << std::endl;
  TEST_ASSERT(expected_acc_key_str == actual_acc_key_str);

  // Optional Account Hash
  CLValue clv_opt_acc_hash_key = CLValue::Option(CLValue::Key(acc_key));
  std::string expected_opt_acc_hash_key_str =
      "220000000100989ca079a5e446071866331468ab949483162588d57ec13ba6bb051f1e15"
      "f8b70d0b";
  std::string actual_opt_acc_hash_key_str =
      hexEncode(ser.ToBytes(clv_opt_acc_hash_key));
  std::cout << "optional account hash key: " << actual_opt_acc_hash_key_str
            << std::endl;
  TEST_ASSERT(expected_opt_acc_hash_key_str == actual_opt_acc_hash_key_str);

  // Optional None Account Hash
  CLValue clv_opt_none_acc_hash_key = CLValue::OptionNone(CLTypeEnum::Key);

  std::string expected_opt_none_acc_hash_key_str = "01000000000d0b";
  std::string actual_opt_none_acc_hash_key_str =
      hexEncode(ser.ToBytes(clv_opt_none_acc_hash_key));

  std::cout << "optional none account hash key: "
            << actual_opt_none_acc_hash_key_str << std::endl;
  TEST_ASSERT(expected_opt_none_acc_hash_key_str ==
              actual_opt_none_acc_hash_key_str);
}

/// Public Key Byte Serialization
void CLValue_ByteSer_PublicKey_Test(void) {
  CLValueByteSerializer ser;

  // Public Key
  Casper::PublicKey pk = Casper::PublicKey::FromHexString(
      "01381b36cd07Ad85348607ffE0fA3A2d033eA941D14763358eBEacE9C8aD3cB771");
  CLValue clv_pk = CLValue::PublicKey(pk);
  std::string expected_pk_str =
      "2100000001381b36cd07ad85348607ffe0fa3a2d033ea941d14763358ebeace9c8ad3cb7"
      "7116";
  std::string actual_pk_str = hexEncode(ser.ToBytes(clv_pk));
  std::cout << "public key: " << actual_pk_str << std::endl;
  TEST_ASSERT(expected_pk_str == actual_pk_str);

  // Optional Public Key
  CLValue clv_opt_pk = CLValue::Option(CLValue::PublicKey(pk));
  std::string expected_opt_pk_str =
      "220000000101381b36cd07ad85348607ffe0fa3a2d033ea941d14763358ebeace9c8ad3c"
      "b7710d16";
  std::string actual_opt_pk_str = hexEncode(ser.ToBytes(clv_opt_pk));
  std::cout << "optional public key: " << actual_opt_pk_str << std::endl;
  TEST_ASSERT(expected_opt_pk_str == actual_opt_pk_str);

  // Optional None Public Key
  CLValue clv_opt_none_pk = CLValue::OptionNone(CLTypeEnum::PublicKey);
  std::string expected_opt_none_pk_str = "01000000000d16";
  std::string actual_opt_none_pk_str = hexEncode(ser.ToBytes(clv_opt_none_pk));
  std::cout << "optional none public key: " << actual_opt_none_pk_str
            << std::endl;
  TEST_ASSERT(expected_opt_none_pk_str == actual_opt_none_pk_str);
}

void CLValue_ByteSer_List_Test(void) {
  CLValueByteSerializer ser;

  // List
  CLValue u32_1 = CLValue::U32(1);
  CLValue u32_2 = CLValue::U32(2);
  CLValue u32_3 = CLValue::U32(3);
  CLValue u32_4 = CLValue::U32(4);

  std::vector<CLValue> list_u32;
  list_u32.push_back(u32_1);
  list_u32.push_back(u32_2);
  list_u32.push_back(u32_3);
  list_u32.push_back(u32_4);

  CLValue clv_list = CLValue::List(list_u32);

  std::string expected_list_str =
      "1400000004000000010000000200000003000000040000000e04";

  std::string actual_list_str = hexEncode(ser.ToBytes(clv_list));
  std::cout << "list: " << actual_list_str << std::endl;
  TEST_ASSERT(expected_list_str == actual_list_str);

  // Optional List
  CLValue clv_opt_list = CLValue::Option(CLValue::List(list_u32));

  std::string expected_opt_list_str =
      "150000000104000000010000000200000003000000040000000d0e04";

  std::string actual_opt_list_str = hexEncode(ser.ToBytes(clv_opt_list));
  std::cout << "optional list: " << actual_opt_list_str << std::endl;
  TEST_ASSERT(expected_opt_list_str == actual_opt_list_str);

  // Optional None List
  CLValue clv_opt_none_list =
      CLValue::OptionNone(CLType(CLTypeEnum::U32, CLTypeEnum::List));

  std::string expected_opt_none_list_str = "01000000000d0e04";
  std::string actual_opt_none_list_str =
      hexEncode(ser.ToBytes(clv_opt_none_list));

  std::cout << "optional none list: " << actual_opt_none_list_str << std::endl;
  TEST_ASSERT(expected_opt_none_list_str == actual_opt_none_list_str);

  // Empty List
  CLValue clv_empty_list =
      CLValue::EmptyList(CLType(CLTypeEnum::Key, CLTypeEnum::List));

  std::string expected_empty_list_str = "04000000000000000e0b";
  std::string actual_empty_list_str = hexEncode(ser.ToBytes(clv_empty_list));
  std::cout << "empty list: " << actual_empty_list_str << std::endl;
  TEST_ASSERT(expected_empty_list_str == actual_empty_list_str);
}

/// ByteArray Byte Serialization
void CLValue_ByteSer_ByteArray_Test(void) {
  CLValueByteSerializer ser;

  // ByteArray
  CBytes byte_array_bytes = hexDecode("0102030405060708");
  CLValue clv_byte_array = CLValue::ByteArray(byte_array_bytes);
  std::string expected_byte_array_str = "0800000001020304050607080f08000000";
  std::string actual_byte_array_str = hexEncode(ser.ToBytes(clv_byte_array));
  std::cout << "byte array: " << actual_byte_array_str << std::endl;
  TEST_ASSERT(expected_byte_array_str == actual_byte_array_str);

  // Optional ByteArray
  CLValue clv_opt_byte_array =
      CLValue::Option(CLValue::ByteArray(byte_array_bytes));
  std::string expected_opt_byte_array_str =
      "090000000101020304050607080d0f08000000";
  std::string actual_opt_byte_array_str =
      hexEncode(ser.ToBytes(clv_opt_byte_array));
  std::cout << "optional byte array: " << actual_opt_byte_array_str
            << std::endl;
  TEST_ASSERT(expected_opt_byte_array_str == actual_opt_byte_array_str);

  // Optional None ByteArray
  CLValue clv_opt_none_byte_array = CLValue::OptionNone(CLType(32));
  std::string expected_opt_none_byte_array_str = "01000000000d0f20000000";
  std::string actual_opt_none_byte_array_str =
      hexEncode(ser.ToBytes(clv_opt_none_byte_array));
  std::cout << "optional none byte array: " << actual_opt_none_byte_array_str
            << std::endl;
  TEST_ASSERT(expected_opt_none_byte_array_str ==
              actual_opt_none_byte_array_str);
}

void CLValue_ByteSer_Result_Test(void) {
  CLValueByteSerializer ser;
  // NOT IMPLEMENTED
  TEST_ASSERT(false);
}

void CLValue_ByteSer_Map_Test(void) {
  CLValueByteSerializer ser;
  // NOT IMPLEMENTED
  TEST_ASSERT(false);
}

void CLValue_ByteSer_Tuple1_Test(void) {
  CLValueByteSerializer ser;
  // NOT IMPLEMENTED
  TEST_ASSERT(false);
}

void CLValue_ByteSer_Tuple2_Test(void) {
  CLValueByteSerializer ser;
  // NOT IMPLEMENTED
  TEST_ASSERT(false);
}

void CLValue_ByteSer_Tuple3_Test(void) {
  CLValueByteSerializer ser;
  // NOT IMPLEMENTED
  TEST_ASSERT(false);
}

void CLValue_ByteSer_Any_Test(void) {
  CLValueByteSerializer ser;
TODO:  // NOT IMPLEMENTED
  TEST_ASSERT(true);
}
}  // namespace Casper