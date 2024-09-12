/* \file OpenGLIndirectBuffer.cpp */

#include "engine_pch.h"
#include "platform/OpenGL/OpenGLIndirectBuffer.h"
#include <glad/glad.h>

namespace Engine
{
	OpenGLIndirectBuffer::OpenGLIndirectBuffer(DrawElementsIndirectCommand * commands, uint32_t count)
	{
		glGenBuffers(1, &m_OpenGL_ID);

		glBindBuffer(GL_DRAW_INDIRECT_BUFFER, m_OpenGL_ID);
		glBufferData(GL_DRAW_INDIRECT_BUFFER, sizeof(DrawElementsIndirectCommand) * count, commands, GL_DYNAMIC_DRAW);
	}

	OpenGLIndirectBuffer::~OpenGLIndirectBuffer()
	{
		glDeleteBuffers(1, &m_OpenGL_ID);
	}

	void OpenGLIndirectBuffer::edit(DrawElementsIndirectCommand * commands, uint32_t count, uint32_t offset)
	{
		glBindBuffer(GL_DRAW_INDIRECT_BUFFER, m_OpenGL_ID);
		glBufferSubData(GL_DRAW_INDIRECT_BUFFER, sizeof(DrawElementsIndirectCommand) * offset, sizeof(DrawElementsIndirectCommand) * count, commands);
	}
}