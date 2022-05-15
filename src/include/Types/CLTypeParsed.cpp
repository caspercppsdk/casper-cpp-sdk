#include "Types/CLTypeParsed.h"

namespace Casper {
bool CLTypeParsed::operator<(const CLTypeParsed& b) const { return true; }
bool CLTypeParsed::operator<(CLTypeParsed&& b) const { return true; }

}  // namespace Casper
