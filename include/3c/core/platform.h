#pragma once

#if defined(__APPLE__)
#define TC_PLATFORM_MACOS
#elif defined(_WIN32) || defined(_WIN64)
#define TC_PLATFORM_WINDOWS
#elif defined(__linux__)
#define TC_PLATFORM_LINUX
#else
#error "Platform not supported"
#endif
