cmake_minimum_required(VERSION 3.16)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
project(MissionControl)

set(CMAKE_PREFIX_PATH "C:/Qt/6.7.3/msvc2019_64")
# TODO: build cfg for ubuntu
find_package(Qt6 REQUIRED COMPONENTS Core Widgets Gui OpenGL OpenGLWidgets WebEngineWidgets)

find_library(OPENGL_LIB NAMES opengl32 PATHS "C:/Windows/System32")

file(GLOB SOURCES "src/*.cpp" "src/ui/*.cpp")
file(GLOB HEADERS "include/*.h" "include/ui/*.h" "../lib") 
file(GLOB RESOURCES "resources/*.qrc") 

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

# IMPORTANT! NOT INCLUDING HEADERS IN ADD_EXECUTABLES WILL CAUSE UNDEFINED REFERENCE TO VTABLE
# This is a quirk of Qt having Meta Object Compilation (MOC), adding the headers forces 
# the MOC-generated object files to be linked 
add_executable(MissionControl
   ${SOURCES}
   ${HEADERS}
   ${RESOURCES}
)
qt_add_resources(MissionControl "resources/resources.qrc")

target_link_libraries(MissionControl 
    PRIVATE 
    Qt6::Widgets
    Qt6::Core
    Qt6::Gui
    Qt6::OpenGL
    Qt6::OpenGLWidgets
    Qt6::WebEngineWidgets
)

if(OPENGL_LIB)
    message(STATUS "Found OpenGL: ${OPENGL_LIB}")
    target_link_libraries(MissionControl PRIVATE ${OPENGL_LIB})
else()
    message("OpenGL not found!")
endif()