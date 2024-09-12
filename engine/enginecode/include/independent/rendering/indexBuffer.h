/* \file indexBuffer */ 
#pragma once

#include <cstdint>

namespace Engine {

	/** \class IndexBuffer 
	*	API agnositc index/element buffer
	*/
	class IndexBuffer {
	public:
		virtual ~IndexBuffer() = default; //!< Destructor
		virtual inline uint32_t getID() const = 0; //!< Get the GPU ID of this buffer
		virtual inline uint32_t getCount() const = 0; //!< Get the number of element in this buffer
		virtual void edit(uint32_t * indices, uint32_t count, uint32_t offset) = 0; //!< Edit the contents of this buffer

		static IndexBuffer* create(uint32_t * indices, uint32_t count); //!< API agnostic create function
		
	};

}
