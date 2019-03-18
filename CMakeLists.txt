cmake_minimum_required(VERSION 3.1)
project(hellofractals)

find_package(Threads REQUIRED)
find_package(PNG REQUIRED)

set(SRC_FILES
src/main.cpp
src/fractalthread.cpp
src/valuegenerator.cpp
src/math_utils.cpp
src/array_utils.cpp
src/image_writer.cpp
src/pixel_utils.cpp
src/vectors.cpp
src/stringutils.cpp)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG")

# using include_directories for this one so that ides can figure this out
include_directories(${CMAKE_CURRENT_BINARY_DIR})

add_executable(hellofractals ${SRC_FILES})

target_include_directories(hellofractals PRIVATE src PUBLIC ${PNG_INCLUDE_DIRS})

target_link_libraries(hellofractals ${PNG_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})

install(TARGETS hellofractals RUNTIME DESTINATION bin)
