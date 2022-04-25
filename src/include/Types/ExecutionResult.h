#pragma once

#include "Base.h"
#include "Types/ExecutionEffect.h"
#include "nlohmann/json.hpp"

namespace Casper {

/// <summary>
/// The failure result of executing a single deploy.
/// </summary>
struct ExecutionResultFailure {
  /// <summary>
  /// The effect of executing the deploy.
  /// </summary>
  ExecutionEffect effect;

  // TODOMS3: Make TransferKey instead of std::string
  /// <summary>
  /// A record of Transfers performed while executing the deploy.
  /// </summary>
  std::vector<std::string> transfers;

  /// <summary>
  /// The cost of executing the deploy.
  /// </summary>
  uint512_t cost;

  /// <summary>
  /// The error message associated with executing the deploy.
  /// </summary>
  std::string error_message;

  ExecutionResultFailure() {}
};

// to_json of ExecutionResultFailure
inline void to_json(nlohmann::json& j, const ExecutionResultFailure& p) {
  j = nlohmann::json{{"effect", p.effect},
                     {"transfers", p.transfers},
                     {"cost", p.cost},
                     {"error_message", p.error_message}};
}

// from_json of ExecutionResultFailure
inline void from_json(const nlohmann::json& j, ExecutionResultFailure& p) {
  j.at("effect").get_to(p.effect);
  j.at("transfers").get_to(p.transfers);
  j.at("cost").get_to(p.cost);
  j.at("error_message").get_to(p.error_message);
}

/// <summary>
/// The success result of executing a single deploy.
/// </summary>
struct ExecutionResultSuccess {
  /// <summary>
  /// The effect of executing the deploy.
  /// </summary>
  ExecutionEffect effect;

  // TODOMS3: Make TransferKey instead of std::string
  /// <summary>
  /// A record of Transfers performed while executing the deploy.
  /// </summary>
  std::vector<std::string> transfers;

  /// <summary>
  /// The cost of executing the deploy.
  /// </summary>
  uint512_t cost;

  ExecutionResultSuccess() {}
};

// to_json of ExecutionResultSuccess
inline void to_json(nlohmann::json& j, const ExecutionResultSuccess& p) {
  j = nlohmann::json{
      {"effect", p.effect}, {"transfers", p.transfers}, {"cost", p.cost}};
}

// from_json of ExecutionResultSuccess
inline void from_json(const nlohmann::json& j, ExecutionResultSuccess& p) {
  j.at("effect").get_to(p.effect);
  j.at("transfers").get_to(p.transfers);
  j.at("cost").get_to(p.cost);
}

/// <summary>
/// The result of executing a single deploy.
/// </summary>
struct ExecutionResult {
  /// <summary>
  /// Failure result of executing the deploy.
  /// </summary>
  std::optional<ExecutionResultFailure> failure = std::nullopt;

  /// <summary>
  /// Success result of executing the deploy.
  /// </summary>
  std::optional<ExecutionResultSuccess> success = std::nullopt;

  /// <summary>
  /// The block hash.
  /// </summary>
  std::string block_hash;

  ExecutionResult() {}
};

// to_json of ExecutionResult
inline void to_json(nlohmann::json& j, const ExecutionResult& p) {
  nlohmann::json result;
  if (p.failure.has_value()) {
    result = nlohmann::json{{"Failure", p.failure.value()}};
  } else if (p.success.has_value()) {
    result = nlohmann::json{{"Success", p.success.value()}};
  }
  j = nlohmann::json{{"result", result}, {"block_hash", p.block_hash}};
}

// from_json of ExecutionResult
inline void from_json(const nlohmann::json& j, ExecutionResult& p) {
  if (j.at("result").find("Success") != j.at("result").end()) {
    p.success = j.at("result").at("Success").get<ExecutionResultSuccess>();
  } else if (j.at("result").find("Failure") != j.at("result").end()) {
    p.failure = j.at("result").at("Failure").get<ExecutionResultFailure>();
  }

  j.at("block_hash").get_to(p.block_hash);
}

}  // namespace Casper
