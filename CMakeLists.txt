cmake_minimum_required(VERSION 3.0)
project(jsonc11)

set(CMAKE_CXX_STANDARD 11)

add_executable(jsonc11 main.cpp json.cc flex.cc bison.cc)
