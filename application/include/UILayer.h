/* UILayer.h */
#pragma once

#include "engine.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace Engine;

class UILayer : public Layer
{
public:
	UILayer(const char * name);
	void onRender() override;
	void onUpdate(float timestep) override;
private:
	glm::mat4 m_view; // camera view matrix
	glm::mat4 m_proj; // camera proj matrix

	SceneWideUniforms m_swu; // Data used throughout the scene
	std::shared_ptr<Texture> m_texture;//!< textures for our scene
	SubTexture scoreLabel;
	SubTexture livesLabel;
	SubTexture gameOverLabel;
	SubTexture youWinLabel;
	SubTexture ball;
	std::array<SubTexture, 10> numberLabels;

	Quad scoreLabelQuad;
	Quad livesLabelQuad;
	Quad gameOverQuad;
	Quad youWinQuad;
	std::array<Quad, 3> ballQuads;
	std::array<Quad, 10> numberQuads;
};