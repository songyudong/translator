cmake_minimum_required(VERSION 3.13.2)
project(translator)

set(CMAKE_DEBUG_POSTFIX "d")

# Test Endianess.
include(TestBigEndian)
test_big_endian(TRANSLATOR_BIG_ENDIAN)

set(TRANSLATOR_VERSION_MAJOR 1)
set(TRANSLATOR_VERSION_MINOR 0)

configure_file("Config.h.in" "Config.h")

include_directories(${PROJECT_BINARY_DIR})
add_subdirectory(generator)
add_subdirectory(runtime)