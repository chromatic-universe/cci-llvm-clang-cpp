//clang_mini_lex.h william k. johnson 2015

#include <clang_mini_tool.h>

using namespace llvm;
using namespace chromatic_llvm_clang;

//------------------------------------------------------------------------
clang_mini_lex::clang_mini_lex( const std::string& file_name ,
                                const translation_args args  ) :  m_str_filename { file_name } ,
                                                                  m_tokens ( nullptr ) ,
                                                                  m_dw_tokens( 0 ) ,
                                                                  m_ptr_translation ( new translation_args( args ) ) ,
                                                                  m_translation_unit ( nullptr  )
{
    //
}

//------------------------------------------------------------------------
clang_mini_lex::~clang_mini_lex()
{
    clang_disposeTokens( m_translation_unit , m_tokens , m_dw_tokens );
    if( m_translation_unit ) { clang_disposeTranslationUnit( m_translation_unit ); }
}

//------------------------------------------------------------------------
clang_mini clang_mini_lex::clang_mini_atom( const unsigned long atom  )
{
      enum CXTokenKind kind = clang_getTokenKind( m_tokens[atom] );
	  CXString name = clang_getTokenSpelling( m_translation_unit , m_tokens[atom]);
      switch (kind)
      {
                    case CXToken_Punctuation:
                        std::cout << "PUNCTUATION(" << clang_getCString(name) << ") ";
                        break;
                    case CXToken_Keyword:
                        std::cout << "\E[31mKEYWORD(" << clang_getCString(name) <<")\E[0m ";
                        break;
                    case CXToken_Identifier:
                        std::cout << "\E[34m IDENTIFIER(" << clang_getCString(name) << ")\E[0m ";
                        break;
                    case CXToken_Literal:
                        std::cout << "LITERAL(" << clang_getCString(name) << ") ";
                        break;
                    case CXToken_Comment :
                        std::cout << "\E[32m COMMENT(" << clang_getCString(name) << ")\E[0m ";
                        break;
                    default:
                        std::cout << "UNKNOWN(" << clang_getCString(name) << ")";
                        break;
      }
      clang_disposeString( name );


       return ( clang_mini::cm_tokenize );
}

//------------------------------------------------------------------------
clang_mini clang_mini_lex::perform()
{
    clang_mini mini = clang_mini::cm_parse_trans;
    CXFile file { nullptr };
    CXSourceRange range;
    unsigned dw_file_size { 0  };

    while( mini != clang_mini::cm_tok_error &&
             mini != clang_mini::cm_tokenized )
    {
        switch( mini )
        {
            case clang_mini::cm_parse_trans :
            {
                std::cout << "instantiating translation unit.....\n";

                mini = clang_mini::cm_diag_error;
                std::pair<bool,struct stat> sb( file_exists( m_str_filename ) );
                if( sb.first == true )
                {
                  dw_file_size = sb.second.st_size;
                  m_translation_unit = clang_parseTranslationUnit( std::get<0>( *m_ptr_translation.get() ) ,
                                                                   std::get<1>( *m_ptr_translation.get() ).c_str()  ,
                                                                   std::get<2>( *m_ptr_translation.get() ) ,
                                                                   std::get<3>( *m_ptr_translation.get() ) ,
                                                                   std::get<4>( *m_ptr_translation.get() ) ,
                                                                   std::get<5>( *m_ptr_translation.get() ) ,
                                                                   std::get<6>( *m_ptr_translation.get() ) );

                  if( m_translation_unit != nullptr )
                  {
                    mini = clang_mini::cm_acquire_file;
                  }
                  else
                  {
                    mini = clang_mini::cm_tok_error;
                    std::cerr << "could not instantiate translation unit...\n";
                  }

               }
               else
               {
                    mini = clang_mini::cm_tok_error;
                    std::cerr << "could not find file..." << m_str_filename <<  "\n";
               }

               break;
            }
            case clang_mini::cm_acquire_file :
            {
                std::cout << "acquire file...\n";

                file = clang_getFile( m_translation_unit , m_str_filename.c_str() );
                file == nullptr ? mini = clang_mini::cm_tok_error : mini = clang_mini::cm_make_range;

                break;
            }
            case clang_mini::cm_make_range :
            {
                std::cout << "make range...\n";

                //begin
                CXSourceLocation loc_start = clang_getLocationForOffset( m_translation_unit , file , 0 );
                //end
                CXSourceLocation loc_end =   clang_getLocationForOffset( m_translation_unit , file , dw_file_size - 1 );
                //range
                range = clang_getRange( loc_start , loc_end );

                mini = clang_mini::cm_tokenize;

                break;
            }
            case clang_mini::cm_tokenize :
            {
                clang_tokenize( m_translation_unit, range, &m_tokens, &m_dw_tokens );
                std::cout << "number of tokens: " << m_dw_tokens  << "\n";

                mini = clang_mini::cm_stream_out;

                break;
            }
            case clang_mini::cm_stream_out :
            {
                for ( unsigned i = 0; i < m_dw_tokens; ++i )
                {
                   clang_mini_atom( i );
                }
                std::cout << "\n";

                mini = clang_mini::cm_tokenized;

                break;
            }
            case clang_mini::cm_tok_error :
            {
                std::cerr << "error in lexer stack....\n";
                break;
            }

        }
    }
    return ( mini );
}
