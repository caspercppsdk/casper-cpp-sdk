#pragma once
#include "Base.h"

// external
#include "nlohmann/json.hpp"
//
#include "magic_enum/magic_enum.hpp"

// types
#include "Types/CLType.h"

namespace Casper {
/// <summary>
/// Access control options for a contract entry point (method).
/// </summary>

struct EntryPointAccess {
  /// <summary>
  /// When public, anyone can call this method (no access controls).
  /// </summary>

  bool is_public;

  /// <summary>
  /// Only users from the listed groups may call this method.
  /// Note: if the list is empty then this method is not callable from outside
  /// the contract.
  /// </summary>

  std::vector<std::string> groups;

  EntryPointAccess() {}
};

/**
 * @brief Construct a JSON object from a EntryPointAccess object.
 *
 * @param j JSON object to construct.
 * @param p EntryPointAccess object to construct from.
 */
inline void to_json(nlohmann::json& j, const EntryPointAccess& p) {
  // NOT IMPLEMENTED
}

/**
 * @brief Construct a EntryPointAccess object from a JSON object.
 *
 * @param j JSON object to construct the object from.
 * @param p EntryPointAccess object to construct.
 */
inline void from_json(const nlohmann::json& j, EntryPointAccess& p) {
  if (j.count("Public") != 0) {
    p.is_public = true;
  } else if (j.count("Groups") != 0) {
    p.groups = j.at("Groups").get<std::vector<std::string>>();
  }
}

/// <summary>
/// Defines whether the code runs in the contract's or the session
/// context.
/// </summary>
enum class EntryPointType {
  /// <summary>
  /// Runs as session code
  /// </summary>
  Session,
  /// <summary>
  /// Runs within contract’s context
  /// </summary>
  Contract
};

// to_json of EntryPointType
inline void to_json(nlohmann::json& j, const EntryPointType& p) {
  j = {{magic_enum::enum_name(p)}};
}

// from_json of EntryPointType
inline void from_json(const nlohmann::json& j, EntryPointType& p) {
  if (j.get<std::string>() == "Session") {
    p = EntryPointType::Session;
  } else if (j.get<std::string>() == "Contract") {
    p = EntryPointType::Contract;
  } else {
    throw std::runtime_error("Invalid EntryPointType");
  }
}

/// <summary>
/// Parameter to a method
/// </summary>
struct Parameter {
  /// <summary>
  /// The name of the parameter in the entry point.
  /// </summary>
  std::string name;

  /// <summary>
  /// The type of the parameter in the entry point.
  /// </summary>
  CLType cl_type;

  Parameter() {}
};

/**
 * @brief Construct a JSON object from a Parameter object.
 *
 * @param j JSON object to construct.
 * @param p Parameter object to construct from.
 */
inline void to_json(nlohmann::json& j, const Parameter& p) {
  j = {{"name", p.name}};
  // std::cout << "parameter to_json" << std::endl;
  to_json(j["cl_type"], p.cl_type);
  // std::cout << "parameter to_json end" << std::endl;
}

/**
 * @brief Construct a Parameter object from a JSON object.
 *
 * @param j JSON object to construct the object from.
 * @param p Parameter object to construct.
 */
inline void from_json(const nlohmann::json& j, Parameter& p) {
  j.at("name").get_to(p.name);
  // std::cout << "parameter from_json" << std::endl;
  from_json(j.at("cl_type"), p.cl_type);

  // std::cout << "parameter from_json end" << std::endl;
}

/// <summary>
/// Type signature of a method. Order of arguments matter since can be
/// referenced by index as well as name.
/// </summary>
struct EntryPoint {
  /// <summary>
  /// Access control options for a contract entry point
  /// </summary>
  EntryPointAccess access;

  /// <summary>
  /// List of input parameters to the method. Order of arguments matter
  /// since can be referenced by index as well as name.
  /// </summary>
  std::vector<Parameter> args;

  /// <summary>
  /// Context of method execution
  /// </summary>
  EntryPointType entry_point_type;

  /// <summary>
  /// Name of the entry point
  /// </summary>
  std::string name;

  /// <summary>
  /// Returned value
  /// </summary>
  CLType ret;

  EntryPoint() {}
};

/**
 * @brief Construct a JSON object from a EntryPoint object.
 *
 * @param j JSON object to construct.
 * @param p EntryPoint object to construct from.
 */
inline void to_json(nlohmann::json& j, const EntryPoint& p) {
  j = {{"access", p.access},
       {"args", p.args},
       {"entry_point_type", p.entry_point_type},
       {"name", p.name}};
  to_json(j["ret"], p.ret);
}

/**
 * @brief Construct a EntryPoint object from a JSON object.
 *
 * @param j JSON object to construct the object from.
 * @param p EntryPoint object to construct.
 */
inline void from_json(const nlohmann::json& j, EntryPoint& p) {
  j.at("access").get_to(p.access);
  j.at("args").get_to(p.args);
  j.at("entry_point_type").get_to(p.entry_point_type);
  j.at("name").get_to(p.name);
  from_json(j.at("ret"), p.ret);
}
}  // namespace Casper
