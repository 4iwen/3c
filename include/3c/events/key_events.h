#pragma once

#include "3c/events/event.h"

#include "3c/core/api.h"

namespace tc {
    struct TC_API KeyPressedEvent : Event {
        KeyPressedEvent(uint32_t key, uint32_t repeatCount): m_key(key), m_repeatCount(repeatCount) {
        }

        EventType getType() override { return EventType::KEY_PRESSED; }

        uint32_t getKey() const { return m_key; }
        uint32_t getRepeatCount() const { return m_repeatCount; }

    private:
        uint32_t m_key;
        uint32_t m_repeatCount;
    };

    struct TC_API KeyReleasedEvent : Event {
        KeyReleasedEvent(uint32_t key): m_key(key) {
        }

        EventType getType() override { return EventType::KEY_RELEASED; }

        uint32_t getKey() const { return m_key; }

    private:
        uint32_t m_key;
    };

    struct TC_API KeyTypedEvent : Event {
        KeyTypedEvent(uint32_t key): m_key(key) {
        }

        EventType getType() override { return EventType::KEY_TYPED; }

        uint32_t getKey() const { return m_key; }

    private:
        uint32_t m_key;
    };
} // namespace tc
