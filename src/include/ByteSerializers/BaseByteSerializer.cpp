#include "ByteSerializers/BaseByteSerializer.h"

namespace Casper {

void BaseByteSerializer::WriteInteger(CBytes& sb, int value) {
  CBytes bytes = hexDecode(i32Encode(value));
  //    if (!BitConverter.IsLittleEndian) Array.Reverse(bytes);

  sb += bytes;
}

void BaseByteSerializer::WriteUInteger(CBytes& sb, uint32_t value) {
  CBytes bytes = hexDecode(u32Encode(value));
  //    if (!BitConverter.IsLittleEndian) Array.Reverse(bytes);

  sb += bytes;
}

void BaseByteSerializer::WriteULong(CBytes& sb, uint64_t value) {
  CBytes bytes = hexDecode(u64Encode(value));
  //    if (!BitConverter.IsLittleEndian) Array.Reverse(bytes);

  sb += bytes;
}

void BaseByteSerializer::WriteByte(CBytes& sb, uint8_t value) {
  // std::cout << "byte write u8: " << u8Encode(value) << std::endl;
  CBytes bytes = hexDecode(u8Encode(value));
  sb += bytes;
}

void BaseByteSerializer::WriteBytes(CBytes& sb, std::vector<uint8_t> value) {
  // TODO: CHECK BELOW!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
  CBytes bytes(value.size());
  for (size_t i = 0; i < value.size(); i++) {
    bytes[i] = value[i];
  }
  sb += bytes;
}

void BaseByteSerializer::WriteBytes(CBytes& sb, CBytes value) { sb += value; }

void BaseByteSerializer::WriteString(CBytes& sb, std::string value) {
  CBytes bytes = hexDecode(stringEncode(value));
  //    if (!BitConverter.IsLittleEndian) Array.Reverse(bytes);

  sb += bytes;
}

}  // namespace Casper
