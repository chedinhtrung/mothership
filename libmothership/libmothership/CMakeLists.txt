cmake_minimum_required(VERSION 3.16)
project(libmothership)

file(GLOB SOURCES "src/*.cpp")
file(GLOB HEADERS "include/*.h") 

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
add_library(mothership "src/dataexchange.cpp")
add_executable(test_dexch ${SOURCES} test/dexch.cpp)
add_executable(test_network ${SOURCES} test/network.cpp)

if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    target_link_libraries(test_network PRIVATE ws2_32)
endif()