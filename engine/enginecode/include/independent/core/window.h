/* \file window.h */
#pragma once

#include "events/eventHandler.h"
#include "core/graphicsContext.h"

namespace Engine
{
	/** \struct WindowProperties
		\brief Properties of a window
	*/
	struct WindowProperties
	{
		char * title;
		uint32_t width;
		uint32_t height;
		bool isFullScreen;
		bool isVSync;

		WindowProperties(char * title = "My Window", uint32_t width = 800, uint32_t height = 600, bool fullscreen = false) : title(title), width(width), height(height), isFullScreen(fullscreen) {}
	};

	/** \class Window
	* Abstract windows base class. All implemented windows should code to this interface.
	*/

	class Window
	{
	public:
		virtual void init(const WindowProperties& properties) = 0; //!< initialise the window
		virtual void close() = 0; //!< Close the window
		virtual ~Window() {}; //!< Destructor
		virtual void onUpdate(float timestep) = 0; //!< Run this to update the window
		virtual void onResize(WindowResizeEvent& e) = 0; //!< Run this to respond to a resize event
		virtual void onMonitorConnected(MonitorConnectedEvent& e) = 0; //!< Run this to respond to a monitor being connected
		virtual void setVSync(bool VSync) = 0; //!< Set the Vsync
		virtual void setFullscreenMode(bool fullscreenState) = 0; //!< Set the full screen state
		virtual unsigned int getWidth() const = 0; //!< Get the windows current width
		virtual unsigned int getHeight() const = 0; //!< Get the windows current height
		float getWidthf() const { return static_cast<float>(getWidth()); }; //!< Get the windows current width as a float
		float getHeightf() const { return static_cast<float>(getHeight()); }; //!< Get the windows current height as a float
		virtual void* getNativeWindow() const = 0; //!< Get the native window
		virtual bool isFullScreenMode() const = 0; //!< Get the full screen status of the window
		virtual bool isVSync() const = 0; //!< Get the VSync status of the window
		
		
		inline EventHandler& getEventHandler() { return m_handler; } //!< Get the event handler for this window

		static Window* create(const WindowProperties& properties = WindowProperties()); //!< Create an api specifi window
	protected:
		EventHandler m_handler; //!< Event handler
		std::shared_ptr<GraphicsContext> m_graphicsContext; //!< Graphics context
	};
}
