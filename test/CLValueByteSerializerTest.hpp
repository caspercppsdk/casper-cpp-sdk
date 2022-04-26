#pragma once

#include "CasperClient.h"
#include "Types/GlobalStateKey.h"
#include "Types/PublicKey.h"
#include "Utils/CryptoUtil.h"
#include <sstream>
#include "Types/CLType.h"
#include "Types/CLConverter.h"

#include "ByteSerializers/DeployByteSerializer.h"
namespace Casper {

/// Bool Byte Serialization
void CLValue_ByteSer_Bool_Test(void);

void CLValue_ByteSer_I32_Test(void);

void CLValue_ByteSer_I64_Test(void);

void CLValue_ByteSer_U8_Test(void);

void CLValue_ByteSer_U32_Test(void);

void CLValue_ByteSer_U64_Test(void);

void CLValue_ByteSer_U128_Test(void);

void CLValue_ByteSer_U256_Test(void);

void CLValue_ByteSer_U512_Test(void);

void CLValue_ByteSer_Unit_Test(void);

void CLValue_ByteSer_String_Test(void);

void CLValue_ByteSer_URef_Test(void);

void CLValue_ByteSer_Key_Test(void);

void CLValue_ByteSer_PublicKey_Test(void);

void CLValue_ByteSer_Option_Test(void);

void CLValue_ByteSer_List_Test(void);

void CLValue_ByteSer_ByteArray_Test(void);

void CLValue_ByteSer_Result_Test(void);

void CLValue_ByteSer_Map_Test(void);

void CLValue_ByteSer_Tuple1_Test(void);

void CLValue_ByteSer_Tuple2_Test(void);

void CLValue_ByteSer_Tuple3_Test(void);

void CLValue_ByteSer_Any_Test(void);
}  // namespace Casper