cmake_minimum_required(VERSION 3.12)
project(dynamic C)

set(CMAKE_C_STANDARD 99)

add_library(dynamic_share SHARED lib.c)
add_executable(dynamic main.c)
