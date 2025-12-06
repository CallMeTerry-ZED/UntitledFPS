/*
 * Copyright (c) 2025 ZED Interactive. All Rights Reserved.
 */

#ifndef LOGGER_H
#define LOGGER_H

#include <spdlog/logger.h>
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/spdlog.h"
#include <spdlog/common.h>
#include "spdlog/fmt/ostr.h"
#include "spdlog/fmt/bundled/core.h" 

namespace FPS
{
    class Logger
    {
    public:
        Logger();
        ~Logger();

        static void Init();
        static void Shutdown();
        static std::shared_ptr<spdlog::logger> GetLogger() { return s_logger; }

    private:
        static std::shared_ptr<spdlog::logger> s_logger;
    };

    // Helper function to convert const unsigned char* to const char* for logging
    inline const char* GlString(const unsigned char* str)
    {
        return str ? reinterpret_cast<const char*>(str) : "null";
    }
}

// Custom formatters
namespace fmt
{
    template <>
    struct formatter<const unsigned char*> : formatter<const char*>
    {
        template <typename FormatContext>
        auto format(const unsigned char* ptr, FormatContext& ctx) const -> decltype(ctx.out())
        {
            return formatter<const char*>::format(
                ptr ? reinterpret_cast<const char*>(ptr) : "null", ctx);
        }
    };
}

#define LOG_TRACE(...)    FPS::Logger::GetLogger()->trace(__VA_ARGS__)
#define LOG_DEBUG(...)    FPS::Logger::GetLogger()->debug(__VA_ARGS__)
#define LOG_INFO(...)     FPS::Logger::GetLogger()->info(__VA_ARGS__)
#define LOG_WARN(...)     FPS::Logger::GetLogger()->warn(__VA_ARGS__)
#define LOG_ERROR(...)    FPS::Logger::GetLogger()->error(__VA_ARGS__)
#define LOG_CRITICAL(...) FPS::Logger::GetLogger()->critical(__VA_ARGS__)

#endif
