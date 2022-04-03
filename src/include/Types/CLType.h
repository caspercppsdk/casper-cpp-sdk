#pragma once

#include "Base.h"
#include "Types/CLTypeInfo.h"
#include "nlohmann/json.hpp"
#include "Types/Definitions.h"
#include "Types/GlobalStateKey.h"
#include "Types/PublicKey.h"
#include "Types/URef.h"

#include <rva/variant.hpp>

namespace Casper {
/// <summary>
/// Casper types, i.e. types which can be stored and manipulated by smart
/// contracts. Provides a description of the underlying data type of a
/// `CLValue`.
/// </summary>
/*
 Bool,
    I32,
    I64,
    U8,
    U32,
    U64,
    U128,
    U256,-
    U512,-
    Unit,-
    String,
    Key,
    URef,
    PublicKey,
    Option(Box<CLType>),
    List(Box<CLType>),
    ByteArray(u32),
    Result {
        ok: Box<CLType>,
        err: Box<CLType>,
    },
    Map {
        key: Box<CLType>,
        value: Box<CLType>,
    },
    Tuple1([Box<CLType>; 1]),
    Tuple2([Box<CLType>; 2]),
    Tuple3([Box<CLType>; 3]),
    Any,
*/
using CLType = rva::variant<bool,            // Bool
                            int32_t,         // I32
                            int64_t,         // I64
                            uint8_t,         // U8
                            uint32_t,        // U32
                            uint64_t,        // U64
                            big_int,         // U128
                            big_int,         // U256
                            big_int,         // U512
                            std::string,     // Unit
                            std::string,     // String
                            GlobalStateKey,  // Key
                            URef,            // URef

                            PublicKey,  // PublicKey
                            // std::optional<rva::self_t>,  // Option
                            std::vector<uint32_t>,
                            std::vector<rva::self_t>  // List
                                                      // ByteArray
                                                      // Result
                                                      // Map
                                                      // Tuple1
                                                      // Tuple2
                                                      // Tuple3
                                                      // Any
                            >;
// std::string,                         // json string
// std::map<std::string, rva::self_t>,  // json object, type is
//  std::map<std::string, CLType>
// std::vector<rva::self_t>>;  // json array, type is std::vector<CLType>

// to_json of CLType
inline void to_json(nlohmann::json& j, const CLType& p) {
  if (std::string(typeid(p).name()).find("std::string") != std::string::npos) {
    j = p;
  }
}

// from_json of CLType
inline void from_json(const nlohmann::json& j, CLType& p) {
  if (j.is_string()) {
    std::string type_name = j.get<std::string>();
    p.emplace<10>(type_name);
  }
}

}  // namespace Casper
