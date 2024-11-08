#pragma once

#include "3c/core/platform.h"

#if defined(TC_BUILD_SHARED)
#if defined(TC_PLATFORM_WINDOWS)
#if defined(TC_EXPORTS)
#define TC_API __declspec(dllexport)
#else
#define TC_API __declspec(dllimport)
#endif
#elif defined(TC_PLATFORM_LINUX) || defined(TC_PLATFORM_MACOS)
#if defined(TC_EXPORTS)
#define TC_API __attribute__((visibility("default")))
#else
#define TC_API
#endif
#else
#error Platform not supported
#endif
#else
#define TC_API
#endif
