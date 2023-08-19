
#pragma once

#include <string>

namespace Casper
{

struct LogConfig
{
    enum class Severity
    {
        trace = 0,
        debug,
        info,
        warn,
        err,
        critical,
        off,
        n_levels
    };
    enum class Sink
    {
        console,
        file_rotating
    };

    std::string log_name;
    Severity severity;
    Sink sink;
};

struct Endpoint
{
    std::string host;
    std::string port;
};
enum class NetworkType
{
    mainnet,
    testnet
};

} // namespace Casper