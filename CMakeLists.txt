cmake_minimum_required(VERSION 2.8)

project(helloworld_gen)

add_executable(hwgen src/main.cpp)

install(TARGETS hwgen DESTINATION bin)
