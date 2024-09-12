/* \file subTexture.h */

#pragma once

#include "platform/OpenGL/OpenGLTexture.h"
#include <memory>
#include <glm/glm.hpp>

namespace Engine {

	/** \class SubTexture
	**  \brief A part of texture complete with size and UV co-ords. Does not hold texels!
	*/

	class SubTexture
	{
	public:
		SubTexture() {}; //!< Default constructor
		SubTexture(const std::shared_ptr<Texture>& texture, const glm::vec2& UVStart, const glm::vec2& UVEnd); //!< Constructor with stuff
		inline glm::vec2 getUVStart() const { return m_UVStart; } //!< Get the start UV co-ords
		inline glm::vec2 getUVEnd()	  const { return m_UVEnd; } //!< Get the end UV co-ords
		glm::ivec2 getSize() const { return m_size; } //!< Get the size of the subtexture 
		glm::vec2 getSizef() const { return { static_cast<float>(m_size.x), static_cast<float>(m_size.y) }; } //!< Get the size of the subtexture  as float
		inline uint32_t getWidth()   const { return m_size.x; } //!< Get the width of the subtexture 
		inline uint32_t getHeight()  const { return m_size.y; } //!< Get the height of the subtexture 
		inline float getWidthf()  const { return static_cast<float>(m_size.x); } //!< Get the width of the subtexture as a float
		inline float getHeightf() const { return static_cast<float>(m_size.y); } //!< Get the height of the subtexture as a float
		float transformU(float U); //!< Transform original to atlased co-ords - U component
		float transformV(float V); //!< Transform original to atlased co-ords - V component
		glm::vec2 transformUV(glm::vec2 UV); //!< Transform original to atlased co-ords
		inline const std::shared_ptr<Texture>& getBaseTexture() const { return m_texture; } //!, Get the base texture
	private:
		std::shared_ptr<Texture> m_texture; //!< base texture
		glm::vec2 m_UVStart; //!< start UV co-ords
		glm::vec2 m_UVEnd; //!< end UV co-ords
		glm::ivec2 m_size; //!< Size in pixels
	};
}