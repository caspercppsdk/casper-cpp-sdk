#pragma once

#include "CasperClient.h"
#include "Types/GlobalStateKey.h"
#include "Types/PublicKey.h"
#include "Utils/CryptoUtil.h"
#include <sstream>
#include "Types/CLType.h"
#include "Types/CLConverter.h"

#include "ByteSerializers/DeployByteSerializer.h"
namespace Casper
{

void DeployItem_ByteSer_ModuleBytes_Test(void);

void DeployItem_ByteSer_StoredContractByHash_Test(void);

void DeployItem_ByteSer_StoredContractByName_Test(void);

void DeployItem_ByteSer_StoredVersionedContractByHash_Test(void);

void DeployItem_ByteSer_StoredVersionedContractByName_Test(void);

void DeployItem_ByteSer_Transfer_Test(void);

} // namespace Casper