#pragma once

#include <spdlog/spdlog.h>

#include <spdlog/fmt/ostr.h>

#include <memory>

class Log
{
public:
    static void init();

    static std::shared_ptr<spdlog::logger>& getLogger() { return s_logger; }

private:
    static std::shared_ptr<spdlog::logger> s_logger;
};

// for the client
#define CC_LOG_TRACE(...) ::Log::getLogger()->trace(__VA_ARGS__)
#define CC_LOG_INFO(...) ::Log::getLogger()->info(__VA_ARGS__)
#define CC_LOG_WARN(...) ::Log::getLogger()->warn(__VA_ARGS__)
#define CC_LOG_ERROR(...) ::Log::getLogger()->error(__VA_ARGS__)
#define CC_LOG_CRITICAL(...) ::Log::getLogger()->critical(__VA_ARGS__)
