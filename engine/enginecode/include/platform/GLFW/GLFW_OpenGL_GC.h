/* GLFW_OpenGL_GC.h */
#pragma once

#include "core/graphicsContext.h"

namespace Engine
{
	class GLFW_OpenGL_GC : public GraphicsContext
	{
	public:
		GLFW_OpenGL_GC(GLFWwindow* win) : m_window(win) {}
		virtual void init() override; //!< Init the graphics context for the given windowing API
		virtual void swapBuffers() override; //!< Swap the front and back buffer (double buffering)
		virtual void updateViewport(int32_t width, int32_t height) override; //!< Change the viewport
	private:
		GLFWwindow * m_window; //!< Pointer to GLFW window
	};
}

