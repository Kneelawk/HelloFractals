cmake_minimum_required(VERSION 3.1)
project(hellofractals)

find_package(Threads REQUIRED)
find_package(PNG REQUIRED)
find_package(BISON REQUIRED)
find_package(FLEX REQUIRED)

BISON_TARGET(ProgramParser src/program/programparser.y ${CMAKE_CURRENT_BINARY_DIR}/programparser.tab.cpp VERBOSE)
FLEX_TARGET(ProgramLexer src/program/programlexer.l ${CMAKE_CURRENT_BINARY_DIR}/programlexer.yy.cpp)
ADD_FLEX_BISON_DEPENDENCY(ProgramLexer ProgramParser)

set(SRC_FILES
src/main.cpp
src/fractalthread.cpp
src/valuegenerator.cpp
src/math_utils.cpp
src/array_utils.cpp
src/image_writer.cpp
src/pixel_utils.cpp
src/vectors.cpp
src/stringutils.cpp

# FractalProgram AST
src/program/program.cpp
src/program/statement.cpp
src/program/block.cpp
src/program/constant.cpp
src/program/declaration.cpp
src/program/assignment.cpp
src/program/variable.cpp
src/program/exponent.cpp
src/program/multiplication.cpp
src/program/division.cpp
src/program/addition.cpp
src/program/subtraction.cpp
src/program/functiondefinition.cpp

# FractalProgram Running
src/program/functiondescription.cpp
src/program/runtimefunction.cpp
src/program/runtimecontext.cpp
src/program/runtimeexception.cpp
src/program/runtimescope.cpp
src/program/runtimescopeinstance.cpp
src/program/validationcontext.cpp
src/program/validationexception.cpp
src/program/validationscope.cpp
src/program/validationscopeinstance.cpp

# FractalProgram Parsing
src/program/programhandler.cpp
src/program/programdriver.cpp
src/program/programlexer.cpp
src/program/parsingexception.cpp
${BISON_ProgramParser_OUTPUTS}
${FLEX_ProgramLexer_OUTPUTS})

set(CMAKE_CXX_STANDARD 17)

# using include_directories for this one so that ides can figure this out
include_directories(${CMAKE_CURRENT_BINARY_DIR})

add_executable(hellofractals ${SRC_FILES})

target_include_directories(hellofractals PRIVATE src src/program PUBLIC ${PNG_INCLUDE_DIRS})

target_link_libraries(hellofractals ${PNG_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT} ${FLEX_LIBRARIES})

install(TARGETS hellofractals RUNTIME DESTINATION bin)
