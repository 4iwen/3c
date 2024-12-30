#pragma once

#include "3c/core/api.h"
#include "3c/window/window.h"
#include "3c/events/window_events.h"
#include "3c/input/glfw/glfw_input.h"
#include "3c/core/time.h"

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

        void setVsync(bool enabled) override;

        void setMaxFps(uint32_t maxFps) override;

        void *getHandle() override;

        std::shared_ptr<Input> getInput() override;

        bool onClose(const WindowCloseEvent &event);

        bool onResize(const WindowResizeEvent &event);

    private:
        void setGlfwCallbacks();

        GLFWwindow *m_windowHandle;
        std::shared_ptr<Input> m_input;
        bool m_isRunning = true;
        Timer m_frameTimer;
        float m_targetFrameTime;
        float m_lastFrameTime;
    };
} // namespace tc
