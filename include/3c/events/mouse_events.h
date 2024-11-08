#pragma once

#include "3c/events/event.h"

#include "3c/core/api.h"

namespace tc {
    struct TC_API MouseButtonPressedEvent : public Event {
        MouseButtonPressedEvent(uint32_t button): m_button(button) {
        }

        EventType getType() override { return EventType::MOUSE_BUTTON_PRESSED; }

        uint32_t getButton() const { return m_button; }

    private:
        uint32_t m_button;
    };

    struct TC_API MouseButtonReleasedEvent : Event {
        MouseButtonReleasedEvent(uint32_t button): m_button(button) {
        }

        EventType getType() override { return EventType::MOUSE_BUTTON_RELEASED; }

        uint32_t getButton() const { return m_button; }

    private:
        uint32_t m_button;
    };

    struct TC_API MouseMovedEvent : Event {
        MouseMovedEvent(float x, float y): m_x(x), m_y(y) {
        }

        EventType getType() override { return EventType::MOUSE_MOVED; }

        float getX() const { return m_x; }
        float getY() const { return m_y; }

    private:
        float m_x, m_y;
    };

    struct TC_API MouseScrolledEvent : Event {
        MouseScrolledEvent(float xOffset, float yOffset): m_xOffset(xOffset), m_yOffset(yOffset) {
        }

        EventType getType() override { return EventType::MOUSE_SCROLLED; }

        float getXOffset() const { return m_xOffset; }
        float getYOffset() const { return m_yOffset; }

    private:
        float m_xOffset, m_yOffset;
    };
} // namespace tc
