#pragma once

#include "3c/events/event.h"

#include "3c/core/api.h"

namespace tc {
    struct TC_API WindowResizeEvent : Event {
        WindowResizeEvent(uint32_t width, uint32_t height): m_width(width), m_height(height) {
        }

        EventType getType() override { return EventType::WINDOW_RESIZE; }

        uint32_t getWidth() const { return m_width; }
        uint32_t getHeight() const { return m_height; }

    private:
        uint32_t m_width, m_height;
    };

    struct TC_API WindowCloseEvent : Event {
        EventType getType() override { return EventType::WINDOW_CLOSE; }
    };

    struct TC_API WindowFocusEvent : Event {
        EventType getType() override { return EventType::WINDOW_FOCUS; }
    };

    struct TC_API WindowLostFocusEvent : Event {
        EventType getType() override { return EventType::WINDOW_LOST_FOCUS; }
    };
} // namespace tc
