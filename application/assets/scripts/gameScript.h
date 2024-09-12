#pragma once

#include "engine.h"

class GameScript : public Engine::NativeScript
{
public:
	GameScript(entt::entity& entity) : NativeScript(entity) {}


	virtual void onUpdate(float timestep) override
	{
		if (!Engine::DataSystem::getBool("gameover")) 
		{
			auto& app = Engine::Application::getInstance();

			auto world = app.getWorld();

			world->Step(timestep, 7, 5);


			// Have we met the win condition?
			bool won = Engine::DataSystem::getInt("blockCount") == 0;
			if (won && !Engine::DataSystem::getBool("won"))
			{
				Engine::DataSystem::getBool("won") = true;
				Engine::Application::getInstance().getAudio()->playSound("win");

				auto& rbView = m_registry.view<Engine::RigidBodyComponent>();
				for (auto& entity : rbView)
				{
					auto& rbc = m_registry.get<Engine::RigidBodyComponent>(entity);
					rbc.setBodyType(Engine::RigidBodyType::_static);
				}
			}
		}
	}

};