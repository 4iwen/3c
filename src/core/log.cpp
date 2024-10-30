#include "pch.h"

#include "3c/core/log.h"

#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>

namespace tc {
    std::shared_ptr<spdlog::logger> Log::s_loggerInstance;

    void Log::init() {
        spdlog::sink_ptr sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
        sink->set_pattern("%T.%e %^%5!l%$: %v");

        s_loggerInstance = std::make_shared<spdlog::logger>("logger", sink);

        s_loggerInstance->set_level(spdlog::level::trace);
        s_loggerInstance->flush_on(spdlog::level::trace);
    }
} // namespace tc
