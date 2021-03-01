grammar ifcc;

axiom : prog       
      ;

prog : 'int' 'main' '(' ')' '{' declaration*? RETURN retValue ';' '}' ;

declaration : 'int' VAR_NAME '=' value ';';
value : CONST | VAR_NAME;
retValue: CONST | VAR_NAME;

RETURN : 'return' ;
VAR_NAME : [a-zA-Z][a-zA-Z0-9]* ;
CONST : [0-9]+ ;
COMMENT : '/*' .*? '*/' -> skip ;
DIRECTIVE : '#' .*? '\n' -> skip ;
WS    : [ \t\r\n] -> channel(HIDDEN);
