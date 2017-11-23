%start main
%{
	#define YYPRINT(file, type, value) fprint(file, "%d", value);

%}
%left MINUS_OP,  PLUS_OP
%left DIVISION_OP, MULT_OP

%token BOOLEAN_TYPE
%token CHAR_TYPE
%token VOID
%token INT
%token STRING
%token INTP
%token CHARP
%token IF
%token ELSE
%token WHILE
%token DO
%token FOR
%token RETURN
%token _NULL
%token AND, DIVISION_OP, ASSIGNMENT, EQUAL, GREAT_THEN, GREAT_EQUAL, LESS_THEN
%token LESS_EQUAL, MINUS_OP, NOT, NOT_EQUAL, OR, PLUS_OP, MULT_OP,BITWISE_AND, BITWISE_XOR
%token IDENTIFIER, STRING_VALUE, CHAR_LITERAL, POINTER_ADDRESS
%token INT_CONSTANT_VALUE, BOOL_CONSTANT_VALUE, BIN_CONSTANT_VALUE, OCT_CONSTANT_VALUE, HEX_CONSTANT_VALUE
%%

main : program {printf("FINAL DONE\n");};

program
	:head_declaration {printf("Done\n");}
	|line_statement
	|line_statement program
	|head_declaration program
	;



head_declaration
	:declaration
	|function_declaration
	;

declaration
	:type list_of_declarators ';'
	;

function_declaration
	:builtin_function_declaration
	|user_function
	;

builtin_function_declaration
	: if_block
	| for_block
	| do_while_block
	| while_block
	;

if_block
	: IF '(' boolean_expr ')' line_statement  
	| IF '(' boolean_expr ')' '{' program '}' 
	| IF '(' boolean_expr ')' line_statement  else_block
	| IF '(' boolean_expr ')' '{' program '}' else_block	
	;

else_block
	: ELSE line_statement
	| ELSE '{' program '}'
	;

while_block
	: WHILE '(' boolean_expr ')' line_statement
	| WHILE '(' boolean_expr ')' '{' program '}'
	;

do_while_block
	: DO line_statement  WHILE '(' boolean_expr ')' ';'
	| DO '{' program '}'  WHILE '(' boolean_expr ')' ';'
	;

for_block
	: FOR '(' for_block_inits ';' boolean_expr ';' for_inits_update ')' line_statement
	| FOR '(' for_block_inits ';' boolean_expr ';' for_inits_update ')' '{' program '}'
	;

for_block_inits
	: for_block_single_init
	| for_block_single_init ',' for_block_inits
	;

for_block_single_init:
	:IDENTIFIER ASSIGNMENT initializator
	;

for_inits_update
	: complex_expression
	| complex_expression ',' for_inits_update
	;

boolean_expr
	: complex_expression
	| boolean_expr boolean_operator boolean_expr
	|or_and_expression
	|'(' boolean_expr ')'
	| NOT boolean_expr
	;
or_and_expression
	:or_expression
	|and_expression
	;

or_expression
	:boolean_expr OR boolean_expr
	;

and_expression
	:boolean_expr AND boolean_expr
	;

line_statement
	: declaration
	| declarator_initialization ';'
	| complex_expression ';'
	| RETURN complex_expression ';'
	;

list_of_declarators
	:declarator_initialization
	|list_of_declarators ',' declarator_initialization
	;

declarator_initialization
	:declarator ASSIGNMENT initializator 
	|declarator
	;


initializator
	: BITWISE_AND IDENTIFIER	
	| BITWISE_XOR IDENTIFIER
	|_NULL	
	|complex_expression
	;


complex_expression
	:'(' complex_expression ')'
	|basic_expression
	|basic_expression operator complex_expression
	;

basic_expression
	:function_result
	|terminal_const_values
	|IDENTIFIER
	|IDENTIFIER '[' INT_CONSTANT_VALUE ']'
	| '|' IDENTIFIER '|'
	;

function_result
	:IDENTIFIER '(' ')'
	|IDENTIFIER '(' parameters_list ')' 
	;
	
parameters_list
	:complex_expression
	|complex_expression ',' parameters_list
	;

terminal_const_values
	:INT_CONSTANT_VALUE
	|BOOL_CONSTANT_VALUE
	|BIN_CONSTANT_VALUE
	|OCT_CONSTANT_VALUE
	|HEX_CONSTANT_VALUE
	|literals
	;

literals
	: CHAR_LITERAL
	| STRING_VALUE
	;


declarator
	:IDENTIFIER
	|declarator '(' ')'
	|declarator '(' params_types_list ')'
	|declarator '[' ']'
	|declarator '[' array_size ']'
	;

params_types_list
	:type
	|params_types_list ',' type
	|type IDENTIFIER
	|params_types_list ',' type IDENTIFIER
	;
	
	

array_size
	:array_size ',' INT_CONSTANT_VALUE
	|complex_expression
	;

/*numeric_expression
	:'(' numeric_expression ')'
	|'(' numeric_expression ')' operator numeric_expression
	|numeric_expression PLUS_OP numeric_expression {$$=$1+$3;}
	|numeric_expression MINUS_OP numeric_expression {$$=$1-$3;}
	|numeric_expression MULT_OP numeric_expression {$$=$1*$3;}
	|numeric_expression DIVISION_OP numeric_expression {$$=$1/$3;}
	|INT_CONSTANT_VALUE {$$=$1;}
	; 
*/



type
	:BOOLEAN_TYPE 
	|CHAR_TYPE
	|VOID
	|INT
	|INTP    
	|CHARP
	|STRING
	;

operator
	:MINUS_OP
	|PLUS_OP
	|DIVISION_OP
	|MULT_OP
	;

boolean_operator
	:EQUAL
	|GREAT_EQUAL
	|LESS_EQUAL
	|GREAT_THEN
	|LESS_THEN
	|NOT_EQUAL
	;
boolean_delimeters
	: AND
	| OR
	;
/*
builtin_function   
	:IF    
	|ELSE {printf("else");}   
	|WHILE{printf("while");}   
	|DO   {printf("do");}   
	|FOR  {printf("for");}
	;
*/
/*
others
	:RETURN {printf("return");}   
	|_NULL {printf("null");}
	;*/
%%
#include "lex.yy.c"

void yyerror(const char *s)
{
	fflush(stdout);
	printf("*** %s\n", s);
}

int main(){yydebug=1; return yyparse(); }
