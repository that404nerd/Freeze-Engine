#pragma once

#include "core/Core.h"

namespace Freeze {

  #define ENUM_ELEMENT(name) {name, #name}
  #define SET_EVENT_TYPE(type) static uint32_t GetStaticEventType() { return ToEventType(EventTypes::type); }
  #define EVENT_BIT(x) (1 << x)

  // All the event types predefined
  enum class EventTypes {
    WindowResizeEvent = EVENT_BIT(0),
    WindowCloseEvent = EVENT_BIT(1),
    KeyPressEvent = EVENT_BIT(2),
    KeyReleaseEvent = EVENT_BIT(3),
    KeyRepeatEvent = EVENT_BIT(4),
    MouseClickEvent = EVENT_BIT(5), 
    MouseReleaseEvent = EVENT_BIT(6),
    None = 0
  };

  constexpr uint32_t ToEventType(EventTypes eventType)
  {
    return static_cast<uint32_t>(eventType);
  }

  // All the events such as WindowEvent, KeyboardEvent, MouseEvent will be derived from Event class
  class Event {
  public:
    virtual uint32_t GetEventType() const = 0;

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
      // Check if the event type is same using bits (much faster than using strings duh...)
      if(m_Event.GetEventType() & static_cast<uint32_t>(T::GetStaticEventType()))
      {
          // Set m_Handled based on the return type of the eventFn function
          m_Event.m_Handled |= func(static_cast<T&>(m_Event)); // Convert the m_Event to whatever template type that is passed
          return true;
      }

      return false;
    }
  private:
    Event& m_Event;
  };
};
