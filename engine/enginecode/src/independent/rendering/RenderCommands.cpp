/** \file RenderCommands.cpp */

#include "engine_pch.h"
#include "rendering/RenderCommands.h"
#include "rendering/RenderAPI.h"
#include <glad/glad.h>
namespace Engine
{
	std::function<void(void)> RenderCommandFactory::getClearColourAndDepthBufferCommand()
	{
		switch (RenderAPI::getAPI())
		{
		case RenderAPI::API::Direct3D:
			return std::function<void(void)>();
		case RenderAPI::API::None:
			return std::function<void(void)>();
		case RenderAPI::API::OpenGL:
			return []() {glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); };
		case RenderAPI::API::Vulkan:
			return std::function<void(void)>();
		default:
			return std::function<void(void)>();
		}
		
	}
	std::function<void(void)> RenderCommandFactory::getClearColourBufferCommand()
	{
		switch (RenderAPI::getAPI())
		{
		case RenderAPI::API::Direct3D:
			return std::function<void(void)>();
		case RenderAPI::API::None:
			return std::function<void(void)>();
		case RenderAPI::API::OpenGL:
			return []() {glClear(GL_COLOR_BUFFER_BIT); };
		case RenderAPI::API::Vulkan:
			return std::function<void(void)>();
		default:
			return std::function<void(void)>();
		}
	}
	std::function<void(void)> RenderCommandFactory::getClearDepthBufferCommand()
	{
		switch (RenderAPI::getAPI())
		{
		case RenderAPI::API::Direct3D:
			return std::function<void(void)>();
		case RenderAPI::API::None:
			return std::function<void(void)>();
		case RenderAPI::API::OpenGL:
			return []() {glClear(GL_DEPTH_BUFFER_BIT); };
		case RenderAPI::API::Vulkan:
			return std::function<void(void)>();
		default:
			return std::function<void(void)>();
		}
	}
	std::function<void(void)> RenderCommandFactory::getEnableBlendingCommand()
	{
		switch (RenderAPI::getAPI())
		{
		case RenderAPI::API::Direct3D:
			return std::function<void(void)>();
		case RenderAPI::API::None:
			return std::function<void(void)>();
		case RenderAPI::API::OpenGL:
			return []() {glEnable(GL_BLEND); };
		case RenderAPI::API::Vulkan:
			return std::function<void(void)>();
		default:
			return std::function<void(void)>();
		}
	}
	std::function<void(void)> RenderCommandFactory::getDisableBlendingCommand()
	{
		switch (RenderAPI::getAPI())
		{
		case RenderAPI::API::Direct3D:
			return std::function<void(void)>();
		case RenderAPI::API::None:
			return std::function<void(void)>();
		case RenderAPI::API::OpenGL:
			return []() {glDisable(GL_BLEND); };
		case RenderAPI::API::Vulkan:
			return std::function<void(void)>();
		default:
			return std::function<void(void)>();
		}
	}
	std::function<void(void)> RenderCommandFactory::getEnableDepthTestingCommand()
	{
		switch (RenderAPI::getAPI())
		{
		case RenderAPI::API::Direct3D:
			return std::function<void(void)>();
		case RenderAPI::API::None:
			return std::function<void(void)>();
		case RenderAPI::API::OpenGL:
			return []() {glEnable(GL_DEPTH_TEST); };
		case RenderAPI::API::Vulkan:
			return std::function<void(void)>();
		default:
			return std::function<void(void)>();
		}
	}
	std::function<void(void)> RenderCommandFactory::getDisableDepthTestingCommand()
	{
		switch (RenderAPI::getAPI())
		{
		case RenderAPI::API::Direct3D:
			return std::function<void(void)>();
		case RenderAPI::API::None:
			return std::function<void(void)>();
		case RenderAPI::API::OpenGL:
			return []() {glDisable(GL_DEPTH_TEST);  };
		case RenderAPI::API::Vulkan:
			return std::function<void(void)>();
		default:
			return std::function<void(void)>();
		}
	}
	std::function<void(void)> RenderCommandFactory::getStandardBlendCommand()
	{
		switch (RenderAPI::getAPI())
		{
		case RenderAPI::API::Direct3D:
			return std::function<void(void)>();
		case RenderAPI::API::None:
			return std::function<void(void)>();
		case RenderAPI::API::OpenGL:
			return []() {glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); };
		case RenderAPI::API::Vulkan:
			return std::function<void(void)>();
		default:
			return std::function<void(void)>();
		}
	}
	std::function<void(void)> RenderCommandFactory::getAdditiveBlendCommand()
	{
		switch (RenderAPI::getAPI())
		{
		case RenderAPI::API::Direct3D:
			return std::function<void(void)>();
		case RenderAPI::API::None:
			return std::function<void(void)>();
		case RenderAPI::API::OpenGL:
			return []() {glBlendFunc(GL_ONE, GL_ONE); };
		case RenderAPI::API::Vulkan:
			return std::function<void(void)>();
		default:
			return std::function<void(void)>();
		}
	}
	std::function<void(void)> RenderCommandFactory::getSetClearColourCommand(float r, float g, float b, float a)
	{
		switch (RenderAPI::getAPI())
		{
		case RenderAPI::API::Direct3D:
			return std::function<void(void)>();
		case RenderAPI::API::None:
			return std::function<void(void)>();
		case RenderAPI::API::OpenGL:
			return [r, g, b, a]() {glClearColor(r, g, b, a); };
		case RenderAPI::API::Vulkan:
			return std::function<void(void)>();
		default:
			return std::function<void(void)>();
		}
	}
}