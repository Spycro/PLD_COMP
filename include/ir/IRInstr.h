#pragma once

#include <vector>
#include <string>
#include <iostream>
#include <initializer_list>
#include "../type/Type.h"

class BasicBlock;

//! The class for one 3-address instruction
class IRInstr {
 
   public:

	/**  constructor */
	IRInstr(BasicBlock* bb, Type* t);
	
	/** Actual code generation */
	virtual void gen_asm(std::ostream &o) = 0; /**< x86 assembly code generation for this IR instruction */
	
 private:
	BasicBlock* bb; /**< The BB this instruction belongs to, which provides a pointer to the CFG this instruction belong to */
	Type* t; //PTDR T QUI
};

