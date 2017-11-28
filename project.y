%start main
%{
	#define YYPRINT(file, type, value) fprint(file, "%d", value);

%}

%left MINUS_OP,  PLUS_OP
%left DIVISION_OP, MULT_OP

%token BOOLEAN_TYPE, CHAR_TYPE, INT, VOID, STRING,  INTP, CHARP
%token IF, ELSE, WHILE, DO, FOR
%token RETURN,  _NULL, MAIN
%token AND, DIVISION_OP, ASSIGNMENT, EQUAL, GREAT_THEN, GREAT_EQUAL, LESS_THEN
%token LESS_EQUAL, MINUS_OP, NOT, NOT_EQUAL, OR, PLUS_OP, MULT_OP,BITWISE_AND, BITWISE_XOR
%token IDENTIFIER, STRING_VALUE, CHAR_LITERAL, POINTER_ADDRESS
%token INT_CONSTANT_VALUE, BOOL_CONSTANT_VALUE, BIN_CONSTANT_VALUE, OCT_CONSTANT_VALUE, HEX_CONSTANT_VALUE

%%



main : program {printf("DONE!!! \n");};

program
	: head_declaration 
	| head_declaration program 
	;


head_declaration
	: functions 
	| line_statement
	| '{' program '}'
	;

line_statement
	: declaration  /* done */
	| declarator_initialization ';'  /* done */
	| RETURN ';' /* done */
	| RETURN expression ';' /* done */
	;

functions
	: builtin_functions 
	| user_function 
	|
	;

declaration
	: type list_of_declarators ';'
	;

builtin_functions
	: if_block
	| loop_functions	
	;

loop_functions
	: for_block
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
	: FOR '(' for_block_inits ';' for_block_boolean_expr ';' for_block_inits_update ')' line_statement
	| FOR '(' for_block_inits ';' for_block_boolean_expr ';' for_block_inits_update ')' '{' program '}'
	;

for_block_inits
	: for_block_single_init
	| for_block_single_init ',' for_block_inits
	;

for_block_single_init
	:IDENTIFIER ASSIGNMENT initializator 
	;

for_block_inits_update
	: IDENTIFIER ASSIGNMENT initializator
	| IDENTIFIER ASSIGNMENT initializator ',' for_block_inits_update
	;

for_block_boolean_expr
	: boolean_expr
	| boolean_expr ',' for_block_boolean_expr
	;


boolean_expr
		: boolean_expr AND boolean_expr_complex
		| boolean_expr OR boolean_expr_complex
		| boolean_expr_complex
		| bool_unary_op boolean_expr_complex
		;

boolean_expr_complex
		: boolean_expr_complex bool_binary_op boolean_expr_simple
		| boolean_expr_simple
		;


boolean_expr_simple
		: complex_expression
		;

bool_binary_op
		: EQUAL
		| NOT_EQUAL
		| LESS_THEN
		| LESS_EQUAL
		| GREAT_THEN
		| GREAT_EQUAL
		;

bool_unary_op
		: NOT
		;


user_function
	: type IDENTIFIER '(' ')' '{' '}'
	| type IDENTIFIER '(' params_types_list ')' '{' '}'
	| type IDENTIFIER '(' ')' '{' program '}'
	| type IDENTIFIER '(' params_types_list ')' '{' program '}'
	| VOID MAIN '(' params_types_list ')' '{' program '}'
	| VOID MAIN '('  ')' '{' program '}'	
	;

/* done */
function_call
	: IDENTIFIER '(' ')'
	| IDENTIFIER '(' function_call_parameters_list ')' 
	;
/* done */
function_call_parameters_list
	: complex_expression
	| complex_expression ',' parameters_list
	;
	



/* done */
list_of_declarators
	: declarator_initialization
	| list_of_declarators ',' declarator_initialization
	;
/* done */
declarator_initialization
	: declarator ASSIGNMENT initializator 
	| declarator
	;

/* done */
initializator
	: bitwize_operators IDENTIFIER	
	| _NULL	
	| expression
	| bitwize_operators '(' initializator ')'
	;



/* done */
complex_expression
	: basic_expression
	| basic_expression operator complex_expression
	
	;
/* done */
basic_expression
	: function_call 
	| terminal_const_values
	| IDENTIFIER '[' INT_CONSTANT_VALUE ']'
	| IDENTIFIER
	| '|' IDENTIFIER '|'
	| '(' boolean_expr ')'
	;


parameters_list
	: complex_expression
	| type complex_expression
	| complex_expression ',' parameters_list
	| type complex_expression ',' parameters_list
	;

terminal_const_values
	: INT_CONSTANT_VALUE
	| BOOL_CONSTANT_VALUE
	| BIN_CONSTANT_VALUE
	| OCT_CONSTANT_VALUE
	| HEX_CONSTANT_VALUE
	| literals
	;

literals
	: CHAR_LITERAL
	| STRING_VALUE
	;

	;
declarator
	: IDENTIFIER
	| declarator '[' ']'
	| declarator '[' array_size ']'
	;

params_types_list
	: type
	| params_types_list ',' type
	| type IDENTIFIER
	| params_types_list ',' type IDENTIFIER
	;
	


array_size
	: array_size ',' INT_CONSTANT_VALUE
	| complex_expression
	;

/*numeric_expression
	: '(' numeric_expression ')'
	| '(' numeric_expression ')' operator numeric_expression
	| numeric_expression PLUS_OP numeric_expression {$$=$1+$3;}
	| numeric_expression MINUS_OP numeric_expression {$$=$1-$3;}
	| numeric_expression MULT_OP numeric_expression {$$=$1*$3;}
	| numeric_expression DIVISION_OP numeric_expression {$$=$1/$3;}
	| INT_CONSTANT_VALUE {$$=$1;}
	; 
*/



type
	: STRING
	| BOOLEAN_TYPE
	| CHAR_TYPE
	| INT
	| INTP
	| CHARP
	;


operator
	: MINUS_OP
	| PLUS_OP
	| DIVISION_OP
	| MULT_OP
	;

bitwize_operators
	: BITWISE_AND	
	| BITWISE_XOR
	;

/* not done */
expression
	: /*complex_expression
	|*/ boolean_expr
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
