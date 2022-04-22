#pragma once

#include "ByteSerializers/BaseByteSerializer.h"
#include "ByteSerializers/CLValueByteSerializer.h"
#include "Types/NamedArg.h"

namespace Casper {
struct NamedArgByteSerializer : public BaseByteSerializer {
  SecByteBlock ToBytes(NamedArg source) {
    SecByteBlock bytes;
    std::cout << "NamedArgByteSerializer: " << std::endl;
    SecByteBlock bName = hexDecode(stringEncode(source.name));
    std::cout << "before write integer" << std::endl;
    WriteInteger(bytes, bName.size());
    WriteBytes(bytes, bName);

    std::cout << "before write clvalue" << std::endl;
    CLValueByteSerializer valueSerializer;
    WriteBytes(bytes, valueSerializer.ToBytes(source.value));
    std::cout << "after write clvalue" << std::endl;
    return bytes;
  }
};

}  // namespace Casper