//walk_a_baby_ast.cpp william k. johnson 2015
//
#include <walk_a_baby_parse.h>


using namespace walk_a_baby;
using namespace llvm;


//llvm intermediate representation generation from abstract syntax
//
//------------------------------------------------------------------------
llvm::Value *numeric_expr_ast::codegen()
{
      ACE_TRACE ( "\E[31mnumeric_expr_ast::codegen()\E[0m" );
      //floating point constant of arbitrary precision
      return ( ConstantFP::get( getGlobalContext() , APFloat( value() ) ) );
}

//------------------------------------------------------------------------
llvm::Value *variable_ast::codegen()

{

      ACE_TRACE( "\E[31mvariable_ast::codegen()\E[0m" );

      //look this variable up in the symbol table - which only contains function names
      llvm::Value* val = walk_a_baby_driver::symbols()->at( m_str_name );
      return val ? val : walk_a_baby_driver::error_v( "unknown variable name" );
}

//------------------------------------------------------------------------
llvm::Value *binary_ast::codegen()
{
      ACE_TRACE( "\E[31mbinary_ast::codegen()\E[0m" );

      Value *lhs = m_lhs_ptr->codegen();
      Value *rhs = m_rhs_ptr->codegen();

      if ( lhs == 0 || rhs == 0) return 0;

      switch ( bin_op() )
      {
          case '+': return walk_a_baby_driver::ir_builder()->CreateFAdd( lhs , rhs , "addtmp" );
          case '-': return walk_a_baby_driver::ir_builder()->CreateFSub( lhs , rhs , "subtmp" );
          case '*': return walk_a_baby_driver::ir_builder()->CreateFMul( lhs , rhs , "multmp" );
          case '<':
          {
            lhs = walk_a_baby_driver::ir_builder()->CreateFCmpULT( lhs , rhs , "cmptmp" );
            // Convert bool 0/1 to double 0.0 or 1.0
            return walk_a_baby_driver::ir_builder()->CreateUIToFP( lhs ,
                                                                   Type::getDoubleTy( getGlobalContext() ) ,
                                                                   "booltmp" );
          }
          default: break;
      }

      //if it wasn't a builtin binary operator, it must be a user defined one. emit
      //a call to it.
      Function* func  = walk_a_baby_driver::module()->getFunction( std::string( "binary" ) + bin_op() );
      assert( func && "binary operator not found!" );

      Value* ops[2] { lhs , rhs };

      return ( walk_a_baby_driver::ir_builder()->CreateCall( func , ops , "binop" ) );
}

//------------------------------------------------------------------------
llvm::Function* prototype_ast::codegen()
{
    ACE_TRACE( "\E[31mprototype_ast::codegen()\E[0m" );

    //make the function type:  double(double,double) etc.
    std::vector<Type*> doubles( m_v_args.size() ,
                             Type::getDoubleTy( getGlobalContext() ) );
    FunctionType *ft = FunctionType::get( Type::getDoubleTy( getGlobalContext() ) ,
     	                                                             doubles ,
                                                                     false );

    Function *f = Function::Create( ft ,
                                    Function::ExternalLinkage ,
                                    name() ,
                                    walk_a_baby_driver::module() );


    //set names for all arguments.
    unsigned idx = 0;
    for ( Function::arg_iterator ai = f->arg_begin(); idx != m_v_args.size();
             ++ai , ++idx)
    {
        ai->setName( m_v_args[idx] );
        //add arguments to variable symbol table.
        //walk_a_baby_driver::symbols()->at( m_v_args[idx] ) = ai;
        walk_a_baby_driver::symbols()->insert( std::make_pair( m_v_args[idx] , ai ) );

    }

    return ( f );
}

//------------------------------------------------------------------------
llvm::Function* function_ast::codegen()
{
      ACE_TRACE( "\E[31mfunction_ast::codegen()\E[0m" );

      walk_a_baby_driver::symbols()->clear();

      Function* func = m_ptr_decl->codegen();
      if ( func == 0 ) { return ( 0 ); }

      //create a new basic block to start insertion into.
      BasicBlock *bb = BasicBlock::Create( getGlobalContext() , "entry", func );
      walk_a_baby_driver::ir_builder()->SetInsertPoint( bb  );

      if ( Value *ret_val = m_ptr_body->codegen() )
      {
          //finish off the function.
          walk_a_baby_driver::ir_builder()->CreateRet( ret_val );
          //validate the generated code, checking for consistency.
          verifyFunction( *func );
          //run optimizing passes in place here
          walk_a_baby_driver::pass_mgr()->run( *func );

          return func;
      }

      //error reading body, remove function.
      func->eraseFromParent();

      return ( 0 );
}

//------------------------------------------------------------------------
llvm::Value*  call_expr_ast::codegen()
{
       ACE_TRACE( "\E[31mcall_expr_ast::codegen()\E[0m" );

       //symbol table lookup
       Function* callee_f  = walk_a_baby_driver::module()->getFunction( callee() );

       if ( callee_f == 0 )
       { return walk_a_baby_driver::error_v( "unknown function referenced" ); }

       //if argument mismatch error
       if ( callee_f->arg_size() != m_v_args.size() )
       { return walk_a_baby_driver::error_v( "incorrect # arguments passed" ); }

       std::vector<Value*> args_v;
       for ( unsigned i = 0, e = m_v_args.size(); i != e; ++i )
       {
           args_v.push_back( m_v_args[i]->codegen() );
           if ( args_v.back() == 0 )
           { return 0; }
       }

       return walk_a_baby_driver::ir_builder()->CreateCall( callee_f , args_v , "calltmp" );
}

//------------------------------------------------------------------------
llvm::Value* if_expr_ast::codegen()
{

      ACE_TRACE( "\E[31mif_expr_ast::codegen()\E[0m" );

      Value* cond_v = m_ptr_cond->codegen();
      if ( cond_v == 0 ) { return ( 0 ); }

      //convert condition to a bool by comparing equal to 0.0.
      cond_v = walk_a_baby_driver::ir_builder()->CreateFCmpONE( cond_v ,
                                                                ConstantFP::get( getGlobalContext() ,
                                                                APFloat( 0.0 ) ) ,
                                                                "ifcond" );

      Function* func = walk_a_baby_driver::ir_builder()->GetInsertBlock()->getParent();

      //create blocks for the then and else cases.insert the 'then' block at the
      //end of the function.
      BasicBlock* then_bb = BasicBlock::Create(getGlobalContext(), "then", func );
      BasicBlock* else_bb  = BasicBlock::Create(getGlobalContext(), "else");
      BasicBlock* merge_bb = BasicBlock::Create(getGlobalContext(), "ifcont");

      walk_a_baby_driver::ir_builder()->CreateCondBr( cond_v , then_bb , else_bb );

      //emit then value.
      walk_a_baby_driver::ir_builder()->SetInsertPoint( then_bb );

      Value* then_v = m_ptr_then->codegen();
      if ( then_v == 0 ) { return ( 0 ); }

      walk_a_baby_driver::ir_builder()->CreateBr( merge_bb );
      //cdegen of 'then' can change the current block, update then_bb for the phi..
      then_bb =  walk_a_baby_driver::ir_builder()->GetInsertBlock();

      //emit else block.
      func->getBasicBlockList().push_back( else_bb );
      walk_a_baby_driver::ir_builder()->SetInsertPoint( else_bb );

      Value* else_v = m_ptr_else->codegen();
      if ( else_v == 0 ) { return ( 0 ); }

       walk_a_baby_driver::ir_builder()->CreateBr( merge_bb );
       //codegen of 'else' can change the current block, update else_bb for the phi.
       else_bb =  walk_a_baby_driver::ir_builder()->GetInsertBlock();

       //emit merge block.
       func->getBasicBlockList().push_back( merge_bb );
       walk_a_baby_driver::ir_builder()->SetInsertPoint( merge_bb );
       PHINode *pn = walk_a_baby_driver::ir_builder()->CreatePHI
                                (
                                      Type::getDoubleTy( getGlobalContext()) ,
                                      2 ,
                                      "iftmp"
                                );
       pn->addIncoming( then_v , then_bb );
       pn->addIncoming( else_v , else_bb );

       return ( pn );
}

//------------------------------------------------------------------------
llvm::Value*  for_expr_ast::codegen()
{
        //emit the start code first, without 'variable' in scope.
        Value* start_val = m_ptr_start->codegen();
        if ( start_val == 0 ) { return ( 0 ); }

        //make the new basic block for the loop header, inserting after current
        // block
        Function* func = walk_a_baby_driver::ir_builder()->GetInsertBlock()->getParent();
        BasicBlock* preheader_bb = walk_a_baby_driver::ir_builder()->GetInsertBlock();
        BasicBlock* loop_bb = BasicBlock::Create(getGlobalContext() , "loop" , func );

        //insert an explicit fall through from the current block to the LoopBB.
        walk_a_baby_driver::ir_builder()->CreateBr( loop_bb );

        //start insertion in LoopBB.
        walk_a_baby_driver::ir_builder()->SetInsertPoint( loop_bb );

        //start the PHI node with an entry for start.
            PHINode* variable = walk_a_baby_driver::ir_builder()->CreatePHI( Type::getDoubleTy( getGlobalContext() ) ,
                                                                         2 ,
                                                                         m_str_var.c_str() );
        variable->addIncoming( start_val , preheader_bb );

        //Within the loop, the variable is defined equal to the phi node.  If it
        //shadows an existing variable, we have to restore it, so save it now.
        Value* old_val = nullptr;
        auto iter = walk_a_baby_driver::symbols()->find( m_str_var );
        if( iter != walk_a_baby_driver::symbols()->end() )
        {
            old_val = iter->second;
            iter->second = variable;
        }
        else
        {
            walk_a_baby_driver::symbols()->insert( std::make_pair( m_str_var , variable ) );
        }

        //emit the body of the loop.  this, like any other expr, can change the
        //current bb.  Note that we ignore the value computed by the body, but don't
        //allow an error.
        if ( m_ptr_body->codegen() == 0 ) { return ( 0 ); }

        //emit the step value.
        Value* step_val;
        if ( m_ptr_step)
        {
            step_val = m_ptr_step->codegen();
            if ( step_val == 0 ) { return ( 0 ); }
        }
        //if not specified, use 1.0.
        else { step_val = ConstantFP::get( getGlobalContext() , APFloat( 1.0 ) ); }

        Value* next_var =  walk_a_baby_driver::ir_builder()->CreateFAdd( variable , step_val , "nextvar" );

        //compute the end condition.
        Value* end_cond = m_ptr_end->codegen();
        if ( end_cond == 0 ) { return ( end_cond ); }

        //convert condition to a bool by comparing equal to 0.0.
        end_cond =  walk_a_baby_driver::ir_builder()->CreateFCmpONE( end_cond ,
                                                                     ConstantFP::get( getGlobalContext() ,
                                                                     APFloat( 0.0 ) ) ,
                                                                     "loopcond" );

        //create the "after loop" block and insert it.
        BasicBlock* loop_end_bb = walk_a_baby_driver::ir_builder()->GetInsertBlock();
        BasicBlock* after_bb = BasicBlock::Create( getGlobalContext() , "afterloop" , func );

        //insert the conditional branch into the end of LoopEndBB.
        walk_a_baby_driver::ir_builder()->CreateCondBr( end_cond , loop_bb , after_bb );

        //any new code will be inserted in AfterBB.
        walk_a_baby_driver::ir_builder()->SetInsertPoint( after_bb );

        //add a new entry to the PHI node for the backedge.
        variable->addIncoming( next_var , loop_end_bb );

        //restore the unshadowed variable.
        if ( old_val ) { iter->second = old_val; }
        else { walk_a_baby_driver::symbols()->erase( iter ); }

        //for expr always returns 0.0.
        return Constant::getNullValue( Type::getDoubleTy( getGlobalContext() ) );

}

//------------------------------------------------------------------------
llvm::Value* unary_expr_ast::codegen()
{
        return ( nullptr );
}

