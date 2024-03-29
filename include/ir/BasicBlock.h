#pragma once 

#include "IRInstr.h"
#include "../ast/Scope.h"

#include <vector>
#include <string>
#include <iostream>
#include <memory>

class CFG;

// Declarations from the parser -- replace with your own
//#include "type.h"


/**  The class for a basic block */

/* A few important comments.
	 IRInstr has no jump instructions.
	 cmp_* instructions behaves as an arithmetic two-operand instruction (add or mult),
	  returning a boolean value (as an int)

	 Assembly jumps are generated as follows:
	 BasicBlock::gen_asm() first calls IRInstr::gen_asm() on all its instructions, and then 
		    if  exit_true  is a  nullptr, 
            the epilogue is generated
        else if exit_false is a nullptr, 
          an unconditional jmp to the exit_true branch is generated
				else (we have two successors, hence a branch)
          an instruction comparing the value of test_var_name to true is generated,
					followed by a conditional branch to the exit_false branch,
					followed by an unconditional branch to the exit_true branch
	 The attribute test_var_name itself is defined when converting 
  the if, while, etc of the AST  to IR.

Possible optimization:
     a cmp_* comparison instructions, if it is the last instruction of its block, 
       generates an actual assembly comparison 
       followed by a conditional jump to the exit_false branch
*/

class BasicBlock {
 public:
	BasicBlock(CFG* entry_cfg, std::shared_ptr<Scope> entry_scope, bool entre_needJmp = false, std::string entry_label="L"+std::to_string(nextBBnumber++));
	void gen_asm(std::ostream &o); /**< x86 assembly code generation for this basic block (very simple) */

	void add_IRInstr(shared_ptr<IRInstr> instruction);

	std::shared_ptr<Scope> getScope();

	const std::shared_ptr<BasicBlock> getExit_true();
	const std::shared_ptr<BasicBlock> getExit_false();
	const std::shared_ptr<BasicBlock> getExit_break();
	const std::shared_ptr<BasicBlock> getExit_continue();

	void setExit_true(std::shared_ptr<BasicBlock> exit_true);
	void setExit_false(std::shared_ptr<BasicBlock> exit_false);
	void setExit_break(std::shared_ptr<BasicBlock> exit_break);
	void setExit_continue(std::shared_ptr<BasicBlock> exit_continue);

	// No encapsulation whatsoever here. Feel free to do better.
	std::string label; /**< label of the BB, also will be the label in the generated code */
	CFG* cfg; /** < the CFG where this block belongs */
	std::vector<shared_ptr<IRInstr>> instrs; /** < the instructions themselves. */
 	std::string test_var_name;  /** < when generating IR code for an if(expr) or while(expr) etc,
													 store here the name of the variable that holds the value of expr */
 protected:
 	static int nextBBnumber; /**< just for naming */

	std::shared_ptr<Scope> scope;

	bool needJmp;
	
	std::shared_ptr<BasicBlock> exit_break = nullptr;//exit here if break happens
	std::shared_ptr<BasicBlock> exit_continue = nullptr;//exit here if continue happens

 	std::shared_ptr<BasicBlock> exit_true =nullptr;  /**< pointer to the next basic block, true branch. If nullptr, return from procedure */ 
	std::shared_ptr<BasicBlock> exit_false = nullptr; /**< pointer to the next basic block, false branch. If null_ptr, the basic block ends with an unconditional jump */

 
};
