/* \file GLFWWindowImpl.cpp*/

#include "engine_pch.h"
#include "platform/GLFW/GLFWWindowImpl.h"
#include "platform/GLFW/GLFW_OpenGL_GC.h"
#include "systems/log.h"
namespace Engine {

#ifdef NG_PLATFORM_WINDOWS
	Window* Window::create(const WindowProperties& properties)
	{
		return new GLFWWindowImpl(properties);
	}
#endif

	GLFWWindowImpl::GLFWWindowImpl(const WindowProperties & properties)
	{
		init(properties);
	}

	void GLFWWindowImpl::init(const WindowProperties & properties)
	{
		m_props = properties;

		m_aspectRatio = static_cast<float>(m_props.width) / static_cast<float>(m_props.height);

		m_native = glfwCreateWindow(m_props.width, m_props.height, m_props.title, nullptr, nullptr);

		m_graphicsContext.reset(new GLFW_OpenGL_GC(m_native));
		m_graphicsContext->init();

		glfwSetWindowUserPointer(m_native, static_cast<void*>(&m_handler));

		int monitorCount;
		GLFWmonitor** monitors = glfwGetMonitors(&monitorCount);
		for (int i = 0; i < monitorCount; i++)
		{
			GLFWmonitor* monitor = *monitors;
			glfwSetMonitorUserPointer(monitor, static_cast<void*>(&m_handler));
			monitors++;
		}

		glfwSetWindowCloseCallback(m_native,
			[](GLFWwindow * window)
		{
			EventHandler* handler = static_cast<EventHandler*>(glfwGetWindowUserPointer(window));
			auto& onClose = handler->getOnCloseCallback();

			WindowCloseEvent e;
			onClose(e);
		}
		);

		glfwSetWindowSizeCallback(m_native,
			[](GLFWwindow * window, int newWidth, int newHeight)
		{
			EventHandler* handler = static_cast<EventHandler*>(glfwGetWindowUserPointer(window));
			auto& onResize = handler->getOnResizeCallback();

			WindowResizeEvent e(newWidth, newHeight);
			onResize(e);
		}
		);

		glfwSetWindowPosCallback(m_native,
			[](GLFWwindow* window, int posX, int posY)
		{
			EventHandler* handler = static_cast<EventHandler*>(glfwGetWindowUserPointer(window));
			auto& onMoved = handler->getOnWindowMovedCallback();

			WindowMovedEvent e(posX, posY);
			onMoved(e);
		}
		);

		glfwSetWindowFocusCallback(m_native,
			[](GLFWwindow* window, int state)
		{
			EventHandler* handler = static_cast<EventHandler*>(glfwGetWindowUserPointer(window));

			if (state == GLFW_TRUE) // Gained focus
			{
				auto& onFocused = handler->getOnFocusCallback();

				WindowFocusEvent e;
				onFocused(e);
			}
			else if (state == GLFW_FALSE) // Lost focus
			{
				auto& onLostFocused = handler->getOnLostFocusCallback();

				WindowLostFocusEvent e;
				onLostFocused(e);
			}
		}
		);

		glfwSetKeyCallback(m_native,
			[](GLFWwindow* window, int keyCode, int scancode, int action, int mods)
		{
			EventHandler* handler = static_cast<EventHandler*>(glfwGetWindowUserPointer(window));

			if (action == GLFW_PRESS)
			{
				auto& onKeyPress = handler->getOnKeyPressedCallback();

				KeyPressedEvent e(keyCode, 0);
				onKeyPress(e);
			}
			else if (action == GLFW_REPEAT)
			{
				auto& onKeyPress = handler->getOnKeyPressedCallback();

				KeyPressedEvent e(keyCode, 1);
				onKeyPress(e);
			}
			else if (action == GLFW_RELEASE)
			{
				auto& onKeyRelease = handler->getOnKeyReleasedCallback();

				KeyReleasedEvent e(keyCode);
				onKeyRelease(e);
			}
		}
		);

		glfwSetCursorPosCallback(m_native,
			[](GLFWwindow* window, double mouseX, double mouseY)
		{
			MouseMovedEvent e(static_cast<float>(mouseX), static_cast<float>(mouseY));

			EventHandler* handler = (EventHandler*)glfwGetWindowUserPointer(window);
			auto& onMouseMovedFunction = handler->getOnMouseMovedCallback();

			onMouseMovedFunction(e);
		}
		);

		glfwSetMouseButtonCallback(m_native,
			[](GLFWwindow* window, int button, int action, int mods)
		{
			EventHandler* handler = (EventHandler*)glfwGetWindowUserPointer(window);
			if (action == GLFW_PRESS)
			{
				MouseButtonPressedEvent e(button);

				auto& onMouseButtonPressedFunction = handler->getOnButtonPressedCallback();

				onMouseButtonPressedFunction(e);
			}
			else if (action == GLFW_RELEASE)
			{
				MouseButtonReleasedEvent e(button);

				auto& onMouseButtonReleasedFunction = handler->getOnButtonReleasedCallback();

				onMouseButtonReleasedFunction(e);
			}
		}
		);

		glfwSetScrollCallback(m_native,
			[](GLFWwindow* window, double xOffset, double yOffset)
		{
			MouseScrolledEvent e(static_cast<float>(xOffset), static_cast<float>(yOffset));
			EventHandler* handler = (EventHandler*)glfwGetWindowUserPointer(window);

			auto& onMouseScrolledFunction = handler->getOnMouseWheelCallback();
			onMouseScrolledFunction(e);
		}
		);

		// Set monitor
		m_monitor = glfwGetPrimaryMonitor();

		glfwSetMonitorCallback(
			[](GLFWmonitor* monitor, int event)
			{
				if (event == GLFW_CONNECTED)
				{
					MonitorConnectedEvent e(static_cast<void *>(monitor));
					EventHandler* handler = (EventHandler*)glfwGetMonitorUserPointer(monitor);

					auto& onMonitorConnectedFunction = handler->getOnMonitorConnectedCallback();
					onMonitorConnectedFunction(e);
				}
				else if (event == GLFW_DISCONNECTED)
				{
					MonitorDisconnectedEvent e(static_cast<void *>(monitor));
					EventHandler* handler = (EventHandler*)glfwGetMonitorUserPointer(monitor);

					auto& onMonitorDisconnectedFunction = handler->getOnMonitorDisconnectedCallback();
					onMonitorDisconnectedFunction(e);
				}
			}
		);
		

		// Store current window position and window size
		glfwGetWindowPos(m_native, &m_nonFullscreenPos.x, &m_nonFullscreenPos.y);
		glfwGetWindowSize(m_native, &m_nonFullscreenSize.x, &m_nonFullscreenSize.y);

		setFullscreenMode(m_props.isFullScreen);
	}

	void GLFWWindowImpl::close()
	{
		glfwDestroyWindow(m_native);
	}

	void GLFWWindowImpl::onUpdate(float timestep)
	{
		glfwPollEvents();
		m_graphicsContext->swapBuffers();
	}

	void GLFWWindowImpl::onResize(WindowResizeEvent & e)
	{
		// Update window size
		m_props.width = e.getSize().x;
		m_props.height = e.getSize().y;
		
		// Update viewport
		m_graphicsContext->updateViewport(m_props.width, m_props.height);
	}

	void GLFWWindowImpl::onMonitorConnected(MonitorConnectedEvent & e)
	{
		m_monitor = static_cast<GLFWmonitor*>(e.getMonitor());
	}

	void GLFWWindowImpl::setVSync(bool VSync)
	{
		m_props.isVSync = VSync;
		if (m_props.isVSync) { glfwSwapInterval(1); }
		else { glfwSwapInterval(0); }
	}

	void GLFWWindowImpl::setFullscreenMode(bool fullscreenState)
	{
		if (isFullScreenMode() == fullscreenState) return;
	
		if (fullscreenState)
		{
			// Store current window position and window size
			glfwGetWindowPos(m_native, &m_nonFullscreenPos.x, &m_nonFullscreenPos.y);
			glfwGetWindowSize(m_native, &m_nonFullscreenSize.x, &m_nonFullscreenSize.y);

			// getfullscreen resolution of monitor
			const GLFWvidmode * mode = glfwGetVideoMode(glfwGetPrimaryMonitor());

			// set video mode to fullscreen
			glfwSetWindowMonitor(m_native, m_monitor, 0, 0, mode->width, mode->height, 0);

			// Update viewport
			m_graphicsContext->updateViewport(mode->width, mode->height);
			
			// Update window size
			m_props.width = mode->width;
			m_props.height = mode->height;
		}
		else
		{
			// restore last window position and size
			glfwSetWindowMonitor(m_native, nullptr, m_nonFullscreenPos.x, m_nonFullscreenPos.y, m_nonFullscreenSize.x, m_nonFullscreenSize.y, 0);
			// Update viewport
			m_graphicsContext->updateViewport(m_nonFullscreenSize.x, m_nonFullscreenSize.y);

			// Update window size
			m_props.width = m_nonFullscreenSize.x;
			m_props.height = m_nonFullscreenSize.y;
		}

		m_props.isFullScreen = !m_props.isFullScreen;

		// Send an on resize event for the camera
		EventHandler* handler = static_cast<EventHandler*>(glfwGetWindowUserPointer(m_native));
		auto& onResize = handler->getOnResizeCallback();

		WindowResizeEvent e(m_props.width, m_props.height);
		onResize(e);
	}
}