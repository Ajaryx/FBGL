function(add_target_clang_tidy TARGET)

if(NOT ENABLE_CLANG_TIDY)
return()
endif()

if(CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
message(STATUS "ignoring clang-tidy for MSVC")
return()
else()

get_target_property(TARGET_SOURCES ${TARGET} SOURCES)

list(
FILTER
TARGET_SOURCES
INCLUDE
REGEX
".*.(cpp|h)")



add_custom_target(
    ${TARGET}_clangtidy
    COMMAND
    ${Python3_EXECUTABLE}
    ${CMAKE_SOURCE_DIR}/tools/run-clang-tidy.py
    ${TARGET_SOURCES}
    -config-file=${CMAKE_SOURCE_DIR}/.clang-tidy
-extra-arg-before=-std=${CMAKE_CXX_STANDARD}
-header-filter=src
-p=${CMAKE_BINARY_DIR}
WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
USES_TERMINAL
)
endif()


endfunction(add_target_clang-tidy TARGET)
