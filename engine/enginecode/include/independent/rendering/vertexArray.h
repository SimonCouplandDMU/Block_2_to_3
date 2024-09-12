/* \file vertexArray.h */

#pragma once

#include <vector>
#include <memory>
#include "VertexBuffer.h"
#include "IndexBuffer.h"

namespace Engine
{
	/** \class VertexArray
	*	Supposedly API agnositc vertex array - only need for OpenGL
	*/

	class VertexArray
	{
	public:
		virtual ~VertexArray() = default; //!< Destructor
		virtual void addVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer) = 0; //!< Add a vertex buffer
		virtual void setIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer) = 0; //!< Set the index buffer
		virtual inline uint32_t getID() const = 0; //!< Get the GPU id of this array
		virtual inline uint32_t getDrawCount() const = 0; //!< Get the draw count from the index buffer
		virtual std::vector<std::shared_ptr<VertexBuffer>> getVertexBuffers() const = 0; //!< Get the vertex buffers
		virtual std::shared_ptr<IndexBuffer> getIndexBuffer() const = 0; //!< Get the index buffer

		static VertexArray* create(); //!< Create vertex array
	};
}