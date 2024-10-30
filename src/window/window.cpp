#include "pch.h"

#include "3c/window/window.h"

#include "3c/core/assert.h"

#include <GLFW/glfw3.h>

namespace tc {
    std::unique_ptr<Window> Window::create(
        const std::string &title,
        const int32_t width,
        const int32_t height
    ) {
        TC_ASSERT(glfwInit(), "Failed to initialize GLFW!");

        std::unique_ptr<Window> window = std::make_unique<Window>();

        window->m_windowHandle = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
        if (window == nullptr) {
            glfwTerminate();
            TC_ASSERT(false, "Failed to create window!");
        }

        return window;
    }
} // namespace tc
