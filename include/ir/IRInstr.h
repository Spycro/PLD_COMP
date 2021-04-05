#pragma once

#include <vector>
#include <string>
#include <iostream>
#include <initializer_list>
#include "../type/Type.h"
#include "SymbolTable.h"

class BasicBlock;

//! The class for one 3-address instruction
class IRInstr {
 
   public:

	/**  constructor */
	IRInstr(BasicBlock* bb_);
	
	/** Actual code generation */
	virtual void gen_asm(std::ostream &o) = 0; /**< x86 assembly code generation for this IR instruction */
	
 protected:
	std::string asmAdaptInstruction(std::string instr, SymbolTableElement* el1, SymbolTableElement* el2, SymbolTableElement* el3);
	BasicBlock* bb; /**< The BB this instruction belongs to, which provides a pointer to the CFG this instruction belong to */
};

