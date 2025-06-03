set(LIBRARY_TESTS "Library_Tests")
set(LIBRARY_TESTS_SOURCES "main.cpp")

add_executable(${LIBRARY_TESTS} ${LIBRARY_TESTS_SOURCES})

target_link_libraries(${LIBRARY_TESTS} PRIVATE ${LIBRARY_NAME} ${GLEW_LIB})

target_include_directories(${LIBRARY_TESTS} PUBLIC ${LIBRARY_INCLUDES_DIR} ${GLEW_INCLUDES_DIR})

add_target_sanitizer(${LIBRARY_TESTS})
