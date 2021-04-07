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
 *        ├ unary (OK)
 *        ├ binary (OK)
 *        ├ ternary (OK)
 *        ├ const (OK)
 *        ├ variable (OK)
 *        ├ array (OK)
 *        └ functionCall (OK)
 */




grammar ifcc ;


axiom : prog ;





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
type : 'int'|'char';
VOID : 'void' ;
BREAK : 'break' ;
CONTINUE : 'continue' ;
RETURN : 'return' ;
DO : 'do' ;
WHILE : 'while' ;
IF : 'if' ;
ELSE : 'else' ;
FOR : 'for' ;
SWITCH : 'switch' ;
MAIN : 'main' ;
SIZEOF : 'sizeof' ;
LT: '<';
LTE: '<=';
GT: '>';
GTE: '>=';
EQUAL: '==';
NOTEQUAL: '!=';
/*
 *    names and numbers
 */
CONST : [0-9]+ ; // TODO : add chars ('a', '\0', '\n' ...), add type modifier
NAME : [a-zA-Z_][a-zA-Z0-9_]* ;
varName : NAME ('[' expression ']')? ;
functionCall 
      : 'putchar(' expression ')' #putchar
      | 'getchar(' ')' #getchar
      | NAME '(' (expression (',' expression)*)? ')' #functionCalling
      ;






///////////////////////////////////////////////////////////////////////////////
//    NOT IN THE AST                                                         //
///////////////////////////////////////////////////////////////////////////////

/*
 *    a program is a bunch of declarations (variables and functions),
 *    it may include the "main" function declaration
 */
prog : (variableDeclaration ';' | functionDeclaration)* ;


functionDeclaration // TODO : add suport for parameters
      : 'int' MAIN '(' VOID? ')' block #mainFunction
      | (type|VOID) NAME '(' (VOID?| functionParametersDeclaration ) ')' block #anyFunction 
      ;
functionParametersDeclaration : type NAME (',' type NAME)* ;

variableDeclaration : type variableDeclarationList ;
variableDeclarationList : varName ('=' expression)? (',' variableDeclarationList)? ;





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
      | variableDeclaration ';' #varDecl
      | controlStructure #controlStruct
      | expression ';' #expr
      ;


instruction : singleInstruction | block ;
block : '{' (singleInstruction|block)* '}' ; // = block : '{' instruction* '}' ;


controlStructure
      : WHILE '(' expression ')' instruction #whileInstr
      | DO instruction WHILE '(' expression ')' ';' #doWhileInstr
      | IF '(' expression ')' instruction (ELSE instruction)? #ifInstr
      | FOR '(' expression ';' expression ';' expression ')' instruction #forInstr // TODO : add support for expression?
      // TODO : add switch
      ;


expression 
      : CONST #const
      | varName #variable
      | functionCall #functCall
      | '(' expression ')' #parenthesis
      // https://en.wikipedia.org/wiki/Operators_in_C_and_C%2B%2B
      | varName '++' #postIncr
      | varName '--' #postDecr
      | '++' varName #preIncr
      | '--' varName #preDecr
      | '-' expression #unaryMinus
      | '+' expression #unaryPlus
      | ('!'|'not') expression #logicalNot
      | ('~'|'compl') expression #bitwiseNot
      | '(' type ')' expression #cast
      | '&' expression #addresOf
      | SIZEOF '(' type ')' #sizeof
      | expression MULTDIVMOD expression #multiplicationDivisionModulo
      | expression plusMinusSymbol expression #plusMinus
      | expression ('<<'|'>>') expression #bitwiseShift
      | expression (LT|LTE|GT|GTE) expression #lesserOrGreater
      | expression (EQUAL|NOTEQUAL) expression #compare
      | expression ('&'|'bitand') expression #bitwiseAnd
      | expression ('^'|'bitxor') expression #bitwiseXor
      | expression ('|'|'bitor') expression #bitwiseOr
      | expression ('&&'|'and') expression #logicalAnd
      | expression ('||'|'or') expression #logicalOr
      | expression '?' expression ':' expression #ternary
      | varName '=' expression #direct_assign
      | varName '+=' expression #add_assign
      | varName '-=' expression #sub_assign
      | varName '*=' expression #mult_assign
      | varName '/=' expression #div_assign
      | varName '%=' expression #mod_assign
      | varName '<<=' expression #bitwiseLeftShift_assign
      | varName '>>=' expression #bitwiseRightShift_assign
      | varName ('&='|'and_eq') expression #bitwiseAnd_assign
      | varName ('^='|'xor_eq') expression #bitwiseXor_assig
      | varName ('|='|'or_eq') expression #bitwiseOr_assign
      //    | expression ',' expression #comma
      ;

MULTDIVMOD : '*' | '/' | '%' ; // remplacer par non terminal ? (en minuscules)
plusMinusSymbol : '+' | '-' ;
