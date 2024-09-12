/* file IndirectBuffer.h*/
#pragma once



namespace Engine
{
	/** \struct DrawElementsIndirectCommand
		\brief This need to perform an indirect draw
	*/

	struct DrawElementsIndirectCommand
	{
		uint32_t drawCount;		//!< Draw count of geometry
		uint32_t instanceCount; //!< NUmber of instacnes to be drawn
		uint32_t firstIndex;	//!< First index in IBO of geometry
		uint32_t firstVertex;	//!< First vertex in VBo of geometry
		uint32_t firstInstance;	//!< First instance in this batch
	};

	/** \class IndexBuffer
	*	API agnostic indirect buffer
	*/
	class IndirectBuffer
	{
	public:
		virtual ~IndirectBuffer() = default; //!< Destructor
		virtual inline uint32_t getID() const = 0; //!< Get the GPU ID of this buffer
		virtual inline uint32_t getCount() const = 0; //!< Get the number of elements in this buffer
		virtual void edit(DrawElementsIndirectCommand * commands, uint32_t count, uint32_t offset) = 0; //!< Edit the contents of this buffer

		static IndirectBuffer* create(DrawElementsIndirectCommand * commands, uint32_t count); //!< API agnostic create function
	};
}
