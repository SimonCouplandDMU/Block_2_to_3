#pragma once

#include <box2d/box2d.h>
#include <entt/entt.hpp>

#include "independent/core/application.h"
#include "independent/components/renderComponent.h"
#include "independent/components/transformComponent.h"
#include "independent/components/nativeScriptComponent.h"

namespace Engine
{
	enum class RigidBodyType {dynamic, _static, kinematic};

	struct PhysicsMaterial
	{
		float friction = 0.2f;
		float restitution = 0.0f;
		float density = 0.0f;
		bool isSensor = false;
	};

	struct RigidBodyComponent
	{
		RigidBodyComponent(entt::entity entity, RigidBodyType bodyType = RigidBodyType::_static) 	// Assumes we already have a rendercomponent and transform component
		{
			auto& app = Application::getInstance();

			auto world = app.getWorld();

			entt::registry& registry = app.getRegistry();
			auto& tc = registry.get<TransformComponent>(entity);

			b2BodyDef bodyDef;
			bodyDef.angle = tc.angle;
			bodyDef.position = b2Vec2(tc.position.x, tc.position.y);
			switch (bodyType)
			{
			case RigidBodyType::dynamic:
				bodyDef.type = b2BodyType::b2_dynamicBody;
				break;
			case RigidBodyType::_static:
				bodyDef.type = b2BodyType::b2_staticBody;
				break;
			case RigidBodyType::kinematic:
				bodyDef.type = b2BodyType::b2_kinematicBody;
				break;
			}
			body = world->CreateBody(&bodyDef);
			body->GetUserData().pointer = static_cast<uintptr_t>(entity);
		}

		void setBodyType(RigidBodyType bodyType)
		{
			if (body)
			{
				switch (bodyType)
				{
				case RigidBodyType::dynamic:
					body->SetType(b2BodyType::b2_dynamicBody);
					break;
				case RigidBodyType::_static:
					body->SetType(b2BodyType::b2_staticBody);
					break;
				case RigidBodyType::kinematic:
					body->SetType(b2BodyType::b2_kinematicBody);
					break;
				}
			}
		}

		b2Body* body = nullptr;
	};


	struct BoxColliderComponent
	{
		BoxColliderComponent(entt::entity entity, const PhysicsMaterial& material = PhysicsMaterial()) 
			: BoxColliderComponent(entity, glm::vec2(0.f, 0.f), material) {}
		

		BoxColliderComponent(entt::entity entity, const glm::vec2& p_offset, const PhysicsMaterial& material = PhysicsMaterial())
			: offset(p_offset)
		{
			auto& app = Application::getInstance();

			auto world = app.getWorld();
			entt::registry& registry = app.getRegistry();
			auto& rbc = registry.get<RigidBodyComponent>(entity);
			auto& rc = registry.get<RenderComponent>(entity);

			b2FixtureDef fixtureDef;
			b2PolygonShape box;
			box.SetAsBox(rc.halfExtents.x, rc.halfExtents.y);
			halfExtents = rc.halfExtents;
			b2Vec2 b2Offset(p_offset.x, p_offset.y);
			box.m_vertices[0] += b2Offset;
			box.m_vertices[1] += b2Offset;
			box.m_vertices[2] += b2Offset;
			box.m_vertices[3] += b2Offset;
			fixtureDef.shape = &box;

			fixtureDef.density = material.density;
			fixtureDef.restitution = material.restitution;
			fixtureDef.friction = material.friction;
			fixtureDef.isSensor = material.isSensor;

			collider = rbc.body->CreateFixture(&fixtureDef);
		}

		BoxColliderComponent(entt::entity entity, const glm::vec2& p_offset, const glm::vec2& p_halfExtents, const PhysicsMaterial& material = PhysicsMaterial())
			: offset(p_offset), halfExtents(p_halfExtents)
		{
			auto& app = Application::getInstance();

			auto world = app.getWorld();
			entt::registry& registry = app.getRegistry();
			auto& rbc = registry.get<RigidBodyComponent>(entity);

			b2FixtureDef fixtureDef;
			b2PolygonShape box;
			box.SetAsBox(p_halfExtents.x, p_halfExtents.y);
			b2Vec2 b2Offset(offset.x, offset.y);
			box.m_vertices[0] += b2Offset;
			box.m_vertices[1] += b2Offset;
			box.m_vertices[2] += b2Offset;
			box.m_vertices[3] += b2Offset;
			fixtureDef.shape = &box;

			fixtureDef.density = material.density;
			fixtureDef.restitution = material.restitution;
			fixtureDef.friction = material.friction;
			fixtureDef.isSensor = material.isSensor;

			collider = rbc.body->CreateFixture(&fixtureDef);
		}

		b2Fixture* collider;
		glm::vec2 halfExtents = glm::vec2(0.f);
		glm::vec2 offset = glm::vec2(0.F);
	};

	struct CircleColliderComponent
	{
		CircleColliderComponent(entt::entity entity, float radius, const PhysicsMaterial& material = PhysicsMaterial()) 
			: CircleColliderComponent(entity, radius, glm::vec2(0.f, 0.f), material) {}

		CircleColliderComponent(entt::entity entity, float p_radius, const glm::vec2& p_offset, const PhysicsMaterial& material = PhysicsMaterial())
			: radius(p_radius), offset (p_offset)
		{
			auto& app = Application::getInstance();

			auto world = app.getWorld();
			entt::registry& registry = app.getRegistry();
			auto& rbc = registry.get<RigidBodyComponent>(entity);

			b2FixtureDef fixtureDef;
			b2CircleShape circle;
			circle.m_radius = p_radius;
			circle.m_p.Set(p_offset.x, p_offset.y);
			fixtureDef.shape = &circle;

			fixtureDef.density = material.density;
			fixtureDef.restitution = material.restitution;
			fixtureDef.friction = material.friction;
			fixtureDef.isSensor = material.isSensor;

			collider = rbc.body->CreateFixture(&fixtureDef);
		}
		float radius;
		glm::vec2 offset = glm::vec2(0.f);
		b2Fixture* collider;
	};

	struct ColliderGroupComponent
	{
		ColliderGroupComponent(entt::entity entity, const PhysicsMaterial& material = PhysicsMaterial())
		{
			boxColliders.emplace_back(entity, material);
		}

		ColliderGroupComponent(entt::entity entity, const glm::vec2& offset, const PhysicsMaterial& material = PhysicsMaterial())
		{
			boxColliders.emplace_back(entity, offset, material);
		}

		ColliderGroupComponent(entt::entity entity, const glm::vec2& offset, const glm::vec2& halfExtents, const PhysicsMaterial& material = PhysicsMaterial())
		{
			boxColliders.emplace_back(entity, offset, halfExtents, material);
		}

		ColliderGroupComponent(entt::entity entity, float radius, const PhysicsMaterial& material = PhysicsMaterial())
		{
			circleColliders.emplace_back(entity, radius, material);
		}

		ColliderGroupComponent(entt::entity entity, float radius, const glm::vec2& offset, const PhysicsMaterial& material = PhysicsMaterial())
		{
			circleColliders.emplace_back(entity, radius, offset, material);
		}

		void addBoxCollider(entt::entity entity, const PhysicsMaterial& material = PhysicsMaterial()) { boxColliders.emplace_back(entity, material); }
		void addBoxCollider(entt::entity entity, const glm::vec2& offset, const PhysicsMaterial& material = PhysicsMaterial()) { boxColliders.emplace_back(entity, offset, material); }
		void addBoxCollider(entt::entity entity, const glm::vec2& offset, const glm::vec2& halfExtents, const PhysicsMaterial& material = PhysicsMaterial()) { boxColliders.emplace_back(entity, offset, halfExtents, material); }
		void addCircleCollider(entt::entity entity, float radius, const PhysicsMaterial& material = PhysicsMaterial()) { circleColliders.emplace_back(entity, radius, material); }
		void addCircleCollider(entt::entity entity, float radius, const glm::vec2& offset, const PhysicsMaterial& material = PhysicsMaterial()) { circleColliders.emplace_back(entity, radius, offset, material); }

		std::vector<BoxColliderComponent> boxColliders;
		std::vector<CircleColliderComponent> circleColliders;
	};

	class CollisionListener : public b2ContactListener
	{
	public:
		CollisionListener() : m_registry(Application::getInstance().getRegistry()) {}
		virtual void BeginContact(b2Contact* contact) override
		{
			entt::entity entityA = static_cast<entt::entity>(contact->GetFixtureA()->GetBody()->GetUserData().pointer);	
			entt::entity entityB = static_cast<entt::entity>(contact->GetFixtureB()->GetBody()->GetUserData().pointer);

			if (m_registry.has<NativeScriptComponent>(entityA))
			{
				auto& nsc = m_registry.get<NativeScriptComponent>(entityA);
				nsc.onCollision(CollisionData(entityB));
			}
		
			if (m_registry.has<NativeScriptComponent>(entityB))
			{
				auto& nsc = m_registry.get<NativeScriptComponent>(entityB);
				nsc.onCollision(CollisionData(entityA));
			}
		}
	private:
		entt::registry& m_registry;
	};

	struct WeldJointComponent
	{
		WeldJointComponent(entt::entity entityA, entt::entity entityB)
		{
			auto& app = Application::getInstance();
			auto world = app.getWorld();
			entt::registry& registry = app.getRegistry();

			b2Body* bodyA = registry.get<RigidBodyComponent>(entityA).body;
			b2Body* bodyB = registry.get<RigidBodyComponent>(entityB).body;

			glm::vec2& posA = registry.get<TransformComponent>(entityA).position;
			glm::vec2& posB = registry.get<TransformComponent>(entityB).position;

			b2Vec2 anchor;
			anchor.x = (posA.x + posB.x) * 0.5f;
			anchor.y = (posA.y + posB.y) * 0.5f;

			b2WeldJointDef wjd;
			wjd.Initialize(bodyA, bodyB, anchor);

			weldJoint = world->CreateJoint(&wjd);
		}
		b2Joint* weldJoint;
	};
}