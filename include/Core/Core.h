/*
 * Copyright (c) 2025 ZED Interactive. All Rights Reserved.
 */

 #ifndef CORE_H
 #define CORE_H

#include <memory>

// Platform detection
#ifdef _WIN32
    #define SANDBOX_PLATFORM_WINDOWS
#elif defined(__linux__)
    #define SANDBOX_PLATFORM_LINUX
#elif defined(__APPLE__)
    #define SANDBOX_PLATFORM_MACOS
#endif

// Debug break - cross-platform
#ifdef SANDBOX_PLATFORM_WINDOWS
    #define SANDBOX_DEBUGBREAK() __debugbreak()
#elif defined(SANDBOX_PLATFORM_LINUX) || defined(SANDBOX_PLATFORM_MACOS)
    #include <signal.h>
    #define SANDBOX_DEBUGBREAK() raise(SIGTRAP)
#else
    #define SANDBOX_DEBUGBREAK() // No-op for other platforms
#endif

// Assertions
#ifdef SANDBOX_DEBUG
    #define SANDBOX_ENABLE_ASSERTS
#endif

#ifdef SANDBOX_ENABLE_ASSERTS
    #include "Core/Logger/Logger.h"
    #define SANDBOX_ASSERT(x, ...) { if(!(x)) { LOG_ERROR("Assertion Failed: {}", __VA_ARGS__); SANDBOX_DEBUGBREAK(); } }
    #define SANDBOX_CORE_ASSERT(x, ...) { if(!(x)) { LOG_ERROR("Assertion Failed: {}", __VA_ARGS__); SANDBOX_DEBUGBREAK(); } }
#else
    #define SANDBOX_ASSERT(x, ...)
    #define SANDBOX_CORE_ASSERT(x, ...)
#endif

namespace Sandbox
{
    template<typename T>
    using Scope = std::unique_ptr<T>;

    template<typename T>
    using Ref = std::shared_ptr<T>;
}

 #endif