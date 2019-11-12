#ifndef __TRANSLATOR_ProtocolWriter_h__
#define __TRANSLATOR_ProtocolWriter_h__

#include <vector>
#include "translator/BinaryWriter.h"

namespace translator
{

class ProtocolWriter
{
public:
	static void writeMID(BinaryWriter* w, MID mid);
#define TRANSLATOR_PROTOCOLWRITER_DECL(T)\
	static void write##T(BinaryWriter* w, const T& v);\
	static void write##T##A(BinaryWriter* w, const std::vector<T>& v);
	TRANSLATOR_PROTOCOLWRITER_DECL(INT64);
	TRANSLATOR_PROTOCOLWRITER_DECL(UINT64);
	TRANSLATOR_PROTOCOLWRITER_DECL(DOUBLE);
	TRANSLATOR_PROTOCOLWRITER_DECL(FLOAT);
	TRANSLATOR_PROTOCOLWRITER_DECL(INT32);
	TRANSLATOR_PROTOCOLWRITER_DECL(UINT32);
	TRANSLATOR_PROTOCOLWRITER_DECL(INT16);
	TRANSLATOR_PROTOCOLWRITER_DECL(UINT16);
	TRANSLATOR_PROTOCOLWRITER_DECL(INT8);
	TRANSLATOR_PROTOCOLWRITER_DECL(UINT8);
	TRANSLATOR_PROTOCOLWRITER_DECL(BOOL);
	TRANSLATOR_PROTOCOLWRITER_DECL(STRING);
	TRANSLATOR_PROTOCOLWRITER_DECL(BINARY);
	// Enum
	template<class T>
	static void writeENUM(BinaryWriter* w, T v)
	{ 
		UINT8 e = (UINT8)v;
		w->write(&e, sizeof(UINT8));
	}
	template<class T>
	static void writeENUMA(BinaryWriter* w, const std::vector<T>& v)
	{ 
		UINT32 s = (UINT32)v.size();
		writeDynSize(w, s);
		for(UINT32 i = 0; i < s; i++)
			writeENUM(w, v[i]);
	}
	// Enum16
	template<class T>
	static void writeENUM16(BinaryWriter* w, T v)
	{ 
		UINT16 e = (UINT16)v;
		writeUINT16(w, e);
	}
	template<class T>
	static void writeENUM16A(BinaryWriter* w, const std::vector<T>& v)
	{ 
		UINT32 s = (UINT32)v.size();
		writeDynSize(w, s);
		for(UINT32 i = 0; i < s; i++)
			writeENUM16(w, v[i]);
	}
	// User
	template<class T>
	static void writeUSER(BinaryWriter* w, const T& v)
	{
		v.serialize(w);
	}
	template<class T>
	static void writeUSERA(BinaryWriter* w, const std::vector<T>& v)
	{	
		UINT32 s = (UINT32)v.size();
		writeDynSize(w, s);
		for(UINT32 i = 0; i < s; i++)
			writeUSER(w, v[i]);
	}
	// Dynamic size.
	static void writeDynSize(BinaryWriter* w, UINT32 s);
};

}

#endif// __TRANSLATOR_ProtocolWriter_h__