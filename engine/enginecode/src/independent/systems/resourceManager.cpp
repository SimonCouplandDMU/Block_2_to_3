/** \file resourceManager.cpp
*/

#include "engine_pch.h"

#include "systems/resourceManager.h"
#include "systems/log.h"
#include <cstdarg>

namespace Engine {
	void ResourceManager::start(SystemSignal init, ...)
	{
		if (init == SystemSignal::ResourceCount)
		{
			va_list args;
			va_start(args, init);

			uint32_t shadersCapacity = va_arg(args, uint32_t);

			uint32_t texturesCapacity = va_arg(args, uint32_t);

			va_end(args);

			m_shaders.reserve(shadersCapacity);

			m_textures.reserve(texturesCapacity);
		}
	}

	void ResourceManager::stop(SystemSignal close, ...)
	{
		m_shaders.clear();
	}

	std::shared_ptr<Shader> ResourceManager::addShader(const char * filepath)
	{
		const char * parsedFilePath = parseFilePath(filepath);
		if (m_shaders.contains(parsedFilePath)) return m_shaders.get(parsedFilePath);
		else
		{
			std::shared_ptr<Shader> temp(Shader::create(filepath));
			m_shaders.add(parsedFilePath, temp);
			return m_shaders.get(parsedFilePath);
		}
	}

	std::shared_ptr<Texture> ResourceManager::addTexture(const char * filepath)
	{
		const char * parsedFilePath = parseFilePath(filepath);
		if (m_textures.contains(parsedFilePath)) return m_textures.get(parsedFilePath);
		else
		{
			std::shared_ptr<Texture> temp(Texture::create(filepath));
			m_textures.add(parsedFilePath, temp);
			return m_textures.get(parsedFilePath);
		}
	}

	std::shared_ptr<Texture> ResourceManager::addTexture(const char * name, unsigned int width, unsigned int height, unsigned int channels, unsigned char * texData)
	{
		if (m_textures.contains(name)) return m_textures.get(name);
		else
		{
			std::shared_ptr<Texture> temp(Texture::create(width, height, channels, texData));
			m_textures.add(name, temp);
			return m_textures.get(name);
		}
	}

	const char *  ResourceManager::parseFilePath(const char * filePath)
	{
		const char * lastBackslash = strrchr(filePath, '\\') + 1;
		const char * lastForwardslash = strrchr(filePath, '/') + 1;
		
		const char * lastSlash = std::max(lastBackslash, lastForwardslash);

		if (lastSlash) return lastSlash;
		else return filePath;

		uint32_t length = strlen(filePath) - strlen(lastSlash);

		char * result;
		strncpy(result, lastSlash, length);
		/*const char * result;

		int lastSlash, lastDot, startPos;

		lastSlash = filePath.find_last_of("/\\");
		startPos = lastSlash + 1;
		if (lastSlash == std::string::npos)
		{
			lastSlash = 0;
			startPos = 0;
		}

		lastDot = filePath.find_last_of(".");
		if (lastDot == std::string::npos) lastDot = filePath.size();

		int nCharsToExtract = lastDot - lastSlash;

		return filePath.substr(startPos, --nCharsToExtract);*/
		return filePath;
	}
}