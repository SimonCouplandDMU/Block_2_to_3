/** \file application.h
*/
#pragma once

#include "systems/log.h"
#include "core/timer.h"
#include "events/events.h"
#include "core/window.h"
#include "systems/randomiser.h"
#include "systems/audio.h"
#include "core/inputPoller.h"
#include "core/layer.h"
#include "rendering/Renderer2D.h"
#include "rendering/lineRenderer.h"
#include "core/layerStack.h"
#include "systems/resourceManager.h"
#include <entt/entt.hpp>
#include <box2d/box2d.h>
#include <systems/dataSystem.h>

namespace Engine {
	/** \struct ApplicationProps
		\brief Properties of the application
	*/

	struct ApplicationProps
	{
		WindowProperties winProps;
		uint32_t vertexCapacity3D = 50000;
		uint32_t indexCapacity3D = 20000;
		uint32_t batchSize3D = 4000;
		uint32_t batchSize2D = 8192;
		const char * fontFilePath = "./assets/fonts/arial.ttf";
		uint32_t characterSize = 86;
		uint32_t shadersCapacity = 40;
		uint32_t texturesCapacity = 30;
	};

	/**
	\class Application
	Fundemental class of the engine. A singleton which runs the game loop infinitely.
	Provides a logging system, timing system, opens a window, holds layers and starts renderers.
	*/

	class Application
	{
	protected:
		Application(ApplicationProps props); //!< Constructor

		std::shared_ptr<Log> m_logSystem; //!< Log system
		std::shared_ptr<System> m_windowsSystem; //!< Windows system
		std::shared_ptr<ResourceManager> m_resourceManager; //!< Resource manager system
		std::shared_ptr<AudioSystem> m_audioSystem; //!< Audio system

		std::shared_ptr<Window> m_window; //!< Window
		std::shared_ptr<Timer> m_timer; //!< Timer
		std::shared_ptr<Randomiser> m_randomNumGen; //!< Random number generator
		
		LayerStack m_layerStack;

		void onClose(WindowCloseEvent& e); //!< Run when the window closes
		void onResize(WindowResizeEvent& e); //!< Run when the window is resized
		void onMoved(WindowMovedEvent& e); //!< Run when the window is moved
		void onGainFocus(WindowFocusEvent& e); //!< Run when the window gains focus
		void onLostFocus(WindowLostFocusEvent& e); //!< Run when the window is loses focus
		void onKeyPressed(KeyPressedEvent& e); //!< Run when a key is pressed
	private:
		static Application* s_instance; //!< Singleton instance of the application
		float m_timestep; //!< Timestep
		bool m_running = true; //!< Is the application running?
		std::vector<entt::entity> m_entities; //!< Our entities
		entt::registry m_registry; //!< ECS
		std::shared_ptr<b2World> m_world; //!< Our physics world
	public:
		virtual ~Application(); //!< Deconstructor
		inline static Application& getInstance() { return *s_instance; } //!< Instance getter from singleton pattern
		inline float getTimestep() { return m_timestep; } //!< Get the timestep of the lastframe
		inline std::shared_ptr<Window> getWindow() { return m_window; } //!< Get the application window
		inline std::shared_ptr<ResourceManager> getResourceManager() { return m_resourceManager; } //!< Get the resources managed by this application
		void run(); //!< Main loop
		inline std::vector<entt::entity>& getEntities() { return m_entities; } //!< Get entities by reference
		inline entt::registry& getRegistry() { return m_registry; }
		inline std::shared_ptr<b2World> getWorld() { return m_world; }
		inline std::shared_ptr<AudioSystem> getAudio() { return m_audioSystem; }
	};

	// To be defined in users code
	Application* startApplication(); //!< Function definition which provides an entry hook
}