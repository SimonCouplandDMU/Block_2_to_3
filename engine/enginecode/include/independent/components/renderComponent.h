#pragma once
#include <glm/glm.hpp>
namespace Engine
{
	struct RenderComponent
	{
		RenderComponent(glm::vec2& he, glm::vec4& colour) 
			: halfExtents(he), tint(colour), texture(RendererCommon::defaultSubTexture) {}

		RenderComponent(glm::vec2& he, SubTexture& tex)
			: halfExtents(he), tint(RendererCommon::defaultTint), texture(tex) {}

		RenderComponent(glm::vec2& he, glm::vec4& colour, SubTexture& tex)
			: halfExtents(he), tint(colour), texture(tex) {}

		glm::vec2 halfExtents;
		glm::vec4 tint;
		SubTexture texture;

	};
}