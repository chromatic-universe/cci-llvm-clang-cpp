//clang_mini_diag.cpp william k. johnson 2015

#include <clang_mini_tool.h>

using namespace llvm;
using namespace chromatic_llvm_clang;

//------------------------------------------------------------------------
clang_mini_diag::clang_mini_diag( const std::string& file_name ,
                                  translation_args args ) : m_str_filename { file_name } ,
                                                            m_ptr_translation ( new translation_args( args ) )
{

}

//------------------------------------------------------------------------
clang_mini_diag::~clang_mini_diag()
{
    //
}

//------------------------------------------------------------------------
clang_mini clang_mini_diag::perform()
{

    clang_mini diag = clang_mini::cm_parse_trans;
    while( diag != clang_mini::cm_diag_error &&
             diag != clang_mini::cm_diag_done )
    {
        switch( diag )
        {
            case clang_mini::cm_parse_trans :
            {
               std::cout << "instantiating translation unit.....\n";

               diag = clang_mini::cm_diag_error;
               std::pair<bool,struct stat> sb( file_exists( m_str_filename ) );

               if( sb.first == true )
               {
                 m_translation_unit = clang_parseTranslationUnit( std::get<0>( *m_ptr_translation.get() ) ,
                                                                  std::get<1>( *m_ptr_translation.get() ).c_str()  ,
                                                                  std::get<2>( *m_ptr_translation.get() ) ,
                                                                  std::get<3>( *m_ptr_translation.get() ) ,
                                                                  std::get<4>( *m_ptr_translation.get() ) ,
                                                                  std::get<5>( *m_ptr_translation.get() ) ,
                                                                  std::get<6>( *m_ptr_translation.get() ) );

                 if( m_translation_unit != nullptr )
                 {
                    diag = clang_mini::cm_diag_count;
                 }
                 else
                 {
                    diag = clang_mini::cm_diag_error;
                    std::cerr << "could not instantiate translation unit...\n";
                 }

               }
               break;
            }
            case clang_mini::cm_diag_count :
            {
                diag = clang_mini::cm_diag_error;
                m_diagnostic_count = clang_getNumDiagnostics( m_translation_unit );
                //no diagnostics as error
                m_diagnostic_count <= 0 ? diag = clang_mini::cm_diag_error : diag = clang_mini::cm_diag_diagnosed;
                std::cout << "getting count of translation units....\n";

                break;
            }
            case clang_mini::cm_diag_diagnosed :
            {
                std::cout << "diagnosing...\n";
                for( unsigned long i = 0; i < m_diagnostic_count; ++i )
                {
                    clang_mini_atom( i );
                }
                diag = clang_mini::cm_diag_done;
                break;
            }
            case clang_mini::cm_diag_done :
            {
                break;
            }
            case clang_mini::cm_diag_error :
            {
                std::cerr << "error in diagnostic stack....\n";
                break;
            }
        }
    }
    return ( diag );
}


//------------------------------------------------- )---------------------
clang_mini clang_mini_diag::clang_mini_atom( const unsigned long atom  )
{

    CXDiagnostic diagnostic = clang_getDiagnostic( m_translation_unit , atom );
    CXString category = clang_getDiagnosticCategoryText( diagnostic );
    CXString message = clang_getDiagnosticSpelling( diagnostic );
    unsigned long severity = clang_getDiagnosticSeverity( diagnostic );

    CXSourceLocation loc = clang_getDiagnosticLocation( diagnostic );
    CXString name;
    unsigned int line = 0;
    unsigned int col = 0;

    clang_getPresumedLocation( loc , &name , &line , &col );

    //format
    std::cout << "severity: "
              << severity << "\n"
              << "file: "
              << clang_getCString( name ) << "\n"
              << "line: "
              << line << "\n"
              << "col: "
              << col << "\n"
              << "category: \""
              << clang_getCString( category )
              << "\" message: "
              << clang_getCString( message ) << "\n"
              << std::endl;

    return ( clang_mini::cm_diag_diagnosed );
}



