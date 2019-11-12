#ifndef __TRANSLATOR_FileWriter_h__
#define __TRANSLATOR_FileWriter_h__

#include "translator/BinaryWriter.h"
#include <cstdio>

namespace translator
{

/** Write binary data to a file. */
class FileWriter : public BinaryWriter
{
public:
	FileWriter(FILE* f):f_(f){}
	virtual void write(const void* data, size_t len);
private:
	FILE* f_;
};

}

#endif//__TRANSLATOR_FileWriter_h__