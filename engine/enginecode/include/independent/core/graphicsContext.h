/* \file graphicsContext.h */
#pragma once

namespace
{
	/**
	\class GraphicsContext
	A graphics API context (base class) which can be attached to a window
	*/
	class GraphicsContext
	{
	public:
		virtual void init() = 0; //!< Init the graphics context for the given windowing API
		virtual void swapBuffers() = 0; //!< Swap the front and back buffer (double buffering)
		virtual void updateViewport(int32_t width, int32_t height) = 0; //!< Change the viewport
	};
}
