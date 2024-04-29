#pragma once

// TODO: Change to std::function maybe....

#include "core/Core.h"

namespace Freeze {

    // All the event types predefined
    enum class EventTypes {
        WindowResizeEvent, WindowCloseEvent,
        KeyPressEvent, KeyReleaseEvent, KeyRepeatEvent,
        MouseClickEvent, MouseReleaseEvent,
        None
    };

    #define ENUM_ELEMENT(name) {name, #name}
    #define SET_EVENT_TYPE(type) static std::string GetStaticEventType() { return ToString(EventTypes::type); }

    // Convert event enum values into strings for debugging
    inline std::string ToString(EventTypes value) {
        static const std::unordered_map<EventTypes, std::string> enumStrings = {
            ENUM_ELEMENT(EventTypes::WindowResizeEvent),
            ENUM_ELEMENT(EventTypes::WindowCloseEvent),
            ENUM_ELEMENT(EventTypes::KeyPressEvent),
            ENUM_ELEMENT(EventTypes::KeyReleaseEvent),
            ENUM_ELEMENT(EventTypes::KeyRepeatEvent),
            ENUM_ELEMENT(EventTypes::MouseClickEvent),
            ENUM_ELEMENT(EventTypes::MouseReleaseEvent),
        };

        auto it = enumStrings.find(value);
        if (it != enumStrings.end()) {
            return it->second;
        } else {
            return "Unknown";
        }
    }

    // All the events such as WindowEvent, KeyboardEvent, MouseEvent will be derived from Event class
    class Event {
    public:
        virtual std::string GetEventType() const = 0;

        virtual ~Event() = default;
    public:
        // Event handled?
        bool m_Handled = false;
    };

    class EventDispatcher {
    public:
        EventDispatcher(Event& event) : m_Event(event) {};

        template<typename T, typename F>
        bool Dispatch(const F& func) 
        {
            if(m_Event.GetEventType() == T::GetStaticEventType()) // Check if the event type is same
            {
                // Set m_Handled based on the return type of the eventFn function
                m_Event.m_Handled |= func(static_cast<T&>(m_Event)); // Convert the m_Event to whatever template type that is passwd
                return true;
            }

            return false;
        }
    private:
        Event& m_Event;
    };
};