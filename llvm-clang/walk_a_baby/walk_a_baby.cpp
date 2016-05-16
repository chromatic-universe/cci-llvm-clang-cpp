//walk_a_baby.cpp william k. johnson 2015

#include <walk_a_baby_parse.h>
#include <walk_a_baby_jit.h>

using namespace walk_a_baby;
using namespace llvm;
#include <ace/Log_Msg.h>
#include <ace/Trace.h>

double printd(double X) {
  printf("%f\n", X);
  return 0;
}

//cli options
static cl::opt<std::string> baby_filename( cl::Positional ,
                                           cl::desc( "baby input c/c++ source file" ) ,
                                           cl::Required );
static cl::opt<bool> baby_interactive( "baby-interactive", cl::desc( "interactive command line compiler" ) );
static cl::opt<bool> baby_trace( "baby-enable-trace", cl::desc( "enable tracing" ) );

namespace helper
{
    //cloning make_unique here until it's standard in C++14.
    template <class T, class... Args>
    static typename std::enable_if<!std::is_array<T>::value, std::unique_ptr<T>>::type
        make_unique(Args &&... args)
    {
        return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
    }
}

int main( int argc , char* argv[] )
{
    //walk-a-baby compiler

    //trace if ACE_NTRACE = 0
    ACE_TRACE ( "main" );
    //debug if ACE_NDEBUG = 0
    ACE_DEBUG ( (LM_DEBUG, "(%P|%t) %s \n" , "/home/wiljoh/greasy.in" ) );

    //environnment initialozations
    InitializeNativeTarget();
    InitializeNativeTargetAsmPrinter();
    InitializeNativeTargetAsmParser();

    //module
    std::unique_ptr<Module> owner = make_unique<Module>( "walk-a-baby", getGlobalContext() );

    //process command line interface
    std::cerr << "\E[32m";
    cl::ParseCommandLineOptions( argc , argv , "walk-a-baby compiler william k. johnson 2015" );
    std::cerr << "\E[0m";
    //we run our command line utility
    if( baby_interactive == false ) { std::cout << "interactive is off..\n"; }

    //engine takes ownership of module
    static std::unique_ptr<walk_a_baby_driver> baby( new walk_a_baby_driver() );
    baby->module( owner.get() );
    static std::string err_str( "" );
        exec_engine_ptr ptr_exec =
        EngineBuilder( std::move( owner ) )
          .setErrorStr( &err_str )
          .setMCJITMemoryManager( llvm::make_unique<SectionMemoryManager>() )
          .create();
    //give a ptr back to our facade for ast processing
    baby->engine( ptr_exec );
    //create pass manager in static scope
    legacy::FunctionPassManager local_fpm( baby->module() );
    //pass a ptr back to our facade for optimizing passes
    baby->pass_mgr( &local_fpm );
    //initialize optimization pipeline
    baby->init_pipeline();
    //driver; lexer and parser are references by composition pointers
    //
    //open token stream
    baby->parse()->lex()->open_stream( baby_filename.c_str() );
    //greedy gobble all input until exhausted
    //all tokens are seen including white space
    //we hand roll our own lexemes
    //
    //first look - lexer
    baby->parse()->next_token();
    //run the main "interpreter loop" , parser and semantics
    baby->perform();
    //deaden the manager ptr
    baby->pass_mgr( 0 ) ;
    //dump intermediate representation to stderr
    //for debugging
    //green
    std::cerr << "\E[32m";
    baby->module()->dump();
    //unred
    std::cerr << "\E[0m";


    return ( 0 );
}


