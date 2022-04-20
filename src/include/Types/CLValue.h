#pragma once

#include "Base.h"
#include "Types/CLType.h"
#include "Types/CLTypeParsed.h"

#include "cryptopp/secblock.h"
#include "ByteSerializers/BaseByteSerializer.h"
#include "Utils/CEP57Checksum.h"
#include "nlohmann/json.hpp"

namespace Casper {

/// A Casper value, i.e. a value which can be stored and manipulated by smart
/// contracts.
///
/// It holds the underlying data as a type-erased, serialized `Vec<u8>` and also
/// holds the [`CLType`] of the underlying data as a separate member.
struct CLValue {
  CLType cl_type;

  SecByteBlock bytes;

  CLTypeParsed parsed;

  CLValue() {}

  CLValue(SecByteBlock bytes, CLType cl_type)
      : cl_type(cl_type), bytes(bytes) {}

  CLValue(SecByteBlock bytes, CLType cl_type, CLTypeParsed parsed)
      : cl_type(cl_type), bytes(bytes), parsed(parsed) {}

  CLValue(SecByteBlock bytes, CLType cl_type, CLTypeParsedRVA parsed)
      : cl_type(cl_type), bytes(bytes), parsed(parsed) {}

  CLValue(SecByteBlock bytes, CLTypeRVA cl_type, CLTypeParsedRVA parsed)
      : cl_type(cl_type), bytes(bytes), parsed(parsed) {}

  CLValue(SecByteBlock bytes, CLTypeRVA cl_type)
      : cl_type(cl_type), bytes(bytes) {}

  CLValue(std::string hex_bytes, CLTypeRVA cl_type, CLTypeParsedRVA parsed) {
    bytes = CEP57Checksum::Decode(hex_bytes);
    cl_type = cl_type;
    parsed = parsed;
  }

  /// <summary>
  /// Returns a `CLValue` object with a boolean type.
  /// </summary>
  static CLValue Bool(bool value) {
    SecByteBlock bytes = SecByteBlock{value ? (byte)0x01 : (byte)0x00};
    return CLValue(bytes, CLTypeEnum::Bool, value);
  }

  /// <summary>
  /// Returns a `CLValue` object with an Int32 type.
  /// </summary>
  static CLValue I32(int32_t value) {
    SecByteBlock bytes = CEP57Checksum::Decode(i32Encode(value));

    return CLValue(bytes, CLTypeEnum::I32, value);
  }

  /// <summary>
  /// Returns a `CLValue` object with an Int64 type.
  /// </summary>
  static CLValue I64(int64_t value) {
    SecByteBlock bytes = CEP57Checksum::Decode(i64Encode(value));

    return CLValue(bytes, CLTypeEnum::I64, value);
  }

  /// <summary>
  /// Returns a `CLValue` object with an U8/byte type.
  /// </summary>
  static CLValue U8(uint8_t value) {
    SecByteBlock bytes = CEP57Checksum::Decode(u8Encode(value));
    return CLValue(bytes, CLTypeEnum::U8, value);
  }

  /// <summary>
  /// Returns a `CLValue` object with an UInt32 type.
  /// </summary>
  static CLValue U32(uint32_t value) {
    SecByteBlock bytes = CEP57Checksum::Decode(u32Encode(value));

    // TODO: check below for all the other functions
    // if (!BitConverter.IsLittleEndian) Array.Reverse(bytes);

    return CLValue(bytes, CLTypeEnum::U32, value);
  }

  /// <summary>
  /// Returns a `CLValue` object with an UInt64 type.
  /// </summary>
  static CLValue U64(uint64_t value) {
    SecByteBlock bytes = CEP57Checksum::Decode(u64Encode(value));

    return CLValue(bytes, CLTypeEnum::U64, value);
  }

  /// <summary>
  /// Returns a `CLValue` object with an U128 type.
  /// </summary>
  static CLValue U128(big_int value) {
    SecByteBlock bytes = CEP57Checksum::Decode(u128Encode(value));

    return CLValue(bytes, CLTypeEnum::U128, value.toString());
  }

  /// <summary>
  /// Returns a `CLValue` object with an U256 type.
  /// </summary>
  static CLValue U256(big_int value) {
    SecByteBlock bytes = CEP57Checksum::Decode(u256Encode(value));

    return CLValue(bytes, CLTypeEnum::U256, value.toString());
  }

  /// <summary>
  /// Returns a `CLValue` object with an U512 type.
  /// </summary>
  static CLValue U512(big_int value) {
    SecByteBlock bytes = CEP57Checksum::Decode(u512Encode(value));
    return CLValue(bytes, CLTypeEnum::U512, value.toString());
  }

  /// <summary>
  /// Returns a `CLValue` object with an U512 type.
  /// </summary>
  // TODO: Check this func for correctness, compare with net-sdk
  static CLValue U512(uint64_t value) {
    SecByteBlock bytes = CEP57Checksum::Decode(u64Encode(value));

    int nonZeros;
    for (nonZeros = bytes.size(); nonZeros > 0; nonZeros--) {
      if (bytes[nonZeros - 1] != 0x00) {
        break;
      }
    }

    SecByteBlock b(1 + nonZeros);
    b[0] = (byte)nonZeros;
    std::copy(bytes.begin(), bytes.begin() + nonZeros, b.begin() + 1);
    return CLValue(b, CLTypeEnum::U512, std::to_string(value));
  }

  /// <summary>
  /// Returns a `CLValue` object with a Unit type.
  /// </summary>
  static CLValue Unit() {
    // TODO: Check SecByteBlock(), maybe (0), should be empty
    return CLValue(SecByteBlock(), CLTypeEnum::Unit, std::nullptr_t());
  }

  /// <summary>
  /// Returns a `CLValue` object with a String type.
  /// </summary>
  static CLValue String(std::string value) {
    SecByteBlock bytes = CEP57Checksum::Decode(stringEncode(value));

    return CLValue(bytes, CLTypeEnum::String, value);
  }

  /// <summary>
  /// Returns a `CLValue` object with a URef type.
  /// </summary>
  static CLValue URef(std::string value) {
    Casper::URef uref(value);
    SecByteBlock bytes = uref.GetBytes();

    return CLValue(bytes, CLTypeEnum::URef, value);
  }

  /// <summary>
  /// Returns a `CLValue` object with a URef type.
  /// </summary>
  static CLValue URef(Casper::URef value) {
    SecByteBlock bytes = value.GetBytes();

    return CLValue(bytes, CLTypeEnum::URef, value.ToString());
  }

  /// <summary>
  /// Wraps a `CLValue` object into an Option `CLValue`.
  /// </summary>

  static CLValue Option(CLValue innerValue) {
    SecByteBlock bytes(1 + innerValue.bytes.size());
    bytes[0] = 0x01;
    std::copy(innerValue.bytes.begin(), innerValue.bytes.end(),
              bytes.begin() + 1);

    return CLValue(bytes, CLOptionTypeInfo(innerValue.cl_type),
                   innerValue.parsed);
  }

  static CLValue Option(int innerValue) {
    CLValue::Option(CLValue::I32(innerValue));
  }

  static CLValue Option(long innerValue) {
    CLValue::Option(CLValue::I64(innerValue));
  }

  static CLValue Option(byte innerValue) {
    CLValue::Option(CLValue::U8(innerValue));
  }

  static CLValue Option(uint innerValue) {
    CLValue::Option(CLValue::U32(innerValue));
  }

  static CLValue Option(ulong innerValue) {
    CLValue::Option(CLValue::U64(innerValue));
  }

  static CLValue Option(std::string innerValue) {
    CLValue::Option(CLValue::String(innerValue));
  }

  static CLValue Option(Casper::URef innerValue) {
    CLValue::Option(CLValue::URef(innerValue));
  }

  static CLValue Option(PublicKey innerValue) {
    CLValue::Option(CLValue::PublicKey(innerValue));
  }

  static CLValue Option(GlobalStateKey innerValue) {
    CLValue::Option(CLValue::Key(innerValue));
  }

  static CLValue Option(SecByteBlock innerValue) {
    CLValue::Option(CLValue::ByteArray(innerValue));
  }

  static CLValue Option(std::vector<CLValue> innerValue) {
    CLValue::Option(CLValue::List(innerValue));
  }

  static CLValue Option(std::map<CLValue, CLValue> innerValue) {
    CLValue::Option(CLValue::Map(innerValue));
  }

  static CLValue OptionNone(CLTypeInfo innerTypeInfo) {
    SecByteBlock bytes(1);
    bytes[0] = 0x00;

    return CLValue(bytes, CLOptionTypeInfo(innerTypeInfo), std::nullptr_t());
  }

  /// <summary>
  /// Returns a List `CLValue` object.
  /// </summary>

  static CLValue List(std::vector<CLValue> values) {
    if (values.size() == 0) throw std::runtime_error("List cannot be empty");

    SecByteBlock sb;

    SecByteBlock bytes = CEP57Checksum::Decode(u32Encode(values.size()));

    sb += bytes;

    auto typeInfo = values[0].cl_type;

    for (auto value : values) {
      if (value.cl_type != typeInfo) {
        throw std::runtime_error(
            "All elements in a list must be of the same type");
      }

      sb += value.bytes;
    }

    return CLValue(sb, CLListTypeInfo(typeInfo), "");
  }

  /// <summary>
  /// Returns a `CLValue` object with a ByteArray type.
  /// </summary>
  static CLValue ByteArray(SecByteBlock bytes) {
    return CLValue(bytes, CLType(bytes.size()), CryptoUtil::hexEncode(bytes));
  }

  /// <summary>
  /// Returns a `CLValue` object with a ByteArray type.
  /// </summary>
  static CLValue ByteArray(std::string hex_val) {
    SecByteBlock bytes = CryptoUtil::hexDecode(hex_val);

    return CLValue(bytes, CLType(bytes.size()), hex_val);
  }

  /// <summary>
  /// Returns a Result `CLValue` with wrapped OK value inside.
  /// To be complete, it must be indicated the type for an err value
  /// </summary>
  static CLValue Ok(CLValue ok, CLTypeInfo errTypeInfo) {
    var typeInfo = CLResultTypeInfo(ok.TypeInfo, errTypeInfo);
    SecByteBlock bytes(1 + ok.bytes.size());
    bytes[0] = 0x01;
    std::copy(ok.bytes.begin(), ok.bytes.end(), bytes.begin() + 1);

    return CLValue(bytes, typeInfo, std::nullptr_t());
  }

  /// <summary>
  /// Returns a Result `CLValue` with wrapped Err value inside.
  /// To be complete, it must be indicated the type for an ok value
  /// </summary>
  static CLValue Err(CLValue err, CLTypeInfo okTypeInfo) {
    var typeInfo = CLResultTypeInfo(okTypeInfo, err.cl_type);

    SecByteBlock bytes(1 + err.bytes.size());
    bytes[0] = 0x00;
    std::copy(err.bytes.begin(), err.bytes.end(), bytes.begin() + 1);

    return CLValue(bytes, typeInfo, std::nullptr_t());
  }

  /// <summary>
  /// Returns a Map `CLValue` object.
  /// </summary>
  static CLValue Map(std::map<CLValue, CLValue> dict) {
    CLMapTypeInfo mapTypeInfo = null;
    SecByteBlock bytes;

    SecByteBlock len = CEP57Checksum::Decode(u32Encode(dict.size()));

    bytes += len;

    for (auto kv : dict) {
      if (mapTypeInfo == null) {
        mapTypeInfo = CLMapTypeInfo(kv.first.cl_type, kv.second.cl_type);
      } else if (mapTypeInfo.KeyType != kv.first.cl_type ||
                 mapTypeInfo.ValueType != kv.second.cl_type) {
        throw std::runtime_error(
            "All elements in a map must be of the same "
            "type");
      }

      bytes += kv.first.bytes;
      bytes += kv.second.bytes;
    }

    return CLValue(bytes, mapTypeInfo, std::nullptr_t());
  }

  /// <summary>
  /// Returns a Tuple1 `CLValue` object.
  /// </summary>
  static CLValue Tuple1(CLValue t0) {
    return CLValue(t0.bytes, CLTuple1TypeInfo(t0.cl_type), t0.parsed);
  }

  /// <summary>
  /// Returns a Tuple2 `CLValue` object.
  /// </summary>
  static CLValue Tuple2(CLValue t0, CLValue t1) {
    SecByteBlock bytes(t0.bytes.size() + t1.bytes.size());

    std::copy(t0.bytes.begin(), t0.bytes.end(), bytes.begin());

    std::copy(t1.bytes.begin(), t1.bytes.end(),
              bytes.begin() + t0.bytes.size());

    return CLValue(bytes, CLTuple2TypeInfo(t0.cl_type, t1.cl_type),
                   CryptoUtil::hexEncode(bytes));
  }

  /// <summary>
  /// Returns a Tuple3 `CLValue` object.
  /// </summary>
  static CLValue Tuple3(CLValue t0, CLValue t1, CLValue t2) {
    SecByteBlock bytes(t0.bytes.size() + t1.bytes.size() + t2.bytes.size());

    std::copy(t0.bytes.begin(), t0.bytes.end(), bytes.begin());

    std::copy(t1.bytes.begin(), t1.bytes.end(),
              bytes.begin() + t0.bytes.size());

    std::copy(t2.bytes.begin(), t2.bytes.end(),
              bytes.begin() + t0.bytes.size() + t1.bytes.size());

    return CLValue(bytes, CLTuple3TypeInfo(t0.cl_type, t1.cl_type, t2.cl_type),
                   CryptoUtil::hexEncode(bytes));
  }

  /// <summary>
  /// Returns a `CLValue` object with a PublicKey type.
  /// </summary>
  static CLValue PublicKey(Casper::PublicKey publicKey) {
    return CLValue(publicKey.GetBytes(), CLTypeEnum::PublicKey,
                   CryptoUtil::hexEncode(publicKey.GetBytes()));
  }

  /// <summary>
  /// Returns a `CLValue` object with a PublicKey type.
  /// </summary>
  static CLValue PublicKey(SecByteBlock value, KeyAlgo keyAlgorithm) {
    SecByteBlock bytes(1 + value.size());
    bytes[0] = (byte)keyAlgorithm;
    std::copy(value.begin(), value.end(), bytes.begin() + 1);

    return CLValue(bytes, CLTypeEnum::PublicKey, CryptoUtil::hexEncode(bytes));
  }

  /// <summary>
  /// Converts a public key into an account hash an returns it wrapped into a
  /// Key `CLValue`
  /// </summary>
  static CLValue KeyFromPublicKey(Casper::PublicKey publicKey) {
    SecByteBlock accountHash =
        AccountHashKey(publicKey.GetAccountHash()).raw_bytes;
    SecByteBlock bytes(1 + accountHash.size());
    bytes[0] = (byte)KeyIdentifier::ACCOUNT;
    std::copy(accountHash.begin(), accountHash.end(), bytes.begin() + 1);

    // TODO: Check key type info alternative, there is no info in cltype as it
    // is an account key, only it is key
    /*
        return  CLValue(bytes,  CLKeyTypeInfo(KeyIdentifier.Account),
                           Hex.ToHexString(bytes));
                           */

    return CLValue(bytes, CLTypeEnum::Key, CryptoUtil::hexEncode(bytes));
  }

  /// <summary>
  /// Returns a `CLValue` object with a GlobalStateKey in it
  /// </summary>
  static CLValue Key(GlobalStateKey key) {
    auto key_serializer = GlobalStateKeyByteSerializer();

    // TODO: Check key type info alternative, there is no info in cltype as it
    // is an account key, only it is key

    return CLValue(key_serializer.ToBytes(key), CLTypeEnum::Key, key);
  }
};

// to json
inline void to_json(nlohmann::json& j, const CLValue& p) {
  j = nlohmann::json{};

  to_json(j["cl_type"], p.cl_type);

  try {
    std::string tmp_bytes = CEP57Checksum::Encode(p.bytes);
    StringUtil::toLower(tmp_bytes);
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
    StringUtil::toLower(hex_bytes_str);
    p.bytes = CEP57Checksum::Decode(hex_bytes_str);
  } catch (const std::exception& e) {
    std::cout << "CLValue-from_json-bytes what(): " << e.what() << std::endl;
  }

  // std::cout << j.at("parsed").dump(2) << std::endl;

  from_json(j.at("parsed"), p.parsed, p.cl_type);
}

}  // namespace Casper

namespace nlohmann {
template <typename T>
struct adl_serializer<std::map<rva::variant<T>, rva::variant<T>>> {
  static void to_json(json& j, const rva::variant<T>& var) {
    j = to_json(std::get<var.index()>(var));
  }

  static void from_json(const json& j, rva::variant<T>& var) {
    from_json(j, std::get<var.index()>(var));
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