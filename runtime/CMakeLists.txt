include_directories(cpp)
set(CPP_DIR cpp/translator)
set(HEADER_LIST
	${CPP_DIR}/Common.h
	${CPP_DIR}/BinaryReader.h
	${CPP_DIR}/BinaryWriter.h
	${CPP_DIR}/ProtocolReader.h
	${CPP_DIR}/ProtocolWriter.h
	${CPP_DIR}/FileReader.h
	${CPP_DIR}/FileWriter.h
	${CPP_DIR}/MemoryReader.h
	${CPP_DIR}/MemoryWriter.h
	)

set(SOURCE_LIST
	${CPP_DIR}/ProtocolReader.cpp
	${CPP_DIR}/ProtocolWriter.cpp
	${CPP_DIR}/FileReader.cpp
	${CPP_DIR}/FileWriter.cpp
	${CPP_DIR}/MemoryReader.cpp
	${CPP_DIR}/MemoryWriter.cpp
	)
	
add_library(translator_cpp STATIC ${HEADER_LIST} ${SOURCE_LIST})
install(TARGETS translator_cpp ARCHIVE DESTINATION lib)
install(FILES ${HEADER_LIST} DESTINATION include/translator)