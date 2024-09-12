/** \file resourceManager.h
*/
#pragma once


#include "system.h"
#include "core/assetManager.h"
#include "rendering/shader.h"
#include "rendering/texture.h"


namespace Engine {

	/**
	\class ResourceManager
	A system which manages resources
	*/

	class ResourceManager : public System
	{
	public:
		void start(SystemSignal init = SystemSignal::None, ...) override; //!< Start the system
		void stop(SystemSignal close = SystemSignal::None, ...) override; //!< Stop the system

		std::shared_ptr<Shader> addShader(const char * filepath);//!< Add a shader
		std::shared_ptr<Texture> addTexture(const char * filepath);//!< Add a texture by load and import from filename
		std::shared_ptr<Texture> addTexture(const char * name, unsigned int width, unsigned int height, unsigned int channels, unsigned char * texData);//!< Add a texture with data

	private:
		AssetManager<Shader> m_shaders; //!< Shaders
		AssetManager<Texture> m_textures; //!< Textures
		const char * parseFilePath(const char * filePath); //!< Strip preceeding dirs and file extension
	};

}