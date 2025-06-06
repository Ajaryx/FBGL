set(LIBRARY_SOURCES "VertexBuffer2D.cpp" "IndexBuffer2D.cpp" "Shader.cpp" "Texture2D.cpp")

if(NOT DEFINED LIBRARY_NAME)
message(FATAL_ERROR "LIBRARY_NAME is undefined")
return()
endif()

#make static
if(FBGL_STATIC)

    add_library(${LIBRARY_NAME} STATIC ${LIBRARY_SOURCES})

    target_compile_definitions(${LIBRARY_NAME} PRIVATE FBGL_STATIC)
    target_compile_definitions(${LIBRARY_NAME} PRIVATE GLEW_STATIC)

    set_target_properties(${LIBRARY_NAME} PROPERTIES

            ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib/static
            LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib/static
        )


    message("FBGL STATIC BUILD")

endif()

#make shared
if(FBGL_SHARED)

    add_library(${LIBRARY_NAME} SHARED ${LIBRARY_SOURCES})

    target_compile_definitions(${LIBRARY_NAME} PRIVATE FBGL_BUILD_DLL)

    set_target_properties(${LIBRARY_NAME} PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib/shared
        LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib/shared
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/shared
    )

    message("FBGL SHARED BUILD")

endif()
