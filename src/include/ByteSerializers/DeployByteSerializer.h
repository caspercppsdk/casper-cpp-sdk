#pragma once

#include "ByteSerializers/DeployApprovalByteSerializer.h"
#include "ByteSerializers/ExecutableDeployItemByteSerializer.h"
#include "Types/Deploy.h"
#include "date/date.h"
#include <chrono>
namespace Casper {
struct DeployByteSerializer : public BaseByteSerializer {
  SecByteBlock ToBytes(DeployHeader source) {
    SecByteBlock bytes;

    WriteBytes(bytes, source.account.GetBytes());

    // replace with source.timestamp
    /*
    std::chrono::milliseconds timestmp =
        std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::system_clock::now().time_since_epoch());
*/
    using namespace date;

    std::istringstream infile{source.timestamp};

    sys_seconds tp;  // This is a system_clock time_point with seconds precision
    infile >> parse("%FT%T", tp);
    std::stringstream ss;
    ss << tp.time_since_epoch().count();
    std::string ts_str = ss.str();

    std::istringstream ss2{ts_str};
    uint64_t timest;
    ss2 >> timest;
    timest *= 1000;
    WriteULong(bytes, timest);
    std::cout << "Timestamp " << timest << std::endl;

    // TODO: Create date util, use it with source.ttl
    WriteULong(bytes, 1800000);

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