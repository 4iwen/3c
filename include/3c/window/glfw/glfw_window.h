#pragma once

#include "3c/core/api.h"
#include "3c/window/window.h"

struct GLFWwindow; // Forward declaration

namespace tc {
    class TC_API GlfwWindow : public Window {
    public:
        GlfwWindow(
            const std::string &title,
            uint32_t width,
            uint32_t height
        );

        ~GlfwWindow() override;

        void update() override;

        void onEvent(Event &event) override;

        void close() override;

        bool shouldClose() override;

        double getTimeSinceCreation() override;

    private:
        void setGlfwCallbacks();

        GLFWwindow *m_windowHandle;
        bool m_isRunning = true;
    };
} // namespace tc
