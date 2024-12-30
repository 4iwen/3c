#include "pch.h"

#include "3c/input/input.h"
#include "3c/context.h"

namespace tc {
    bool Input::isKeyPressed(KeyCode key) {
        return Context::get()->getWindow()->getInput()->isKeyPressedImpl(key);
    }

    bool Input::isMouseButtonPressed(MouseButtonCode mouseButton) {
        return Context::get()->getWindow()->getInput()->isMouseButtonPressedImpl(mouseButton);
    }

    std::pair<float, float> Input::getMousePosition() {
        return Context::get()->getWindow()->getInput()->getMousePositionImpl();
    }
} // namespace tc
