cmake_minimum_required(VERSION 3.14)
project(ClionProject C)

set(CMAKE_C_STANDARD 99)

add_executable(ClionProject main.c tablero.h tablero.c Cliente.c Cliente.h)