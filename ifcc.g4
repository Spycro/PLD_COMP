/*
 *    Not in the AST :
 *
 *    program (OK)
 *     └ declaration
 *        ├ program (OK)
 *        ├ function (OK)
 *        ├ variable (OK)
 *        └ array (OK)

 *    AST class diagram :
 *
 *    instruction (OK)
 *     ├ nullInstr (OK)
 *     ├ break (OK)
 *     ├ continue (OK)
 *     ├ return (OK)
 *     ├ block (OK)
 *     ├ controlStructure (OK)
 *     │  ├ whileInstr (OK)
 *     │  ├ doWhileInstr (OK)
 *     │  ├ ifInstr (OK)
 *     │  └ forInstr (OK)
 *     └ expression (OK)
 *        ├ affectation (OK)
 *        ├ unary
 *        ├ binary
 *        ├ ternary (OK)
 *        ├ const (OK)
 *        ├ variable (OK)
 *        ├ array (OK)
 *        └ functionCall
 */




grammar ifcc ;


axiom : prog ;




plusminus : '+' #returnPlus 
      | '-' #returnMinus;

///////////////////////////////////////////////////////////////////////////////
//    SYMBOLS                                                                //
///////////////////////////////////////////////////////////////////////////////

/*
 *    comments and spaces
 */
COMMENT : '/*' .*? '*/' -> skip ;
COMMENTLINE : '//' .*? '\n' -> skip ;
DIRECTIVE : '#' .*? '\n' -> skip ;
WS    : [ \t\r\n] -> channel(HIDDEN) ;


/*
 *    keywords
 */
TYPE : 'int' ; // TODO : add char
VOID : 'void' ;
BREAK : 'break' ;
CONTINUE : 'continue' ;
RETURN : 'return' ;
DO : 'do' ;
WHILE : 'while' ;
IF : 'if' ;
ELSE : 'else' ;
FOR : 'for' ;
MAIN : 'main' ;


/*
 *    names and numbers
 */
CONST : [0-9]+ ; // TODO : add chars ('a', '\0', '\n' ...)
NAME : [a-zA-Z_][a-zA-Z0-9_]* ;





///////////////////////////////////////////////////////////////////////////////
//    NOT IN THE AST                                                         //
///////////////////////////////////////////////////////////////////////////////

/*
 *    a program is a bunch of declarations (variables and functions),
 *    it may include the "main" function declaration
 */
prog : (variableDeclaration | functionDeclaration)* ; // TODO : add support for arrays


functionDeclaration : (TYPE|VOID) NAME '(' VOID? ')' block ; // TODO : add suport for parameters 


variableDeclaration : TYPE variableDeclarationList ;
variableDeclarationList : NAME ('[' expression ']')? ('=' expression)? (',' variableDeclarationList)? ;





///////////////////////////////////////////////////////////////////////////////
//    AST CLASS DIAGRAM                                                      //
///////////////////////////////////////////////////////////////////////////////

/*
 *    an instruction is either a simple single inscruction (ie. a line of code)
 *    or a block (ie. multiple lines of code enclosed by a {})
 *
 *    singleInstruction is introduced to avoid unhandled recursive definition
 *    of instruction and block
 */
singleInstruction
      : ';' #nullInstr
      | BREAK ';' #breakInstr
      | CONTINUE ';' #continueInstr
      | RETURN expression? ';' #returnInstr
      | controlStructure #controlStructure
      | expression ';' #expression
      ;


instruction : singleInstruction | block ;
block : '{' (singleInstruction|block)* '}' ; // = block : '{' instruction* '}' ;


controlStructure
      : WHILE '(' expression ')' instruction #whileInstr
      | DO instruction WHILE '(' expression ')' ';' #doWhileInstr
      | IF '(' expression ')' instruction (ELSE instruction)? #ifInstr
      | FOR '(' expression? ';' expression? ';' expression? ')' instruction #forInstr
      ;


expression
      : affectation #affectation
      | unary #unary
      | binary #binary
      | ternary #ternary
      | CONST #const
      | NAME ('[' expression ']')? #variable
      // TODO : add function call
      ;


affectation : NAME ('[' expression ']')? '=' expression ;


unary // TODO : complete this
      : '(' expression ')' #parenthesis
      | '-' expression #minus
      ;


binary // TODO : complete this
      : expression '*' expression #mult
      | expression '/' expression #div
      | expression '-' expression #minus
      | expression '+' expression #plus
      ;


ternary : expression '?' expression ':' expression ;
