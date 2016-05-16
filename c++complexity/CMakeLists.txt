#cmake c++complexity  william k. johnson 2015

#version
cmake_minimum_required(VERSION 2.6)
#project
project(CPPCOMPLEX)

#compiler
#set (CMAKE_CXX_COMPILER     "/dev_tools/bin/clang++")
message(STATUS ${CMAKE_CXX_COMPILER})
message(STATUS ${CMAKE_C_COMPILER})
#cpp flags
set(CMAKE_CXX_FLAGS_DEBUG "-fPIC -Wall -g -O0  -Qunused-arguments  -DDEBUG -std=c++11")
set(CMAKE_CXX_FLAGS_RELEASE "-fPIC -Wall -O3  -Qunused-arguments  -DNDEBUG -std=c++11")

#includes
include_directories(../include)
link_directories(${CPPCOMPLEX_SOURCE_DIR}) 

execute_process(COMMAND ${CMAKE_COMMAND} -E echo bar OUTPUT_VARIABLE FOO)
#shared library
add_library(cci_cmplx SHARED c++complexity.cpp)
#install
install_targets( /lib cci_cmplx)


