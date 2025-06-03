cmake_minimum_required(VERSION 4.0.2)

project(FBGL
VERSION 0.1.0
LANGUAGES C CXX)

#define basic paths and cmake settings
#my lib paths
set(LIBRARY_NAME "FBGL")
set(LIBRARY_SOURCES_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(LIBRARY_INCLUDES_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)

#glew lib paths
set(GLEW_LIB "GLEW")
set(GLEW_LIB_DIR ${CMAKE_CURRENT_SOURCE_DIR}/external/glew_lib)
set(GLEW_INCLUDES_DIR ${GLEW_LIB_DIR}/include)
set(GLEW_SOURCE_PATH_DIR ${GLEW_LIB_DIR}/src)
set(GLEW_LIB_SOURCES
${GLEW_SOURCE_PATH_DIR}/glew.c)


set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED)
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

message(STATUS "library output path set to " ${LIBRARY_OUTPUT_DIRECTORY})


find_package(Python3 COMPONENTS Interpreter REQUIRED)
find_program(CLANGTIDY clang-tidy)
find_package(OpenGL REQUIRED)

#options
option(FBGL_STATIC "Build FBGL static" ON)
option(FBGL_SHARED "Build FBGL shared" OFF)
option(ENABLE_BUILD_LIB_TESTS "Build Tests" ON)
option(ENABLE_COMPILER_WARNING "turn on compiler Warnings for FGGL" ON)
option(ENABLE_SANITIZER_ADDR "Enable address sanitizer" ON)
option(ENABLE_SANITIZER_UNDEF "Enable unfefined sanitizer" ON)
option(ENABLE_CLANG_TIDY "Enable clang-tidy" OFF)
option(ENABLE_CLANG_FORMAT "Enable clang-format" OFF)

#compile glew
include(CompileGLEWLib)
compile_glew_lib(${GLEW_LIB_SOURCES})
target_include_directories(${GLEW_LIB} PRIVATE ${GLEW_INCLUDES_DIR})

#include sanitizre if enabled
if(ENABLE_SANITIZER_ADDR AND ENABLE_SANITIZER_UNDEF)
include(Sanitizer)
endif()


if(NOT FBGL_STATIC AND NOT FBGL_SHARED)
set(FBGL_STATIC ON)
message(STATUS "Static and Shared build time are both off.. set default build type to static")
elseif(FBGL_STATIC AND FBGL_SHARED)
message(STATUS "Static and Shared build time are both ON.. set default build type to static")
set(FBGL_STATIC ON)
set(FBGL_SHARED OFF)
endif()

add_subdirectory(${LIBRARY_SOURCES_DIR})

if(ENABLE_COMPILER_WARNING)
include(CompilerWarnings)
add_target_sanitizer(${LIBRARY_NAME})
endif()

if(ENABLE_CLANG_TIDY)
include(ClangTidy)
add_target_clang_tidy(${LIBRARY_NAME})
endif()


if(ENABLE_CLANG_FORMAT)
include(ClangFormat)
add_format_target()
endif()


target_link_libraries(${LIBRARY_NAME} PRIVATE ${GLEW_LIB} OpenGL::GL)
add_target_compiler_warnings(${LIBRARY_NAME})


#link to include dir glew and lib dir
target_include_directories(${LIBRARY_NAME} PUBLIC ${GLEW_INCLUDES_DIR} ${LIBRARY_INCLUDES_DIR})

if(ENABLE_BUILD_LIB_TESTS)
add_subdirectory(tests)
endif()
