#pragma once

#include "ByteSerializers/BaseByteSerializer.h"
#include "ByteSerializers/CLValueByteSerializer.h"
#include "Types/NamedArg.h"
#include "Utils/StringUtil.h"
namespace Casper {
struct NamedArgByteSerializer : public BaseByteSerializer {
  CBytes ToBytes(NamedArg source) {
    CBytes bytes;
    CBytes bName = hexDecode(StringUtil::getStringBytesWithoutLength(source.name));
    WriteInteger(bytes, bName.size());
    WriteBytes(bytes, bName);
    CLValueByteSerializer valueSerializer;
    WriteBytes(bytes, valueSerializer.ToBytes(source.value));
    return bytes;
  }
};

}  // namespace Casper