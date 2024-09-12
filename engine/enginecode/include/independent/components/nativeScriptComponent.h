#pragma once

#include <entt/entt.hpp>
#include "events/events.h"

namespace Engine
{
	struct CollisionData
	{
		CollisionData(entt::entity e) : other(e) {}
		entt::entity other;
	};

	class NativeScript
	{
	public:
		NativeScript() : m_entity(entt::null), m_registry(Engine::Application::getInstance().getRegistry()) {};
		NativeScript(entt::entity& entity) : m_entity(entity), m_registry(Engine::Application::getInstance().getRegistry()) {};
		virtual ~NativeScript() = default;
		virtual void onCreate() {};
		virtual void onDestroy() {};
		virtual void onUpdate(float timestep) {};
		virtual void onKeyPress(KeyPressedEvent& e) {};
		virtual void onCollision(CollisionData& collisionData) {};
		bool isRegisteredForDeletion() {return m_isRegisteredForDeletion; }
	protected:
		entt::entity m_entity;
		entt::registry& m_registry;
		bool m_isRegisteredForDeletion = false;
	};

	class NativeScriptComponent
	{
	public:
		NativeScriptComponent() = default;
		~NativeScriptComponent() = default;
		template <typename G, typename ...Args> void create(Args&& ... args)
		{
			G* ptr = new G(std::forward<Args>(args) ...);
			m_instance.reset(static_cast<NativeScript*>(ptr));
			m_instance->onCreate();
		};
		void onUpdate(float timestep) { m_instance->onUpdate(timestep); };
		void onKeyPress(KeyPressedEvent& e) { m_instance->onKeyPress(e); };
		bool isRegisteredForDeletion() { return m_instance->isRegisteredForDeletion(); }
		void onCollision(CollisionData& collisionData) { m_instance->onCollision(collisionData); }
	protected:
		std::shared_ptr<NativeScript> m_instance = nullptr;
	};
}