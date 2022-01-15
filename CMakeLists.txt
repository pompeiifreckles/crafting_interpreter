cmake_minimum_required(VERSION 3.21)
project(Crafting_Interpreter)

set(CMAKE_CXX_STANDARD 17)

add_executable(Crafting_Interpreter main.cpp Lox.cpp Lox.h TokenType.h Token.cpp Token.h Scanner.cpp Scanner.h TokenType.cpp)
