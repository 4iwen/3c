#pragma once

#include "3c/events/event.h"

#include "3c/core/api.h"

namespace tc {
    struct TC_API WindowResizeEvent : Event {
        WindowResizeEvent(int32_t width, int32_t height): m_width(width), m_height(height) {
        }

        EVENT_TYPE(WINDOW_RESIZE);

        int32_t getWidth() const { return m_width; }
        int32_t getHeight() const { return m_height; }

    private:
        int32_t m_width, m_height;
    };

    struct TC_API WindowCloseEvent : Event {
        EVENT_TYPE(WINDOW_CLOSE);
    };

    struct TC_API WindowFocusEvent : Event {
        EVENT_TYPE(WINDOW_FOCUS);
    };

    struct TC_API WindowLostFocusEvent : Event {
        EVENT_TYPE(WINDOW_LOST_FOCUS);
    };
} // namespace tc
