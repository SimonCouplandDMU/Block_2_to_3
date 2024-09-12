/** \file GLFWWindowImpl.h */
#pragma once

#include "core/window.h"
#include <GLFW/glfw3.h>

namespace Engine
{
	/** \class GLFWWindowImpl
	* Implementation of a window using GLFW
	*/

	class GLFWWindowImpl : public Window
	{
	public:
		GLFWWindowImpl(const WindowProperties& properties); //!< Constructor
		virtual void init(const WindowProperties& properties) override; //!< initialise the window
		virtual void close() override; //!< Close the window
		//virtual ~Window() {};
		virtual void onUpdate(float timestep) override;
		virtual void onResize(WindowResizeEvent& e) override;
		virtual void onMonitorConnected(MonitorConnectedEvent& e) override;
		virtual void setVSync(bool VSync) override;
		virtual inline unsigned int getWidth() const override { return m_props.width; }
		virtual inline unsigned int getHeight() const override { return m_props.height; }
		virtual inline void* getNativeWindow() const override {return m_native;}
		virtual inline bool isFullScreenMode() const override { return m_props.isFullScreen; }
		virtual inline bool isVSync() const override { return m_props.isVSync; }
		virtual void setFullscreenMode(bool fullscreenState) override;
	private:
		WindowProperties m_props; //!< Properties
		GLFWwindow * m_native; //!< Native GLFW window
		GLFWmonitor * m_monitor; //!< native monitor on which the window is rendered
		float m_aspectRatio; //!< Aspect ratio 
		glm::ivec2 m_nonFullscreenPos; //!< Last position of the window when not in fullscreen mode
		glm::ivec2 m_nonFullscreenSize; //!< Last size of the window when not in fullscreen mode
	};
}
