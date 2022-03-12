#pragma once

#include "Base.h"
#include "Types/CLTypeInfo.h"
#include "nlohmann/json.hpp"

namespace Casper {
/// <summary>
/// Casper types, i.e. types which can be stored and manipulated by smart
/// contracts. Provides a description of the underlying data type of a
/// `CLValue`.
/// </summary>

struct CLType {
  std::optional<CLTypeInfo> type_info = std::nullopt;
  std::optional<CLMapTypeInfo> map_type_info = std::nullopt;
  std::optional<CLOptionTypeInfo> option_type_info = std::nullopt;
  std::optional<CLListTypeInfo> list_type_info = std::nullopt;
  std::optional<CLByteArrayTypeInfo> byte_array_type_info = std::nullopt;
  std::optional<CLResultTypeInfo> result_type_info = std::nullopt;
  std::optional<CLTuple1TypeInfo> tuple1_type_info = std::nullopt;
  std::optional<CLTuple2TypeInfo> tuple2_type_info = std::nullopt;
  std::optional<CLTuple3TypeInfo> tuple3_type_info = std::nullopt;

  operator CLTypeEnum() const { return CLTypeEnum::Map; }

  CLType() {}
};

// to_json of CLType
inline void to_json(nlohmann::json& j, const CLType& p) {
  j = nlohmann::json{};

  if (p.type_info.has_value()) {
    j = p.type_info.value();
  } else if (p.map_type_info.has_value()) {
    j["Map"] = p.map_type_info.value();
  } else if (p.option_type_info.has_value()) {
    j["Option"] = p.option_type_info.value();
  } else if (p.list_type_info.has_value()) {
    j["List"] = p.list_type_info.value();
  } else if (p.byte_array_type_info.has_value()) {
    j["ByteArray"] = p.byte_array_type_info.value();
  } else if (p.result_type_info.has_value()) {
    j["Result"] = p.result_type_info.value();
  } else if (p.tuple1_type_info.has_value()) {
    j["Tuple1"] = p.tuple1_type_info.value();
  } else if (p.tuple2_type_info.has_value()) {
    j["Tuple2"] = p.tuple2_type_info.value();
  } else if (p.tuple3_type_info.has_value()) {
    j["Tuple3"] = p.tuple3_type_info.value();
  }
}

// from_json of CLType
inline void from_json(const nlohmann::json& j, CLType& p) {
  if (j.find("Map") != j.end()) {
    p.map_type_info = j.at("Map").get<CLMapTypeInfo>();
  } else if (j.find("Option") != j.end()) {
    p.option_type_info = j.at("Option").get<CLOptionTypeInfo>();
  } else if (j.find("List") != j.end()) {
    p.list_type_info = j.at("List").get<CLListTypeInfo>();
  } else if (j.find("ByteArray") != j.end()) {
    p.byte_array_type_info = j.at("ByteArray").get<CLByteArrayTypeInfo>();
  } else if (j.find("Result") != j.end()) {
    p.result_type_info = j.at("Result").get<CLResultTypeInfo>();
  } else if (j.find("Tuple1") != j.end()) {
    p.tuple1_type_info = j.at("Tuple1").get<CLTuple1TypeInfo>();
  } else if (j.find("Tuple2") != j.end()) {
    p.tuple2_type_info = j.at("Tuple2").get<CLTuple2TypeInfo>();
  } else if (j.find("Tuple3") != j.end()) {
    p.tuple3_type_info = j.at("Tuple3").get<CLTuple3TypeInfo>();
  } else if (j.is_string()) {
    j.get_to(p.type_info);
  }
}

}  // namespace Casper
