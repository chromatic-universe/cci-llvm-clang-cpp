//walk_baby_lex william k. johnson 2015

#include "ace/Log_Msg.h"
#include <ace/Trace.h>

#include <walk_a_baby_lex.h>
#include <sys/stat.h>

using namespace walk_a_baby;

int walk_a_baby_lex::m_numeric_val = 0;
std::string walk_a_baby_lex::m_string_ident_val = "";
std::string walk_a_baby_lex::function_prefix = "def";
std::string walk_a_baby_lex::extern_prefix = "extern";
std::string  walk_a_baby_lex::if_prefix = "if";
std::string  walk_a_baby_lex::then_prefix = "then";
std::string  walk_a_baby_lex::else_prefix = "else";
std::string  walk_a_baby_lex::for_prefix = "for";
std::string  walk_a_baby_lex::in_prefix = "in";
std::string  walk_a_baby_lex::bin_prefix = "binary";
std::string  walk_a_baby_lex::unary_prefix = "unary";



std::unique_ptr<std::ifstream> walk_a_baby_lex::m_ptr_ifstr( new std::ifstream );

//-------------------------------------------------:-------------------------------------------------
walk_a_baby_lex::walk_a_baby_lex()
{
    //
}

//--------------------------------------------------------------------------------------------------
walk_a_baby_lex::~walk_a_baby_lex()
{
   ACE_Trace _( ACE_TEXT( "\E[31mwalk_a_baby_lex:walk_a_baby_lex()\E[0m" ) , __LINE__ );

   ifstr_ptr ifstr = dynamic_cast<ifstr_ptr>( m_ptr_ifstr.get() );
   if( ifstr != nullptr )
   {
        if( ifstr->is_open() == true )
        {
            ifstr->close();
            std::cout << "\E[31mclosing lexer stream....\n" << "\E[0m";
        }

   }
}

//--------------------------------------------------------------------------------------------------
std::ostream& operator<<( std::ostream &ostr, const walk_a_baby::walk_a_baby_lex& wabl )
{
    return ostr << "todo-walk_a_baby\n";
}

//--------------------------------------------------------------------------------------------------
void walk_a_baby_lex::open_stream( const std::string& file_name )
{
    //stat filename
    struct stat buf;
    if ( !( stat( file_name.c_str() , &buf ) == 0 ) )
    {
         std::cerr << "file "
                   << file_name
                   << " does not exist..aborting...\n";
    }
    else
    {


            //set stream ptr to filestream
            stream_factory( stream_type::st_file_stream  );
            ifstr_ptr ifstr = dynamic_cast<ifstr_ptr>( m_ptr_ifstr.get() );
            //open file stream
            ifstr->open ( file_name.c_str() , std::ifstream::in );
            if( ifstr->is_open() )
            {
                //set stream error bits
                //ifstr->exceptions( std::ios::failbit | std::ios::badbit );
                //allow lexer to handle whitespace
                //*( ifstr ) >> std::noskipws;
                ACE_DEBUG ( ( LM_DEBUG , "\E[31mopened lexer stream\E[0m" ) ) ;

            }
    }
}

//--------------------------------------------------------------------------------------------------
void walk_a_baby_lex::open_stream()
{
    //set stream to stringstream
    //todo
}

//--------------------------------------------------------------------------------------------------
int walk_a_baby_lex::stream_p()
{

    char c { 0 };

    //read stream , set failbit on error
    //badbit, eofbit or failbitnot set
    if( m_ptr_ifstr->good() == true ) { m_ptr_ifstr->get( c ); }

    return ( (int) c );

}

//------------------------------------------------------------------------
void walk_a_baby_lex::stream_factory( const stream_type st )
{
    ifstr_ptr ifstr { nullptr };

    switch( st )
    {
        case stream_type::st_file_stream :
        {
            //reset unique pointer
            if( m_ptr_ifstr.get() )
            {
                //if file stream , close it
                ifstr = dynamic_cast<std::ifstream*>( m_ptr_ifstr.get() );
                if( ifstr )
                {
                    if( ifstr->is_open()  ) { ifstr->close(); }
                }
             }
             //reset unique ptr
             m_ptr_ifstr.reset ( new std::ifstream( nullptr ) );

             break;
        }
        case stream_type::st_string_stream :
        {
             //todo
             break;
        }
        case stream_type::st_stream_buf :
        {
             //todo
             break;
        }
        default :
            break;
    }
}

//------------------------------------------------------------------------
int walk_a_baby_lex::acquire_token()
{
        static int last_char = ' ';

        //skip any whitespace. iostream skip whitespace is off
        while( isspace( last_char ) ) {  last_char = stream_p(); }

        if ( isalpha( last_char ) )
        {
            //identifier: [a-zA-Z][a-zA-Z0-9]*
            m_string_ident_val = last_char;
            while ( isalnum( ( last_char = stream_p() ) ) ) { m_string_ident_val += last_char; }

            if ( m_string_ident_val == function_prefix )
            {  return (int) token_type::tok_func_def; }
            if ( m_string_ident_val == extern_prefix )
            {  return (int) token_type::tok_extern; }
            if ( m_string_ident_val == if_prefix )
            {  return (int) token_type::tok_if; }
            if ( m_string_ident_val == then_prefix )
            {  return (int) token_type::tok_then; }
            if ( m_string_ident_val == else_prefix )
            {  return (int) token_type::tok_else; }
            if ( m_string_ident_val == for_prefix )
            {  return (int) token_type::tok_for; }
            if ( m_string_ident_val == in_prefix )
            {  return (int) token_type::tok_in; }
             if ( m_string_ident_val == bin_prefix )
            {  return (int) token_type::tok_binary; }
            if ( m_string_ident_val == unary_prefix )
            {  return (int) token_type::tok_unary; }

            return (int) token_type::tok_identifier;
       }

       if ( isdigit( last_char ) || last_char == '.')
       {
           //number: [0-9.]+
           std::string num_str;
           do
           {
                num_str += last_char;
                last_char = stream_p();
           } while ( isdigit( last_char ) || last_char == '.' );

           m_numeric_val = strtod( num_str.c_str(), nullptr);

           return (int) token_type::tok_numeric;
      }

      if ( last_char == '#' )
      {
          //comment until end of line.
          do{ last_char = stream_p(); }
          while ( last_char != stream()->eof() && last_char != '\n' && last_char != '\r');

          if ( last_char != stream()->eof() ) { return acquire_token(); }
      }

      //check for end of file.  don't eat the eof.
      if ( last_char == stream()->eof() ) { return ( (int) token_type::tok_eof ); }

      //otherwise, just return the character as its ascii value.
      int this_char = last_char;
      last_char = stream_p();

      return ( this_char );
}




