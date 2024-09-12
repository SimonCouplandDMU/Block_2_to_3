/** \file application.cpp
*/

#include "engine_pch.h"
#include "core/application.h"

#ifdef NG_PLATFORM_WINDOWS
#include "platform/GLFW/GLFWSystem.h"
#endif


namespace Engine {
	// Set static vars
	Application* Application::s_instance = nullptr;

	Application::Application(ApplicationProps appProps)
	{
		if (s_instance == nullptr)
		{
			s_instance = this;
		}

		// Start systems

		//Start log
		m_logSystem.reset(new Log);
		m_logSystem->start();

		// Start the windows System
#ifdef NG_PLATFORM_WINDOWS
		m_windowsSystem.reset(new GLFWSystem);
#endif
		m_windowsSystem->start();

		// Start the resource manager
		m_resourceManager.reset(new ResourceManager);
		m_resourceManager->start(SystemSignal::ResourceCount, appProps.shadersCapacity, appProps.texturesCapacity);

		// Start timer (not a system)
		m_timer.reset(new ChronoTimer);
		m_timer->start();

		// Start random number gen
		m_randomNumGen.reset(new Randomiser);
		m_randomNumGen->start();

		// Start the audio system
		m_audioSystem.reset(new AudioSystem);
		m_audioSystem->start();

		m_window.reset(Window::create(appProps.winProps));
		
		m_window->getEventHandler().setOnCloseCallback(std::bind(&Application::onClose, this, std::placeholders::_1));
		m_window->getEventHandler().setOnResizeCallback(std::bind(&Application::onResize, this, std::placeholders::_1));
		m_window->getEventHandler().setOnWindowMovedCallback(std::bind(&Application::onMoved, this, std::placeholders::_1));
		m_window->getEventHandler().setOnFocusCallback(std::bind(&Application::onGainFocus, this, std::placeholders::_1));
		m_window->getEventHandler().setOnLostFocusCallback(std::bind(&Application::onLostFocus, this, std::placeholders::_1));
		
		m_window->getEventHandler().setOnKeyPressedCallback(std::bind(&Application::onKeyPressed, this, std::placeholders::_1));
		m_window->getEventHandler().setOnKeyReleasedCallback(std::bind(&LayerStack::onKeyReleased, &m_layerStack, std::placeholders::_1));
		
		m_window->getEventHandler().setOnMouseMovedCallback(std::bind(&LayerStack::onMouseMoved, &m_layerStack, std::placeholders::_1));
		m_window->getEventHandler().setOnButtonPressedCallback(std::bind(&LayerStack::onMousePressed, &m_layerStack, std::placeholders::_1));
		m_window->getEventHandler().setOnButtonReleasedCallback(std::bind(&LayerStack::onMouseReleased, &m_layerStack, std::placeholders::_1));
		m_window->getEventHandler().setOnMouseWheelCallback(std::bind(&LayerStack::onMouseWheel, &m_layerStack, std::placeholders::_1));

		m_window->getEventHandler().setOnMonitorConnectedCallback(std::bind(&Window::onMonitorConnected, m_window.get(), std::placeholders::_1));

		InputPoller::setNativeWindow(m_window->getNativeWindow());

		Renderer2D::init(appProps.batchSize2D, appProps.fontFilePath, appProps.characterSize);

		LineRenderer::init(4096);

		m_world.reset(new b2World(b2Vec2(0.f, 0.f)));

		m_timer->reset();
	}

	void Application::onClose(WindowCloseEvent & e)
	{
		m_running = false;
		e.handle(true);
	}

	void Application::onResize(WindowResizeEvent & e)
	{
		m_window->onResize(e);
		for (auto& layer : m_layerStack) layer->onResize(e);
		e.handle(true);
	}

	void Application::onMoved(WindowMovedEvent & e)
	{
		e.handle(true);
	}

	void Application::onGainFocus(WindowFocusEvent & e)
	{
		m_layerStack.setAllActive(true);
		e.handle(true);
	}

	void Application::onLostFocus(WindowLostFocusEvent & e)
	{
		m_layerStack.setAllActive(false);
		e.handle(true);
	}

	void Application::onKeyPressed(KeyPressedEvent & e)
	{
		switch (e.getKeyCode())
		{
		case NG_KEY_ESCAPE:
			m_running = false;
			e.handle(true);
			break;
		case NG_KEY_F10:
			m_window->setFullscreenMode(!m_window->isFullScreenMode());
			e.handle(true);
			break;
		default:
			m_layerStack.onKeyPressed(e);
		}
	}

	Application::~Application()
	{
		// Stop systems

		// Audio system
		m_audioSystem->stop();
		// Stop windows system
		m_windowsSystem->stop();
		// Stop rand num gen
		m_randomNumGen->stop();
		// Stop resource manager
		m_resourceManager->stop();
		// Stop logger
		m_logSystem->stop();
	}


	void Application::run()
	{
		while (m_running)
		{
			m_timestep = m_timer->getElapsedTime();
			m_timer->reset();

			m_layerStack.update(m_timestep);
			m_layerStack.render();

			m_window->onUpdate(m_timestep);
		}

	}

}
