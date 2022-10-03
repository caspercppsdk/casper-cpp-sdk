#include <atomic>

#include <spdlog/spdlog.h>
#include <spdlog/sinks/rotating_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>

#include "Algorithm/Join.hpp"
#include "Utils/LogConfigurator.h"

namespace Casper
{
    using LogConfig = Casper::LogConfig;

    spdlog::level::level_enum get_level(LogConfig::Severity const log_level)
    {
        using Severity = LogConfig::Severity;
        switch(log_level)
        {
            case Severity::trace:
                return spdlog::level::level_enum::trace;
            case Severity::debug:
                return spdlog::level::level_enum::debug;
            case Severity::info:
                return spdlog::level::level_enum::info;
            case Severity::warn:
                return spdlog::level::level_enum::warn;
            case Severity::err:
                return spdlog::level::level_enum::err;
            case Severity::critical:
                return spdlog::level::level_enum::critical;
            case Severity::off:
                return spdlog::level::level_enum::off;
            case Severity::n_levels:
                return spdlog::level::level_enum::n_levels;
            default:
                SPDLOG_ERROR("Not correct spdlog severity {}, so TRACE will be used.", static_cast<int>(log_level));
        }
        return spdlog::level::level_enum::trace;
    }

    std::shared_ptr<spdlog::logger> LogConfigurator::initDefault(LogConfig const& log_config)
    {
        LogConfigurator log{log_config.log_name};
        return log.configure(log_config);
    }

    LogConfigurator::LogConfigurator(std::string const& log_name) noexcept:
    log_name_{log_name}
{}

std::shared_ptr<spdlog::logger> LogConfigurator::configure(LogConfig const& log_config)
{
    using Sink = LogConfig::Sink;
    auto logger = log_config.sink == Sink::console ? configureConsoleLogger() : configureRotatingLogger();
    spdlog::set_level(get_level(log_config.severity));
    spdlog::set_pattern("[%b %m, %Y][%H:%M:%S:%e][%t][%^%l%$][%n][%!:%#] %v");
    spdlog::set_default_logger(logger);
    return logger;
}

std::shared_ptr<spdlog::logger> LogConfigurator::configureRotatingLogger()
{
    auto const max_size = 1048576 * 5;
    auto const max_files = 10;
    return spdlog::rotating_logger_mt(log_name_, algorithm::join("logs/rotating_", log_name_, ".txt"), max_size, max_files);
}

std::shared_ptr<spdlog::logger> LogConfigurator::configureConsoleLogger()
{
    return spdlog::stdout_color_mt(log_name_);
}
}