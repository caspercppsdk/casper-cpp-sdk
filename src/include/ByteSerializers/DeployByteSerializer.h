#pragma once

#include "ByteSerializers/DeployApprovalByteSerializer.h"
#include "ByteSerializers/ExecutableDeployItemByteSerializer.h"
#include "Types/Deploy.h"
#include "date/date.h"
#include <chrono>
namespace Casper {
struct DeployByteSerializer : public BaseByteSerializer {
  CBytes ToBytes(DeployHeader source) {
    CBytes bytes;

    WriteBytes(bytes, source.account.GetBytes());
    // std::cout << "acc:" << hexEncode(source.account.GetBytes()) << std::endl;
    //  replace with source.timestamp
    /*
    std::chrono::milliseconds timestmp =
        std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::system_clock::now().time_since_epoch());
    */
    uint64_t ttp = strToTimestamp(source.timestamp);
    WriteULong(bytes, ttp);
    //  TODO: Create date util, use it with source.ttl
    WriteULong(bytes, 1800000);
    WriteULong(bytes, source.gas_price);
    WriteBytes(bytes, hexDecode(source.body_hash));
    WriteInteger(bytes, source.dependencies.size());
    for (auto& dependency : source.dependencies) {
      WriteBytes(bytes, hexDecode(dependency));
    }

    WriteString(bytes, source.chain_name);
    return bytes;
  }

  CBytes ToBytes(Deploy source) {
    CBytes bytes;

    ExecutableDeployItemByteSerializer itemSerializer;
    DeployApprovalByteSerializer approvalSerializer;

    WriteBytes(bytes, ToBytes(source.header));
    WriteBytes(bytes, hexDecode(source.hash));
    WriteBytes(bytes, itemSerializer.ToBytes(source.payment));
    WriteBytes(bytes, itemSerializer.ToBytes(source.session));

    // add the approvals
    WriteInteger(bytes, source.approvals.size());
    for (auto& approval : source.approvals) {
      WriteBytes(bytes, approvalSerializer.ToBytes(approval));
    }

    return bytes;
  }
};

}  // namespace Casper