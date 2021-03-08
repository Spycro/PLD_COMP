// Copied from a file generated from ifcc.g4 by ANTLR 4.7.2


#include "visitor.h"



antlrcpp::Any Visitor::visitAxiom(ifccParser::AxiomContext *ctx) {
	return visitChildren(ctx);
}
antlrcpp::Any Visitor::visitProg(ifccParser::ProgContext *ctx){
	//The start of the program, basic stuff. No need to explain
	std::cout<<".globl	main\n"
			" main: \n"
			"#prologue\n"
			"	pushq %rbp #save rbp on stack\n"
			"	movq %rsp, %rbp #define rbp for current function\n"
			"#body\n";

	//Visit all the lines that the user may have written
	for(auto line : ctx->line()){
		visit(line);
	}


	//the return part of the function
	std::string retval = visit(ctx->expression()); //get the expression that we are returning
	std::cout<<" 	movl	"<<retval<<", %eax\n" //move it where it has to be

			"#epiligue\n" // ehm the epilogue, not explainion needed
			"	popq %rbp #restore rbp from stack\n"
			" 	ret\n";


	// show remaining warnings detected
	for(auto varName:symbolsNotUsed){
		std::cerr<< varName<<" not used, please remove\n";//explains itself
	}
	return 0;
}

antlrcpp::Any Visitor::visitLine(ifccParser::LineContext *ctx){
	return visitChildren(ctx);//Here the children will either be a declaration or an affection
}

antlrcpp::Any Visitor::visitDeclaration(ifccParser::DeclarationContext *ctx) {
	//Start to read the declaration list for this "TYPE", always in INT in this case
	//The corresponding declaration list will be a list of children that are either simple or assign Declarations
	//The meaning of these two types are explained in the .h, will not repeat myself
	visitChildren(ctx);
	return 0;
}

antlrcpp::Any Visitor::visitSimpleDeclaration(ifccParser::SimpleDeclarationContext *ctx){
	std::string variableName = ctx->VARIABLE_NAME()->getText(); //Get the variable name
	addVariable(variableName); //add it using private function, see private function if you do not understand
	visitChildren(ctx); //Go to next declaration in list if exists
	return 0;
}
antlrcpp::Any Visitor::visitAssignDeclaration(ifccParser::AssignDeclarationContext *ctx){
	std::string variableName = ctx->VARIABLE_NAME()->getText(); //get variable name
	std::string position  = addVariable(variableName); //add it to symbols
	std::string variableContents = visit(ctx->expression()); //get expression result to fill variable with	
	std::cout<<"	movl	"<<variableContents<<", %eax#"<<variableName<<"\n"; //assembly code, self explanatory
	std::cout<<"	movl	%eax, "<<position<<"#"<<variableName<<"\n";
	visitChildren(ctx);//Go to next declaration in list if exists
	return 0;
}

antlrcpp::Any Visitor::visitAffectation(ifccParser::AffectationContext *ctx) {
	std::string variableName = ctx->VARIABLE_NAME()->getText(); //get variable name to be filled
	std::string variablePosition = getVariable(variableName); //get its position
	std::string expressionResultPosition = visit(ctx->expression());//Get the position of the result of the expression

	std::cout<<"	movl	"<<expressionResultPosition<<", %eax\n";
	std::cout<<"	movl	%eax, "<<variablePosition<<"\n";
	return (std::string) variablePosition;
}

antlrcpp::Any Visitor::visitPreIncrement(ifccParser::PreIncrementContext *ctx) {
	std::string variableName = ctx->VARIABLE_NAME()->getText(); //get variable name to be filled
	symbolsNotUsed.erase(variableName);//Show that this variable has been used on the right side of an affectation
	std::string variablePosition = getVariable(variableName); //get its position

	std::cout<<"	movl	$1, %eax\n";
	std::cout<<"	addl	"<<variablePosition<<", %eax\n";
	std::cout<<"	movl	%eax, " << variablePosition<<"\n"; // we add one, what did you expect
	return (std::string) variablePosition;
}
antlrcpp::Any Visitor::visitPostIncrement(ifccParser::PostIncrementContext *ctx) {
	std::string variableName = ctx->VARIABLE_NAME()->getText(); //get variable name to be filled
	symbolsNotUsed.erase(variableName);//Show that this variable has been used on the right side of an affectation
	std::string variablePosition = getVariable(variableName); //get its position

	std::string copyPosition = addVariable();
	std::cout<<"	movl	"<<variablePosition<<", %eax\n"; //we create a copy
	std::cout<<"	movl	%eax, "<<copyPosition<<"\n";

	std::cout<<"	movl	$1, %eax\n";
	std::cout<<"	addl	"<<variablePosition<<", %eax\n"; 
	std::cout<<"	movl	%eax, " << variablePosition<<"\n"; //we add one, again...
	return (std::string) copyPosition;
}
antlrcpp::Any Visitor::visitPostDecrement(ifccParser::PostDecrementContext *ctx) {
	std::string variableName = ctx->VARIABLE_NAME()->getText(); //get variable name to be filled
	symbolsNotUsed.erase(variableName);//Show that this variable has been used on the right side of an affectation
	std::string variablePosition = getVariable(variableName); //get its position

	std::string copyPosition = addVariable();
	std::cout<<"	movl	"<<variablePosition<<", %eax\n"; //copy again, you need a bigger screen. look up
	std::cout<<"	movl	%eax, "<<copyPosition<<"\n";

	std::cout<<"	movl	"<<variablePosition<<", %eax\n";
	std::cout<<"	subl	$1, %eax\n";
	std::cout<<"	movl	%eax, " << variablePosition<<"\n"; // look up
	return (std::string) copyPosition;
}
antlrcpp::Any Visitor::visitPreDecrement(ifccParser::PreDecrementContext *ctx) {
	std::string variableName = ctx->VARIABLE_NAME()->getText(); //get variable name to be filled
	symbolsNotUsed.erase(variableName);//Show that this variable has been used on the right side of an affectation
	std::string variablePosition = getVariable(variableName); //get its position

	std::cout<<"	movl	"<<variablePosition<<", %eax\n";
	std::cout<<"	subl	$1, %eax\n";
	std::cout<<"	movl	%eax, " << variablePosition<<"\n"; //we add one
	return (std::string) variablePosition;
}


antlrcpp::Any Visitor::visitConst(ifccParser::ConstContext *ctx){
	return (std::string) ("$" + ctx->CONST()->getText()); //Get const, You really don't need an explanation here
}
antlrcpp::Any Visitor::visitVariable(ifccParser::VariableContext *ctx){
	std::string varName = ctx->VARIABLE_NAME()->getText(); //Get variable name
	symbolsNotUsed.erase(varName);//Show that this variable has been used on the right side of an affectation
	return getVariable(varName);//return position of variable
}

antlrcpp::Any Visitor::visitMult(ifccParser::MultContext *ctx){
	//in simple terms, gets both results from left and right part, 
	//assigns one to a registry then moves result to a temp variable. The temp variable position is then returned
	std::string left = visit(ctx->expression(0));
	std::string right = visit(ctx->expression(1));

	std::cout<<"	movl	"<<right<<", %eax\n";
	std::cout<<"	imul	"<<left<<", %eax\n";
	std::string result = addVariable();
	std::cout<<"	movl	%eax, " << result<<"\n";

	return result;
}
antlrcpp::Any Visitor::visitDiv(ifccParser::DivContext *ctx){
	//Clear edx and then assign left result to eax. This is because idiv takes a 64bit operator
	//assign right to ebx. Idiv cannot take consts.
	//Then perform mult, idiv will auto take edx,eax and one of the operators
	//For the rest, view mult
	std::string left = visit(ctx->expression(0));
	std::string right = visit(ctx->expression(1));

	std::cout<<"	movl	"<<left<<", %eax\n";
	std::cout<<"	movl	$0, %edx\n";
	std::cout<<"	movl	"<<right<<", %ebx\n";
	std::cout<<"	idiv	%ebx\n";
	std::string result = addVariable();
	std::cout<<"	movl	%eax, " << result<<"\n";

	return result;
}
antlrcpp::Any Visitor::visitAdd(ifccParser::AddContext *ctx){
	//view mult, only one instruction has changed so it should not be hard
	std::string left = visit(ctx->expression(0));
	std::string right = visit(ctx->expression(1));

	std::cout<<"	movl	"<<right<<", %eax\n";
	std::cout<<"	addl	"<<left<<", %eax\n";
	std::string result = addVariable();
	std::cout<<"	movl	%eax, " << result<<"\n";

	return result;
}
antlrcpp::Any Visitor::visitSub(ifccParser::SubContext *ctx){
	//view mult, only one instruction has changed so it should not be hard
	std::string left = visit(ctx->expression(0));
	std::string right = visit(ctx->expression(1));

	std::cout<<"	movl	"<<left<<", %eax\n";
	std::cout<<"	subl	"<<right<<", %eax\n";
	std::string result = addVariable();
	std::cout<<"	movl	%eax, " << result<<"\n";

	return result;
}

antlrcpp::Any Visitor::visitMinus(ifccParser::MinusContext *ctx){
	//get value of expression and negate it. (0-expression obviously)
	std::string expr = visit(ctx->expression());

	std::cout<<"	movl	$0, %eax\n";
	std::cout<<"	subl	"<<expr<<", %eax\n";
	std::string result = addVariable();
	std::cout<<"	movl	%eax, " << result<<"\n";
	return result;
}
antlrcpp::Any Visitor::visitExpressionValue(ifccParser::ExpressionValueContext *ctx){
	return (visit(ctx->value()));//get value of expression, see visitConst and visitVariable
}
antlrcpp::Any Visitor::visitPar(ifccParser::ParContext *ctx){
	return (visit(ctx->expression()));//Return expression
}
antlrcpp::Any Visitor::visitAffectationValue(ifccParser::AffectationValueContext *ctx) {
	return (visit(ctx->affectationall()));//return variable that was just affected
}


//Here come the private functions

std::string Visitor::addVariable(){ //used for the addition of temp variables
	return this->addVariable("temp" + std::to_string((--stackPointer)*8), true);
}
std::string Visitor::addVariable(std::string name, bool temp){//used for the addition of normal variables
	auto symbol  = symbols.find(name);
	std::string placement;
	if(symbol == symbols.end()){ //See if variable has already been declared
		int position  = (--stackPointer)*8;//if it has not, then create is obviously
		placement = std::to_string(position) + "(%rbp)";
		symbols.emplace(name,placement);
		if(!temp){
			symbolsNotUsed.emplace(name);
		}
	}else{//if it has, shout at the user
		std::cerr<< name<<" Declared more than once, please remove\n";
		throw "Declared more than once, please remove";
		placement = symbol->second;
	}
	return placement;//return the position of the variable
}
std::string Visitor::getVariable(std::string name){//Get an existing variable from the stack
	auto symbol = symbols.find(name);
	if(symbol != symbols.end()){
		return symbol->second; // return its position if it exists
	}
	std::cerr<<"(!!!ERROR VARIABLE NOT FOUND: " << name << "!!!)\n"; // If it does not, shout at the user a lot. Cause this is serious
	throw "ERROR VARIABLE NOT FOUND";
	return (std::string) "NotFound";
}