#include "Types/CLValue.h"

namespace Casper {

bool CLValue::operator<(const CLValue& b) const {
  if (this->bytes.size() < b.bytes.size()) {
    return true;
  } else if (this->cl_type.type.which() < b.cl_type.type.which()) {
    return true;
  } else if (parsed.parsed.which() < b.parsed.parsed.which()) {
    return true;
  } else if (bytes.data() < b.bytes.data()) {
    return true;
  } else {
    if (cl_type.type.which() == 0) {
      CLTypeEnum type = boost::get<CLTypeEnum>(cl_type.type);

      switch (type) {
        case CLTypeEnum::Bool:
          return boost::get<bool>(parsed.parsed) <
                 boost::get<bool>(b.parsed.parsed);
        case CLTypeEnum::I32:
          return boost::get<int32_t>(parsed.parsed) <
                 boost::get<int32_t>(b.parsed.parsed);
        case CLTypeEnum::I64:
          return boost::get<int64_t>(parsed.parsed) <
                 boost::get<int64_t>(b.parsed.parsed);
        case CLTypeEnum::U8:
          return boost::get<uint8_t>(parsed.parsed) <
                 boost::get<uint8_t>(b.parsed.parsed);
        case CLTypeEnum::U32:
          return boost::get<uint32_t>(parsed.parsed) <
                 boost::get<uint32_t>(b.parsed.parsed);
        case CLTypeEnum::U64:
          return boost::get<uint64_t>(parsed.parsed) <
                 boost::get<uint64_t>(b.parsed.parsed);
        case CLTypeEnum::U128:
          return boost::get<uint128_t>(parsed.parsed) <
                 boost::get<uint128_t>(b.parsed.parsed);
        case CLTypeEnum::U256:
          return boost::get<uint256_t>(parsed.parsed) <
                 boost::get<uint256_t>(b.parsed.parsed);
        case CLTypeEnum::U512:
          return boost::get<uint512_t>(parsed.parsed) <
                 boost::get<uint512_t>(b.parsed.parsed);
        case CLTypeEnum::Unit:
          return true;
        case CLTypeEnum::String:
          return boost::get<std::string>(parsed.parsed) <
                 boost::get<std::string>(b.parsed.parsed);
        case CLTypeEnum::Key:
          return boost::get<GlobalStateKey>(parsed.parsed).key <
                 boost::get<GlobalStateKey>(b.parsed.parsed).key;
        case CLTypeEnum::URef:
          return boost::get<Casper::URef>(parsed.parsed) <
                 boost::get<Casper::URef>(b.parsed.parsed);

        default:
          return false;
      }
    }
    // TODO: Implement CLValue comparison for other types.
  }

  return false;
}

}  // namespace Casper