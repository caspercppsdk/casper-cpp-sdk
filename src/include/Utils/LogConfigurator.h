#pragma once

#include <memory>
#include <string>
#include "Types/Configuration.h"
namespace spdlog { class logger; }

namespace Casper
{

class LogConfigurator final
{
    std::string const log_name_;
public:
    static std::shared_ptr<spdlog::logger> initDefault(LogConfig const& log_config);

private:
    explicit LogConfigurator(std::string const& log_name) noexcept;
    std::shared_ptr<spdlog::logger> configure(LogConfig const& log_config);
    std::shared_ptr<spdlog::logger> configureRotatingLogger();
    std::shared_ptr<spdlog::logger> configureConsoleLogger();
};
} // namespace Casper