#pragma once

#include "engine.h"

class PaddleScript : public Engine::NativeScript
{
public:
	PaddleScript(entt::entity& entity) : NativeScript(entity) {}

	void onUpdate(float timestep) override
	{
		b2Vec2 desiredVel(0.f,0.f);

		if (Engine::InputPoller::isKeyPressed(NG_KEY_LEFT))
		{
			// Set desired vel to -2.5
			desiredVel.x = -2.5f;
		}

		if (Engine::InputPoller::isKeyPressed(NG_KEY_RIGHT))
		{
			// Set desired vel to 2.5
			desiredVel.x += 2.5f;
		}

		auto& rbc = m_registry.get<Engine::RigidBodyComponent>(m_entity);

		float leftLimit = 1.6125f;
		float rightLimit = 10.24f - leftLimit;
		float xPosition = rbc.body->GetPosition().x;

		if (xPosition <= leftLimit) desiredVel.x = std::max(desiredVel.x, 0.f);
		if (xPosition >= rightLimit) desiredVel.x = std::min(desiredVel.x, 0.f);
		rbc.body->SetLinearVelocity(desiredVel);
	}


};