#pragma once

#include "3c/core/api.h"

#include <spdlog/spdlog.h>

namespace tc {
    class TC_API Log {
    public:
        static void init();

        static std::shared_ptr<spdlog::logger> &getLogger() {
            return s_loggerInstance;
        }

    private:
        static std::shared_ptr<spdlog::logger> s_loggerInstance;
    };
} // namespace tc

#define TC_INFO(...) ::tc::Log::getLogger()->info(__VA_ARGS__)
#define TC_WARN(...) ::tc::Log::getLogger()->warn(__VA_ARGS__)
#define TC_ERROR(...) ::tc::Log::getLogger()->error(__VA_ARGS__)