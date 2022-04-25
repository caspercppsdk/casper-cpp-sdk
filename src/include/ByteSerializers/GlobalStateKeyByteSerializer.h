#pragma once

#include "ByteSerializers/BaseByteSerializer.h"
#include "Types/GlobalStateKey.h"

namespace Casper {
struct GlobalStateKeyByteSerializer : public BaseByteSerializer {
  CBytes ToBytes(GlobalStateKey& source) {
    CBytes bytes;

    WriteByte(bytes, (CryptoPP::byte)source.key_identifier);

    WriteBytes(bytes, source.raw_bytes);

    if (source.ToString().find("uref-") != std::string::npos) {
      URef uref(source.ToString());
      WriteByte(bytes, (CryptoPP::byte)uref.access_rights);
    }

    return bytes;
  }
};

}  // namespace Casper