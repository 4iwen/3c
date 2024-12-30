#pragma once

#include "3c/core/api.h"
#include "3c/input/input.h"

namespace tc {
    class TC_API GlfwInput : public Input {
    protected:
        bool isKeyPressedImpl(KeyCode key) override;

        bool isMouseButtonPressedImpl(MouseButtonCode mouseButton) override;

        std::pair<float, float> getMousePositionImpl() override;
    };
} // namespace tc
