#cmake cci_mini_clang  william k. johnson 2015

#version
cmake_minimum_required(VERSION 2.8)
#project
project(CCIMINICLANG)

#cpp flags
set(CXX_FLAGS "-rdynamic -omit-frame-pointer -fvisibility-inlines-hidden -fno-exceptions -fPIC -ffunction-sections -fdata-sections -Wcast-qual")
set(CMAKE_CXX_FLAGS_DEBUG "-Wall -g -O0  -Qunused-arguments -fno-rtti -std=c++11 ${CXX_FLAGS}") 
set(CMAKE_CXX_FLAGS_RELEASE "-Wall -O3  -fno-rtti -Qunused-arguments  -DNDEBUG -std=c++11 " ${CXX_FLAGS})

#build macros
add_definitions(-D_GNU_SOURCE
                -D__STDC_CONSTANT_MACROS 
                -D__STDC_FORMAT_MACROS 
                -D__STDC_LIMIT_MACROS               
               )

#environment
execute_process(COMMAND $ENV{LLVM_CONFIG} --includedir OUTPUT_VARIABLE LLVM_INCLUDE)
execute_process(COMMAND $ENV{LLVM_CONFIG} --ldflags OUTPUT_VARIABLE LLVM_LDFLAGS)
execute_process(COMMAND $ENV{LLVM_CONFIG} --libdir OUTPUT_VARIABLE LLVM_LIBDIR)                    
execute_process(COMMAND $ENV{LLVM_CONFIG} --libs OUTPUT_VARIABLE LLVM_LIBS)                    
execute_process(COMMAND $ENV{LLVM_CONFIG} --system-libs OUTPUT_VARIABLE LLVM_SYSTEM_LIBS)
string(STRIP ${LLVM_LIBDIR} LIB)

#link
link_directories(
                  ${CMAKE_INSTALL_PREFIX}/lib
                  ${LIB}
                 )
#include
include_directories(${LLVM_INCLUDE}
                    /usr/include
                    ../../include
                   )
#executables
add_executable(cci_mini_diag clang_mini_diag.cpp mini_diag_main)
add_executable(cci_mini_lex clang_mini_lex.cpp mini_lex_main)
add_executable(cci_mini_driver clang_mini_driver.cpp mini_driver_main)
string(STRIP ${LLVM_LIBS} LIBS)
string(STRIP ${LLVM_SYSTEM_LIBS} SYSTEM_LIBS)
set(CLANG_LIBS "-Wl,--start-group -lclang -lclangFrontend -lclangDriver -lclangSerialization -lclangParse -lclangSema -lclangAnalysis -lclangEdit -lclangAST -lclangLex -lclangBasic -Wl,--end-group")
target_link_libraries(cci_mini_diag ${CLANG_LIBS} ${LIBS} ${SYSTEM_LIBS})
target_link_libraries(cci_mini_lex ${CLANG_LIBS} ${LIBS} ${SYSTEM_LIBS})
target_link_libraries(cci_mini_driver ${CLANG_LIBS} ${LIBS} ${SYSTEM_LIBS})

#shared library
add_library(cci_mini_clang SHARED clang_mini_diag.cpp
                                  clang_mini_lex.cpp
                                  clang_mini_driver.cpp
                                  clang_mini_preproc.cpp)
add_library(cci_mini_clang_static STATIC clang_mini_diag.cpp
                                  clang_mini_lex.cpp
                                  clang_mini_driver.cpp
                                  clang_mini_preproc.cpp)

target_link_libraries(cci_mini_clang ${CLANG_LIBS} ${LIBS} ${SYSTEM_LIBS})
target_link_libraries(cci_mini_clang_static ${CLANG_LIBS} ${LIBS} ${SYSTEM_LIBS})

#install
install_targets(/bin cci_mini_diag)
install_targets(/bin cci_mini_lex)
install_targets(/bin cci_mini_driver)
install_targets(/lib cci_mini_clang)
install_targets(/lib cci_mini_clang_static)
    
