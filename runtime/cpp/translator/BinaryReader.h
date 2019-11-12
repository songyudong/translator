#ifndef __TRANSLATOR_BinaryReader_h__
#define __TRANSLATOR_BinaryReader_h__

#include "translator/Common.h"

namespace translator
{

class BinaryReader
{
public:
	virtual bool read(void* data, size_t len) = 0;
};

}

#endif// __TRANSLATOR_BinaryReader_h__