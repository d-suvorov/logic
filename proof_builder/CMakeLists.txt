project(proof_builder)
cmake_minimum_required(VERSION 2.8)
aux_source_directory(. SRC_LIST)
add_definitions(-std=c++11)
add_executable(${PROJECT_NAME} ${SRC_LIST} "parser.h" "parser.cpp" "syntax_tree.h"
               "syntax_tree.cpp" "proof_utils.h" "proof_utils.cpp")
