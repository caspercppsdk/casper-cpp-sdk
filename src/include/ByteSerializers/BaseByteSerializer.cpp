#include "ByteSerializers/BaseByteSerializer.h"

namespace Casper {

void BaseByteSerializer::WriteInteger(SecByteBlock& sb, int value) {
  SecByteBlock bytes = hexDecode(i32Encode(value));
  //    if (!BitConverter.IsLittleEndian) Array.Reverse(bytes);

  sb += bytes;
}

void BaseByteSerializer::WriteUInteger(SecByteBlock& sb, uint32_t value) {
  SecByteBlock bytes = hexDecode(u32Encode(value));
  //    if (!BitConverter.IsLittleEndian) Array.Reverse(bytes);

  sb += bytes;
}

void BaseByteSerializer::WriteULong(SecByteBlock& sb, uint64_t value) {
  SecByteBlock bytes = hexDecode(u64Encode(value));
  //    if (!BitConverter.IsLittleEndian) Array.Reverse(bytes);

  sb += bytes;
}

void BaseByteSerializer::WriteByte(SecByteBlock& sb, uint8_t value) {
  std::cout << "byte write u8: " << u8Encode(value) << std::endl;
  SecByteBlock bytes = hexDecode(u8Encode(value));
  sb += bytes;
}

void BaseByteSerializer::WriteBytes(SecByteBlock& sb,
                                    std::vector<uint8_t> value) {
  // TODO: CHECK BELOW!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
  SecByteBlock bytes(value.size());
  for (size_t i = 0; i < value.size(); i++) {
    bytes[i] = value[i];
  }
  sb += bytes;
}

void BaseByteSerializer::WriteBytes(SecByteBlock& sb, SecByteBlock value) {
  sb += value;
}

void BaseByteSerializer::WriteString(SecByteBlock& sb, std::string value) {
  SecByteBlock bytes = hexDecode(stringEncode(value));
  //    if (!BitConverter.IsLittleEndian) Array.Reverse(bytes);

  sb += bytes;
}

}  // namespace Casper
