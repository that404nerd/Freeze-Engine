#pragma once

#include "Event.h"
#include "core/Core.h"

namespace Freeze {

    class WindowResizeEvent : public Event
	{
	public:
		WindowResizeEvent(uint32_t width, uint32_t height) : m_Width(width), m_Height(height) {};

		uint32_t GetWidth() const { return m_Width; }
		uint32_t GetHeight() const { return m_Height; }

		std::string GetEventType() const override
		{
			return ToString(EventTypes::WindowResizeEvent);
		}

		SET_EVENT_TYPE(WindowResizeEvent)
	private:
		uint32_t m_Width, m_Height;
	};

	class WindowCloseEvent : public Event
	{
	public:
		WindowCloseEvent() = default;

        std::string GetEventType() const override
        {
			return ToString(EventTypes::WindowCloseEvent);
        }

		SET_EVENT_TYPE(WindowCloseEvent)
	};

};