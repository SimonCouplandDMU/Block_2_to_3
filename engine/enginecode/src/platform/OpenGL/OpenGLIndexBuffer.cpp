/* \file OpenGLIndexBuffer.cpp*/

#include "engine_pch.h"
#include <glad/glad.h>
#include "platform/OpenGL/OpenGLIndexBuffer.h"

namespace Engine
{
	OpenGLIndexBuffer::OpenGLIndexBuffer(uint32_t * indices, uint32_t count) : m_count(count)
	{
		glCreateBuffers(1, &m_OpenGL_ID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_OpenGL_ID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint32_t) * count, indices, GL_DYNAMIC_DRAW);
	}

	OpenGLIndexBuffer::~OpenGLIndexBuffer()
	{
		glDeleteBuffers(1, &m_OpenGL_ID);
	}

	void OpenGLIndexBuffer::edit(uint32_t * indices, uint32_t count, uint32_t offset)
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_OpenGL_ID);
		glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint32_t) * offset, sizeof(uint32_t) * count, indices);
	}
}