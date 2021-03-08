grammar ifcc;

axiom : prog       
      ;

prog : TYPE 'main' '(' 'void'? ')' '{' line* RETURN expression ';' '}';


line : (declaration | affectationall) ';' ;

affectationall : VARIABLE_NAME '=' expression #affectation
            | '++' VARIABLE_NAME #preIncrement
            | '--' VARIABLE_NAME #preDecrement
            | VARIABLE_NAME '++' #postIncrement
            | VARIABLE_NAME '--' #postDecrement;

declarationlist : VARIABLE_NAME ( ',' declarationlist)? #simpleDeclaration
            | VARIABLE_NAME '=' expression ( ',' declarationlist)? #assignDeclaration ;

declaration : TYPE declarationlist ;

value : CONST #const
      | VARIABLE_NAME #variable ;

expression : affectationall #affectationValue 
      | expression '*' expression #mult
      | expression '/' expression #div
      | expression '-' expression #sub
      | expression '+' expression #add
      | '-' expression #minus
      | value #expressionValue
      | '(' expression ')' #par;



TYPE : 'int' ;
RETURN : 'return' ;
CONST : [0-9]+ ;
VARIABLE_NAME : [a-zA-Z_][a-zA-Z0-9_]* ;
COMMENT : '/*' .* '*/' -> skip ;
COMMENTLINE : '//' .* '\n' -> skip ;
DIRECTIVE : '#' .* '\n' -> skip ;
WS    : [ \t\r\n] -> channel(HIDDEN);
