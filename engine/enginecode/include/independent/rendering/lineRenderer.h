/** \file renderer2D.h */
#pragma once

#include "rendering/RendererCommon.h"

namespace Engine
{
	/** \class LineRendererVertex
	*	Definition of vertex used in the Line renderer
	*/
	class LineRendererVertex
	{
	public:
		LineRendererVertex() = default; //!< Default constructor
		LineRendererVertex(const glm::vec4& pos, const glm::vec4& pTint) : //!< Constructor with stuff
			position(pos), tint(RendererCommon::pack(pTint)) {}
		glm::vec4 position; //!< Vertex position (homogeneuous co-ords)
		uint32_t tint; //!< Tint applied to the vertex
		static VertexBufferLayout layout; //!< Layout of the vertex buffer for this type
	};


	/** \class LineRenderer
	** \brief Class which allows the rendering of lines and shapes
	*/
	class LineRenderer
	{
	public:
		static void init(uint32_t batchSize); //!< Init the internal data of the renderer
		static void begin(const SceneWideUniforms& swu); //!< Begin a 2D scene
		static void submit(const glm::vec2& start, const glm::vec2& end, const glm::vec4& tint); //!< Render a tinted line segment
		static void submit(const glm::vec2& centre, const glm::vec2& halfExtents, float angle, const glm::vec4& tint); //!< Render a tinted box
		static void submit(const glm::vec2& centre, float radius, const glm::vec4& tint); //!< Render a tinted circle

		static void end(); //!< Stop rendering a 2D scene
		static void flush(); //!< Flush the renderer
	private:
		/** \struct InternalData
		\brief Data held by the renderer
		*/
		struct InternalData
		{
			std::shared_ptr<Shader> shader; //!< Shader used render the batches of quads
			std::shared_ptr<VertexArray> VAO; //!< Vertex array
			std::shared_ptr<UniformBuffer> UBO; //!< Uniform buffer object
			uint32_t batchSize; //!< Maximum batch size
			uint32_t drawCount; //!< Curretn draw count - always <= batch size
			std::vector<LineRendererVertex> vertices; //!< CPU side vertices, builds to batches
			float circleVertexCount = 60.f; //!< Number of points in a circle (minus 1)
		};

		static std::shared_ptr<InternalData> s_data; //!< Internal data
	};
}