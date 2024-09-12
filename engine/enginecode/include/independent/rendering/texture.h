/* \file texture.h */

#pragma once

#include <cstdint>

namespace Engine
{
	/** \class Texture
	**  \brief A texture held on the GPU
	*/

	class Texture
	{
	public:
		~Texture() = default; //!< Destructor
		virtual void edit(uint32_t xOffset, uint32_t yOffset, uint32_t width, uint32_t height, unsigned char * data) = 0; //!<Edit this texture
		virtual inline uint32_t getID() = 0; //!< Get GPU ID of this texture
		virtual inline uint32_t getWidth() = 0; //!< Get the width of this texture
		virtual inline uint32_t getHeight() = 0; //!< Get the height of this texture
		virtual inline float getWidthf() = 0; //!< Get the width of this texture as a float
		virtual inline float getHeightf() = 0; //!< Get the height of this texture as a float
		virtual inline uint32_t getChannels() = 0; //!, Get the number of channels of this texture

		static Texture * create(const char * filepath); //!< Create API specific texture from a file
		static Texture * create(uint32_t width, uint32_t height, uint32_t channels, unsigned char * data); //!< Create API specific texture from raw data
	};
}