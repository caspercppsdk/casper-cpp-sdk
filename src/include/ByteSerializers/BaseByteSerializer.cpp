#include "ByteSerializers/BaseByteSerializer.h"

namespace Casper {

void BaseByteSerializer::WriteInteger(SecByteBlock& sb, int value) {
  SecByteBlock bytes = CEP57Checksum::Decode(i32Encode(value));
  //    if (!BitConverter.IsLittleEndian) Array.Reverse(bytes);

  sb += bytes;
}

void BaseByteSerializer::WriteUInteger(SecByteBlock& sb, uint32_t value) {
  SecByteBlock bytes = CEP57Checksum::Decode(u32Encode(value));
  //    if (!BitConverter.IsLittleEndian) Array.Reverse(bytes);

  sb += bytes;
}

void BaseByteSerializer::WriteULong(SecByteBlock& sb, uint64_t value) {
  SecByteBlock bytes = CEP57Checksum::Decode(u64Encode(value));
  //    if (!BitConverter.IsLittleEndian) Array.Reverse(bytes);

  sb += bytes;
}

void BaseByteSerializer::WriteByte(SecByteBlock& sb, uint8_t value) {
  SecByteBlock bytes = CEP57Checksum::Decode(u8Encode(value));
  sb += bytes;
}

void BaseByteSerializer::WriteBytes(SecByteBlock& sb,
                                    const std::vector<uint8_t>& value) {
  // TODO: CHECK BELOW!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
  SecByteBlock bytes(value.size());
  for (size_t i = 0; i < value.size(); i++) {
    bytes[i] = value[i];
  }
  sb += bytes;
}

void BaseByteSerializer::WriteBytes(SecByteBlock& sb,
                                    const SecByteBlock& value) {
  sb += value;
}

void BaseByteSerializer::WriteString(SecByteBlock& sb, std::string value) {
  SecByteBlock bytes = CEP57Checksum::Decode(stringEncode(value));
  //    if (!BitConverter.IsLittleEndian) Array.Reverse(bytes);

  sb += bytes;
}

}  // namespace Casper
