#pragma once

#include "ByteSerializers/BaseByteSerializer.h"
#include "Types/GlobalStateKey.h"

namespace Casper {
struct GlobalStateKeyByteSerializer : public BaseByteSerializer {
  SecByteBlock ToBytes(GlobalStateKey& source) {
    SecByteBlock bytes;

    WriteByte(bytes, (byte)source.key_identifier);

    WriteBytes(bytes, source.raw_bytes);

    if (source.ToString().find("uref-") != std::string::npos) {
      URef uref(source.ToString());
      WriteByte(bytes, (byte)uref.access_rights);
    }

    return bytes;
  }
};

}  // namespace Casper