#include "FileWriter.h"

namespace translator
{

void FileWriter::write(const void* data, size_t len)
{
	fwrite(data, 1, len, f_);
}

}