//walk_a_baby_parse.h william k. johnson 2015

#pragma once

#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wunused-variable"
#pragma GCC diagnostic ignored "-Wunused-function"
#pragma GCC diagnostic ignored "-Wunused-private-field"
#pragma GCC diagnostic ignored "-Wswitch"


//llvm
#include "llvm/ADT/STLExtras.h"
#include "llvm/Analysis/Passes.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/ExecutionEngine/ExecutionEngine.h"
#include "llvm/ExecutionEngine/MCJIT.h"
#include "llvm/ExecutionEngine/SectionMemoryManager.h"
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Verifier.h"
#include "llvm/Support/TargetSelect.h"
#include "llvm/Transforms/Scalar.h"
//c++ standard
#include <cctype>
#include <cstdio>
#include <memory>
#include <string>
#include <vector>
#include <utility>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <map>
#include <set>
#include <walk_a_baby_lex.h>
#include <walk_a_baby_ast.h>

//adaptive coummnication environment
#include <ace/Log_Msg.h>
#include <ace/Trace.h>

//c runtime for rand
#include <ctime>
#include <cstdlib>

extern "C"
{
    double printd(double X);
}


namespace walk_a_baby
{

        //forward declarations
        class walk_a_baby_parse;
        class walk_a_baby_driver;
        class mc_jit_assist;

        //aliases
        using   v_str = std::vector<std::string> ;
        using   v_str_ptr = v_str*;
        using   walk_a_baby_parse_ptr = walk_a_baby_parse*;
        using   module_ptr = llvm::Module*;
        using   ir_builder_ptr = llvm::IRBuilder<>*;
        using   symbol_table = std::map<std::string, llvm::Value*>;
        using   symbol_table_ptr = symbol_table*;
        using   pass_mgr_ptr = llvm::legacy::FunctionPassManager*;
        using   driver_ptr = walk_a_baby_driver*;
        using   module_vector = std::vector<module_ptr>;
        using   exec_engine_ptr = llvm::ExecutionEngine*;
        using   engine_vector = std::vector<exec_engine_ptr>;
        using   mc_jit_assist_ptr = mc_jit_assist*;
        using   void_ptr = void*;
        using   function_ptr = llvm::Function*;

        //generic helpers
        //string helpers , we use generic decltype to
        //bypass string  - const char* brain damage
        template<class T>
        auto generate_unique_name( T root ) -> decltype( std::forward<T> ( root ) )
        {
            T uq;
            static int i = 0;
            std::ostringstream ostr;
            ostr << root << i++ << std::endl;

            uq = ostr.str();

            return std::forward<T> ( uq );
        }

        template<class T>
        auto make_legal_function_name( T name ) -> decltype( std::forward<T> ( name ) )
        {
            T uq;
            std::string legal_elements { "_abcdefghijklmnopqrstuvwxyz \
                                          ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789" };

            if ( name.empty() )
            {
               return std::forward<T> ( generate_unique_name<std::string> ( "anon_func_" ) );
            }

            std::string  nm = name;
            //look for a numeric first character
            if ( nm.find_first_of( "0123456789" ) == 0 )
            {
                nm.insert( 0 , 1 , 'n' );
            }

        }


        //just in time
        class mc_jit_assist
        {
            public :

                //ctor
                mc_jit_assist( llvm::LLVMContext&  c );

                //dtor
                ~mc_jit_assist();

            private :

                //attributes
                llvm::LLVMContext& m_context;
                module_ptr m_open_module;
                module_vector m_modules;
                engine_vector m_engines;

            public :

                //services
                function_ptr get_function( const std::string fn_name );
                module_ptr get_module_for_new_function();
                void_ptr get_pointer_to_function( function_ptr f );
                void_ptr get_symbol_address( const std::string &name );
                void dump();
        };

        class helping_memory_manager : public llvm::SectionMemoryManager
        {

           public:

                //ctor
                helping_memory_manager( mc_jit_assist_ptr helper ) : m_jit( helper )
                {}
                //dtor
                ~helping_memory_manager() override
                {}

                //this method returns the address of the specified symbol.
                //our implementation will attempt to find symbols in other
                //modules associated with the mc_jit to cross link symbols
                //from one generated module to another.
                uint64_t getSymbolAddress(const std::string &Name) override;

           private :

                //no copy
                helping_memory_manager( const helping_memory_manager& hmm ) = delete;
                //no assign
                void operator= ( const helping_memory_manager& hmm ) = delete;

                //attributes
                 mc_jit_assist_ptr m_jit;

            public :

                //
        };

        //parser
        class walk_a_baby_parse
        {

            public :

                //ctors
                explicit walk_a_baby_parse();

                //dtor
                virtual ~walk_a_baby_parse();


           protected :

                //attributes
                static std::unique_ptr<walk_a_baby_lex> m_ptr_lex;
                static driver_ptr m_ptr_parent;

                ///binopPrecedence - this holds the precedence for each
                ///binary operator that is defined.
                static std::map<char, int> bin_op_precedence;
                static std::map<std::string, std::unique_ptr<prototype_ast>> function_protos;

                //helpers


            private :

                //no assign
                const walk_a_baby_parse& operator= ( const walk_a_baby_parse& wabl );
                //copy
                walk_a_baby_parse( const walk_a_baby_parse& wapb );

                //attributes

            public :

                //accessors-inspectors
                static walk_a_baby_lex_ptr lex() { return ( m_ptr_lex.get() );  }

                //mutators
                static void driver( driver_ptr ptr ) { m_ptr_parent = ptr; }

                //services
                static int next_token();
                static expr_ast_ptr parse_expression();
                static expr_ast_ptr parse_paren_expr();
                static expr_ast_ptr parse_identifier_expr();
                static expr_ast_ptr parse_primary();
                static expr_ast_ptr parse_numeric_expr();
                static expr_ast_ptr parse_bin_op_rhs( int expr_prec ,
                                                      expr_ast_ptr lhs );
                static function_ast_ptr parse_definition();
                static prototype_ast_ptr parse_prototype();
                static prototype_ast_ptr parse_extern();
                static function_ast_ptr parse_top_level_expr();
                static expr_ast_ptr parse_if_expr();
                static expr_ast_ptr parse_for_expr();
                static expr_ast_ptr parse_unary_expr();

                void handle_definition();
                void handle_extern();
                void handle_top_level_expression();

                static int get_tok_precedence();

                //immutable
                static int current_lex_token;

        };

        //driver
        class walk_a_baby_driver
        {

            friend std::ostream& operator << ( std::ostream& ostr , const walk_a_baby_driver& wabd  )
                          { return ( ostr << "todo=walk-a-baby-driver" ); }

            public :

                  //ctor
                  walk_a_baby_driver();

                  //dtor
                  virtual ~walk_a_baby_driver();

            protected :

                 //

            private :

                //attributes , initialization order here is significant
                static std::unique_ptr<v_str> m_v_filenames;
                static std::unique_ptr<walk_a_baby_parse> m_baby_parse;
                static std::unique_ptr<symbol_table> m_symbol_table;
                static module_ptr m_ptr_module;
                static std::unique_ptr<llvm::IRBuilder<>> m_ir_builder;
                static pass_mgr_ptr m_pass_mgr;
                static mc_jit_assist_ptr m_ptr_jit;

                //no copy
                walk_a_baby_driver( const walk_a_baby_driver& wabd );
                //no assign
                const walk_a_baby_driver& operator= ( const walk_a_baby_driver& wabd );

            public :

                //accessors-inspectors
                v_str_ptr file_name() const noexcept { return ( m_v_filenames.get() ); }
                static walk_a_baby_parse_ptr parse() { return ( m_baby_parse.get() ); }
                static module_ptr module() { return ( std::move( m_ptr_module ) ); }
                static ir_builder_ptr ir_builder() { return ( m_ir_builder.get() ); }
                static symbol_table_ptr symbols() { return ( m_symbol_table.get() ); }
                static pass_mgr_ptr pass_mgr() { return ( m_pass_mgr ); }
                static mc_jit_assist_ptr jit() { return ( m_ptr_jit ); }

                //mutators
                void file_name( const v_str sources ) { *file_name() = sources;  }
                static void module( module_ptr ptr ) {  ptr = std::move( m_ptr_module ); }
                static void pass_mgr( pass_mgr_ptr ptr ) { m_pass_mgr = ptr; }
                static void jit( mc_jit_assist_ptr jit_ptr ) { m_ptr_jit = jit_ptr; }

                //helpers
                static llvm::Value* error_v( const std::string& str ) { std::cerr << str << "\n"; return ( 0 ); }
                static void init_pipeline();

                //services
                static void perform();


        };
}

