#pragma once

#include "Base.h"
#include "nlohmann/json.hpp"

#include "Types/GlobalStateKey.h"
#include "Types/PublicKey.h"
#include "Types/URef.h"

#include "rva/variant.hpp"
#include <tuple>

#include <unordered_map>
#include <optional>
#include "magic_enum/magic_enum.hpp"
#include "wide-integer/uintwide_t.h"

namespace Casper {

uint64_t strToTimestamp(std::string str);

CBytes hexDecode(std::string hex);

std::string hexEncode(CBytes decoded);

// Encoding && Decoding

bool boolDecode(const std::string& byte_str);

std::string boolEncode(bool val);

int32_t i32Decode(const std::string& byte_str);

std::string i32Encode(int32_t val);

int64_t i64Decode(const std::string& byte_str);

std::string i64Encode(int64_t val);

uint8_t u8Decode(const std::string& byte_str);

std::string u8Encode(uint8_t val);

uint32_t u32Decode(const std::string& byte_str);

std::string u32Encode(uint32_t val);

uint64_t u64Decode(const std::string& byte_str);

std::string u64Encode(uint64_t val);

std::string stringDecode(const std::string& byte_str);

std::string stringEncode(const std::string& val);

GlobalStateKey urefDecode(const std::string& byte_str);

}  // namespace Casper
