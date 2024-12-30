#pragma once

#include "3c/core/api.h"
#include "3c/input/key_codes.h"
#include "3c/input/mouse_codes.h"

namespace tc {
    class TC_API Input {
    public:
        virtual ~Input() = default;

        static bool isKeyPressed(KeyCode key);

        static bool isMouseButtonPressed(MouseButtonCode mouseButton);

        static std::pair<float, float> getMousePosition();

    protected:
        virtual bool isKeyPressedImpl(KeyCode key) = 0;

        virtual bool isMouseButtonPressedImpl(MouseButtonCode mouseButton) = 0;

        virtual std::pair<float, float> getMousePositionImpl() = 0;
    };
} // namespace tc
