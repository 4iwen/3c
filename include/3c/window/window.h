#pragma once

#include <GLFW/glfw3.h>

#include "3c/core/api.h"

struct GLFWwindow;

namespace tc {
    class TC_API Window {
    public:
        static std::unique_ptr<Window> create(
            const std::string &title,
            int32_t width,
            int32_t height
        );

    private:
        GLFWwindow *m_windowHandle = nullptr;
    };
} // namespace tc
