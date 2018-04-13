cmake_minimum_required(VERSION 3.1)
project(hellofractals)

set(SRC_FILES
src/main.cpp
src/fractalthread.cpp
src/valuegenerator.cpp
src/math_utils.cpp
src/array_utils.cpp
src/image_writer.cpp
src/pixel_utils.cpp
src/vectors.cpp)

find_package(Threads REQUIRED)
find_package(PNG REQUIRED)

set(CMAKE_CXX_STANDARD 17)

add_executable(hellofractals ${SRC_FILES})

target_include_directories(hellofractals PUBLIC ${PNG_INCLUDE_DIRS})

target_link_libraries(hellofractals ${PNG_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})

install(TARGETS hellofractals RUNTIME DESTINATION bin)
