cmake_minimum_required(VERSION 4.0.2)

project(FBGL
VERSION 0.1.0
LANGUAGES CXX)

#define basic paths and cmake settings
set(LIBRARY_NAME "FBGL")
set(LIBRARY_SOURCES_DIR ${PROJECT_SOURCE_DIR}/src)
set(LIBRARY_INCLUDES_DIR ${PROJECT_SOURCE_DIR}/include)

set(GLEW_LIB_DIR ${PROJECT_SOURCE_DIR}/external/glew_lib)
set(GLEW_INCLUDES_DIR ${GLEW_LIB_DIR}/include)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED)
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

message(STATUS "library output path set to " ${LIBRARY_OUTPUT_DIRECTORY})


#options
option(FBGL_STATIC "Build FBGL static" ON)
option(FBGL_SHARED "Build FBGL shared" OFF)

add_subdirectory(${LIBRARY_SOURCES_DIR})
add_subdirectory(${LIBRARY_INCLUDES_DIR})
add_subdirectory(tests)

#link to include dir glew
target_include_directories(${LIBRARY_NAME} PRIVATE ${GLEW_LIB_DIR})
