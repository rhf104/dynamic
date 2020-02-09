cmake_minimum_required(VERSION 3.12)
project(convec C)

set(CMAKE_CXX_STANDARD C99)

add_library(convec SHARED lib.c)
add_executable(convec_test convec.c test.c)
