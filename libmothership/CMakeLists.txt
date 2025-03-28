cmake_minimum_required(VERSION 3.16)
project(libmothership)

file(GLOB SOURCES "src/*.cpp")
file(GLOB HEADERS "include/*.h") 

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
add_library(mothership ${SOURCES})
add_executable(libmothership_test ${SOURCES} test/test.cpp)
