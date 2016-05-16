#cmake libLLVMwalk_a_baby  william k. johnson 2015

#version
cmake_minimum_required(VERSION 2.6)
#project
project(LLVMWALKABABY)

set(CXX_FLAGS "-rdynamic -omit-frame-pointer -fvisibility-inlines-hidden -fno-exceptions -fPIC -ffunction-sections -fdata-sections -Wcast-qual")
set(CMAKE_CXX_FLAGS_DEBUG "-Wall -g -O0  -Qunused-arguments -Wno-missing-field-initializers -fno-rtti -Wno-long-long -Wno-comment -std=c++11 ${CXX_FLAGS}") 

execute_process(COMMAND $ENV{LLVM_CONFIG} --includedir OUTPUT_VARIABLE LLVM_INCLUDE)
execute_process(COMMAND $ENV{LLVM_CONFIG} --ldflags OUTPUT_VARIABLE LLVM_LDFLAGS)
execute_process(COMMAND uname OUTPUT_VARIABLE UNAME)

link_directories(/dev_tools/lib
                 /usr/lib/i386-linux-gnu
                 ${CPPCOMPLEX_SOURCE_DIR}
                 )
include_directories(${LLVM_INCLUDE} 
                    /usr/include
                   )
                   


add_definitions(-D_GNU_SOURCE
                -D__STDC_CONSTANT_MACROS 
                -D__STDC_FORMAT_MACROS 
                -D__STDC_LIMIT_MACROS               
               )

set(LOADABLE_MODULE_OPTIONS_A "-bundle -undefined dynamic_lookup")
set(LOADABLE_MODULE_OPTIONS_B "-shared -W1 , -O1")
   

#shared library
add_library(LLVMwalk_a_baby SHARED walk_a_baby_pass.cpp)

#install
install_targets( /lib LLVMwalk_a_baby)
    
