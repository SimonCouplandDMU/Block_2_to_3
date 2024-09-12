/** \file GLFWSystem.h */
#pragma once

#include "systems/system.h"
#include "systems/log.h"

#include <GLFW/glfw3.h>

namespace Engine
{
	class GLFWSystem : public System
	{
		virtual void start(SystemSignal init = SystemSignal::None, ...) override//!< Start the system
		{
			auto errorCode = glfwInit();
			if (!errorCode)
			{
				Log::error("Cannot init GLFW: {0}", errorCode);
			}
		}
		virtual void stop(SystemSignal close = SystemSignal::None, ...) override //!< Stop the system
		{
			glfwTerminate();
		}
	};
}
