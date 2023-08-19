#pragma once
#include <sstream>
namespace Casper
{
inline auto constexpr sourceSecretKey{R"##(
-----BEGIN EC PRIVATE KEY-----
MHQCAQEEIMGEU6dZjQwqi6zxin+xo4lyheatcwX8GZHCFrEkwb8GoAcGBSuBBAAK
oUQDQgAEVyTiUwxcjymLpB/hyvooKUq3sE1PGt4CWkomgThXCzrwRxXvf8TWe3LD
XuNaF5c10s/VXDPu8o6HZJm+FFgmQQ==
-----END EC PRIVATE KEY-----
)##"};

inline auto constexpr sourceED25519SecretKey{R"##(
-----BEGIN PRIVATE KEY-----
MC4CAQAwBQYDK2VwBCIEIIjMMDDA3lArezb5L1aDItA5G/mUWN8m1x5Ha9fJsOgb
-----END PRIVATE KEY-----
)##"};


} // namespace Casper