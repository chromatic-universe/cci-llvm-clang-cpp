//walk_a_baby optimization pass   william k. johnson 2015


#include "llvm/Pass.h"
#include "llvm/IR/Function.h"
#include "llvm/Support/raw_ostream.h"

using namespace llvm;

//everything lives here
namespace
{
    namespace
    {
        struct walk_a_baby_pass : public FunctionPass
        {
            static char ID;

            //ctor
            walk_a_baby_pass() : FunctionPass( ID )
            {}


            bool runOnFunction( Function &func ) override
            {
                errs() << "walk-a-baby --- ";
                errs() << func.getName() << ": ";
                errs() << func.getArgumentList().size() << "\n";

                return false;
            }
        };
    }

    char walk_a_baby_pass::ID = 0;
    static RegisterPass<walk_a_baby_pass> X( "walkababypass" ,
                                             "walk a baby pass" ,
                                             false ,
                                             false );
}

