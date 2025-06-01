#pragma once

#include "Event.h"

namespace Freeze {

    class MouseEvent : public Event {
    public:
        MouseEvent(int keycode) : m_KeyCode(keycode) {};

        int GetKeyCode() { return m_KeyCode; }
    protected:
        int m_KeyCode;
    };

    class MouseClickEvent : public MouseEvent {
    public:
        MouseClickEvent(int keycode) : MouseEvent(keycode) {};

        uint32_t GetEventType() const override
        {
          return ToEventType(EventTypes::MouseClickEvent);
        } 

        SET_EVENT_TYPE(MouseClickEvent)
    };

    class MouseReleaseEvent : public MouseEvent {
    public:
        MouseReleaseEvent(int keycode) : MouseEvent(keycode) {};

        uint32_t GetEventType() const override
        {
          return ToEventType(EventTypes::MouseReleaseEvent);
        }

        SET_EVENT_TYPE(MouseReleaseEvent)
    };

};
