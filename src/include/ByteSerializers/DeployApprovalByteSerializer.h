#pragma once

#include "ByteSerializers/BaseByteSerializer.h"
#include "Types/DeployApproval.h"

namespace Casper {
struct DeployApprovalByteSerializer : public BaseByteSerializer {
  SecByteBlock ToBytes(DeployApproval& source) {
    SecByteBlock bytes;
    WriteBytes(bytes, source.signer.GetBytes());
    WriteBytes(bytes, source.signature.GetBytes());
    return bytes;
  }
};

}  // namespace Casper