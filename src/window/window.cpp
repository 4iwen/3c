#include "pch.h"

#include "3c/window/window.h"
#include "3c/core/assert.h"
#include "3c/window/glfw/glfw_window.h"

namespace tc {
    std::shared_ptr<Window> Window::create(
        const std::string &title,
        uint32_t width,
        uint32_t height,
        WindowBackendType backendType
    ) {
        switch (backendType) {
            default:
                TC_ASSERT(false, "No window backend selected");
            case WindowBackendType::GLFW:
                return std::make_shared<GlfwWindow>(title, width, height);
        }
    }
} // namespace tc
