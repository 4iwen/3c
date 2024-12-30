#pragma once

#include "3c/core/api.h"

#define EVENT_TYPE(type) \
    static tc::EventType getTypeStatic() { \
        return tc::EventType::type; \
    } \
    \
    tc::EventType getType() override { \
        return getTypeStatic(); \
    }

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

        template<typename T, typename C>
        bool dispatch(const C &callback) {
            if (m_event.getType() == T::getTypeStatic()) {
                m_event.handled |= callback(static_cast<T &>(m_event));

                return true;
            }

            return false;
        }

    private:
        Event &m_event;
    };
} // namespace tc
