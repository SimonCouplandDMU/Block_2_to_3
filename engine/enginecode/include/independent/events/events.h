/* \file events.h*/
#pragma once

#include "codes.h"
#include "windowsEvents.h"
#include "keyboardEvents.h"
#include "mouseEvents.h"

namespace Engine
{
	class MonitorConnectedEvent : public Event
	{
	public:
		MonitorConnectedEvent(void * monitor) : m_monitor(monitor) {} //!< Constructor
		static EventType getStaticType() { return EventType::MonitorConnected; } //!< Return static type
		virtual inline EventType getEventType() const override { return EventType::MonitorConnected; } //!< Get the event type
		virtual inline int32_t getCategoryFlags() const override { return EventCategoryApplication; } //!< Get the event category flags
		inline void* getMonitor() { return m_monitor; } //!< Get a raw pointer to the monitor
	private:
		void * m_monitor; //Raw pointer to the current monitor
	};

	class MonitorDisconnectedEvent : public Event
	{
	public:
		MonitorDisconnectedEvent(void * monitor) : m_monitor(monitor) {} //!< Constructor
		static EventType getStaticType() { return EventType::MonitorDisconnected; } //!< Return static type
		virtual inline EventType getEventType() const override { return EventType::MonitorDisconnected; } //!< Get the event type
		virtual inline int32_t getCategoryFlags() const override { return EventCategoryApplication; } //!< Get the event category flags
		inline void* getMonitor() { return m_monitor; } //!< Get a raw pointer to the monitor
	private:
		void * m_monitor; //Raw pointer to the current monitor
	};
}