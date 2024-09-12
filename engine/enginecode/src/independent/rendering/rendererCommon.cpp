/* \file RendererCommon.cpp */

#include "engine_pch.h"

#include "rendering/RendererCommon.h"

namespace Engine
{
	TextureUnitManager RendererCommon::texUnitMan = TextureUnitManager(32);

	std::array<int32_t, 32> RendererCommon::textureUnits = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31 };
	std::shared_ptr<Texture> RendererCommon::defaultTexture = nullptr;
	SubTexture RendererCommon::defaultSubTexture;
	glm::vec4 RendererCommon::defaultTint = glm::vec4(1.0f);

	std::unique_ptr<RenderCommand> RendererCommon::clearColourDepthBuffer(Engine::RenderCommandFactory::createCommand(Engine::RenderCommand::Commands::clearColourAndDepthBuffer));
	std::unique_ptr<RenderCommand> RendererCommon::enableBlending(Engine::RenderCommandFactory::createCommand(Engine::RenderCommand::Commands::enableBlending));
	std::unique_ptr<RenderCommand> RendererCommon::disableBlending(Engine::RenderCommandFactory::createCommand(Engine::RenderCommand::Commands::disableBlending));
	std::unique_ptr<RenderCommand> RendererCommon::enableDepthTest(Engine::RenderCommandFactory::createCommand(Engine::RenderCommand::Commands::enableDepthTesting));
	std::unique_ptr<RenderCommand> RendererCommon::disableDepthTest(Engine::RenderCommandFactory::createCommand(Engine::RenderCommand::Commands::disableDepthTesting));
	std::unique_ptr<RenderCommand> RendererCommon::setStandardBlend(Engine::RenderCommandFactory::createCommand(Engine::RenderCommand::Commands::setStandardBlendFunc));
	std::unique_ptr<RenderCommand> RendererCommon::setAdditiveBlend(Engine::RenderCommandFactory::createCommand(Engine::RenderCommand::Commands::setAdditiveBlendFunc));

	uint32_t RendererCommon::pack(const glm::vec4& tint)
	{
		uint32_t result = 0;

		uint32_t r = (static_cast<uint32_t>(tint.r * 255.f)) << 0;
		uint32_t g = (static_cast<uint32_t>(tint.g * 255.f)) << 8;
		uint32_t b = (static_cast<uint32_t>(tint.b * 255.f)) << 16;
		uint32_t a = (static_cast<uint32_t>(tint.a * 255.f)) << 24;

		result = (r | g | b | a);
		return result;
	}
}