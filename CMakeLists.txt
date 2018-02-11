cmake_minimum_required(VERSION 2.6)
project(hellofractals)

add_executable(hellofractals main.cpp)

install(TARGETS hellofractals RUNTIME DESTINATION bin)
