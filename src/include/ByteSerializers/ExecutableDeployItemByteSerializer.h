#pragma once

#include "ByteSerializers/BaseByteSerializer.h"
#include "ByteSerializers/NamedArgByteSerializer.h"
#include "Types/ExecutableDeployItem.h"

namespace Casper {
struct ExecutableDeployItemByteSerializer : public BaseByteSerializer {
  CBytes ToBytes(ExecutableDeployItem source) {
    CBytes bytes;
    NamedArgByteSerializer namedArgSerializer;

    uint8_t source_tag = 0;
    if (source.module_bytes.has_value()) {
      source_tag = 0;
      WriteByte(bytes, source_tag);

      auto item = source.module_bytes.value();
      if (item.module_bytes.size() == 0 ||
          item.module_bytes.data() == nullptr) {
        WriteInteger(bytes, 0);
      } else {
        WriteInteger(bytes, item.module_bytes.size());
        WriteBytes(bytes, item.module_bytes);
      }

      bytes += hexDecode(u32Encode(item.args.size()));
      for (auto arg : item.args) {
        WriteBytes(bytes, namedArgSerializer.ToBytes(arg));
      }

    } else if (source.stored_contract_by_hash.has_value()) {
      source_tag = 1;
      WriteByte(bytes, source_tag);

      auto item = source.stored_contract_by_hash.value();
      WriteBytes(bytes, hexDecode(item.hash));
      WriteString(bytes, item.entry_point);

      bytes += hexDecode(u32Encode(item.args.size()));
      for (auto arg : item.args) {
        WriteBytes(bytes, namedArgSerializer.ToBytes(arg));
      }

    } else if (source.stored_contract_by_name.has_value()) {
      source_tag = 2;
      WriteByte(bytes, source_tag);

      auto item = source.stored_contract_by_name.value();
      WriteString(bytes, item.name);
      WriteString(bytes, item.entry_point);

      bytes += hexDecode(u32Encode(item.args.size()));
      for (auto arg : item.args) {
        WriteBytes(bytes, namedArgSerializer.ToBytes(arg));
      }

    } else if (source.stored_versioned_contract_by_hash.has_value()) {
      source_tag = 3;
      WriteByte(bytes, source_tag);

      auto item = source.stored_versioned_contract_by_hash.value();
      WriteBytes(bytes, CryptoUtil::hexDecode(item.hash));

      if (item.version.has_value()) {
        WriteByte(bytes, 1);
        WriteUInteger(bytes, item.version.value());
      } else {
        WriteByte(bytes, 0);
      }

      WriteString(bytes, item.entry_point);

      bytes += hexDecode(u32Encode(item.args.size()));
      for (auto arg : item.args) {
        WriteBytes(bytes, namedArgSerializer.ToBytes(arg));
      }
    } else if (source.stored_versioned_contract_by_name.has_value()) {
      source_tag = 4;
      WriteByte(bytes, source_tag);

      auto item = source.stored_versioned_contract_by_name.value();
      WriteString(bytes, item.name);

      if (item.version.has_value()) {
        WriteByte(bytes, 1);
        WriteUInteger(bytes, item.version.value());
      } else {
        WriteByte(bytes, 0);
      }

      WriteString(bytes, item.entry_point);

      bytes += hexDecode(u32Encode(item.args.size()));
      for (auto arg : item.args) {
        WriteBytes(bytes, namedArgSerializer.ToBytes(arg));
      }
    } else if (source.transfer.has_value()) {
      source_tag = 5;
      WriteByte(bytes, source_tag);
      TransferDeployItem item = source.transfer.value();
      bytes += hexDecode(u32Encode(item.args.size()));

      for (NamedArg arg : item.args) {
       WriteBytes(bytes, namedArgSerializer.ToBytes(arg));
      }
    } else {
      nlohmann::json j;
      to_json(j, source);
      throw std::runtime_error("Unsupported ExecutableDeployItem type: " +
                               j.dump(2));
    }
    return bytes;
  }
};

}  // namespace Casper