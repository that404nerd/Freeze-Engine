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

        std::string GetEventType() const override
        {
			return ToString(EventTypes::KeyPressEvent);
        }

		SET_EVENT_TYPE(KeyPressEvent)
    };

    class KeyRepeatEvent : public KeyEvent {
    public:
        KeyRepeatEvent(int keycode, bool isRepeated = false) 
            : KeyEvent(keycode), m_IsRepeated(isRepeated) {};

        std::string GetEventType() const override
        {
			return ToString(EventTypes::KeyRepeatEvent);
        }

        bool IsRepeated() { return m_IsRepeated; }

		SET_EVENT_TYPE(KeyRepeatEvent)
    private:
        bool m_IsRepeated;
    };

    class KeyReleaseEvent : public KeyEvent {
    public:
        KeyReleaseEvent(int keycode) : KeyEvent(keycode) {};

        std::string GetEventType() const override
        {
			return ToString(EventTypes::KeyReleaseEvent);
        }

		SET_EVENT_TYPE(KeyReleaseEvent)
    };

};