#ifndef __TRANSLATOR_MemoryWriter_h__
#define __TRANSLATOR_MemoryWriter_h__

#include "translator/BinaryWriter.h"

namespace translator
{

	/** Write binary data to memory. */
	class MemoryWriter : public BinaryWriter
	{
	public:
		MemoryWriter(BINARY* d):data_(d) {}
		BINARY*	data()	{ return data_; }
		virtual void write(const void* data, size_t len);
	private:
		BINARY*		data_;
	};

}

#endif//__TRANSLATOR_MemoryWriter_h__