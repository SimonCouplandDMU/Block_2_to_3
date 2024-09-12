/* sceneLayer.h */
#pragma once

#include "engine.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace Engine;

class SceneLayer : public Layer
{
public:
	SceneLayer(const char * name, std::vector<entt::entity>& entities, entt::registry& registry);
	void onRender() override;
	void onUpdate(float timestep) override;
private:
	glm::mat4 m_view; // camera view matrix
	glm::mat4 m_proj; // camera proj matrix

	SceneWideUniforms m_swu; // Data used throughout the scene
	std::shared_ptr<RenderCommand> m_clear;

	std::vector<entt::entity>& m_entities; //!< Our entities
	entt::registry& m_registry; //!< ECS

	std::shared_ptr<Texture> m_texture;//!< textures for our scene
	CollisionListener m_collisionListener; //!< Physics listener
};