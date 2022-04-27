#include "Types/CLValue.h"

namespace Casper {

bool CLValue::operator<(const CLValue& b) const {
  if (this->bytes.size() < b.bytes.size()) {
    return true;
  } else if (this->cl_type.type.index() < b.cl_type.type.index()) {
    return true;
  } else if (parsed.parsed.index() < b.parsed.parsed.index()) {
    return true;
  } else if (bytes.data() < b.bytes.data()) {
    return true;
  } else {
    if (cl_type.type.index() == 0) {
      CLTypeEnum type = std::get<CLTypeEnum>(cl_type.type);

      switch (type) {
        case CLTypeEnum::Bool:
          return std::get<bool>(parsed.parsed) <
                 std::get<bool>(b.parsed.parsed);
        case CLTypeEnum::I32:
          return std::get<int32_t>(parsed.parsed) <
                 std::get<int32_t>(b.parsed.parsed);
        case CLTypeEnum::I64:
          return std::get<int64_t>(parsed.parsed) <
                 std::get<int64_t>(b.parsed.parsed);
        case CLTypeEnum::U8:
          return std::get<uint8_t>(parsed.parsed) <
                 std::get<uint8_t>(b.parsed.parsed);
        case CLTypeEnum::U32:
          return std::get<uint32_t>(parsed.parsed) <
                 std::get<uint32_t>(b.parsed.parsed);
        case CLTypeEnum::U64:
          return std::get<uint64_t>(parsed.parsed) <
                 std::get<uint64_t>(b.parsed.parsed);
        case CLTypeEnum::U128:
          return std::get<uint128_t>(parsed.parsed) <
                 std::get<uint128_t>(b.parsed.parsed);
        case CLTypeEnum::U256:
          return std::get<uint256_t>(parsed.parsed) <
                 std::get<uint256_t>(b.parsed.parsed);
        case CLTypeEnum::U512:
          return std::get<uint512_t>(parsed.parsed) <
                 std::get<uint512_t>(b.parsed.parsed);
        case CLTypeEnum::Unit:
          return true;
        case CLTypeEnum::String:
          return std::get<std::string>(parsed.parsed) <
                 std::get<std::string>(b.parsed.parsed);
        case CLTypeEnum::Key:
          return std::get<GlobalStateKey>(parsed.parsed).key <
                 std::get<GlobalStateKey>(b.parsed.parsed).key;
        case CLTypeEnum::URef:
          return std::get<Casper::URef>(parsed.parsed) <
                 std::get<Casper::URef>(b.parsed.parsed);

        default:
          return false;
      }
    }
    // TODO: Implement CLValue comparison for other types.
  }
}

}  // namespace Casper