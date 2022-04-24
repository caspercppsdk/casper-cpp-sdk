#pragma once
#include "Base.h"

#include "Types/CLConverter.h"
#include "Utils/CryptoUtil.h"
#include "Utils/CEP57Checksum.h"

namespace Casper {

class BaseByteSerializer {
 protected:
  static void WriteInteger(CBytes& sb, int value);

  static void WriteUInteger(CBytes& sb, uint32_t value);

  static void WriteULong(CBytes& sb, uint64_t value);

  static void WriteByte(CBytes& sb, uint8_t value);

  static void WriteBytes(CBytes& sb,  std::vector<uint8_t> value);

  static void WriteBytes(CBytes& sb,  CBytes value);

  static void WriteString(CBytes& sb, std::string value);
};

}  // namespace Casper
