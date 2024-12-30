#pragma once

#include "3c/core/platform.h"
#include "3c/core/log.h"

#if defined(TC_PLATFORM_WINDOWS)
#define TC_DEBUG_BREAK() __debugbreak()
#elif defined(TC_PLATFORM_MACOS) || defined(TC_PLATFORM_LINUX)
#define TC_DEBUG_BREAK() __builtin_trap()
#else
#error "Debug break for this platform is not supported"
#endif
#define TC_ASSERT(condition, ...) { \
    if (!(condition)) { \
        TC_ERROR(__VA_ARGS__); \
        TC_DEBUG_BREAK(); \
    } \
}
