//walk_a_baby_parse.cpp william k. johnson 2015

#include <walk_a_baby_parse.h>

using namespace llvm;
using namespace walk_a_baby;

namespace helper
{
    template <class T, class... Args>
    static typename std::enable_if<!std::is_array<T>::value, std::unique_ptr<T>>::type
    make_unique(Args &&... args)
    {
            return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
    }
}


//static initializations
//
//current lexical token
int walk_a_baby_parse::current_lex_token = 0;
//lexer
std::unique_ptr<walk_a_baby::walk_a_baby_lex> walk_a_baby_parse::m_ptr_lex( new walk_a_baby_lex() );
//parser
std::unique_ptr<walk_a_baby::walk_a_baby_parse> walk_a_baby_driver::m_baby_parse( new walk_a_baby_parse() );
//vector of sources
std::unique_ptr<walk_a_baby::v_str> walk_a_baby_driver::m_v_filenames( new v_str  );
//execution engine
exec_engine_ptr walk_a_baby_driver::m_ptr_exec( nullptr );
//module ptr for jit
module_ptr walk_a_baby_driver::m_ptr_module( nullptr );
//llvm ir builder
std::unique_ptr<IRBuilder<>> walk_a_baby_driver::m_ir_builder( new IRBuilder<>( getGlobalContext() ) );
//symbol table
std::unique_ptr<symbol_table> walk_a_baby_driver::m_symbol_table( new symbol_table );
//function pass manager
pass_mgr_ptr walk_a_baby_driver::m_pass_mgr( nullptr );
//install standard binary operators. 1 is lowest precedence.
std::map<char,int> walk_a_baby_parse::bin_op_precedence= { {'<', 10} , {'+' , 20} , {'=' , 20} , {'*' , 40} };

//------------------------------------------------------------------------
walk_a_baby_parse::walk_a_baby_parse()
{
    ACE_Trace _( ACE_TEXT( "%twalk_a_baby_parse::walk_a_baby_parse()" ) , __LINE__ );
}

//------------------------------------------------------------------------
walk_a_baby_parse::~walk_a_baby_parse()
{
    ACE_Trace _( ACE_TEXT( " walk_a_baby_parse::~walk_a_baby_parse()" ) , __LINE__ );
}
//------------------------------------------------------------------------
expr_ast_ptr walk_a_baby_parse::parse_numeric_expr()
{
    ACE_Trace _( ACE_TEXT( "walk_a_baby_parse::parse_numeric_expr" ) , __LINE__ );

    std::unique_ptr<expr_ast> result ( new numeric_expr_ast( walk_a_baby_lex::m_numeric_val ) );
    //consume
    next_token();

    return ( result );
}

//-------------------------------------------------------------------------
expr_ast_ptr walk_a_baby_parse::parse_paren_expr()
{
    ACE_TRACE( "walk_a_baby_parse::parse_paren_expr" );

    ///parenexpr ::= '(' expression ')'

    //consume paren '('
    next_token();

    auto v = parse_expression();
    if ( !v ) { return ( 0 ); }

    if ( current_lex_token != ')' )
    {
        std::cerr << "expected ')'" << "\n";
        return ( nullptr );
    }

    //conume paren ')'
    next_token();

    return ( v );
}

//------------------------------------------------------------------------
expr_ast_ptr walk_a_baby_parse::parse_identifier_expr()
{
    ACE_Trace _( ACE_TEXT( "walk_a_baby_parse::parse_identifier_expr" ) , __LINE__ );

    /// identifierexpr:w
    //
    ///   ::= identifier
    ///   ::= identifier '(' expression* ')'
    std::string id_name = walk_a_baby_lex::m_string_ident_val;
    std::vector<expr_ast_ptr> args;

    //consume
    next_token();

    if ( current_lex_token != '(' )
    {
          // simple variable ref
          return ( helper::make_unique<variable_ast>( id_name ) );
    }
    else
    {
        //call
        //consume
        next_token();
        if ( current_lex_token != ')' )
        {
            while ( 1 )
            {
                if ( auto arg = parse_expression() )
                {
                    args.push_back( std::move( arg ) );
                }
                else
                {
                    return ( nullptr );
                }

                if ( current_lex_token  == ')' )
                {

                    break;
                }

                if ( current_lex_token != ',' )
                {

                    std::cerr << "Expected ')' or ',' in argument list\n";
                    return ( nullptr );
                }

                next_token();
            }
        }

        //eat the ')'.
        next_token();
    }


    return llvm::make_unique<call_expr_ast>( id_name , std::move( args ) ) ;

}

//------------------------------------------------------------------------
expr_ast_ptr walk_a_baby_parse::parse_expression()
{
    ACE_TRACE( "walk_a_baby_parse::parse_expression" );

    /// expression
    ///   ::= primary binoprhs
    ///

    expr_ast_ptr lhs = parse_unary_expr();
    if ( !lhs ) { return ( 0 ); }

    return parse_bin_op_rhs( 0 , std::move( lhs ) ) ;
}

//------------------------------------------------------------------------
expr_ast_ptr walk_a_baby_parse::parse_primary()
{
    ACE_TRACE( "\E[34mwalk_a_baby_parse::parse_primary\E[0m");

    /// primary
    ///   ::= identifierexpr
    ///   ::= numberexpr
    ///   ::= parenexpr
    switch ( current_lex_token )
    {
        default:
        {
            std::cerr << "unknown token when expecting an expression\n";
            std::cout << "unknown token=" << current_lex_token << "\n";
            return ( nullptr );
        }
        case (int) token_type::tok_identifier :
            return ( parse_identifier_expr() );
        case (int) token_type::tok_numeric:
            return ( parse_numeric_expr() );
        case '(' :
            return ( parse_paren_expr() );
        case (int) token_type::tok_if :
            return ( parse_if_expr() );
        case (int) token_type::tok_for :
            return ( parse_for_expr() );
    }
}

//------------------------------------------------------------------------
int walk_a_baby_parse::next_token()
{
    //ACE_TRACE( "walk_a_baby_parse::next_token" );

    return( current_lex_token = m_ptr_lex->acquire_token() );
}

//------------------------------------------------------------------------
//get the precedence of the pending binary operator token.
int walk_a_baby_parse::get_tok_precedence()
{
    //ACE_TRACE( "%T walk_a_baby_parse::get_token_precedence" );

    if ( !isascii( current_lex_token ) ) { return ( -1 ); }

    //make sure it's a declared binop.
    int tok_prec = bin_op_precedence[current_lex_token];
    if ( tok_prec <= 0 ) return( -1 );

    return ( tok_prec );
}

//------------------------------------------------------------------------
expr_ast_ptr walk_a_baby_parse::parse_bin_op_rhs( int expr_prec ,
                                                    expr_ast_ptr lhs )
{
    ACE_Trace _( ACE_TEXT( "walk_a_baby_parse::parse_bin_op_rhs" ) , __LINE__ );

    /// binoprhs
    ///   ::= ('+' primary)*
    // if this is a binop, find its precedence.
    while ( 1 )
    {
        int tok_prec = get_tok_precedence();

        // If this is a binop that binds at least as tightly as the current binop,
        // consume it, otherwise we are done.
         if ( tok_prec < expr_prec ) return ( lhs );

        //we know this is a binop.
        int bin_op = current_lex_token;
        next_token(); // eat binop

        //parse the primary expression after the binary operator.
        expr_ast_ptr rhs = parse_unary_expr();
        if ( !rhs ) { return ( 0 ); }

        //if BinOp binds less tightly with RHS than the operator after RHS, let
        //the pending operator take RHS as its LHS.
        int next_prec = get_tok_precedence();

        if ( tok_prec < next_prec)
        {
            rhs = parse_bin_op_rhs( tok_prec + 1 , std::move( rhs ) );
            if ( rhs == 0 ) { return ( 0 ); }
        }

        //merge lhs/rhs
        lhs = helper::make_unique<binary_ast>( bin_op , std::move( lhs ) ,
                                                        std::move( rhs ) );
    }
}

//------------------------------------------------------------------------
expr_ast_ptr walk_a_baby_parse::parse_if_expr()
{

    /// ifexpr ::= 'if' expression 'then' expression 'else' expression
    next_token();  // eat the if.

    //condition.
    expr_ast_ptr cond = parse_expression();
    if ( !cond ) { return ( 0 ); }

    if ( current_lex_token != (int) token_type::tok_then )
    {
        std::cerr << "expected then\n";
        return ( nullptr  );
    }

    next_token();  // eat the then

    expr_ast_ptr then = parse_expression();
    if ( then == 0 ) { return ( 0 ); }

    if ( current_lex_token != (int) token_type::tok_else )
    {
        std::cerr << "expected else\n";
        return ( nullptr );
    }

    next_token();

    expr_ast_ptr _else = parse_expression();
    if ( !_else ) { return ( 0 ); }

    return ( helper::make_unique<if_expr_ast>( std::move( cond ) ,
                                               std::move( then ) ,
                                               std::move( _else ) ) );
}

//------------------------------------------------------------------------
expr_ast_ptr walk_a_baby_parse::parse_for_expr()
{
    //forexpr ::= 'for' identifier '=' expr ',' expr (',' expr)? 'in' expression

    next_token();  // eat the for.

    if ( current_lex_token != (int) token_type::tok_identifier )
    {
        std::cerr << "expected identifier after for\n";
        return ( nullptr );
    }

    std::string id_name( walk_a_baby_lex::m_string_ident_val );
    next_token();  // eat identifier.

    if ( current_lex_token != '=')
    {
        std::cerr << "expected = after for\n";
        return ( nullptr );
    }
    next_token();  // eat '='.

    expr_ast_ptr start = parse_expression();
    if ( start == 0 ) { return ( 0 ); }
    if ( current_lex_token != ',')
    {
        std::cerr << "expected ',' after for start value\n";
        return ( nullptr );
    }
    next_token();

    expr_ast_ptr end = parse_expression();
    if ( end == 0) { return ( 0 ); }

    //the step value is optional.
    expr_ast_ptr step = 0;
    if ( current_lex_token == ',' )
    {
        next_token();
        step = parse_expression();
        if ( step == 0) { return ( 0 ); }
    }

    if ( current_lex_token != (int) token_type::tok_in )
    {
        std::cerr << "expected 'in' after for\n";
        return ( nullptr );
    }
    next_token();  // eat 'in'.

    expr_ast_ptr body = parse_expression();
    if ( body == 0 ) { return ( 0 ); }

    return helper::make_unique<for_expr_ast>( id_name ,
                                             std::move( start ) ,
                                             std::move( end  ),
                                             std::move( step ) ,
                                             std::move( body ) );
}

//------------------------------------------------------------------------
expr_ast_ptr walk_a_baby_parse::parse_unary_expr()
{
    ACE_TRACE( "walk_a_baby_parse::parse_unary_expr" );

    /// unary
    ///   ::= primary
    ///   ::= '!' unary
    //if the current token is not an operator, it must be a primary expr.
    int g = isascii( current_lex_token );
    if ( !isascii( current_lex_token ) ||
            current_lex_token  == '('  ||
            current_lex_token  == ',' )
    {
        return ( parse_primary() );
    }

    //if this is a unary operator, read it.
    int op_c = current_lex_token;
    next_token();

    if( expr_ast_ptr operand = parse_unary_expr() )
    { return ( helper::make_unique<unary_expr_ast>( op_c , std::move( operand ) ) ); }

    return ( 0 );
}

//------------------------------------------------------------------------
prototype_ast_ptr walk_a_baby_parse::parse_prototype()
{
    /// prototype  ::= id '(' id* ')'
    ///            ::= binary LETTER number? (id, id)
    ACE_TRACE( "walk_a_baby_parse::parse_prototype" );

    unsigned kind = 0;  // 0 = identifier, 1 = unary, 2 = binary.
    unsigned binary_precedence = 30;

    std::string fn_name;
    switch ( current_lex_token )
    {
        case (int) token_type::tok_identifier :
        {
            fn_name = walk_a_baby_lex::m_string_ident_val;
            kind = 0;
            next_token();

            break;
        }
        case (int) token_type::tok_unary :
        {
            next_token();
            if ( !isascii( current_lex_token) )
            {
                std::cerr <<  "expected unary operator\n";
                return( nullptr );
            }
            fn_name = "unary";
            fn_name += (char) current_lex_token;
            kind = 1;
            next_token();

            break;
        }
        case (int) token_type::tok_binary :
        {
            next_token();
            if ( !isascii( current_lex_token ) )
            {
                std::cerr << "expected binary operator\n";
                return ( nullptr );
            }
            fn_name = "binary";
            fn_name += (char) current_lex_token;
            kind = 2;
            next_token();

            //read the precedence if present.
            if ( current_lex_token == (int) token_type::tok_numeric )
            {
                if (  walk_a_baby_lex::m_numeric_val < 1 ||
                       walk_a_baby_lex::m_numeric_val > 100 )
                {
                    std::cerr << "invalid precedence: must be 1..100\n";
                    return ( nullptr );
                }

                binary_precedence = (unsigned)  walk_a_baby_lex::m_numeric_val;
                next_token();

                break;
            }
        }
        default :
        {
            std::cerr << "expected function name in prototype\n";
            return ( nullptr );
        }
    }

    if ( current_lex_token != '(' )
    {
        std::cerr << "expected '(' in prototype\n";
        return ( nullptr );
    }
    std::vector<std::string> arg_names;
    while ( next_token() ==  (int) token_type::tok_identifier )
    {
       arg_names.push_back( walk_a_baby_lex::m_string_ident_val );
    }
    if ( current_lex_token != ')' )
    {
        std::cerr << "expected ')' in prototype\n";
        return( nullptr );
    }
    //success
    std::cout << "parsed proto..." << "function name=" << fn_name << "\n";

    next_token(); // eat ')'.

    //verify right number of names for operator.
    if ( kind && arg_names.size() != kind)
    {
        std::cerr << "invalid number of operands for operator\n";
        return ( nullptr );
    }

   return ( helper::make_unique<prototype_ast>( fn_name ,
                                                 arg_names ,
                                                 kind != 0 ,
                                                 binary_precedence ) );
}

//------------------------------------------------------------------------
function_ast_ptr walk_a_baby_parse::parse_definition()
{
    ACE_Trace _( ACE_TEXT( "walk_a_baby_parse::parse_definition" ) , __LINE__ );

    /// definition ::= 'def' prototype expression

    next_token();  // eat def.
    prototype_ast_ptr proto = parse_prototype();
    if ( !proto ) { return ( nullptr ); }


    if ( expr_ast_ptr e = parse_expression() )
    {
        std::cout << "parse_definition...\n";
        return ( helper::make_unique<function_ast>( std::move( proto ) ,
                                                 std::move( e ) ) );
    }

    return ( nullptr );
}

//------------------------------------------------------------------------
prototype_ast_ptr walk_a_baby_parse::parse_extern()
{
    ACE_Trace _( ACE_TEXT( "walk_a_baby_parse::parse_extern" ) , __LINE__ );

    /// external ::= 'extern' prototype
    next_token();  // eat extern .

    return ( parse_prototype() );
}

//------------------------------------------------------------------------
function_ast_ptr walk_a_baby_parse::parse_top_level_expr()
{
    ACE_TRACE( "walk_a_baby_parse::parse_top_level_expression" );

    /// toplevelexpr ::= expression
    if ( expr_ast_ptr e = parse_expression())
    {
        //make an anonymous proto.
       std::unique_ptr<prototype_ast> proto ( new prototype_ast( "" , std::vector<std::string>() ) );

       return ( helper::make_unique<function_ast>( std::move( proto )  ,
                                                    std::move(  e  ) ) );
    }

    return ( nullptr );
}

//------------------------------------------------------------------------
void walk_a_baby_parse::handle_extern()
{
    ACE_TRACE( "walk_a_baby_parse::handle_extern" );

    std::cout << "parsed an extern\n";

    if ( prototype_ast_ptr p = parse_extern() )
    {
        if( Function *f = p->codegen() )
        {
               f->dump();
        }
    }
    else
    {
        //skip token for error recovery.
        next_token();
    }
}

//------------------------------------------------------------------------
void walk_a_baby_parse::handle_definition()
{
    ACE_Trace _( ACE_TEXT( "walk_a_baby_parse::handle_definition" ) , __LINE__ );

    if( function_ast_ptr  f = parse_definition() )
    {

        if ( Function* lf = f->codegen() )
        {
            std::cerr << "\E[32mparsed a function definition.\n";
            //lf->dump();
            std::cerr << "\E[0m";
        }

    }
    else
    {
        //skip token for error recovery.
        next_token();
    }

}

//------------------------------------------------------------------------
void walk_a_baby_parse::handle_top_level_expression()
{
   ACE_TRACE( "walk_a_baby_parse::handle_top_level_expression" );

   //evaluate a top-level expression into an anonymous function.
   if ( auto f = parse_top_level_expr() )
   {
        if ( auto *lf = f->codegen() )
        {
            std::cout << "parsed a top-level expr\n";
            lf->dump();
            walk_a_baby_driver::engine()->finalizeObject();
            //jit function, returning a function pointer.
            void *fptr = walk_a_baby_driver::engine()->getPointerToFunction( lf );

            //cast it to the right type (takes no arguments, returns a double) so we
            //can call it as a native function.
            double (*fp)() = (double (*)())(intptr_t)fptr;

            std::cout <<  "evaluated to " <<  fp() << "\n";
        }
   }
   else
   {
        //skip token for error recovery.
        next_token();
   }
}

//
//walk_a_baby_driver
walk_a_baby_driver::walk_a_baby_driver ()
{
    ACE_TRACE( "walk_a_baby_driver::walk_a_baby_driver ()" );
}

//------------------------------------------------------------------------
void walk_a_baby_driver::init_pipeline()
{
    m_ptr_module->setDataLayout( *m_ptr_exec->getDataLayout() );

    pass_mgr()->add( createBasicAliasAnalysisPass() );
    //simple "peephole" optimizations and bit-twiddling optzns.
    /*pass_mgr()->add( createInstructionCombiningPass() );
    //reassociate expressions.
    pass_mgr()->add( createReassociatePass() );
    //eliminate common subexpressions.
    pass_mgr()->add( createGVNPass() );
    //simplify the control flow graph (deleting unreachable blocks, etc).
    pass_mgr()->add( createCFGSimplificationPass() );

    pass_mgr()->doInitialization();*/

}

//------------------------------------------------------------------------
walk_a_baby_driver::~walk_a_baby_driver()
{
    ACE_Trace _( ACE_TEXT( "walk_a_baby_driver::~walk_a_baby_driver ()" ) , __LINE__ );
}

//------------------------------------------------------------------------
void walk_a_baby_driver::perform()
{
    ACE_Trace _( ACE_TEXT( "walk_a_baby_driver::perform ()" ) , __LINE__ );

    /// top ::= definition | external | expression | ';'


    while ( 1 )
    {
        if( parse()->lex()->stream()->eof() == true ) break;

        switch ( walk_a_baby_parse::current_lex_token  )
        {
            case (int) token_type::tok_eof :
                return;
            case ';': // ignore top-level semicolons.
            {
                parse()->next_token();
                break;
            }
            case (int) token_type::tok_func_def :
            {
                parse()->handle_definition();
                break;
            }
            case (int) token_type::tok_extern :
            {
                parse()->handle_extern();
                break;
            }
            default:
            {
                parse()-> handle_top_level_expression();
                break;
            }
        }
    }

}




