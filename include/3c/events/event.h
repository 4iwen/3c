#pragma once

#include "3c/core/api.h"

namespace tc {
    enum class TC_API EventType {
        NONE,
        WINDOW_CLOSE,
        WINDOW_RESIZE,
        WINDOW_FOCUS,
        WINDOW_LOST_FOCUS,
        KEY_PRESSED,
        KEY_RELEASED,
        KEY_TYPED,
        MOUSE_BUTTON_PRESSED,
        MOUSE_BUTTON_RELEASED,
        MOUSE_MOVED,
        MOUSE_SCROLLED
    };

    struct TC_API Event {
        virtual ~Event() = default;

        virtual EventType getType() = 0;

        bool handled = false;
    };

    using EventCallback = std::function<void(Event &)>;

    class TC_API EventDispatcher {
    public:
        EventDispatcher(Event &event): m_event(event) {
        }

        void dispatch(EventType type, const EventCallback &func) {
            if (m_event.getType() == type) {
                func(m_event);
            }
        }

    private:
        Event &m_event;
    };
} // namespace tc
