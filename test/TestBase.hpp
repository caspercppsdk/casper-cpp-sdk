#pragma once

#include <gtest/gtest.h>

#include "CasperClient.h"

#include "Types/CLConverter.h"
#include "Types/CLType.h"
#include "Types/GlobalStateKey.h"
#include "Types/PublicKey.h"

#include "Utils/CryptoUtil.h"
#include "Utils/StringUtil.h"

template <typename StringT1, typename StringT2> inline bool cmpStr(const StringT1& str1, const StringT2& str2)
{
    return Casper::StringUtil::toLower(str1) == Casper::StringUtil::toLower(str2);
}