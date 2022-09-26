#pragma once

#include "Base.h"
#include "ByteSerializers/GlobalStateKeyByteSerializer.h"
#include "Types/CLType.h"
#include "Types/CLTypeParsed.h"
#include "Utils/CEP57Checksum.h"
#include <cryptopp/secblock.h>
#include "nlohmann/json.hpp"

namespace Casper {

/// A Casper value, i.e. a value which can be stored and manipulated by smart
/// contracts.
///
/// It holds the underlying data as a type-erased, serialized `Vec<u8>` and also
/// holds the [`CLType`] of the underlying data as a separate member.
struct CLValue {
  CLType cl_type;

  CBytes bytes;

  CLTypeParsed parsed;

  CLValue() {}

  CLValue(CBytes bytes, CLType cl_type) : cl_type(cl_type), bytes(bytes) {}

  CLValue(CBytes bytes, CLType cl_type, CLTypeParsed parsed)
      : cl_type(cl_type), bytes(bytes), parsed(parsed) {}

  CLValue(CBytes bytes, CLType cl_type, CLTypeParsedRVA parsed)
      : cl_type(cl_type), bytes(bytes), parsed(parsed) {}

  CLValue(CBytes bytes, CLTypeRVA cl_type, CLTypeParsedRVA parsed)
      : cl_type(cl_type), bytes(bytes), parsed(parsed) {}

  CLValue(CBytes bytes, CLTypeRVA cl_type) : cl_type(cl_type), bytes(bytes) {}

  CLValue(std::string hex_bytes, CLTypeRVA cl_type, CLTypeParsedRVA parsed) {
    bytes = hexDecode(hex_bytes);
    cl_type = cl_type;
    parsed = parsed;
  }

  bool operator<(const CLValue& b) const;

  /// <summary>
  /// Returns a `CLValue` object with a boolean type.
  /// </summary>
  static CLValue Bool(bool value) {
    CBytes bytes(1);
    bytes[0] = value ? (CryptoPP::byte)0x01 : (CryptoPP::byte)0x00;
    return CLValue(bytes, CLTypeEnum::Bool, value);
  }

  /// <summary>
  /// Returns a `CLValue` object with an Int32 type.
  /// </summary>
  static CLValue I32(int32_t value) {
    CBytes bytes = hexDecode(i32Encode(value));

    return CLValue(bytes, CLTypeEnum::I32, value);
  }

  /// <summary>
  /// Returns a `CLValue` object with an Int64 type.
  /// </summary>
  static CLValue I64(int64_t value) {
    CBytes bytes = hexDecode(i64Encode(value));

    return CLValue(bytes, CLTypeEnum::I64, value);
  }

  /// <summary>
  /// Returns a `CLValue` object with an U8/byte type.
  /// </summary>
  static CLValue U8(uint8_t value) {
    CBytes bytes = hexDecode(u8Encode(value));
    return CLValue(bytes, CLTypeEnum::U8, value);
  }

  /// <summary>
  /// Returns a `CLValue` object with an UInt32 type.
  /// </summary>
  static CLValue U32(uint32_t value) {
    CBytes bytes = hexDecode(u32Encode(value));

    // TODO: check below for all the other functions
    // if (!BitConverter.IsLittleEndian) Array.Reverse(bytes);

    return CLValue(bytes, CLTypeEnum::U32, value);
  }

  /// <summary>
  /// Returns a `CLValue` object with an UInt64 type.
  /// </summary>
  static CLValue U64(uint64_t value) {
    CBytes bytes = hexDecode(u64Encode(value));
    // std::cout << "U64(" << value << ") = " << std::endl;
    return CLValue(bytes, CLTypeEnum::U64, value);
  }

  /// <summary>
  /// Returns a `CLValue` object with an U128 type.
  /// </summary>
  static CLValue U128(uint128_t value) {
    CBytes bytes = hexDecode(u128ToHex(value));

    return CLValue(bytes, CLTypeEnum::U128, u128ToDec(value));
  }

  /// <summary>
  /// Returns a `CLValue` object with an U256 type.
  /// </summary>
  static CLValue U256(uint256_t value) {
    CBytes bytes = hexDecode(u256ToHex(value));

    return CLValue(bytes, CLTypeEnum::U256, u256ToDec(value));
  }

  /// <summary>
  /// Returns a `CLValue` object with an U512 type.
  /// </summary>
  static CLValue U512(uint512_t value) {
    // std::cout << "u512ToHex: " << u512ToHex(value) << std::endl;
    CBytes bytes = hexDecode(u512ToHex(value));
    // std::cout << "after bytes" << std::endl;
    return CLValue(bytes, CLTypeEnum::U512, u512ToDec(value));
  }

  /// <summary>
  /// Returns a `CLValue` object with a Unit type.
  /// </summary>
  static CLValue Unit() {
    // TODO: Check CBytes(), maybe (0), should be empty
    return CLValue(CBytes(0), CLTypeEnum::Unit, std::monostate{});
  }

  /// <summary>
  /// Returns a `CLValue` object with a String type.
  /// </summary>
  static CLValue String(std::string value) {
    CBytes bytes = hexDecode(stringEncode(value));

    return CLValue(bytes, CLTypeEnum::String, value);
  }

  /// <summary>
  /// Returns a `CLValue` object with a URef type.
  /// </summary>
  static CLValue URef(std::string value) {
    Casper::URef uref(value);
    CBytes bytes(33);

    std::copy(uref.raw_bytes.begin(), uref.raw_bytes.end(), bytes.begin());

    bytes[32] = (CryptoPP::byte)uref.access_rights;

    return CLValue(bytes, CLTypeEnum::URef, value);
  }

  /// <summary>
  /// Returns a `CLValue` object with a URef type.
  /// </summary>
  static CLValue URef(Casper::URef& value) {
    CBytes bytes(33);

    std::copy(value.raw_bytes.begin(), value.raw_bytes.end(), bytes.begin());
    bytes[32] = (CryptoPP::byte)value.access_rights;
    return CLValue(bytes, CLTypeEnum::URef, value.ToString());
  }

  /// <summary>
  /// Wraps a `CLValue` object into an Option `CLValue`.
  /// </summary>

  static CLValue Option(CLValue innerValue) {
    // std::cout << "Option(CLValue innerValue)" << std::endl;
    //  std::cout << "size: " << innerValue.bytes.size() << std::endl;
    CBytes bytes(1 + innerValue.bytes.size());
    bytes[0] = 0x01;
    // std::cout << "before copy" << std::endl;
    std::copy(innerValue.bytes.begin(), innerValue.bytes.end(),
              bytes.begin() + 1);
    // std::cout << "after copy" << std::endl;

    nlohmann::json j;
    to_json(j, innerValue.parsed);
    // std::cout << "innerValue.parsed: " << j.dump() << std::endl;
    std::optional<CLTypeRVA> opt_with_inner = innerValue.cl_type.type;
    return CLValue(bytes, CLType(opt_with_inner), innerValue.parsed);
  }

  static CLValue Option(int32_t innerValue) {
    return CLValue::Option(CLValue::I32(innerValue));
  }

  static CLValue Option(int64_t innerValue) {
    return CLValue::Option(CLValue::I64(innerValue));
  }

  static CLValue Option(uint8_t innerValue) {
    return CLValue::Option(CLValue::U8(innerValue));
  }

  static CLValue Option(uint32_t innerValue) {
    return CLValue::Option(CLValue::U32(innerValue));
  }

  static CLValue Option(uint64_t innerValue) {
    return CLValue::Option(CLValue::U64(innerValue));
  }

  static CLValue Option(std::string innerValue) {
    return CLValue::Option(CLValue::String(innerValue));
  }

  static CLValue Option(Casper::URef innerValue) {
    return CLValue::Option(CLValue::URef(innerValue));
  }
  /*
  02000000 01 00 0d00 opt bool false
  02000000 01 01 0d00 opt bool true
  01000000 00 0d 00   opt bool none
  01000000 00 0d
  */

  static CLValue Option(PublicKey innerValue) {
    return CLValue::Option(CLValue::PublicKey(innerValue));
  }

  static CLValue Option(GlobalStateKey innerValue) {
    return CLValue::Option(CLValue::Key(innerValue));
  }

  static CLValue Option(CBytes innerValue) {
    return CLValue::Option(CLValue::ByteArray(innerValue));
  }

  static CLValue Option(std::vector<CLValue>& innerValue) {
    return CLValue::Option(CLValue::List(innerValue));
  }

  static CLValue Option(std::map<CLValue, CLValue> innerValue) {
    return CLValue::Option(CLValue::Map(innerValue));
  }

  static CLValue OptionNone(CLType innerTypeInfo) {
    CBytes bytes(1);

    bytes[0] = (CryptoPP::byte)0x00;
    std::optional<CLTypeRVA> opt_with_inner = innerTypeInfo.type;
    return CLValue(bytes, CLType(opt_with_inner), std::monostate{});
  }

  static CLValue OptionNone(CLType innerKeyTypeInfo, CLType innerValueTypeInfo,
                            CLTypeEnum innerType = CLTypeEnum::Map) {
    if (innerType == CLTypeEnum::Map) {
      CBytes bytes(1);

      bytes[0] = (CryptoPP::byte)0x00;
      std::map<CLTypeRVA, CLTypeRVA> inner_type_info;
      inner_type_info[innerKeyTypeInfo.type] = innerValueTypeInfo.type;
      std::optional<CLTypeRVA> opt_with_inner = CLType(inner_type_info).type;

      return CLValue(bytes, CLType(opt_with_inner), std::monostate{});
    } else {
      // Result None
      CBytes bytes(1);
      bytes[0] = (CryptoPP::byte)0x00;

      std::map<std::string, CLTypeRVA> result_type_info;
      result_type_info["Ok"] = innerKeyTypeInfo.type;
      result_type_info["Err"] = innerValueTypeInfo.type;

      std::map<std::string, CLTypeRVA> res_info;
      res_info["Result"] = result_type_info;

      std::optional<CLTypeRVA> opt_with_inner = CLType(res_info).type;

      return CLValue(bytes, CLType(opt_with_inner), std::monostate{});
    }
  }

  static CLValue OptionNoneTuple1(CLTypeRVA innerTypeInfo) {
    CBytes bytes(1);

    bytes[0] = (CryptoPP::byte)0x00;

    std::map<std::string, std::vector<CLTypeRVA>> tuple1_type_info;
    std::vector<CLTypeRVA> tuple1_type_info_vec;

    tuple1_type_info_vec.push_back(innerTypeInfo);
    tuple1_type_info["Tuple1"] = tuple1_type_info_vec;

    std::optional<CLTypeRVA> opt_with_inner = CLType(tuple1_type_info).type;

    return CLValue(bytes, CLType(opt_with_inner), std::monostate{});
  }

  static CLValue OptionNoneTuple2(CLTypeRVA innerTypeInfo1,
                                  CLTypeRVA innerTypeInfo2) {
    CBytes bytes(1);

    bytes[0] = (CryptoPP::byte)0x00;

    std::map<std::string, std::vector<CLTypeRVA>> tuple2_type_info;
    std::vector<CLTypeRVA> tuple2_type_info_vec;

    tuple2_type_info_vec.push_back(innerTypeInfo1);
    tuple2_type_info_vec.push_back(innerTypeInfo2);
    tuple2_type_info["Tuple2"] = tuple2_type_info_vec;

    std::optional<CLTypeRVA> opt_with_inner = CLType(tuple2_type_info).type;

    return CLValue(bytes, CLType(opt_with_inner), std::monostate{});
  }

  static CLValue OptionNoneTuple3(CLTypeRVA innerTypeInfo1,
                                  CLTypeRVA innerTypeInfo2,
                                  CLTypeRVA innerTypeInfo3) {
    CBytes bytes(1);

    bytes[0] = (CryptoPP::byte)0x00;

    std::map<std::string, std::vector<CLTypeRVA>> tuple3_type_info;
    std::vector<CLTypeRVA> tuple3_type_info_vec;

    tuple3_type_info_vec.push_back(innerTypeInfo1);
    tuple3_type_info_vec.push_back(innerTypeInfo2);
    tuple3_type_info_vec.push_back(innerTypeInfo3);
    tuple3_type_info["Tuple3"] = tuple3_type_info_vec;

    std::optional<CLTypeRVA> opt_with_inner = CLType(tuple3_type_info).type;

    return CLValue(bytes, CLType(opt_with_inner), std::monostate{});
  }

  static CLValue OptionNone(CLTypeEnum innerType) {
    return CLValue::OptionNone(CLType(innerType));
  }

  /// <summary>
  /// Returns a List `CLValue` object.
  /// </summary>

  static CLValue List(std::vector<CLValue> values) {
    if (values.size() == 0) {
      std::cout << "List size is 0" << std::endl;
      throw std::runtime_error("List cannot be empty");
    }

    CBytes sb;

    CBytes bytes = hexDecode(u32Encode(values.size()));

    // std::cout << "bytes: " << bytes.size() << std::endl;
    // std::cout << "bytes: " << hexEncode(bytes) << std::endl;

    sb += bytes;

    CLTypeRVA first_elem_type = values[0].cl_type.type;

    std::vector<CLTypeParsedRVA> parsed_values;
    CLTypeParsedRVA parsed_elems;

    // std::cout << "after typeInfo" << std::endl;
    for (auto value : values) {
      sb += value.bytes;
      parsed_values.push_back(value.parsed.parsed);

      if (value.cl_type.type.which() != first_elem_type.which()) {
        throw std::runtime_error(
            "All elements in a list must be of the same type");
      }
    }

    // std::cout << "after for" << std::endl;
    parsed_elems = parsed_values;

    return CLValue(sb, CLType(first_elem_type, CLTypeEnum::List), parsed_elems);
  }

  static CLValue EmptyList(CLType innerType) {
    CBytes bytes = hexDecode(u32Encode(0));
    return CLValue(bytes, innerType, std::monostate{});
  }

  /// <summary>
  /// Returns a `CLValue` object with a ByteArray type.
  /// </summary>
  static CLValue ByteArray(CBytes bytes) {
    return CLValue(bytes, CLType(bytes.size()), hexEncode(bytes));
  }

  /// <summary>
  /// Returns a `CLValue` object with a ByteArray type.
  /// </summary>
  static CLValue ByteArray(std::string hex_val) {
    CBytes bytes = CryptoUtil::hexDecode(hex_val);

    return CLValue(bytes, CLType(bytes.size()), hex_val);
  }

  /// <summary>
  /// Returns a Result `CLValue` with wrapped OK value inside.
  /// To be complete, it must be indicated the type for an err value
  /// </summary>
  static CLValue Ok(CLValue ok, CLType errTypeInfo) {
    CLType okTypeInfo(ok.cl_type.type, errTypeInfo.type, CLTypeEnum::Result);

    CBytes sb(1 + ok.bytes.size());

    sb[0] = (CryptoPP::byte)0x01;

    std::copy(ok.bytes.begin(), ok.bytes.end(), sb.begin() + 1);

    return CLValue(sb, okTypeInfo, ok.parsed);
  }

  /// <summary>
  /// Returns a Result `CLValue` with wrapped Err value inside.
  /// To be complete, it must be indicated the type for an ok value
  /// </summary>
  static CLValue Err(CLValue err, CLType okTypeInfo) {
    CLType errTypeInfo(okTypeInfo.type, err.cl_type.type, CLTypeEnum::Result);

    CBytes sb(1 + err.bytes.size());

    sb[0] = (CryptoPP::byte)0x00;

    std::copy(err.bytes.begin(), err.bytes.end(), sb.begin() + 1);

    return CLValue(sb, errTypeInfo, err.parsed);
  }

  /// <summary>
  /// Returns a Map `CLValue` object.
  /// </summary>
  static CLValue Map(std::map<CLValue, CLValue>& dict) {
    CLTypeRVA keyType;
    CLTypeRVA valueType;
    CBytes bytes;
    std::cout << "dict size: " << dict.size() << std::endl;

    CBytes len = hexDecode(u32Encode(dict.size()));
    std::map<CLTypeParsedRVA, CLTypeParsedRVA> parsed_dict;
    bytes += len;
    int i = 0;
    std::cout << "dict size: " << dict.size() << std::endl;
    for (auto kv : dict) {
      parsed_dict[kv.first.parsed.parsed] = kv.second.parsed.parsed;
      if (i == 0) {
        keyType = kv.first.cl_type.type;
        valueType = kv.second.cl_type.type;
      } else if (keyType.which() != kv.first.cl_type.type.which() ||
                 valueType.which() != kv.second.cl_type.type.which()) {
        throw std::runtime_error(
            "All elements in a map must be of the same "
            "type");
      }

      bytes += kv.first.bytes;
      bytes += kv.second.bytes;
      i++;
    }
    std::cout << "bytes: " << bytes.size() << std::endl;
    std::map<CLTypeRVA, CLTypeRVA> mp;
    mp[keyType] = valueType;
    std::cout << "map: " << mp.size() << std::endl;
    CLTypeRVA ty(mp);
    std::cout << "ty: " << std::endl;

    return CLValue(bytes, CLType(ty), parsed_dict);
  }

  static CLValue EmptyMap(CLType keyType, CLType valueType) {
    CBytes bytes = hexDecode(u32Encode(0));

    // Custom key and value type map
    std::map<CLTypeRVA, CLTypeRVA> mp;
    mp[keyType.type] = valueType.type;

    CLTypeRVA ty(mp);

    return CLValue(bytes, ty, std::monostate{});
  }

  /// <summary>
  /// Returns a Tuple1 `CLValue` object.
  /// </summary>
  static CLValue Tuple1(CLValue t0) {
    std::map<std::string, std::vector<CLTypeRVA>> mp;
    mp["Tuple1"] = {t0.cl_type.type};
    CLTypeRVA ty(mp);
    return CLValue(t0.bytes, CLType(ty), t0.parsed);
  }

  /// <summary>
  /// Returns a Tuple2 `CLValue` object.
  /// </summary>
  static CLValue Tuple2(CLValue t0, CLValue t1) {
    CBytes bytes(t0.bytes.size() + t1.bytes.size());

    std::copy(t0.bytes.begin(), t0.bytes.end(), bytes.begin());

    std::copy(t1.bytes.begin(), t1.bytes.end(),
              bytes.begin() + t0.bytes.size());

    std::map<std::string, std::vector<CLTypeRVA>> mp;
    mp["Tuple2"] = {t0.cl_type.type, t1.cl_type.type};
    CLTypeRVA ty(mp);

    return CLValue(bytes, CLType(ty), hexEncode(bytes));
  }

  /// <summary>
  /// Returns a Tuple3 `CLValue` object.
  /// </summary>
  static CLValue Tuple3(CLValue t0, CLValue t1, CLValue t2) {
    CBytes bytes(t0.bytes.size() + t1.bytes.size() + t2.bytes.size());

    std::copy(t0.bytes.begin(), t0.bytes.end(), bytes.begin());

    std::copy(t1.bytes.begin(), t1.bytes.end(),
              bytes.begin() + t0.bytes.size());

    std::copy(t2.bytes.begin(), t2.bytes.end(),
              bytes.begin() + t0.bytes.size() + t1.bytes.size());

    std::map<std::string, std::vector<CLTypeRVA>> mp;
    mp["Tuple3"] = {t0.cl_type.type, t1.cl_type.type, t2.cl_type.type};
    CLTypeRVA ty(mp);

    return CLValue(bytes, CLType(ty), hexEncode(bytes));
  }

  /// <summary>
  /// Returns a `CLValue` object with a PublicKey type.
  /// </summary>
  static CLValue PublicKey(Casper::PublicKey publicKey) {
    return CLValue(publicKey.GetBytes(), CLType(CLTypeEnum::PublicKey),
                   hexEncode(publicKey.GetBytes()));
  }

  /// <summary>
  /// Returns a `CLValue` object with a PublicKey type.
  /// </summary>
  static CLValue PublicKey(CBytes value, KeyAlgo keyAlgorithm) {
    CBytes bytes(1 + value.size());
    bytes[0] = (CryptoPP::byte)keyAlgorithm;
    std::copy(value.begin(), value.end(), bytes.begin() + 1);

    return CLValue(bytes, CLType(CLTypeEnum::PublicKey), hexEncode(bytes));
  }

  /// <summary>
  /// Converts a public key into an account hash an returns it wrapped into a
  /// Key `CLValue`
  /// </summary>
  /*
  static CLValue KeyFromPublicKey(Casper::PublicKey publicKey) {
    CBytes accountHash =
        AccountHashKey(publicKey.GetAccountHash()).raw_bytes;

    std::cout << "\n\n\n\n\nAccountHashKey size: " << accountHash.size()
              << std::endl
              << std::endl
              << std::endl
              << std::endl;


    CBytes bytes(1 + accountHash.size());

    bytes[0] = (CryptoPP::byte)KeyIdentifier::Account;

    std::copy(accountHash.begin(), accountHash.end(), bytes.begin() + 1);



    return CLValue(bytes, CLKeyTypeInfo(KeyIdentifier.Account),
                   hexEncode(bytes));

    return CLValue(bytes, CLType(CLTypeEnum::Key), hexEncode(bytes));
  }
  */
  /// <summary>
  /// Returns a `CLValue` object with a GlobalStateKey in it
  /// </summary>
  static CLValue Key(GlobalStateKey& key) {
    auto key_serializer = GlobalStateKeyByteSerializer();

    return CLValue(key_serializer.ToBytes(key), CLType(CLTypeEnum::Key), key);
  }
};

// to json
inline void to_json(nlohmann::json& j, const CLValue& p) {
  j = nlohmann::json{};

  to_json(j["cl_type"], p.cl_type);

  try {
    std::string tmp_bytes = hexEncode(p.bytes);
    j["bytes"] = tmp_bytes;
  } catch (const std::exception& e) {
    std::cout << "CLValue-to_json-bytes what(): " << e.what() << std::endl;
  }

  to_json(j["parsed"], p.parsed);
}

// from json
inline void from_json(const nlohmann::json& j, CLValue& p) {
  from_json(j.at("cl_type"), p.cl_type);
  try {
    std::string hex_bytes_str = j.at("bytes").get<std::string>();
    p.bytes = hexDecode(hex_bytes_str);
  } catch (const std::exception& e) {
    std::cout << "CLValue-from_json-bytes what(): " << e.what() << std::endl;
  }

  // std::cout << j.at("parsed").dump(2) << std::endl;

  from_json(j.at("parsed"), p.parsed, p.cl_type);
}

}  // namespace Casper

namespace nlohmann {
template <typename T>
struct adl_serializer<std::map<boost::make_recursive_variant<T>, boost::make_recursive_variant<T>>> {
  static void to_json(json& j, const boost::make_recursive_variant<T>& var) {
    j = to_json(boost::get<var.which()>(var));
  }

  static void from_json(const json& j, boost::make_recursive_variant<T>& var) {
    from_json(j, boost::get<var.which()>(var));
  }
};

}  // namespace nlohmann

/*

namespace nlohmann {
template <typename T>
adl_serializer<std::map<Casper::CLTypeParsedRVA, T>> {
  // define to_json/from_json here
  void to_json(json & j, std::unordered_map<EC, T> const& map) {

  }
  // likewise for from_json?
}

}  // namespace nlohmann

template<typename ValueType>
struct adl_serializer {
    template<typename BasicJsonType>
    static void to_json(BasicJsonType& j, const T& value) {
        // calls the "to_json" method in T's namespace
    }

    template<typename BasicJsonType>
    static void from_json(const BasicJsonType& j, T& value) {
        // same thing, but with the "from_json" method
    }
};
*/
