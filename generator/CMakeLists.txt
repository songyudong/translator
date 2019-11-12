find_package(BISON REQUIRED)
find_package(FLEX REQUIRED)

message(${CMAKE_CURRENT_BINARY_DIR})

FLEX_TARGET(TRANSLATOR_SCANNER translator.l ${CMAKE_CURRENT_BINARY_DIR}/lex.yy.cpp)
BISON_TARGET(TRANSLATOR_PARSER translator.y ${CMAKE_CURRENT_BINARY_DIR}/translator.tab.cpp)


ADD_FLEX_BISON_DEPENDENCY(TRANSLATOR_SCANNER TRANSLATOR_PARSER)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_BINARY_DIR})
if(MSVC)
	include_directories($ENV{GNUWIN32_DIR}/include)   
endif()

set(PARSER_FILES
	${BISON_TRANSLATOR_PARSER_OUTPUTS}
	${FLEX_TRANSLATOR_SCANNER_OUTPUTS}
	translator.y
	translator.l
	)
set(SPEC_FILES	
	Definition.h
	)
set(GEN_FILES
	CppGenerator.cpp
	CSGenerator.cpp
	LUAGenerator.cpp
	)
set(MISC_FILES	
	translator.cpp
	CodeFile.h
	CodeFile.cpp
	CodeGenerator.h
	CodeGenerator.cpp
	Options.h
	Options.cpp
	Context.h
	Context.cpp
	)

source_group( parser FILES ${PARSER_FILES})
source_group( spec FILES ${SPEC_FILES})
source_group( gen FILES ${GEN_FILES})
source_group( misc FILES ${MISC_FILES})

add_executable(translator ${PARSER_FILES} ${SPEC_FILES} ${GEN_FILES} ${MISC_FILES})

# install translator
install(TARGETS translator DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/install)