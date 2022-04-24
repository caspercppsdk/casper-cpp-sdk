#pragma once

#include "ByteSerializers/BaseByteSerializer.h"
#include "ByteSerializers/CLValueByteSerializer.h"
#include "Types/NamedArg.h"
#include "Utils/StringUtil.h"
namespace Casper {
struct NamedArgByteSerializer : public BaseByteSerializer {
  CBytes ToBytes(NamedArg source) {
    CBytes bytes;
    // std::cout << "NamedArgByteSerializer: " << std::endl;
    CBytes bName =
        hexDecode(StringUtil::getStringBytesWithoutLength(source.name));
    // std::cout << "before write integer len:" << bName.size() << std::endl;
    WriteInteger(bytes, bName.size());
    WriteBytes(bytes, bName);

    // std::cout << "before write clvalue" << std::endl;
    CLValueByteSerializer valueSerializer;
    // std::cout << source.name << std::endl;
    // std::cout << hexEncode(valueSerializer.ToBytes(source.value)) <<
    // std::endl;
    WriteBytes(bytes, valueSerializer.ToBytes(source.value));
    // std::cout << "after write clvalue" << std::endl;
    return bytes;
  }
};

}  // namespace Casper