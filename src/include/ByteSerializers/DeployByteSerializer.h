#pragma once

#include "ByteSerializers/DeployApprovalByteSerializer.h"
#include "ByteSerializers/ExecutableDeployItemByteSerializer.h"
#include "Types/Deploy.h"

namespace Casper {
struct DeployByteSerializer : public BaseByteSerializer {
  SecByteBlock ToBytes(DeployHeader source) {
    SecByteBlock bytes;

    WriteBytes(bytes, source.account.GetBytes());

    // WriteULong(bytes, source.timestamp);

    // WriteULong(bytes, source.ttl);

    WriteULong(bytes, source.gas_price);

    WriteBytes(bytes, CEP57Checksum::Decode(source.body_hash));

    WriteInteger(bytes, source.dependencies.size());
    for (auto& dependency : source.dependencies) {
      WriteBytes(bytes, CEP57Checksum::Decode(dependency));
    }

    WriteString(bytes, source.chain_name);

    return bytes;
  }

  SecByteBlock ToBytes(Deploy source) {
    SecByteBlock bytes;

    ExecutableDeployItemByteSerializer itemSerializer;
    DeployApprovalByteSerializer approvalSerializer;

    WriteBytes(bytes, ToBytes(source.header));

    WriteBytes(bytes, CEP57Checksum::Decode(source.hash));

    WriteBytes(bytes, itemSerializer.ToBytes(source.payment));

    WriteBytes(bytes, itemSerializer.ToBytes(source.session));

    // add the approvals
    //
    WriteInteger(bytes, source.approvals.size());
    for (auto& approval : source.approvals) {
      WriteBytes(bytes, approvalSerializer.ToBytes(approval));
    }

    return bytes;
  }
};

}  // namespace Casper