/* \file fixed2DOrthoController.h */
#pragma once

#include "camera.h"

#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>

namespace Engine
{
	/** \struct Fixed2DParams
		\brief Parameters for a fixed 2D orthographic camera
	*/

	struct Fixed2DParams
	{
		float top = 0;
		float left = 0;
		float width = 800;
		float height = 600;
	};

	/** \class FixedOrthoCameraController2D
		\brief Basic fixed 2D orthographic camera
	*/

	class FixedOrthoCameraController2D : public CameraController
	{
	public:
		FixedOrthoCameraController2D(Fixed2DParams& params) //!< Contructor
		{
			m_camera.view = glm::mat4(1.0f);
			m_camera.projection = glm::ortho(params.left, params.width + params.left, params.top + params.height, params.top);
		}
	};
}
