#include "Config.h"
#include "ProtocolReader.h"

namespace translator
{

bool ProtocolReader::readMID(BinaryReader* r, MID& mid)
{
#if TRANSLATOR_BIG_ENDIAN
	if(!r->read(&mid, sizeof(MID))) return false;
	mid = swapEndian(mid);
	return true;
#endif //TRANSLATOR_BIG_ENDIAN
	return r->read(&mid, sizeof(MID));
}

#if TRANSLATOR_BIG_ENDIAN
	#define TRANSLATOR_PROTOCOLREADER_SINGLE_IMP(T)\
		bool ProtocolReader::read##T(BinaryReader* r, T& v, UINT32 maxArray, UINT32 maxValue)\
		{if(!r->read(&v, sizeof(T))) return false;\
		v = swapEndian<T>(v); return true;\ }
#else //TRANSLATOR_BIG_ENDIAN
	#define TRANSLATOR_PROTOCOLREADER_SINGLE_IMP(T)\
		bool ProtocolReader::read##T(BinaryReader* r, T& v, UINT32 maxArray, UINT32 maxValue)\
		{ return r->read(&v, sizeof(T)); }
#endif //TRANSLATOR_BIG_ENDIAN

#define TRANSLATOR_PROTOCOLREADER_ARRAY_IMP(T)\
bool ProtocolReader::read##T##A(BinaryReader* r, std::vector<T>& v, UINT32 maxArray, UINT32 maxValue)\
{\
	UINT32 s;\
	if(!readDynSize(r, s) || s > maxArray) return false;\
	v.resize(s);\
	for(UINT32 i = 0; i < s; i++) if(!read##T(r, v[i], maxArray, maxValue)) return false;\
	return true;\
}

#define TRANSLATOR_PROTOCOLREADER_SIMPLE_IMP(T)\
	TRANSLATOR_PROTOCOLREADER_SINGLE_IMP(T);\
	TRANSLATOR_PROTOCOLREADER_ARRAY_IMP(T);

TRANSLATOR_PROTOCOLREADER_SIMPLE_IMP(INT64);
TRANSLATOR_PROTOCOLREADER_SIMPLE_IMP(UINT64);
TRANSLATOR_PROTOCOLREADER_SIMPLE_IMP(DOUBLE);
TRANSLATOR_PROTOCOLREADER_SIMPLE_IMP(FLOAT);
TRANSLATOR_PROTOCOLREADER_SIMPLE_IMP(INT32);
TRANSLATOR_PROTOCOLREADER_SIMPLE_IMP(UINT32);
TRANSLATOR_PROTOCOLREADER_SIMPLE_IMP(INT16);
TRANSLATOR_PROTOCOLREADER_SIMPLE_IMP(UINT16);
TRANSLATOR_PROTOCOLREADER_SIMPLE_IMP(INT8);
TRANSLATOR_PROTOCOLREADER_SIMPLE_IMP(UINT8);

bool ProtocolReader::readBOOL(BinaryReader* r, BOOL& v, UINT32 maxArray, UINT32 maxValue)
{
	UINT8 v1 = v?1:0;
	return r->read(&v, sizeof(BOOL));
}

bool ProtocolReader::readBOOLA(BinaryReader* r, std::vector<BOOL>& v, UINT32 maxArray, UINT32 maxValue)
{
	UINT32 s;
	if(!readDynSize(r, s) || s > maxArray) return false;
	v.resize(s);
	for(UINT32 i = 0; i < s; i++) 
	{
		BOOL b;
		if(!readBOOL(r, b, 0, maxValue)) 
			return false;
		v[i] = b;
	}
	return true;
}

bool ProtocolReader::readSTRING(BinaryReader* r, STRING& v, UINT32 maxArray, UINT32 maxValue)
{
	UINT32 len;
	if(!readDynSize(r, len) || len > maxValue)
		return false;
	v.resize(len);
	return r->read((void*)v.c_str(), len);
}
TRANSLATOR_PROTOCOLREADER_ARRAY_IMP(STRING);

bool ProtocolReader::readBINARY(BinaryReader* r, BINARY& v, UINT32 maxArray, UINT32 maxValue)
{
	UINT32 len;
	if(!readDynSize(r, len) || len > maxValue)
		return false;
	v.resize(len);
	if(len > 0)
		return r->read((void*)(&(v[0])), len);
	return true;
}
TRANSLATOR_PROTOCOLREADER_ARRAY_IMP(BINARY);

bool ProtocolReader::readDynSize(BinaryReader* r, UINT32& s)
{
	s = 0;
	UINT8 b;
	if(!r->read(&b, sizeof(UINT8)))
		return false;
	size_t n = (b & 0XC0)>>6;
	s = (b & 0X3F);
	for(size_t i = 0; i < n; i++)
	{
		if(!r->read(&b, sizeof(UINT8)))
			return false;
		s = (s<<8)|b;
	}
	return true;
}

}