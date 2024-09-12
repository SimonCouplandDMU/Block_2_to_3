/** \file renderer2D.h */
#pragma once

#include "rendering/RendererCommon.h"

namespace Engine
{
	/** \class Renderer2DVertex
	*	Definition of vertex used in the 2D renderer
	*/
	class Renderer2DVertex
	{
	public:
		Renderer2DVertex() = default; //!< Default constructor
		Renderer2DVertex(const glm::vec4& pos, const glm::vec2& UVs, uint32_t tu, const glm::vec4& pTint) : //!< Constructor with stuff
			position(pos), uvCoords(UVs), texUnit(tu), tint(RendererCommon::pack(pTint)) {}
		glm::vec4 position; //!< Vertex position (homogeneuous co-ords)
		glm::vec2 uvCoords; //!< UV cords
		uint32_t texUnit; //!< TEx unit for the texture
		uint32_t tint; //!< Tint applied to the vertex
		static VertexBufferLayout layout; //!< Layout of the vertex buffer for this type
	};


	/** \class Renderer2D
	** \brief Class which allows the rendering of simple 2D primitives
	*/
	class Renderer2D
	{
	public:
		static void init(uint32_t batchSize, const char * fontFilePath, uint32_t charSize); //!< Init the internal data of the renderer
		static void begin(const SceneWideUniforms& swu); //!< Begin a 2D scene
		static void submit(const Quad& quad, const glm::vec4& tint); //!< Render a tinted quad
		static void submit(const Quad& quad, const SubTexture& texture); //!< Render a textured quad
		static void submit(const Quad& quad, const glm::vec4& tint, const SubTexture& texture); //!< Render a textured and tinted quad
		static void submit(const Quad& quad, const glm::vec4& tint, float angle, bool degrees = false); //!< Render a textured and tinted quad
		static void submit(const Quad& quad, const SubTexture& texture, float angle, bool degrees = false); //!< Render a textured and tinted quad
		static void submit(const Quad& quad, const glm::vec4& tint, const SubTexture& texture, float angle, bool degrees = false); //!< Render a textured and tinted quad

		static void submit(char ch, const glm::vec2& position, float& advance, const glm::vec4& tint); //!< Render a single character with a tint
		static void submit(const char * text, const glm::vec2& position, const glm::vec4& tint); //!< Render a single character with a tint

		static void end(); //!< Stop rendering a 2D scene
		static void flush(); //!< Flsuh the renderer
	private:
		/** \struct GlyphData
		\brief Data associated with a single glyph
		*/
		struct GlyphData
		{
			unsigned char ch;
			glm::vec2 size;
			glm::vec2 bearing;
			float advance;
			SubTexture subTexture;
		};
		/** \struct InternalData
		\brief Data held by the renderer
		*/
		struct InternalData
		{
			std::shared_ptr<Shader> shader; //!< Shader used render the batches of quads
			std::shared_ptr<VertexArray> VAO; //!< Vertex array
			std::shared_ptr<UniformBuffer> UBO; //!< Uniform buffer object
			std::array<glm::vec4, 4> quad; //!< Prototypical quad used by the renderer
			uint32_t batchSize; //!< Maximum batch size
			uint32_t drawCount; //!< Curretn draw count - always <= batch size
			std::vector<Renderer2DVertex> vertices; //!< CPU side vertices, builds to batches
			
			unsigned char firstGlyph = 32; //!< First ASCII glyph
			unsigned char lastGlyph = 126; //!< Last ASCII glyph
			std::vector <GlyphData> glyphData; //!< Glyphs data
			TextureAtlas glyphAtlas; //!< Glyph textures
		};

		static std::shared_ptr<InternalData> s_data; //!< Internal data

		static void RtoRGBA(unsigned char *DSTbuffer, unsigned char * SRCbuffer, uint32_t width, uint32_t height); //!< Convert buffer Red to RGBA buffer
	};
}