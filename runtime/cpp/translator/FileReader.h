#ifndef __TRANSLATOR_FileReader_h__
#define __TRANSLATOR_FileReader_h__

#include "translator/BinaryReader.h"
#include <cstdio>

namespace translator
{

/** Read binary data from a file. */
class FileReader : public BinaryReader
{
public:
	FileReader(FILE* f):f_(f){}
	virtual bool read(void* data, size_t len);
private:
	FILE* f_;
};

}

#endif//__TRANSLATOR_FileReader_h__