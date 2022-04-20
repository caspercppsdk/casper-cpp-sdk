#pragma once
#include "Base.h"

#include "Types/CLTypeParsedConverter.h"
#include "Utils/CryptoUtil.h"
#include "Utils/CEP57Checksum.h"

namespace Casper {

class BaseByteSerializer {
 protected:
  static void WriteInteger(SecByteBlock& sb, int value);

  static void WriteUInteger(SecByteBlock& sb, uint32_t value);

  static void WriteULong(SecByteBlock& sb, uint64_t value);

  static void WriteByte(SecByteBlock& sb, uint8_t value);

  static void WriteBytes(SecByteBlock& sb, const std::vector<uint8_t>& value);

  static void WriteBytes(SecByteBlock& sb, const SecByteBlock& value);

  static void WriteString(SecByteBlock& sb, std::string value);
};

}  // namespace Casper
