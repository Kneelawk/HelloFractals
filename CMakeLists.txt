cmake_minimum_required(VERSION 3.1)
project(hellofractals)

set(CMAKE_CXX_STANDARD 17)

add_executable(hellofractals src/main.cpp)

install(TARGETS hellofractals RUNTIME DESTINATION bin)
