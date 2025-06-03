function(compile_glew_lib GLEW_SOURCES)


message(STATUS "trying to build GLEW...")

if(FBGL_STATIC)
add_library(${GLEW_LIB} STATIC ${GLEW_SOURCES})

message(STATUS ${GLEW_SOURCE_DIR})

target_compile_definitions(${GLEW_LIB} PUBLIC GLEW_STATIC)
message(STATUS "GLEW LIB STATIC BUILD")
endif()


if(FBGL_SHARED)
add_library(${GLEW_LIB} SHARED ${GLEW_SOURCES})

target_compile_definitions(${GLEW_LIB} PUBLIC GLEW_BUILD)
message(STATUS "GLEW LIB SHARED BUILD")
endif()

target_link_libraries(${GLEW_LIB} PUBLIC OpenGL::GL)


   set_target_properties(${GLEW_LIB} PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin
        ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib
        LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib
    )

endfunction(compile_glew_lib)
