#pragma once

#include "engine.h"

class BallScript : public Engine::NativeScript
{
public:
	BallScript(entt::entity& entity) : NativeScript(entity) 
	{
	}

	virtual void onCreate() override
	{
		// Sort out ball
		auto& registry = Engine::Application::getInstance().getRegistry();
		auto& rbc = registry.get<RigidBodyComponent>(m_entity);
		rbc.body->SetFixedRotation(true);

		prepareForSpawn();
		m_isRegisteredForRespawn = true;
		m_respawnActioned = true;
		m_respawnTimeout = 3.0f;
	};

	virtual void onCollision(Engine::CollisionData& collisionData) override
	{
		bool playPing = true;
		auto& registry = Engine::Application::getInstance().getRegistry();

		if (registry.has<Engine::BoxColliderComponent>(collisionData.other))
		{
			auto& otherBcc = registry.get<Engine::BoxColliderComponent>(collisionData.other);

			if (otherBcc.collider->IsSensor())
			{
				m_isRegisteredForRespawn = true;
				m_respawnActioned = false;
				playPing = false;
				auto lives = --Engine::DataSystem::getInt("lives");
				if (lives < 0)
				{
					Engine::Application::getInstance().getAudio()->playSound("gameover");
					Engine::DataSystem::getBool("gameover") = true;

				}
				else Engine::Application::getInstance().getAudio()->playSound("loseLife");
			}
		}
		if (playPing) Engine::Application::getInstance().getAudio()->playSound("ping");
		

	};

	virtual void onUpdate(float timestep) override
	{

		if (m_isRegisteredForRespawn)
		{
			if (!m_respawnActioned)
			{
				prepareForSpawn();
				m_respawnActioned = true;
			}
			m_respawnTimeout -= timestep;

			if (m_respawnTimeout < 0.f)
			{
				// Respawn
				spawn();
				m_isRegisteredForRespawn = false;
				m_respawnTimeout = 0.f;
			}
		}
	};
private:
	float m_respawnTimeout = 0.f;
	bool m_isRegisteredForRespawn = true;
	bool m_respawnActioned = false;

private:
	void prepareForSpawn()
	{
		m_respawnTimeout = 3.0f;

		auto& registry = Engine::Application::getInstance().getRegistry();
		auto& world = Engine::Application::getInstance().getWorld();

		// get paddle
		auto& paddleView = registry.view<ColliderGroupComponent>();
		auto& paddleTc = registry.get<TransformComponent>(paddleView.front());

		auto& tc = registry.get<TransformComponent>(m_entity);
		tc.position = glm::vec2(paddleTc.position.x, paddleTc.position.y + 0.3f);

		auto& ccc = registry.get<CircleColliderComponent>(m_entity);

		Engine::PhysicsMaterial ballMat;
		ballMat.density = ccc.collider->GetDensity();
		ballMat.friction = ccc.collider->GetFriction();
		ballMat.isSensor = ccc.collider->IsSensor();
		ballMat.restitution = ccc.collider->GetRestitution();

		float radius = ccc.radius;

		auto& rbc = registry.get<RigidBodyComponent>(m_entity);
		world->DestroyBody(rbc.body);

		rbc = RigidBodyComponent(m_entity, RigidBodyType::dynamic);
		ccc = CircleColliderComponent(m_entity, radius, ballMat);

		// Create weld joint on m_entity
		registry.emplace<WeldJointComponent>(m_entity, m_entity, paddleView.front());
	}

	void spawn()
	{
		auto& registry = Engine::Application::getInstance().getRegistry();
		auto& world = Engine::Application::getInstance().getWorld();

		// Destroy the weld joint
		b2Joint* weldJoint = registry.get<WeldJointComponent>(m_entity).weldJoint;
		world->DestroyJoint(weldJoint);
		registry.remove<WeldJointComponent>(m_entity);

		float angle = glm::radians(Randomiser::uniformFloatBetween(-55.f, 55.0f));
		float scalar = 0.35f;
		float xImpulse = sin(angle);
		float yImpulse = cos(angle);
		float mag = sqrt(xImpulse * xImpulse + yImpulse * yImpulse);
		xImpulse = xImpulse / mag * scalar;
		yImpulse = yImpulse / mag * scalar;
		mag = sqrt(xImpulse * xImpulse + yImpulse * yImpulse);
		auto& ballRbc = m_registry.get<RigidBodyComponent>(m_entity);
		ballRbc.body->ApplyLinearImpulseToCenter(b2Vec2(xImpulse, yImpulse), true);
		ballRbc.body->SetFixedRotation(true);
	}
};