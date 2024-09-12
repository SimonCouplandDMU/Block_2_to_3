#pragma once
#include <glm/glm.hpp>

namespace Engine
{
	struct TransformComponent
	{
		TransformComponent(glm::vec2& pos, float ang = 0.f) : position(pos), angle(ang) {}

		glm::vec2 position; // X and Y
		float angle; // Angle in radians
	};
}