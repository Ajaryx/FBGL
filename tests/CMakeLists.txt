set(LIBRARY_TESTS "Library_Tests")
set(LIBRARY_TESTS_SOURCES "main.cpp")

add_executable(${LIBRARY_TESTS} ${LIBRARY_TESTS_SOURCES})

target_link_libraries(${LIBRARY_TESTS} PRIVATE ${LIBRARY_NAME} ${GLEW_LIB})

target_include_directories(${LIBRARY_TESTS} PUBLIC ${LIBRARY_INCLUDES_DIR} ${GLEW_INCLUDES_DIR})

set_target_properties(${LIBRARY_TESTS} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_target_sanitizer(${LIBRARY_TESTS})

include(FetchContent)

FetchContent_Declare(
    SDL3
    GIT_REPOSITORY https://github.com/libsdl-org/SDL
    GIT_TAG release-3.2.16
    GIT_SHALLOW TRUE
)
FetchContent_MakeAvailable(SDL3)

FetchContent_Declare(
    glm
    GIT_REPOSITORY https://github.com/g-truc/glm
    GIT_TAG 1.0.1
    GIT_SHALLOW TRUE
)
FetchContent_MakeAvailable(glm)


target_link_libraries(${LIBRARY_TESTS} PRIVATE SDL3::SDL3 glm::glm)
