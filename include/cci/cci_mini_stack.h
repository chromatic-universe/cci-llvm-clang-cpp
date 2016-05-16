//cci_mini_stack.h william k. johhnson 2015
#pragma once

#include "cci.h"

//definition
#define T cci_mini_stack_t
typedef struct T *T;

//top returns top obj but does remove it
//pop removes tob obj but does return it

//cci interface 'namespace'

//cci_mini_stack
extern T        cci_mini_stack_new( void );
extern int      cci_mini_stack_empty( T stk );
extern void     cci_mini_stack_push( T stk , void* x );
extern void*    cci_mini_stack_top( T stk );
extern void     cci_mini_stack_pop( T stk );
extern void     cci_mini_stack_free( T *stk );


#undef T

