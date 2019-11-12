#ifndef __TRANSLATOR_MemoryReader_h__
#define __TRANSLATOR_MemoryReader_h__

#include "translator/BinaryReader.h"

namespace translator
{

/** Read binary data from a memory buffer. */
class MemoryReader : public BinaryReader
{
public: 
	MemoryReader (void* data, size_t len);
	virtual bool read(void* data, size_t len);
private:
	char*	data_;
	size_t	len_;
	size_t	ptr_;
};


}

#endif//__TRANSLATOR_MemoryReader_h__