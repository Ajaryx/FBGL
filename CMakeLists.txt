cmake_minimum_required(VERSION 4.0.2)

project(FBGL
VERSION 0.1.0
LANGUAGES C CXX)

#define basic paths and cmake settings
#my lib paths
set(LIBRARY_NAME "FBGL")
set(LIBRARY_SOURCES_DIR ${CMAKE_SOURCE_DIR}/src)
set(LIBRARY_INCLUDES_DIR ${CMAKE_SOURCE_DIR}/include)

#glew lib paths
set(GLEW_LIB "GLEW")
set(GLEW_LIB_DIR ${CMAKE_SOURCE_DIR}/external/glew_lib)
set(GLEW_INCLUDES_DIR ${GLEW_LIB_DIR}/include)
set(GLEW_SOURCE_PATH_DIR ${GLEW_LIB_DIR}/src)
set(GLEW_LIB_SOURCES
${GLEW_SOURCE_PATH_DIR}/glew.c)


set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED)
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)

message(STATUS "library output path set to " ${LIBRARY_OUTPUT_DIRECTORY})

find_package(OpenGL REQUIRED)

#options
option(FBGL_STATIC "Build FBGL static" ON)
option(FBGL_SHARED "Build FBGL shared" OFF)

#compile glew
include(CompileGLEWLib)
compile_glew_lib(${GLEW_LIB_SOURCES})
target_include_directories(${GLEW_LIB} PRIVATE ${GLEW_INCLUDES_DIR})




if(NOT FBGL_STATIC AND NOT FBGL_SHARED)
set(FBGL_STATIC ON)
message(STATUS "Static and Shared build time are both off.. set default build type to static")
elseif(FBGL_STATIC AND FBGL_SHARED)
message(STATUS "Static and Shared build time are both ON.. set default build type to static")
set(FBGL_STATIC ON)
set(FBGL_SHARED OFF)
endif()

add_subdirectory(${LIBRARY_SOURCES_DIR})


#link to glew target
#MSVC
if(CMAKE_CXX_COMPILER_ID MATCHES "MSVC")

    target_link_libraries(${LIBRARY_NAME} PRIVATE ${GLEW_LIB} OpenGL::GL)
    message(STATUS "LINKED WITH GLEW")

    #clang gcc
elseif(CMAKE_CXX_COMPILER_ID MATCHES "GNU" OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")

    target_link_libraries(${LIBRARY_NAME} PRIVATE ${GLEW_LIB} OpenGL::GL)

    message(STATUS "LINKED WITH GLEW")

endif()


#link to include dir glew and lib dir
target_include_directories(${LIBRARY_NAME} PRIVATE ${GLEW_INCLUDES_DIR} ${LIBRARY_INCLUDES_DIR})

add_subdirectory(tests)
