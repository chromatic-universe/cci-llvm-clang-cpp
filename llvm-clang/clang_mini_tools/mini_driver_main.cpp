//mini_driver_main.cpp william k. johnson 2015


#include <clang_mini_tool.h>

using namespace llvm;
using namespace clang;
using namespace chromatic_llvm_clang;

static cl::opt<std::string> filename( cl::Positional ,
                                      cl::desc( "input file" ) ,
                                      cl::Required );

int main( int argc , char* argv[] )
{

    cl::ParseCommandLineOptions( argc , argv , "clang_mini_driver" );

    std::unique_ptr<clang_mini_driver> mini( new clang_mini_driver( filename ) );
    clang_mini mini_return = mini->perform();

    return ( 0 );

}
