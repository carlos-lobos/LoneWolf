cmake_minimum_required(VERSION 3.20)
project(LoneWolf LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(lonewolf
    src/main.cpp
    src/lexer/Lexer.cpp
)

target_include_directories(lonewolf PRIVATE include)
