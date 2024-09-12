/* textureAtlas.h */
#pragma once

#include <vector>
#include "rendering/subTexture.h"

namespace Engine
{
	/** \struct SimpleRect
		\brief A really simple description of a rectangle
	*/

	struct SimpleRect { int32_t x, y, w, h; };

	/** \class TextureAtlas
	**  \brief A tree based data structure combined with a texture to hold subtextures - does not hold texels
	*/

	class TextureAtlas
	{
	public:
		TextureAtlas(glm::ivec2 size = { 1024, 800 }, uint32_t channels = 4, uint32_t reservedSpaces = 32); //!< Constructor, takes size and channels
		bool add(const char * filepath, SubTexture& result); //!< Attempt to add a subtexture with a file
		bool add(int32_t width, int32_t height, uint32_t channels, unsigned char * data, SubTexture& result); //!< Attempt to add a subtexture with a file
		inline uint32_t getChannels() const { return m_baseTexture->getChannels(); } //!< get the number of channels of this atlas
		inline std::shared_ptr<Texture> getBaseTexture() const { return m_baseTexture; } //!< get the base texture
		inline uint32_t getID() const { return m_baseTexture->getID(); } //!< Get the GPU ID of the base texture

		std::vector<SimpleRect> m_spaces; //!< Gaps left which can be filled
	private:
		
		std::shared_ptr<Texture> m_baseTexture; //!< texture which hold all subtexture pixel data
	};
}
