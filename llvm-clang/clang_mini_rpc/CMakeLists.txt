#cmake clang_mini_rpc  william k. johnson 2015

#version
cmake_minimum_required(VERSION 2.8)
#project
project(CLANGMINIRPC)

#cpp flags
set(CMAKE_CXX_FLAGS_DEBUG "-Wall -g -O0  -Qunused-arguments -std=c++11") 
set(CMAKE_CXX_FLAGS_RELEASE "-Wall -O3  -Qunused-arguments  -DNDEBUG -std=c++11")

#link
link_directories(
                  ${CMAKE_INSTALL_PREFIX}/lib
                )
#include
include_directories(${CLANGMINIRPC_SOURCE_DIR}
                    ${CLANGMINIRPC_SOURCE_DIR}/gen-cpp
                    /cci-server/include
                    /usr/include                    
                   )

#executable
add_executable(clang_mini_rpc clang_mini_rpc_client.cpp
                              gen-cpp/cci_mini_clang_rpc.cpp
                              gen-cpp/cci_mini_rpc_constants.cpp
                              gen-cpp/cci_mini_rpc_types.cpp)

#link libs
target_link_libraries(clang_mini_rpc -levent -lthrift -lthriftnb -lthrift_shared_cpp)



