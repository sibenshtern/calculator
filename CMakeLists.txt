cmake_minimum_required(VERSION 3.23)
project(calculator)

set(CMAKE_CXX_STANDARD 17)

add_executable(calculator main.cpp grammar.cpp token.cpp variable.cpp grammar.h token.h variable.h)
