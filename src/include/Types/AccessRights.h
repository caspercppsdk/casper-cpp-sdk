#pragma once
#include <cstdint>

#include "magic_enum/magic_enum.hpp"
#include "nlohmann/json.hpp"

namespace Casper {
/**
 * @brief The access rights of an account as a binary value enum.
 *
 */
enum struct AccessRights : uint8_t {
  /// <summary>
  /// No permissions
  /// </summary>
  NONE = 0b000,
  /// <summary>
  /// Permission to read the value under the associated URef.
  /// </summary>
  READ = 0b001,
  /// <summary>
  /// Permission to write a value under the associated URef.
  /// </summary>
  WRITE = 0b010,
  /// <summary>
  /// Permission to add to the value under the associated URef.
  /// </summary>
  ADD = 0b100,
  /// <summary>
  /// Permission to read or write the value under the associated URef.
  /// </summary>
  READ_WRITE = 0b011,
  /// <summary>
  /// Permission to read or add to the value under the associated URef.
  /// </summary>
  READ_ADD = 0b101,
  /// <summary>
  /// Permission to add to, or write the value under the associated URef.
  /// </summary>
  ADD_WRITE = 0b110,
  /// <summary>
  /// Permission to read, add to, or write the value under the associated URef.
  /// </summary>
  READ_ADD_WRITE = 0b111
};

// to_json of AccessRights
inline void to_json(nlohmann::json& j, const AccessRights& p) {
  j = nlohmann::json{{"access_rights", magic_enum::enum_name(p)}};
}

// from_json of AccessRights
// inline void from_json(const nlohmann::json& j, AccessRights& p) {
//    Not implemented
// }

}  // namespace Casper
