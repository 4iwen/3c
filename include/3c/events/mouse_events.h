#pragma once

#include "3c/events/event.h"
#include "3c/core/api.h"
#include "3c/input/mouse_codes.h"

namespace tc {
    struct TC_API MouseButtonPressedEvent : Event {
        MouseButtonPressedEvent(MouseButtonCode button): m_button(button) {
        }

        EVENT_TYPE(MOUSE_BUTTON_PRESSED);

        MouseButtonCode getButton() const { return m_button; }

    private:
        MouseButtonCode m_button;
    };

    struct TC_API MouseButtonReleasedEvent : Event {
        MouseButtonReleasedEvent(MouseButtonCode button): m_button(button) {
        }

        EVENT_TYPE(MOUSE_BUTTON_RELEASED);

        MouseButtonCode getButton() const { return m_button; }

    private:
        MouseButtonCode m_button;
    };

    struct TC_API MouseMovedEvent : Event {
        MouseMovedEvent(float x, float y): m_x(x), m_y(y) {
        }

        EVENT_TYPE(MOUSE_MOVED);

        float getX() const { return m_x; }
        float getY() const { return m_y; }

    private:
        float m_x, m_y;
    };

    struct TC_API MouseScrolledEvent : Event {
        MouseScrolledEvent(float xOffset, float yOffset): m_xOffset(xOffset), m_yOffset(yOffset) {
        }

        EVENT_TYPE(MOUSE_SCROLLED);

        float getXOffset() const { return m_xOffset; }
        float getYOffset() const { return m_yOffset; }

    private:
        float m_xOffset, m_yOffset;
    };
} // namespace tc
