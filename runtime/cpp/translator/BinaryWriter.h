#ifndef __TRANSLATOR_BinaryWriter_h__
#define __TRANSLATOR_BinaryWriter_h__

#include "translator/Common.h"

namespace translator
{

class BinaryWriter
{
public:
	virtual void write(const void* data, size_t len) = 0;
};

}

#endif// __TRANSLATOR_BinaryWriter_h__