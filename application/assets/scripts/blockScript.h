#pragma once

#include "engine.h"

class BlockScript : public Engine::NativeScript
{
public:
	BlockScript(entt::entity& entity) : NativeScript(entity) {}

	virtual void onCollision(Engine::CollisionData& collisionData) override
	{
		if (!m_isRegisteredForDeletion)
		{
			Engine::DataSystem::getInt("score") += 10;
			Engine::DataSystem::getInt("blockCount")--;
			m_isRegisteredForDeletion = true;
		}
	};
};