//clang_mini_driver.cpp william k. johnson 2015
//
//this utility may be handy to verify setups
//and thus is heavily commented

#include <clang_mini_tool.h>

using namespace llvm;
//using namespace clang;
using clang::CompilerInstance;
using clang::TargetOptions;
using clang::TargetInfo;
using clang::FileEntry;
using clang::Token;
using clang::ASTContext;
using clang::ASTConsumer;
using clang::Parser;
using clang::DiagnosticOptions;
using clang::TextDiagnosticPrinter;
using namespace chromatic_llvm_clang;


//------------------------------------------------------------------------
clang_mini_driver::clang_mini_driver( const std::string& file_name ) : m_ptr_compiler( new CompilerInstance() ) ,
                                                                       m_ptr_diag_options( new DiagnosticOptions() ) ,
                                                                       m_str_filename { file_name }
{
    tagline( "filename" , file_name );
}

//------------------------------------------------------------------------
clang_mini_driver::~clang_mini_driver()
{
    tagline( "driver destructor" , "fini" );
}

//------------------------------------------------------------------------
clang_mini clang_mini_driver::perform()
{

    if( file_exists( m_str_filename ).first == false )
    { return ( clang_mini::cm_driver_error ); }
    tagline( "file exists" , "ok" );


    //target info
    TargetInfo* pti = nullptr;

    //consumer
    ASTConsumer* ast_consumer;
    const FileEntry* p_file = nullptr;
    std::shared_ptr<TargetOptions> pto;
    DiagnosticOptions diagnostic_options;

    clang_mini mini = clang_mini::cm_set_diag_opts;

    while( mini != clang_mini::cm_driver_error &&
             mini != clang_mini::cm_driven )
    {
        switch( mini )
        {
            case clang_mini::cm_set_diag_opts :
            {
                m_ptr_compiler->createDiagnostics();
                tagline( "create diagnostics" , "ok" );

                //target options
                pto = std::make_shared<TargetOptions>();
                pto->Triple = sys::getDefaultTargetTriple();
                tagline( "set target options" , "ok" );

                mini = clang_mini::cm_driver_set_target;

                break;
            }
            case clang_mini::cm_driver_set_target :
            {
                //target info
                pti = TargetInfo::CreateTargetInfo( m_ptr_compiler->getDiagnostics() ,
                                                    pto );
                tagline( "create target info" , "ok" );
                //set target
                m_ptr_compiler->setTarget( pti );
                tagline( "set target" , "ok" );

                mini = clang_mini::cm_set_compiler_mgrs;

                break;
            }
            case clang_mini::cm_set_compiler_mgrs :
            {
                //create file manager
                m_ptr_compiler->createFileManager();
                tagline( "create file manager" , "ok" );
                //create source manager
                m_ptr_compiler->createSourceManager( m_ptr_compiler->getFileManager() );
                tagline( "create source manager" , "ok" );
                //create preprocessor
                m_ptr_compiler->getLangOpts().CPlusPlus = 1;
                m_ptr_compiler->createPreprocessor( clang::TU_Complete );
                tagline( "create preprocessor" , "ok" );

                mini = clang_mini::cm_set_ast_consumer;

                break;

            }
            case clang_mini::cm_set_ast_consumer :
            {

                m_ptr_compiler->getPreprocessorOpts().UsePredefines = false;
                m_ptr_compiler->setASTConsumer( llvm::make_unique<ASTConsumer>(  ));
                tagline( "set ast consumer" , "ok" );

                mini = clang_mini::cm_create_sema;

                break;
            }
            case clang_mini::cm_create_sema :
            {
                clang::HeaderSearchOptions headerSearchOptions;
                m_ptr_compiler->getHeaderSearchOpts().UseBuiltinIncludes = false;
                m_ptr_compiler->getHeaderSearchOpts().UseStandardSystemIncludes = true;
                m_ptr_compiler->getHeaderSearchOpts().UseStandardCXXIncludes = true;
                clang::InitializePreprocessor(m_ptr_compiler->getPreprocessor(),
                              m_ptr_compiler->getPreprocessorOpts(),
                              m_ptr_compiler->getFrontendOpts());
                m_ptr_compiler->createASTContext();
                tagline( "create ast context" , "ok" );
                m_ptr_compiler->createSema( clang::TU_Complete , NULL );
                tagline( "create sema" , "ok" );
                p_file = m_ptr_compiler->getFileManager(). \
                         getFile( m_str_filename );
                p_file ?  mini = clang_mini::cm_parse_ast
                       :  mini = clang_mini::cm_driver_error;

                break;
            }
            case clang_mini::cm_parse_ast :
            {
               m_ptr_compiler->getSourceManager(). \
                               setMainFileID( m_ptr_compiler->getSourceManager(). \
                               createFileID( p_file ,
                               clang::SourceLocation() ,
                               clang::SrcMgr::C_User) );
               m_ptr_compiler->getDiagnosticClient().BeginSourceFile( m_ptr_compiler->getLangOpts(), 0);
               clang::ParseAST( m_ptr_compiler->getSema() );
               tagline( "parse ast" , "ok" );
               mini = clang_mini::cm_stream_stats;

               break;
            }
            case clang_mini::cm_stream_stats :
            {
                mini = clang_mini::cm_driven;

                m_ptr_compiler->getASTContext().PrintStats();
                m_ptr_compiler->getASTContext().Idents.PrintStats();

                break;
            }
            case clang_mini::cm_driver_error :
            {
                std::cerr << "error in driver stack....\n";
                break;
            }
        }
    }


    return ( mini );
}

//------------------------------------------------------------------------
clang_mini clang_mini_driver::clang_mini_atom( const unsigned long atom )
{
       clang_mini mini = clang_mini::cm_driven;

       return ( mini );
}

