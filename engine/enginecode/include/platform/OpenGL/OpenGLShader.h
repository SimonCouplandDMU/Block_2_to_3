/* \file OpenGLShader.h*/
#pragma once

#include "rendering/shader.h"

namespace Engine {
	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader(const char* vertexFilepath, const char* fragmentFilepath);
		OpenGLShader(const char* filepath);
		~OpenGLShader();
		virtual uint32_t getID() const override{ return m_OpenGL_ID; }

		virtual void uploadInt(const char* name, int value) override;
		virtual void uploadIntArray(const char* name, int32_t* values, uint32_t count) override;
		virtual void uploadFloat(const char* name, float value) override;
		virtual void uploadFloat2(const char* name, const glm::vec2& value) override;
		virtual void uploadFloat3(const char* name, const glm::vec3& value) override;
		virtual void uploadFloat4(const char* name, const glm::vec4& value) override;
		virtual void uploadMat4(const char* name, const glm::mat4& value) override;
	private:
		uint32_t m_OpenGL_ID;
		void compileAndLink(const char * vertexShaderSrc, const char * fragmentShaderSrc);
	};
}
