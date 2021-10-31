cmake_minimum_required(VERSION 3.7)

project(vcalc)
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wpedantic -Wextra -Werror")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)  # for neovim deoplete

set(VCALC_VERSION "0.1.0")
set(VCALC_BUG_ADDRESS "github.com/lkirk/vcalc/issues")
set(VCALC_DOC_STRING "vcalc is an array-oriented programming language")

find_package(BISON)
find_package(FLEX)

# Generate the lexer/parser
set(PARSER_DIR ${CMAKE_CURRENT_BINARY_DIR}/parser)
file(MAKE_DIRECTORY ${PARSER_DIR})
BISON_TARGET(parser parser.y ${PARSER_DIR}/parser.c COMPILE_FLAGS "-Werror")
FLEX_TARGET(lexer lexer.l ${PARSER_DIR}/lexer.c DEFINES_FILE ${PARSER_DIR}/lexer.h)
ADD_FLEX_BISON_DEPENDENCY(lexer parser)


include_directories("." ${PARSER_DIR})
add_definitions(-DYY_NO_INPUT -DYY_NO_UNPUT)

add_executable(
  vcalc
  main.c
  ast.c
  ${PARSER_DIR}/lexer.c
  ${PARSER_DIR}/parser.c
  ${BISON_parser_OUTPUTS}
  ${FLEX_parser_OUTPUTS}
)

target_link_libraries(vcalc
  m
  y
  ${BISON_LIBRARIES}
  ${FLEX_LIBRARIES}
)
