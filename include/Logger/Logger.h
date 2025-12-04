/*
 * Copyright (c) 2025 ZED Interactive. All Rights Reserved.
 */

#ifdef LOGGER_H
#define LOGGER_H

#include "spdlog/spdlog.h"

namespace FPS
{
    class Logger
    {
    public:
        static void Init();
        static void Shutdown();
        static std::shared_ptr<spdlog::Logger> GetLogger() { return s_logger; }

    private:
        static std::shared_ptr<spdlog::Logger> s_logger;
    };
}

#define LOG_TRACE(...)    FPS::Logger::GetLogger()->trace(__VA_ARGS__)
#define LOG_DEBUG(...)    FPS::Logger::GetLogger()->debug(__VA_ARGS__)
#define LOG_INFO(...)     FPS::Logger::GetLogger()->info(__VA_ARGS__)
#define LOG_WARN(...)     FPS::Logger::GetLogger()->warn(__VA_ARGS__)
#define LOG_ERROR(...)    FPS::Logger::GetLogger()->error(__VA_ARGS__)
#define LOG_CRITICAL(...) FPS::Logger::GetLogger()->critical(__VA_ARGS__)

#endif
