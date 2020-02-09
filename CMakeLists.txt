cmake_minimum_required(VERSION 3.12)
project(convec C)

set(CMAKE_CXX_STANDARD C99)

add_library(loop SHARED loop.c)
add_library(convec STATIC convec.c)

add_executable(convec_test test.c)
target_link_libraries(convec_test convec)
