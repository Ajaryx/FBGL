set(LIBRARY_SOURCES "VertexBuffer.cpp")

if(NOT DEFINED LIBRARY_NAME)
message(FATAL_ERROR "LIBRARY_NAME is undefined")
return()
endif()

#make static
if(FBGL_STATIC)

add_library(${LIBRARY_NAME} STATIC ${LIBRARY_SOURCES})
set_target_properties(${LIBRARY_NAME} PROPERTIES

ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib)


message("FBGL STATIC BUILD")

endif()

#make shared
if(FBGL_SHARED)

add_library(${LIBRARY_NAME} SHARED ${LIBRARY_SOURCES})

set_target_properties(${LIBRARY_NAME} PROPERTIES
LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin
RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)


message("FBGL SHARED BUILD")

endif()



#init glew
#MSVC
if(CMAKE_CXX_COMPILER_ID MATCHES "MSVC")

target_link_libraries(${LIBRARY_NAME} PRIVATE ${GLEW_LIB_DIR}/glew32s.lib)
message(STATUS "LINKED WITH glew32s.lib")

#clang gcc
elseif(CMAKE_CXX_COMPILER_ID MATCHES "GNU" OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")

target_link_libraries(${LIBRARY_NAME} PRIVATE ${GLEW_LIB_DIR}/libGLEW.a)
message(STATUS "LINKED WITH libGLEW.a")
endif()
