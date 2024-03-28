project(CompressData VERSION 1.0 LANGUAGES CXX)

file(GLOB_RECURSE SOURCES "source/*.cpp")

add_executable(CompressData ${SOURCES})