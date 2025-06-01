#pragma once

#include "Event.h"

namespace Freeze {

    class KeyEvent : public Event {
    public:
        int GetKeyCode() { return m_KeyCode; }
    public:
        KeyEvent(int keycode) : m_KeyCode(keycode) {};

    protected:
        int m_KeyCode;
    };

    class KeyPressEvent : public KeyEvent {
    public:
        KeyPressEvent(int keycode) : KeyEvent(keycode) {};

        uint32_t GetEventType() const override
        {
          return ToEventType(EventTypes::KeyPressEvent);
        }

        SET_EVENT_TYPE(KeyPressEvent)
    };

    class KeyRepeatEvent : public KeyEvent {
    public:
        KeyRepeatEvent(int keycode, bool isRepeated = false) 
            : KeyEvent(keycode), m_IsRepeated(isRepeated) {};

        uint32_t GetEventType() const override
        {
          return ToEventType(EventTypes::KeyRepeatEvent);
        }

        bool IsRepeated() { return m_IsRepeated; }

        SET_EVENT_TYPE(KeyRepeatEvent)
    private:
        bool m_IsRepeated;
    };

    class KeyReleaseEvent : public KeyEvent {
    public:
        KeyReleaseEvent(int keycode) : KeyEvent(keycode) {};

        uint32_t GetEventType() const override
        {
          return ToEventType(EventTypes::KeyReleaseEvent);
        }

        SET_EVENT_TYPE(KeyReleaseEvent)
    };

};
