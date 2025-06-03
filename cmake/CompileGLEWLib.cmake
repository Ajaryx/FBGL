function(compile_glew_lib GLEW_SOURCES)


message(STATUS "trying to build GLEW...")
if(FBGL_STATIC)
add_library(${GLEW_LIB} STATIC ${GLEW_SOURCES})

message(STATUS ${GLEW_SOURCE_DIR})
message(STATUS "GLEW LIB STATIC BUILD")
endif()


if(FBGL_SHARED)
add_library(${GLEW_LIB} SHARED ${GLEW_SOURCES})

message(STATUS "GLEW LIB SHARED BUILD")
endif()


endfunction(compile_glew_lib)
