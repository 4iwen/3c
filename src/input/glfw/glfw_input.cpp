#include "pch.h"

#include "3c/input/glfw/glfw_input.h"
#include "3c/context.h"

#include <GLFW/glfw3.h>

namespace tc {
    bool GlfwInput::isKeyPressedImpl(KeyCode key) {
        int state = glfwGetKey(
            static_cast<GLFWwindow *>(Context::get()->getWindow()->getHandle()),
            static_cast<int>(key)
        );

        if (state == GLFW_PRESS) {
            return true;
        }

        return false;
    }

    bool GlfwInput::isMouseButtonPressedImpl(MouseButtonCode mouseButton) {
        int state = glfwGetMouseButton(
            static_cast<GLFWwindow *>(Context::get()->getWindow()->getHandle()),
            static_cast<int>(mouseButton)
        );

        if (state == GLFW_PRESS) {
            return true;
        }

        return false;
    }

    std::pair<float, float> GlfwInput::getMousePositionImpl() {
        double mouseX;
        double mouseY;

        glfwGetCursorPos(
            static_cast<GLFWwindow *>(Context::get()->getWindow()->getHandle()),
            &mouseX,
            &mouseY
        );

        return {mouseX, mouseY};
    }
} // namespace tc
