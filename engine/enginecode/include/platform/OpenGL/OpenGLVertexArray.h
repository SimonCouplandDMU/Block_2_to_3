/* \file OpenGLVertexArray */
#pragma once

#include "rendering/vertexArray.h"

namespace Engine
{
	class OpenGLVertexArray : public VertexArray
	{
	private:
		std::vector<std::shared_ptr<VertexBuffer>> m_vertexBuffers; //!< Container for vertex buffers
		std::shared_ptr<IndexBuffer> m_indexBuffer; //!< Index bufer for all vertex buffers
		uint32_t m_OpenGL_ID; //!< Id of the buffer in OpenGL
		uint32_t m_attributeIndex = 0; //!< Index of next buffer attribute to be set
	public:
		OpenGLVertexArray(); //!< Constructor
		~OpenGLVertexArray(); //!< Destructor;
		inline virtual uint32_t getID() const override { return m_OpenGL_ID; } //!<Get the render ID of this vertex array
		void addVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer) override; //!< Add a vertex buffer
		void setIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer) override; //!< Set the index buffer for all vertex buffer
		std::vector<std::shared_ptr<VertexBuffer>> getVertexBuffers() const override; //!< Get the vertex buffers
		std::shared_ptr<IndexBuffer> getIndexBuffer() const override; //!< Get the index buffer
		inline uint32_t getDrawCount() const override {
			return m_indexBuffer->getCount();
		}; //!< returns the number of primitives to draw
	};
}
