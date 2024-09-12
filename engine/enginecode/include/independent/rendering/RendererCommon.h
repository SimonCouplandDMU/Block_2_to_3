/** \file rendererCommon.h*/
#pragma once


#include <glm/glm.hpp>
#include <unordered_map>
#include <memory>
#include <array>
#include "rendering/shaderDataType.h"
#include "rendering/vertexArray.h"
#include "rendering/texture.h"
#include "rendering/subTexture.h"
#include "rendering/shader.h"
#include "rendering/RenderCommands.h"
#include "rendering/bufferLayout.h"
#include "rendering/uniformBuffer.h"
#include "rendering/textureUnitManager.h"
#include "rendering/textureAtlas.h"

namespace Engine
{
	using SceneWideUniforms = std::unordered_map<const char *, std::pair<ShaderDataType, void *>>;

	/** \class RendererCommon
	**  \brief Data and functuionality common to all rendererds
	*/
	class RendererCommon
	{
	public:
		static void actionCommand(std::shared_ptr<RenderCommand>& command) { command->m_action(); } //!< Action a command
		static void actionCommand(std::unique_ptr<RenderCommand>& command) { command->m_action(); } //!< Action a command
		static TextureUnitManager texUnitMan; //!< Texture unit manager - control use of texture slot on the GPU
		static uint32_t pack(const glm::vec4& tint); //!< Pack a float 4 to a normalised 32 bit Uint (so RGBA)
		static std::array<int32_t, 32> textureUnits; //!< Texture units
		static std::shared_ptr<Texture> defaultTexture; //!< Default white texture
		static SubTexture defaultSubTexture;  //!< Default white sub texture
		static glm::vec4 defaultTint; //!< Default white tint

		template<class G>
		static std::vector<G> concatonate(const std::vector<G>& a, const std::vector<G>& b); //!< Concatonate geometry together
		template<class G>
		static void append(const std::vector<G>& src, std::vector<G>& dst); //!< Append once piece of geometry to another

		//!< Held render commands
		static std::unique_ptr<RenderCommand> clearColourDepthBuffer; 
		static std::unique_ptr<RenderCommand> enableBlending;
		static std::unique_ptr<RenderCommand> disableBlending;
		static std::unique_ptr<RenderCommand> enableDepthTest;
		static std::unique_ptr<RenderCommand> disableDepthTest;
		static std::unique_ptr<RenderCommand> setStandardBlend;
		static std::unique_ptr<RenderCommand> setAdditiveBlend;
	};

	template<class G>
	static std::vector<G> RendererCommon::concatonate(const std::vector<G>& a, const std::vector<G>& b)
	{
		std::vector<G> result;
		result.resize(a.size() + b.size());
		std::copy(a.begin(), a.end(), result.begin());
		std::copy(b.begin(), b.end(), result.begin() + a.size());
		return result;
	}

	template<class G>
	static void RendererCommon::append(const std::vector<G>& src, std::vector<G>& dst)
	{
		dst.resize(dst.size() + src.size());
		std::copy(b.begin(), b.end(), result.begin() + a.size());
	}
	
	class Quad
	{
	public:
		Quad() = default;
		static Quad createCentreHalfExtents(const glm::vec2& centre, const glm::vec2& halfExtents);
	private:
		glm::vec3 m_translate = glm::vec3(0.f); //!< Translation vector
		glm::vec3 m_scale = glm::vec3(1.f); //!< Scale vector
		friend class Renderer2D;
	};
}
