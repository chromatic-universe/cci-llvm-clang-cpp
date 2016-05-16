//mini_lex_main.cpp william k. johnson 2015
//
#include <clang_mini_tool.h>

using namespace llvm;
using namespace chromatic_llvm_clang;

static cl::opt<std::string> filename( cl::Positional ,
                                      cl::desc( "input file" ) ,
                                      cl::Required );

int main( int argc , char* argv[] )
{
    cl::ParseCommandLineOptions( argc , argv , "clang_mini_lex" );
    const char* dargs[] = { "-x" ,
                            "c++" ,
                            "-std=c++11" ,
                            "-I../../include" ,
                            "-I./" ,
                            "-I/dev_src/dev_src_a/dev_src/include"  ,
                            "-I/usr/include/linux/limits.h" ,
                            "-I/dev_tools/bin/../lib/clang/3.5.1/include" ,
                            "-I/dev_tools/lib/clang/3.5.1/include" ,
                            "-I/usr/include" ,
                            "-I/usr/include/glib-2.0" ,
							"-I/usr/lib/i386-linux-gnu/glib-2.0/include"};
    CXIndex idx = clang_createIndex( 0 , 0 );
    translation_args targs;
    std::get<0>( targs ) = idx;
    std::get<1>( targs ) = filename;
    std::get<2>( targs ) = dargs;
    std::get<3>( targs ) = 12;
    std::get<4>( targs ) = NULL;
    std::get<5>( targs ) = 0;
    std::get<6>( targs ) = CXTranslationUnit_None;

    std::unique_ptr<clang_mini_lex> mini( new clang_mini_lex( filename , targs ) );
    mini->perform();


    return ( 0 );
}

