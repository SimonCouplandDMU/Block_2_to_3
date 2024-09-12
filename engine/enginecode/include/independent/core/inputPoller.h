/* \file inputPoller.h */

#include <glm/glm.hpp>

namespace Engine
{
	/* \class InputPoller
	*	API agnostic input poller for getting curretn keyboard/mouse state
	*/
	class InputPoller
	{
	public:
		static bool isKeyPressed(int32_t keyCode); //!< is the key pressed?
		static bool isMouseButtonPressed(int32_t mouseButton); // is the mouse button pressed
		static glm::vec2 getMousePosition(); //!< current mouse position
		static void setNativeWindow(void* nativeWin); //!< Set the native window 
		inline static float getMouseX() { return getMousePosition().x; } //!< Get the current x position of the mouse
		inline static float getMouseY() { return getMousePosition().y; } //!< Get the current y position of the mouse
	};
}
#pragma once
