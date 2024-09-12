/* \file vertexBuffer.h */

#pragma once

#include "rendering/bufferLayout.h"

namespace Engine
{
	/** \class VertexBuffer
	*	API agnositc vertex buffer
	*/

	class VertexBuffer
	{
	public:
		virtual ~VertexBuffer() = default; //!< Destructor
		virtual inline uint32_t getID() const = 0; //!< Get the GPU ID of this buffer
		virtual inline const VertexBufferLayout& getLayout() const = 0; //!< Get the layout of this buffer
		virtual void edit(void* vertices, uint32_t size, uint32_t offset) = 0; //!< Edit the contents of this buffer

		static VertexBuffer* create(void* vertices, uint32_t size, VertexBufferLayout layout); //!< API agnostic create function
	};
}