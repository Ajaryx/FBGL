function(add_target_compiler_warnings TARGET)


set(MSVC_Warnings
/W4)

set(Clang_Warnings
-Wall
-Wextra
-Wformat
-Wsign-compare
-Wconversion
-Wunused
-Wnull-dereference
-Wimplicit-fallthrough)

set(GCC_Warnings
-Wall
-Wextra
-Wformat
-Wsign-compare
-Wconversion
-Wunused
-Wnull-dereference
-Wimplicit-fallthrough)

if(CMAKE_CXX_COMPILER_ID MATCHES "MSVC")

target_compile_options(${TARGET} PRIVATE ${MSVC_Warnings})

elseif(CMAKE_CXX_COMPILER_ID MATCHES "Clang")

target_compile_options(${TARGET} PRIVATE ${Clang_Warnings})


elseif(CMAKE_CXX_COMPILER_ID MATCHES "GNU")

target_compile_options(${TARGET} PRIVATE ${GCC_Warnings})


else()
message(WARNING "Unsuported compiler cannot add compiler warnings!")

endif()

endfunction(add_target_compiler_warnings)
