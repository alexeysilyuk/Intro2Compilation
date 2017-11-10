%start program
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
%token AND, RIGHT_SLASH, ASSIGNMENT, COMPARATION, GREAT_THEN, GREAT_EQUAL, LESS_THEN
%token LESS_EQUAL, MINUS, NOT, NOT_EQUAL, OR, PLUS, MULT,BITWISE_AND, BITWISE_XOR
%token CONSTANT_VALUE, IDENTIFIER, STRING_VALUE, STRING_LITERAL, POINTER_ADDRESS
%%
program
	:head_declaration
	|program head_declaration 
	;

head_declaration
	:declaration
	/*|function_define*/
	;

declaration
	:type ';'
	|type list_of_declarators ';'
	;

list_of_declarators
	:declarator_initialization
	|list_of_declarators ',' declarator_initialization
	;

declarator_initialization
	:declarator 
	|declarator '=' initializator 
	;

declarator
	:IDENTIFIER {printf("YACC_DEC_ID\n");}
	|'(' declarator ')'
	|declarator '(' ')'
	|declarator '(' identifiers_list ')'
	|declarator '(' params_types_list ')'
	/*|declarator '[' ']'*/
	|declarator '[' array_size ']'
	;
	
array_size
	:CONSTANT_VALUE
	|array_size ',' CONSTANT_VALUE
	;

identifiers_list
	:IDENTIFIER
	|identifiers_list ',' IDENTIFIER
	;


params_types_list
	:type
	|params_types_list ',' type
	|type IDENTIFIER
	|params_types_list ',' type IDENTIFIER
	;
	

initializator
	:assignment_expression	{printf("INIT\n");}
	| "&"IDENTIFIER	
	| "^"IDENTIFIER
	;

assignment_expression
	: basic_expression 	
	;

basic_expression
	: IDENTIFIER 
	| CONSTANT_VALUE 
	| STRING_LITERAL
	| '(' expression ')'
	;

expression
	:assignment_expression
	|expression ',' assignment_expression	
	;


type
	:BOOLEAN_TYPE {printf("boolean\n");}
	|CHAR_TYPE {printf("char\n");}
	|VOID {printf("void\n");}
	|INT  {printf("int\n");}
	|STRING_VALUE {printf("string\n");} 
	|INTP {printf("intp\n");}   
	|CHARP{printf("charp\n");}
	|STRING_LITERAL {printf("char\n");}
	;
/*function   
	:IF   {printf("if");}   
	|ELSE {printf("else");}   
	|WHILE{printf("while");}   
	|DO   {printf("do");}   
	|FOR  {printf("for");}
	;

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

int main(){return yyparse(); }
