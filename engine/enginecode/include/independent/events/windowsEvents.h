/* \file windowsEvents.h */
#pragma once

#include "event.h"

#include <glm/glm.hpp>

namespace Engine
{
	class WindowCloseEvent : public Event
	{
	public:
		static EventType getStaticType() { return EventType::WindowClose; } //!< Return static type
		virtual inline EventType getEventType() const override { return EventType::WindowClose; } //!< Get the event type
		virtual inline int32_t getCategoryFlags() const override { return EventCategoryWindow;  } //!< Get the event category flags
	};

	class WindowResizeEvent : public Event
	{
	public:
		WindowResizeEvent(int32_t width, int32_t height) : m_width(width), m_height(height) {}
		static EventType getStaticType() { return EventType::WindowResize; } //!< Return static type
		virtual inline EventType getEventType() const override { return EventType::WindowResize; } //!< Get the event type
		virtual inline int32_t getCategoryFlags() const override { return EventCategoryWindow; } //!< Get the event category flags

		inline int32_t getWidth() const { return m_width; }
		inline int32_t getHeight() const { return m_height; }
		inline glm::ivec2 getSize() const { return { m_width, m_height }; }
	private:
		int32_t m_width;	//!< Window width after resize
		int32_t m_height;	//!< Window height after resize
	};

	class WindowFocusEvent : public Event
	{
	public:
		WindowFocusEvent() {}
		static EventType getStaticType() { return EventType::WindowFocus; }
		virtual inline EventType getEventType() const override { return EventType::WindowFocus; }
		virtual inline int32_t getCategoryFlags() const override { return EventCategoryWindow; }
	};

	class WindowLostFocusEvent : public Event
	{
	public:
		WindowLostFocusEvent() {}
		static EventType getStaticType() { return EventType::WindowLostFocus; }
		virtual inline EventType getEventType() const override { return EventType::WindowLostFocus; }
		virtual inline int32_t getCategoryFlags() const override { return EventCategoryWindow; }
	};

	class WindowMovedEvent : public Event
	{
	public:
		WindowMovedEvent(int32_t x, int32_t y) : m_xPos(x), m_yPos(y) {}
		static EventType getStaticType() { return EventType::WindowMoved; }
		virtual inline EventType getEventType() const override { return EventType::WindowMoved; }
		virtual inline int32_t getCategoryFlags() const override { return EventCategoryWindow; }

		inline int32_t getXPos() const { return m_xPos; }
		inline int32_t getYPos() const { return m_yPos; }
		inline glm::ivec2 getPos() const { return { m_xPos, m_yPos }; }
	private:
		int32_t m_xPos;
		int32_t m_yPos;
	};
}