#pragma once

#include "Types/GlobalStateKey.h"

namespace Casper {
enum class OpKind { Read, Write, Add, NoOp };

struct Operation {
  GlobalStateKey key;
  OpKind kind;
};
}  // namespace Casper
