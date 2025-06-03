set(LIBRARY_SOURCES "VertexBuffer.cpp" "Shader.cpp")

if(NOT DEFINED LIBRARY_NAME)
message(FATAL_ERROR "LIBRARY_NAME is undefined")
return()
endif()

#make static
if(FBGL_STATIC)

add_library(${LIBRARY_NAME} STATIC ${LIBRARY_SOURCES})
 target_compile_definitions(${LIBRARY_NAME} PRIVATE FBGL_STATIC)
 set_target_properties(${LIBRARY_NAME} PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin
        ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib
        LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib
    )

message("FBGL STATIC BUILD")

endif()

#make shared
if(FBGL_SHARED)

    add_library(${LIBRARY_NAME} SHARED ${LIBRARY_SOURCES})
    target_compile_definitions(${LIBRARY_NAME} PRIVATE FBGL_BUILD_DLL)
    set_target_properties(${LIBRARY_NAME} PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin
        ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib
        LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib
    )

    message("FBGL SHARED BUILD")

endif()
