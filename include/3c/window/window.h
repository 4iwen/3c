#pragma once

#include "3c/core/api.h"
#include "3c/events/event.h"

namespace tc {
    enum class TC_API WindowBackendType {
        NONE,
        GLFW
    };

    class TC_API Window {
    public:
        virtual ~Window() = default;

        virtual void update() = 0;

        virtual void onEvent(Event &event) = 0;

        virtual void close() = 0;

        virtual bool shouldClose() = 0;

        virtual double getTimeSinceCreation() = 0;

        static std::shared_ptr<Window> create(
            const std::string &name,
            uint32_t width,
            uint32_t height,
            WindowBackendType backendType
        );
    };
} // namespace tc
