cmake_minimum_required(VERSION 3.13)
project(StringCompression C)

set(CMAKE_C_STANDARD 99)

add_executable(StringCompression main.c stringbuilder.c stringbuilder.h)