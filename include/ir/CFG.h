#pragma once

#include "BasicBlock.h"
#include "../SymbolTable.h"
#include "../ast/Function.h"
#include "type/Void.h"
#include "type/Type.h"

#include <iostream>
#include <memory>
#include <string>

/** The class for the control flow graph, also includes the symbol table */

/* A few important comments:
	 The entry block is the one with the same label as the AST function name.
	   (it could be the first of bbs, or it could be defined by an attribute value)
	 The exit block is the one with both exit pointers equal to nullptr.
     (again it could be identified in a more explicit way)

 */
class CFG {
 public:
	CFG(Function* ast, std::string label_, VarType::Type* type, std::vector<SymbolTableElement> params_ = std::vector<SymbolTableElement>());
	CFG(shared_ptr<Node>  function);

	
	
	void add_bb(shared_ptr<BasicBlock> bb); 

	void incrementSpacer(int cnt);

	// x86 code generation: could be encapsulated in a processor class in a retargetable compiler
	void gen_asm(std::ostream& o);
	//std::string IR_reg_to_asm(std::string reg); /**< helper method: inputs a IR reg or input variable, returns e.g. "-24(%rbp)" for the proper value of 24 */	;

	std::string getLabel();


	// basic block management
	std::shared_ptr<BasicBlock> current_bb;

	

private :
	void gen_asm_prologue(std::ostream& o);
	void gen_asm_epilogue(std::ostream& o);
	std::shared_ptr<SymbolTableElement> inspectInstruction(shared_ptr<Node>);
 protected:	
	std::vector<shared_ptr<SymbolTableElement>> myParams;
	std::list <std::shared_ptr<BasicBlock>> bbs; /**< all the basic blocks of this CFG*/	

	int memorySpacer = 0; //Number of temp variables in the function
	Function* ast; /**< The AST this CFG comes from */
	std::string label; //TODO : a modifier!! -> Function
	VarType::Type* type; //TODO : a modifier!! -> Function
};