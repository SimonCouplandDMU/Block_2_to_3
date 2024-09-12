/* \file OpenGLVertexBuffer.h */
#pragma once

#include "rendering/vertexBuffer.h"

namespace Engine
{
	class OpenGLVertexBuffer : public VertexBuffer
	{
	public:
		OpenGLVertexBuffer(void* vertices, uint32_t size, VertexBufferLayout layout);
		~OpenGLVertexBuffer();
		virtual void edit(void* vertices, uint32_t size, uint32_t offset) override;
		virtual inline uint32_t getID() const override { return m_OpenGL_ID; }
		virtual inline const VertexBufferLayout& getLayout() const override { return m_layout; }
	private:
		uint32_t m_OpenGL_ID; //!< Render ID
		VertexBufferLayout m_layout;
	};
}