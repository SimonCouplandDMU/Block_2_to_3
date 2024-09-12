/** \file uniformBuffer.h */
#pragma once

#include <ctype.h>
#include <memory>
#include <unordered_map>

#include "bufferLayout.h"
#include "shader.h"

namespace Engine
{
	/** \class IndexBuffer
	*	API agnositc uniform buffer
	*/
	class UniformBuffer
	{
	public:
		virtual ~UniformBuffer() = default; //!< Destructor
		virtual uint32_t getID() = 0; //!< Get the GPU ID of this buffer
		virtual UniformBufferLayout getLayout() = 0; //!< Get the layout of this buffer
		virtual void attachShaderBlock(const std::shared_ptr<Shader>& shader, const char * blockName) = 0; //!< Attach a shader and block to this UBO
		virtual void uploadData(const char * uniformName, void * data) = 0; //!< Upload a single uniform value to this buffer

		static UniformBuffer* create(const UniformBufferLayout& layout); //!< API agnostic create function
	protected:
		UniformBufferLayout m_layout; //!< Uniform Buffer layout
		std::unordered_map<const char *, std::pair<uint32_t, uint32_t>> m_uniformCache; //!< Stores uniform names with offsets and sizes
		uint32_t m_blockNumber; //!< Block number for this UBO
	};
}

