function(add_target_sanitizer TARGET)


message(STATUS "trying to enable sanitizer...")

if(CMAKE_CXX_COMPILER_ID MATCHES "MSVC")

    message(WARNING "Sanitizer are not available yet for MSVC")

elseif(CMAKE_CXX_COMPILER_ID MATCHES "Clang" OR CMAKE_CXX_COMPILER_ID MATCHES "GNU")

    target_compile_options(${TARGET} PUBLIC "-fno-omit-frame-pointer")
    target_link_options(${TARGET} PUBLIC "-fno-omit-frame-pointer")

    if(ENABLE_SANITIZER_ADDR)

        target_compile_options(${TARGET} PUBLIC "-fsanitize=address")
        target_link_options(${TARGET} PUBLIC "-fsanitize=address")

    elseif(ENABLE_SANITIZER_UNDEF)

        target_compile_options(${TARGET} PUBLIC "-fsanitize=undefined")
        target_link_options(${TARGET} PUBLIC "-fsanitize=undefined")

    endif()

else()

message(WARNING "Unsuported enviroment for Sanitizer!")
endif()


endfunction(add_target_sanitizer TARGET)
