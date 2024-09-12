/* \file shader.h*/
#pragma once

#include <cstdint>
#include <glm/glm.hpp>

namespace Engine
{
	/** \class Shader
	**  \brief API agnositc abstraction of a shader program
	*/

	class Shader
	{
	public:
		virtual ~Shader() = default; //!< Destructor
		virtual uint32_t getID() const = 0; //!< Get the GPU ID of this shader program
		virtual void uploadInt(const char* name, int value) = 0; //!< Upload an integer uniform
		virtual void uploadIntArray(const char* name, int32_t* values, uint32_t count) = 0; //!< Upload an integer array uniform
		virtual void uploadFloat(const char* name, float value) = 0; //!< Upload a float uniform
		virtual void uploadFloat2(const char* name, const glm::vec2& value) = 0; //!< Upload a float[2] uniform
		virtual void uploadFloat3(const char* name, const glm::vec3& value) = 0; //!< Upload a float[3] uniform
		virtual void uploadFloat4(const char* name, const glm::vec4& value) = 0; //!< Upload a float[4] uniform
		virtual void uploadMat4(const char* name, const glm::mat4& value) = 0; //!< Upload a Mat uniform

		static Shader * create(const char* vertexFilepath, const char* fragmentFilepath); //!< API agnoisitc create from filepaths
		static Shader * create(const char* filepath); //!< API agnostic create from single filepath
	};
}
