#include "pch.h"

#include "3c/core/log.h"

#include <spdlog/sinks/basic_file_sink.h>

namespace tc {
    void Log::init() {
        spdlog::set_pattern("%T.%e %^%5!l%$: %v");

        getLogger()->set_level(spdlog::level::trace);
        getLogger()->flush_on(spdlog::level::trace);
    }

    void Log::shutdown() {
        spdlog::shutdown();
    }
} // namespace tc
