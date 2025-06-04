function(add_format_target)

file(GLOB_RECURSE CMAKE_FILES_CPP "*/*.cpp")
file(GLOB_RECURSE CMAKE_FILES_H "*/*.hpp")

find_package(Python3 COMPONENTS Interpreter REQUIRED)

set(CPP_FILES
${CMAKE_FILES_CPP}
${CMAKE_FILES_H})

list(
FILTER
CPP_FILES
EXCLUDE
REGEX
"${CMAKE_SOURCE_DIR}/(build/external)/.*")

find_program(CLANGFORMAT clang-format)

if(CLANGFORMAT)
add_custom_target(
    run_clang_format
    COMMAND
    ${PYTHON3_EXECUTABLE}
${CMAKE_SOURCE_DIR}/tools/run-clang-format.py ${CPP_FILES}
--in-place
WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
USES_TERMINAL
)
else()
message(WARNING "Clang format not found :(")
endif()
endfunction(ad)
