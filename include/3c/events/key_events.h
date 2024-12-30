#pragma once

#include "3c/core/api.h"
#include "3c/events/event.h"
#include "3c/input/key_codes.h"

namespace tc {
    struct TC_API KeyPressedEvent : Event {
        KeyPressedEvent(KeyCode key, uint32_t repeatCount): m_key(key), m_repeatCount(repeatCount) {
        }

        EVENT_TYPE(KEY_PRESSED);

        KeyCode getKey() const { return m_key; }
        uint32_t getRepeatCount() const { return m_repeatCount; }

    private:
        KeyCode m_key;
        uint32_t m_repeatCount;
    };

    struct TC_API KeyReleasedEvent : Event {
        KeyReleasedEvent(KeyCode key): m_key(key) {
        }

        EVENT_TYPE(KEY_RELEASED);

        KeyCode getKey() const { return m_key; }

    private:
        KeyCode m_key;
    };

    struct TC_API KeyTypedEvent : Event {
        KeyTypedEvent(KeyCode key): m_key(key) {
        }

        EVENT_TYPE(KEY_TYPED);

        KeyCode getKey() const { return m_key; }

    private:
        KeyCode m_key;
    };
} // namespace tc
