/** \file eventHandler.h*/
#pragma once

#include "events.h"

#include <functional>

namespace Engine
{
	/**
	* \class EventHandler
	* Provides a bunch of functions as attribute which can be connect to varoius part of the engine as required
	*/

	class EventHandler
	{
	public:
		/* Setters */
		void setOnCloseCallback(const std::function<void(WindowCloseEvent&)>& fn) { m_onCloseCallback = fn; }
		void setOnResizeCallback(const std::function<void(WindowResizeEvent&)>& fn) { m_onResizeCallback = fn; }
		void setOnFocusCallback(const std::function<void(WindowFocusEvent&)>& fn) { m_onFocusCallback = fn; }
		void setOnLostFocusCallback(const std::function<void(WindowLostFocusEvent&)>& fn) { m_onLostFocusCallback = fn; }
		void setOnWindowMovedCallback(const std::function<void(WindowMovedEvent&)>& fn) { m_onWindowMovedCallback = fn; }
		void setOnKeyPressedCallback(const std::function<void(KeyPressedEvent&)>& fn) { m_onKeyDownCallback = fn; }
		void setOnKeyReleasedCallback(const std::function<void(KeyReleasedEvent&)>& fn) { m_onKeyUpCallback = fn; }
		void setOnKeyTypedCallback(const std::function<void(KeyTypedEvent&)>& fn) { m_onKeyTypedCallback = fn; }
		void setOnButtonPressedCallback(const std::function<void(MouseButtonPressedEvent&)>& fn) { m_onMouseDownCallback = fn; }
		void setOnButtonReleasedCallback(const std::function<void(MouseButtonReleasedEvent&)>& fn) { m_onMouseUpCallback = fn; }
		void setOnMouseMovedCallback(const std::function<void(MouseMovedEvent&)>& fn) { m_onMouseMovedCallback = fn; }
		void setOnMouseWheelCallback(const std::function<void(MouseScrolledEvent&)>& fn) { m_onMouseWheelCallback = fn; }
		void setOnMonitorConnectedCallback(const std::function<void(MonitorConnectedEvent&)>& fn) { m_onMonitorConnectedCallback = fn; }
		void setOnMonitorDisconnectedCallback(const std::function<void(MonitorDisconnectedEvent&)>& fn) { m_onMonitorDisconnectedCallback = fn; }

		/* Getters */
		std::function<void(WindowCloseEvent&)>& getOnCloseCallback() { return m_onCloseCallback; }
		std::function<void(WindowResizeEvent&)>& getOnResizeCallback() { return m_onResizeCallback; }
		std::function<void(WindowFocusEvent&)>& getOnFocusCallback() { return m_onFocusCallback; }
		std::function<void(WindowLostFocusEvent&)>& getOnLostFocusCallback() { return m_onLostFocusCallback; }
		std::function<void(WindowMovedEvent&)>& getOnWindowMovedCallback() { return m_onWindowMovedCallback; }
		std::function<void(KeyPressedEvent&)>& getOnKeyPressedCallback() { return m_onKeyDownCallback; }
		std::function<void(KeyReleasedEvent&)>& getOnKeyReleasedCallback() { return m_onKeyUpCallback; }
		std::function<void(KeyTypedEvent&)>& getOnKeyTypedCallback() { return m_onKeyTypedCallback; }
		std::function<void(MouseButtonPressedEvent&)>& getOnButtonPressedCallback() { return m_onMouseDownCallback; }
		std::function<void(MouseButtonReleasedEvent&)>& getOnButtonReleasedCallback() { return m_onMouseUpCallback; }
		std::function<void(MouseMovedEvent&)>& getOnMouseMovedCallback() { return m_onMouseMovedCallback; }
		std::function<void(MouseScrolledEvent&)>& getOnMouseWheelCallback() { return m_onMouseWheelCallback; }
		std::function<void(MonitorConnectedEvent&)>& getOnMonitorConnectedCallback() { return m_onMonitorConnectedCallback; }
		std::function<void(MonitorDisconnectedEvent&)>& getOnMonitorDisconnectedCallback() { return m_onMonitorDisconnectedCallback; }
	private:
		/* Attributes */
		std::function<void(WindowCloseEvent&)> m_onCloseCallback = std::bind(&EventHandler::defaultOnClose, this, std::placeholders::_1);
		std::function<void(WindowResizeEvent&)> m_onResizeCallback = std::bind(&EventHandler::defaultOnResize, this, std::placeholders::_1);
		std::function<void(WindowFocusEvent&)> m_onFocusCallback = std::bind(&EventHandler::defaultOnFocus, this, std::placeholders::_1);
		std::function<void(WindowLostFocusEvent&)> m_onLostFocusCallback = std::bind(&EventHandler::defaultOnLostFocus, this, std::placeholders::_1);
		std::function<void(WindowMovedEvent&)> m_onWindowMovedCallback = std::bind(&EventHandler::defaultOnWindowMoved, this, std::placeholders::_1);
		std::function<void(KeyPressedEvent&)> m_onKeyDownCallback = std::bind(&EventHandler::defaultOnKeyPress, this, std::placeholders::_1);
		std::function<void(KeyReleasedEvent&)> m_onKeyUpCallback = std::bind(&EventHandler::defaultOnKeyRelease, this, std::placeholders::_1);
		std::function<void(KeyTypedEvent&)> m_onKeyTypedCallback = std::bind(&EventHandler::defaultOnKeyTyped, this, std::placeholders::_1);
		std::function<void(MouseButtonPressedEvent&)> m_onMouseDownCallback = std::bind(&EventHandler::defaultOnMouseDown, this, std::placeholders::_1);
		std::function<void(MouseButtonReleasedEvent&)> m_onMouseUpCallback = std::bind(&EventHandler::defaultOnMouseUp, this, std::placeholders::_1);
		std::function<void(MouseMovedEvent&)> m_onMouseMovedCallback = std::bind(&EventHandler::defaultOnMouseMoved, this, std::placeholders::_1);
		std::function<void(MouseScrolledEvent&)> m_onMouseWheelCallback = std::bind(&EventHandler::defaultOnMouseWheel, this, std::placeholders::_1);
		std::function<void(MonitorConnectedEvent&)> m_onMonitorConnectedCallback = std::bind(&EventHandler::defaultOnMonitorConnected, this, std::placeholders::_1);
		std::function<void(MonitorDisconnectedEvent&)> m_onMonitorDisconnectedCallback = std::bind(&EventHandler::defaultOnMonitorDisconnected, this, std::placeholders::_1);

		/* Defaults */
		void defaultOnClose(WindowCloseEvent& e) { e.handle(false); }
		void defaultOnResize(WindowResizeEvent& e) { e.handle(false); }
		void defaultOnFocus(WindowFocusEvent& e) { e.handle(false); }
		void defaultOnLostFocus(WindowLostFocusEvent& e) { e.handle(false); }
		void defaultOnWindowMoved(WindowMovedEvent& e) { e.handle(false); }
		void defaultOnKeyPress(KeyPressedEvent& e) { e.handle(false); }
		void defaultOnKeyRelease(KeyReleasedEvent& e) { e.handle(false); }
		void defaultOnKeyTyped(KeyTypedEvent& e) { e.handle(false); }
		void defaultOnMouseDown(MouseButtonPressedEvent& e) { e.handle(false); }
		void defaultOnMouseUp(MouseButtonReleasedEvent& e) { e.handle(false); }
		void defaultOnMouseMoved(MouseMovedEvent& e) { e.handle(false); }
		void defaultOnMouseWheel(MouseScrolledEvent& e) { e.handle(false); }
		void defaultOnMonitorConnected(MonitorConnectedEvent& e) { e.handle(false); }
		void defaultOnMonitorDisconnected(MonitorDisconnectedEvent& e) { e.handle(false); }
	};
}
