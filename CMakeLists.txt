cmake_minimum_required(VERSION 3.12)
project(convec C)

set(CMAKE_CXX_STANDARD C99)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fno-omit-frame-pointer -fsanitize=address")
set(CMAKE_LINKER_FLAGS_DEBUG "${CMAKE_LINKER_FLAGS_DEBUG} -fno-omit-frame-pointer -fsanitize=address")

add_library(test_loop SHARED loop.c)
add_library(convec STATIC convec.c)

add_executable(convec_test test.c)
target_link_libraries(convec_test convec)
