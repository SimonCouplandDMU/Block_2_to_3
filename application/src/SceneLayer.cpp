/* \file SceneLayer.cpp*/

#include "sceneLayer.h"
#include "gameScript.h"
#include "paddleScript.h"
#include "blockScript.h"
#include "ballScript.h"

SceneLayer::SceneLayer(const char * name, std::vector<entt::entity>& entities, entt::registry& registry) 
	: Layer(name), m_entities(entities), m_registry(registry)
{
	auto& app = Application::getInstance();
	auto world = app.getWorld();
	world->SetContactListener(&m_collisionListener);

	m_view = glm::mat4(1.f);
	m_proj = glm::ortho(0.f, 10.24f, 0.f, 8.f);

	m_swu["u_view"] = std::pair<ShaderDataType, void*>(ShaderDataType::Mat4, static_cast<void*>(glm::value_ptr(m_view)));
	m_swu["u_projection"] = std::pair<ShaderDataType, void*>(ShaderDataType::Mat4, static_cast<void*>(glm::value_ptr(m_proj)));

	m_clear.reset(RenderCommandFactory::createCommand(RenderCommand::Commands::clearColourAndDepthBuffer));

	std::shared_ptr<RenderCommand> setColour;
	setColour.reset(RenderCommandFactory::createCommand(RenderCommand::Commands::setClearColour, 1.f,1.f,1.f,1.f));
	RendererCommon::actionCommand(setColour);

	std::shared_ptr<RenderCommand> enableBlending;
	enableBlending.reset(RenderCommandFactory::createCommand(RenderCommand::Commands::enableBlending));
	RendererCommon::actionCommand(enableBlending);

	std::shared_ptr<RenderCommand> setBlendMode;
	setBlendMode.reset(RenderCommandFactory::createCommand(RenderCommand::Commands::setStandardBlendFunc));
	RendererCommon::actionCommand(setBlendMode);

	// Add game data
	Engine::DataSystem::addBool("won", false);
	Engine::DataSystem::addBool("gameover", false);
	Engine::DataSystem::addInt("score", 0);
	Engine::DataSystem::addInt("lives", 3);
	Engine::DataSystem::addInt("blockCount", 27);
	// Add audio assets
	if (!Engine::Application::getInstance().getAudio()->addSound("ping", "./assets/audio/ping.wav"))
		Engine::Log::error("Audio file: {0} did not load", "./assets/audio/ping.wav");
	if (!Engine::Application::getInstance().getAudio()->addSound("loseLife", "./assets/audio/loseLife.wav"))
		Engine::Log::error("Audio file: {0} did not load", "./assets/audio/loseLife.wav");
	if (!Engine::Application::getInstance().getAudio()->addSound("gameover", "./assets/audio/gameover.wav"))
		Engine::Log::error("Audio file: {0} did not load", "./assets/audio/gameover.wav");
	if (!Engine::Application::getInstance().getAudio()->addSound("win", "./assets/audio/win.wav"))
		Engine::Log::error("Audio file: {0} did not load", "./assets/audio/win.wav");


	m_texture.reset(Texture::create("./assets/textures/block_ss.png"));
	SubTexture whiteBlock;
	SubTexture redBall;
	SubTexture paddle;

	whiteBlock = SubTexture(m_texture, glm::vec2(0.f, 0.745173745), glm::vec2(0.165, 0.629));

	float u = (1.f / 384.f);
	float v = (1.f / 258.f);
	glm::vec2 c(200.f, 10.f);
	float p = 9.f;
	redBall = SubTexture(m_texture, glm::vec2(c.x * u - (p * u), c.y * v + (p * v)), glm::vec2(c.x * u + (p * u), c.y * v - (p * v)));

	c = { 120.f, 11.f };
	glm::vec2 p2(40.f, 9.f);
	paddle = SubTexture(m_texture, glm::vec2(c.x * u - (p2.x * u), c.y * v + (p2.y * v)), glm::vec2(c.x * u + (p2.x * u), c.y * v - (p2.y * v)));

	m_entities.reserve(1000);

	PhysicsMaterial staticBlockMaterial;
	staticBlockMaterial.restitution = 1.0f;

	PhysicsMaterial dynamicMaterial;
	dynamicMaterial.density = 1.0f;
	dynamicMaterial.restitution = 1.0f;
	dynamicMaterial.friction = 0.f;

	PhysicsMaterial sensorMaterial;
	sensorMaterial.isSensor = true;

	// GamePlay script entity
	m_entities.push_back(m_registry.create());
	{
		auto& nsc = m_registry.emplace<NativeScriptComponent>(m_entities.back());
		nsc.create<GameScript>(m_entities.back());
	}
	// Blocks

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			glm::vec4 blockColour;

			if (i % 2)
			{
				if (j % 2) blockColour = glm::vec4(0.f, 1.f, 1.f, 1.f);
				else blockColour = glm::vec4(1.f, 0.f, 1.f, 1.f);
			}
			else
			{
				if (!(j % 2)) blockColour = glm::vec4(0.f, 1.f, 1.f, 1.f);
				else blockColour = glm::vec4(1.f, 0.f, 1.f, 1.f);
			}

			m_entities.push_back(m_registry.create());
			m_registry.emplace<TransformComponent>(m_entities.back(), glm::vec2(1.12f + static_cast<float>(j), 6.f + static_cast<float>(i) * 0.5));
			m_registry.emplace<RenderComponent>(m_entities.back(), glm::vec2(0.5f, 0.25f), blockColour, whiteBlock);
			m_registry.emplace<RigidBodyComponent>(m_entities.back(), m_entities.back());
			m_registry.emplace<BoxColliderComponent>(m_entities.back(), m_entities.back(), staticBlockMaterial);
			auto& nsc = m_registry.emplace<NativeScriptComponent>(m_entities.back());
			nsc.create<BlockScript>(m_entities.back());
		}
	}

	// Floor
	m_entities.push_back(m_registry.create());
	m_registry.emplace<TransformComponent>(m_entities.back(), glm::vec2(5.12f, 0.25f));
	m_registry.emplace<RenderComponent>(m_entities.back(), glm::vec2(5.12f, 0.25f), glm::vec4(0.f, 1.f, 0.f, 1.f));
	m_registry.emplace<RigidBodyComponent>(m_entities.back(), m_entities.back());
	m_registry.emplace<BoxColliderComponent>(m_entities.back(), m_entities.back(), staticBlockMaterial);

	// Top
	m_entities.push_back(m_registry.create());
	m_registry.emplace<TransformComponent>(m_entities.back(), glm::vec2(5.12f, 8.0f));
	m_registry.emplace<RenderComponent>(m_entities.back(), glm::vec2(5.12f, 0.25f), glm::vec4(0.f, 1.f, 0.f, 1.f));
	m_registry.emplace<RigidBodyComponent>(m_entities.back(), m_entities.back());
	m_registry.emplace<BoxColliderComponent>(m_entities.back(), m_entities.back(), staticBlockMaterial);

	// Left
	m_entities.push_back(m_registry.create());
	m_registry.emplace<TransformComponent>(m_entities.back(), glm::vec2(0.3f, 4.f));
	m_registry.emplace<RenderComponent>(m_entities.back(), glm::vec2(0.3f, 4.f), glm::vec4(0.f, 1.f, 0.f, 1.f));
	m_registry.emplace<RigidBodyComponent>(m_entities.back(), m_entities.back());
	m_registry.emplace<BoxColliderComponent>(m_entities.back(), m_entities.back(), staticBlockMaterial);

	// Right
	m_entities.push_back(m_registry.create());
	m_registry.emplace<TransformComponent>(m_entities.back(), glm::vec2(10.24f-0.3f, 4.f));
	m_registry.emplace<RenderComponent>(m_entities.back(), glm::vec2(0.3f, 4.f), glm::vec4(0.f, 1.f, 0.f, 1.f));
	m_registry.emplace<RigidBodyComponent>(m_entities.back(), m_entities.back());
	m_registry.emplace<BoxColliderComponent>(m_entities.back(), m_entities.back(), staticBlockMaterial);

	// Paddle
	m_entities.push_back(m_registry.create());
	m_registry.emplace<TransformComponent>(m_entities.back(), glm::vec2(5.12f, 1.25f));
	m_registry.emplace<RenderComponent>(m_entities.back(), glm::vec2(1.f, 0.25f), glm::vec4(1.f, 1.f, 1.f, 1.f), paddle);
	m_registry.emplace<RigidBodyComponent>(m_entities.back(), m_entities.back(), RigidBodyType::kinematic);
	auto& cgc = m_registry.emplace<ColliderGroupComponent>(m_entities.back(), m_entities.back(), glm::vec2(0.f), glm::vec2(0.875f, 0.1f), dynamicMaterial);

	cgc.addCircleCollider(m_entities.back(), 0.1f, glm::vec2(-0.875f, 0.0f), dynamicMaterial);
	cgc.addCircleCollider(m_entities.back(), 0.1f, glm::vec2(0.875f, 0.0f), dynamicMaterial);

	{
		auto& nsc = m_registry.emplace<NativeScriptComponent>(m_entities.back());
		nsc.create<PaddleScript>(m_entities.back());
	}

	// Ball
	m_entities.push_back(m_registry.create());
	m_registry.emplace<TransformComponent>(m_entities.back(), glm::vec2(5.12f, 4.0f));
	m_registry.emplace<RenderComponent>(m_entities.back(), glm::vec2(0.25f, 0.25f), glm::vec4(1.f, 1.f, 1.f, 1.f), redBall);
	m_registry.emplace<RigidBodyComponent>(m_entities.back(), m_entities.back(), RigidBodyType::dynamic);
	m_registry.emplace<CircleColliderComponent>(m_entities.back(), m_entities.back(), 0.2f, dynamicMaterial);
	m_registry.get<RigidBodyComponent>(m_entities.back());

	{
		auto& nsc = m_registry.emplace<NativeScriptComponent>(m_entities.back());
		nsc.create<BallScript>(m_entities.back());
	}

	// Death Sensor
	m_entities.push_back(m_registry.create());
	m_registry.emplace<TransformComponent>(m_entities.back(), glm::vec2(5.12f, 0.65f));
	m_registry.emplace<RigidBodyComponent>(m_entities.back(), m_entities.back(), RigidBodyType::_static);
	m_registry.emplace<BoxColliderComponent>(m_entities.back(), m_entities.back(), glm::vec2(0.f), glm::vec2(4.5f, 0.125f), sensorMaterial);
}


void SceneLayer::onRender()
{
	RendererCommon::actionCommand(m_clear);

	Renderer2D::begin(m_swu);

	auto renderView = m_registry.view<TransformComponent, RenderComponent>();
	for (auto entity : renderView)
	{
		auto& transformComp = m_registry.get<TransformComponent>(entity);
		auto& renderComp = m_registry.get<RenderComponent>(entity);

		Renderer2D::submit(Quad::createCentreHalfExtents(transformComp.position, renderComp.halfExtents), renderComp.tint, renderComp.texture, transformComp.angle);
	}

	Renderer2D::end();

	// Line rendering debug - change #if 0 to #if 1 to enable
#if 0
	LineRenderer::begin(m_swu);

	auto rigidBodyView = m_registry.view<RigidBodyComponent>();
	for (auto entity : rigidBodyView)
	{
		auto& rigidBodyComp = m_registry.get<RigidBodyComponent>(entity);
		glm::vec2 pos(rigidBodyComp.body->GetPosition().x, rigidBodyComp.body->GetPosition().y);
		
		// Box Colliders
		if (m_registry.has<BoxColliderComponent>(entity))
		{
			auto& boxComp = m_registry.get<BoxColliderComponent>(entity);
			LineRenderer::submit(pos + boxComp.offset, boxComp.halfExtents, glm::degrees(rigidBodyComp.body->GetAngle()), glm::vec4(0.f, 0.f, 1.f, 1.f));
		}

		// Circle colliders
		if (m_registry.has<CircleColliderComponent>(entity))
		{
			auto& circleComp = m_registry.get<CircleColliderComponent>(entity);
			glm::vec2 rotatedOffset;
			rotatedOffset.x = cos(rigidBodyComp.body->GetAngle()) * circleComp.offset.x - sin(rigidBodyComp.body->GetAngle()) * circleComp.offset.y;
			rotatedOffset.y = cos(rigidBodyComp.body->GetAngle()) * circleComp.offset.y + sin(rigidBodyComp.body->GetAngle()) * circleComp.offset.x;
			LineRenderer::submit(pos + rotatedOffset, circleComp.radius, glm::vec4(0.f, 0.f, 1.f, 1.f));
		}

		// Collider groups
		if (m_registry.has<ColliderGroupComponent>(entity))
		{
			auto& colliderGroupComp = m_registry.get<ColliderGroupComponent>(entity);

			for (auto& boxComp : colliderGroupComp.boxColliders)
			{
				LineRenderer::submit(pos + boxComp.offset, boxComp.halfExtents, glm::degrees(rigidBodyComp.body->GetAngle()), glm::vec4(0.f, 0.f, 1.f, 1.f));
			}

			for (auto& circleComp : colliderGroupComp.circleColliders)
			{
				glm::vec2 rotatedOffset;
				rotatedOffset.x = cos(rigidBodyComp.body->GetAngle()) * circleComp.offset.x - sin(rigidBodyComp.body->GetAngle()) * circleComp.offset.y;
				rotatedOffset.y = cos(rigidBodyComp.body->GetAngle()) * circleComp.offset.y + sin(rigidBodyComp.body->GetAngle()) * circleComp.offset.x;
				LineRenderer::submit(pos + rotatedOffset, circleComp.radius, glm::vec4(0.f, 0.f, 1.f, 1.f));
			}
		}
	}

	LineRenderer::end();
#endif
}

void SceneLayer::onUpdate(float timestep)
{
	auto& app = Engine::Application::getInstance();
	auto world = app.getWorld();

	auto rigidBodyView = m_registry.view<Engine::TransformComponent, Engine::RigidBodyComponent>();
	for (auto entity : rigidBodyView)
	{
		auto& transformComp = m_registry.get<Engine::TransformComponent>(entity);
		auto& rigidBodyComp = m_registry.get<Engine::RigidBodyComponent>(entity);

		transformComp.position.x = rigidBodyComp.body->GetPosition().x;
		transformComp.position.y = rigidBodyComp.body->GetPosition().y;
		transformComp.angle = rigidBodyComp.body->GetAngle();
	}

	auto nativeScriptView = m_registry.view<Engine::NativeScriptComponent>();
	for (auto entity : nativeScriptView)
	{
		auto& nsc = m_registry.get<Engine::NativeScriptComponent>(entity);
		nsc.onUpdate(timestep);

		if (nsc.isRegisteredForDeletion())
		{
			auto& rigidBodyComp = m_registry.get<Engine::RigidBodyComponent>(entity);
			world->DestroyBody(rigidBodyComp.body);

			for (auto it = m_entities.begin(); it != m_entities.end(); ++it)
			{
				if (*it == entity)
				{
					m_entities.erase(it);
					break;
				}
			}
			m_registry.destroy(entity);
		}
	}
}

