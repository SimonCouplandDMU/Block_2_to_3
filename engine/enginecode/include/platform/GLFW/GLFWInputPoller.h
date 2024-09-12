/* \file GLFWInputPoller.h */

#include <glm/glm.hpp>
#include <GLFW/glfw3.h>

namespace Engine
{
	/* \class GLFWInputPoller
	*	Input poller for getting curretn keyboard/mouse state specific to the GLFW system
	*/
	class GLFWInputPoller
	{
	public:
		static bool isKeyPressed(int32_t keyCode); //!< is the key pressed?
		static bool isMouseButtonPressed(int32_t mouseButton); // is the mouse button pressed
		static glm::vec2 getMousePosition(); //!< current mouse position
		static void setCurrentWindow(GLFWwindow* newWin) { s_window = newWin; }
	private:
		static GLFWwindow* s_window; //!< Current GLFW window
	};
}
#pragma once
