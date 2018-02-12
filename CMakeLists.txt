cmake_minimum_required(VERSION 3.1)
project(hellofractals)

find_package(Threads)

set(CMAKE_CXX_STANDARD 17)

add_executable(hellofractals
src/main.cpp
src/fractalthread.cpp
src/valuegenerator.cpp
src/math_utils.cpp)

target_link_libraries(hellofractals ${CMAKE_THREAD_LIBS_INIT})

install(TARGETS hellofractals RUNTIME DESTINATION bin)
