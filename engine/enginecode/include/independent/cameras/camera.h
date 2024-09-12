/* \file camera.h */
#pragma once

#include <glm/glm.hpp>
#include "events/events.h"

namespace Engine
{
	/** \class Camera
		\brief Basic Camera base class
	*/
	class Camera
	{
	public:
		glm::mat4 view; //!< View matrix of the camera
		glm::mat4 projection; //!< Projection matrix of the camera
		void updateView(const glm::mat4& transform) //!< Update the view matrix as an inverse of a model (transform) matrix
		{
			view = glm::inverse(transform);
		}
	};

	/** \class CameraController
		\brief Basic Camera Controller base class, replace later on when ECS is implemented
	*/
	class CameraController
	{
	public:
		Camera& getCamera() { return m_camera; } //!< Accessor for camera
		virtual void onUpdate(float t) {}; //!< Can update the camera
		virtual void onResize(WindowResizeEvent& e) {}; //!< Can handle events
	protected:
		Camera m_camera; //!< Camera being controlled
	};
}