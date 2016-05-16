#cmake walk-a-baby  william k. johnson 2015

#version
cmake_minimum_required(VERSION 2.6)
#project
project(WALKABABY)

#cpp flags
set(CXX_FLAGS "-rdynamic -omit-frame-pointer -fvisibility-inlines-hidden -fno-exceptions -fPIC -ffunction-sections -fdata-sections -Wcast-qual")

set(CMAKE_CXX_FLAGS_DEBUG "-Wall -g -O0  -Qunused-arguments -fno-rtti -std=c++11 ${CXX_FLAGS}") 
set(CMAKE_CXX_FLAGS_RELEASE "-DACE_NTRACE=1 -Wextra-Wall -O3  -fno-rtti -Qunused-arguments  -DNDEBUG -std=c++11 " ${CXX_FLAGS})

add_definitions(-D_GNU_SOURCE
                -D__STDC_CONSTANT_MACROS 
                -D__STDC_FORMAT_MACROS 
                -D__STDC_LIMIT_MACROS                
                -DACE_NTRACE=0) 
                
execute_process(COMMAND $ENV{LLVM_CONFIG} --includedir OUTPUT_VARIABLE LLVM_INCLUDE)
execute_process(COMMAND $ENV{LLVM_CONFIG} --libs core mcjit native OUTPUT_VARIABLE LLVM_LIBS)                    
execute_process(COMMAND $ENV{LLVM_CONFIG} --system-libs OUTPUT_VARIABLE LLVM_SYSTEM_LIBS)
execute_process(COMMAND $ENV{LLVM_CONFIG} --ldflags OUTPUT_VARIABLE LLVM_LDFLAGS)
   
#includes
#mishegas for strange clang include location
execute_process(COMMAND $ENV{LLVM_CONFIG} --libdir OUTPUT_VARIABLE LLVM_DIR)
execute_process(COMMAND $ENV{LLVM_CONFIG} --version OUTPUT_VARIABLE LLVM_VERSION)
string(STRIP ${LLVM_DIR} DIR)
string(STRIP ${LLVM_VERSION} VERSION)
set(CLANG_INCLUDE "${DIR}/clang/${VERSION}/include")

link_directories(${DEV_LIB}
                 ${DEV_LIB}/i386-linux-gnu
                 )
include_directories(../../include
                    ${LLVM_INCLUDE}
                    $ENV{ACE_ROOT}
                    )
#target
add_executable(walk-a-baby walk_a_baby_ast.cpp 
               walk_a_baby_lex.cpp walk_a_baby_parse.cpp
               walk_a_baby.cpp )
string(STRIP ${LLVM_LIBS} LIBS)
string(STRIP ${LLVM_SYSTEM_LIBS} SYSTEM_LIBS)
set(CLANG_LIBS "-Wl,--start-group -lclang -lclangFrontend -lclangDriver -lclangSerialization -lclangParse -lclangSema -lclangAnalysis -lclangEdit -lclangAST -lclangLex -lclangBasic -Wl,--end-group")
target_link_libraries(walk-a-baby -lACE ${CLANG_LIBS} ${LIBS} ${SYSTEM_LIBS})

install_targets(/bin walk-a-baby)
message(STATUS "install target: ${CMAKE_INSTALL_PREFIX}/bin")

SET(CPACK_GENERATOR "DEB")
SET(CPACK_DEBIAN_PACKAGE_MAINTAINER "william k. johnson")
 
INCLUDE(CPack)

