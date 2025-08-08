cmake_minimum_required(VERSION 3.10)
project(coolc)

find_package(LLVM REQUIRED CONFIG)

include_directories(include ${LLVM_INCLUDE_DIRS})
add_definitions(${LLVM_DEFINITIONS})

set(SOURCES
  src/lexer.l
  src/parser.y
  src/ast.cpp
  src/codegen.cpp
  src/main.cpp
)

add_executable(coolc ${SOURCES})
target_link_libraries(coolc LLVMCore LLVMSupport)

# Flex/Bison integration
find_package(BISON REQUIRED)
find_package(FLEX REQUIRED)
BISON_TARGET(Parser src/parser.y ${CMAKE_CURRENT_BINARY_DIR}/parser.cpp)
FLEX_TARGET(Lexer src/lexer.l ${CMAKE_CURRENT_BINARY_DIR}/lexer.cpp)
ADD_FLEX_BISON_DEPENDENCY(Lexer Parser)

