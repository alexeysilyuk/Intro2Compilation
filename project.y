%{
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct node {
	char* token;
	struct node* first;
	struct node* second;
	struct node* third;
	struct node* four;

	/* Max possible childs on for rule are 4
	There fore in another rules simple use NULL 
	for rest of child */
} node;


node* mk_node (char* token, node* child);

void printTree (node* tree, int space);


#define YYSTYPE struct node*

%}


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



main : program {printf("DONE!!! \n"); printTree($1, 0);  };

program
	: head_declaration { $$ = mknode("PROGRAM", $1, NULL, NULL, NULL); }
	| head_declaration program { $$ = mknode("PROGRAM", $1, $2, NULL, NULL); }
	;


head_declaration
	:code_block { $$ = mknode("HEAD", $1, NULL, NULL, NULL); }
	|functions  { $$ = mknode("HEAD", $1, NULL, NULL, NULL); }
	| line_statement { $$ = mknode("HEAD", $1, NULL, NULL, NULL); }
	;

code_block:
	 '{' program '}' { $$ = mknode("BLOCK", $2, NULL, NULL, NULL); }
	|'{' '}' { $$ = mknode("BLOCK", NULL, NULL, NULL, NULL); }
	;

functions
	: builtin_functions { $$ = mknode("FUNCTION", $1, NULL, NULL, NULL); }
	| user_function  { $$ = mknode("FUNCTION", $1, NULL, NULL, NULL); }
	;

line_statement
	: declaration { $$ = mknode("LINE_STATMENT", $1, NULL, NULL, NULL); }  /* done */
	| declarator_initialization ';' { $$ = mknode("LINE_STATMENT", $1, NULL, NULL, NULL); }   /* done */
	| RETURN ';' { $$ = mknode("LINE_STATMENT", NULL, NULL, NULL, NULL); }  /* done */
	| RETURN expression ';' { $$ = mknode("LINE_STATMENT", $2, NULL, NULL, NULL); }  /* done */
	|function_call ';' { $$ = mknode("LINE_STATMENT", $1, NULL, NULL, NULL); }
	;



declaration
	: type list_of_declarators ';' { $$ = mknode("DECLARATION", $1, $2, NULL, NULL); }
	;

builtin_functions
	: if_block { $$ = mknode("BUILD_IN", $1, NULL, NULL, NULL); }
	| loop_functions { $$ = mknode("BUILD_IN", $1, NULL, NULL, NULL); }
	;

loop_functions
	: for_block { $$ = mknode("LOOP", $1, NULL, NULL, NULL); }
	| do_while_block { $$ = mknode("LOOP", $1, NULL, NULL, NULL); }
	| while_block { $$ = mknode("LOOP", $1, NULL, NULL, NULL); }
	;

if_block
	: IF '(' boolean_expr ')' line_statement  { $$ = mknode("IF", $3, $5, NULL, NULL); }
	| IF '(' boolean_expr ')' code_block  { $$ = mknode("IF", $3, $5, NULL, NULL); }
	| IF '(' boolean_expr ')' line_statement  else_block { $$ = mknode("IF", $3, $5, $6, NULL); }
	| IF '(' boolean_expr ')' code_block else_block	{ $$ = mknode("IF", $3, $5, $6, NULL); }
	;

else_block
	: ELSE line_statement { $$ = mknode("ELSE", $2, NULL, NULL, NULL); }
	| ELSE code_block { $$ = mknode("ELSE", $2, NULL, NULL, NULL); }
	;

while_block
	: WHILE '(' boolean_expr ')' line_statement { $$ = mknode("WHILE", $3, $5, NULL, NULL); }
	| WHILE '(' boolean_expr ')' code_block { $$ = mknode("WHILE", $3, $5, NULL, NULL); }
	;

do_while_block
	: DO line_statement  WHILE '(' boolean_expr ')' ';' { $$ = mknode("DO_WHILE", $2, $5, NULL, NULL); }
	| DO code_block  WHILE '(' boolean_expr ')' ';' { $$ = mknode("DO_WHILE", $2, $5, NULL, NULL); }
	;

for_block
	: FOR '(' for_block_inits ';' for_block_boolean_expr ';' for_block_inits_update ')' line_statement { $$ = mknode("FOR", $3, $5, $7, NULL); }
	| FOR '(' for_block_inits ';' for_block_boolean_expr ';' for_block_inits_update ')' code_block { $$ = mknode("FOR", $3, $5, $7, $9); }
	;

for_block_inits
	: for_block_single_init { $$ = mknode("FOR_INIT", $1, NULL, NULL, NULL); }
	| for_block_single_init ',' for_block_inits { $$ = mknode("FOR_INIT", $1, $3, NULL, NULL); }
	;

for_block_single_init
	:IDENTIFIER ASSIGNMENT initializator { $$ = mknode("FOR_INIT_SINGLE", $1, $2, $3, NULL); }
	;

for_block_inits_update
	: IDENTIFIER ASSIGNMENT initializator { $$ = mknode("FOR_UPDATE", $1, $2, $3, NULL); }
	| IDENTIFIER ASSIGNMENT initializator ',' for_block_inits_update { $$ = mknode("FOR_UPDATE", $1, $2, $3, $5); }
	;

for_block_boolean_expr
	: boolean_expr { $$ = mknode("FOR_EXPRESION", $1, NULL, NULL, NULL); }
	| boolean_expr ',' for_block_boolean_expr { $$ = mknode("FOR_EXPRESION", $1, $3, NULL, NULL); }
	;


boolean_expr
		: boolean_expr AND boolean_expr_complex { $$ = mknode("BOOLEAN_EXPR", $1, $2, $3, NULL); }
		| boolean_expr OR boolean_expr_complex { $$ = mknode("BOOLEAN_EXPR", $1, $2, $3, NULL); }
		| boolean_expr_complex { $$ = mknode("BOOLEAN_EXPR", $1, NULL, NULL, NULL); }
		| bool_unary_op boolean_expr_complex { $$ = mknode("BOOLEAN_EXPR", $1, $2, NULL, NULL); }
		;

boolean_expr_complex
		: boolean_expr_complex bool_binary_op boolean_expr_simple { $$ = mknode("BOOLEAN_EXPR_COMPLEX", $1, $2, $3, NULL); }
		| boolean_expr_simple { $$ = mknode("BOOLEAN_EXPR_COMPLEX", $1, NULL, NULL, NULL); }
		;


boolean_expr_simple
		: complex_expression { $$ = mknode("BOOLEAN_EXPR_SIMPLE", $1, NULL, NULL, NULL); }
		;

bool_binary_op
		: EQUAL { $$ = mknode("BOOLEAN_OP", $1, NULL, NULL, NULL); }
		| NOT_EQUAL { $$ = mknode("BOOLEAN_OP", $1, NULL, NULL, NULL); }
		| LESS_THEN { $$ = mknode("BOOLEAN_OP", $1, NULL, NULL, NULL); }
		| LESS_EQUAL { $$ = mknode("BOOLEAN_OP", $1, NULL, NULL, NULL); }
		| GREAT_THEN { $$ = mknode("BOOLEAN_OP", $1, NULL, NULL, NULL); }
		| GREAT_EQUAL { $$ = mknode("BOOLEAN_OP", $1, NULL, NULL, NULL); }
		;

bool_unary_op
		: NOT { $$ = mknode("BOOLEAN_OP", $1, NULL, NULL, NULL); }
		;


user_function
	: type IDENTIFIER '(' ')' code_block { $$ = mknode("USER_FUNC", $1, $2, $5, NULL); }
	| type IDENTIFIER '(' params_types_list ')' code_block { $$ = mknode("USER_FUNC", $1, $2, $4, $6); }
	| VOID MAIN '(' params_types_list ')' code_block { $$ = mknode("USER_FUNC", $1, $2, $4, $6); }
	| VOID MAIN '('  ')' code_block	{ $$ = mknode("USER_FUNC", $1, $2, $5, NULL); }
	;

/* done */
function_call
	: IDENTIFIER '(' ')' { $$ = mknode("FUNC_CALL", $1, NULL, NULL, NULL); }
	| IDENTIFIER '(' function_call_parameters_list ')' { $$ = mknode("FUNC_CALL", $1, $3, NULL, NULL); }
	;
/* done */
function_call_parameters_list 
	: complex_expression { $$ = mknode("FUNC_PARAM", $1, NULL, NULL, NULL); }
	| complex_expression ',' parameters_list { $$ = mknode("FUNC_PARAM", $1, $3, NULL, NULL); }
	;
	



/* done */
list_of_declarators
	: declarator_initialization { $$ = mknode("LIST_DECL", $1, NULL, NULL, NULL); }
	| list_of_declarators ',' declarator_initialization { $$ = mknode("LIST_DECL", $1, $3, NULL, NULL); }
	;
/* done */
declarator_initialization
	: declarator ASSIGNMENT initializator { $$ = mknode("DECL_INIT", $1, $2, $3, NULL); }
	| declarator { $$ = mknode("DECL_INIT", $1, NULL, NULL, NULL); }
	;

/* done */
initializator: 
	| _NULL	{ $$ = mknode("INIT", $1, NULL, NULL, NULL); }
	| expression { $$ = mknode("INIT", $1, NULL, NULL, NULL); }
	| bitwize_operators  initializator { $$ = mknode("INIT", $1, $2, NULL, NULL); } 
	;


/* done */
complex_expression
	: basic_expression { $$ = mknode("EXPRESSION", $1, NULL, NULL, NULL); }
	| basic_expression operator complex_expression { $$ = mknode("EXPRESSION", $1, $2, $3, NULL); }
	
	;
/* done */
basic_expression
	: function_call { $$ = mknode("SIMPLE_EXPRESSION", $1, NULL, NULL, NULL); }
	| terminal_const_values { $$ = mknode("SIMPLE_EXPRESSION", $1, NULL, NULL, NULL); }
	| IDENTIFIER '[' INT_CONSTANT_VALUE ']' { $$ = mknode("SIMPLE_EXPRESSION", $1, $3, NULL, NULL); }
	| IDENTIFIER { $$ = mknode(yytext, $1, NULL, NULL, NULL); }
	| '|' IDENTIFIER '|' { $$ = mknode("SIMPLE_EXPRESSION", $2, NULL, NULL, NULL); }
	| '(' boolean_expr ')' { $$ = mknode("SIMPLE_EXPRESSION", $2, NULL, NULL, NULL); }
	;


parameters_list
	: complex_expression { $$ = mknode("PARAM_LIST", $1, NULL, NULL, NULL); }
	| type complex_expression { $$ = mknode("PARAM_LIST", $1, $2, NULL, NULL); }
	| complex_expression ',' parameters_list { $$ = mknode("PARAM_LIST", $1, $3, NULL, NULL); }
	| type complex_expression ',' parameters_list { $$ = mknode("PARAM_LIST", $1, $2, $4, NULL); }
	;

terminal_const_values
	: INT_CONSTANT_VALUE { $$ = mknode(yytext, $1, NULL, NULL, NULL); }
	| BOOL_CONSTANT_VALUE { $$ = mknode(yytext, $1, NULL, NULL, NULL); }
	| BIN_CONSTANT_VALUE { $$ = mknode(yytext, $1, NULL, NULL, NULL); }
	| OCT_CONSTANT_VALUE { $$ = mknode(yytext, $1, NULL, NULL, NULL); }
	| HEX_CONSTANT_VALUE { $$ = mknode(yytext, $1, NULL, NULL, NULL); }
	| literals { $$ = mknode("CONST", $1, NULL, NULL, NULL); }
	;

literals
	: CHAR_LITERAL { $$ = mknode(yytext, $1, NULL, NULL, NULL); }
	| STRING_VALUE { $$ = mknode(yytext, $1, NULL, NULL, NULL); }
	;

	;
declarator
	: IDENTIFIER { $$ = mknode("DECLARATOR", $1, NULL, NULL, NULL); }
	| declarator '[' ']' { $$ = mknode("DECLARATOR", $1, $2, $3, NULL); }
	| declarator '[' array_size ']'  { $$ = mknode("DECLARATOR", $1, $2, $3, $4); }
	;

params_types_list
	: type { $$ = mknode("PARAM_TYPE_LIST", $1, NULL, NULL, NULL); }
	| params_types_list ',' type { $$ = mknode("PARAM_TYPE_LIST", $1, $3, NULL, NULL); }
	| type IDENTIFIER { $$ = mknode("PARAM_TYPE_LIST", $1, $2, NULL, NULL); }
	| params_types_list ',' type IDENTIFIER { $$ = mknode("PARAM_TYPE_LIST", $1, $3, $4, NULL); }
	;
	


array_size
	: array_size ',' INT_CONSTANT_VALUE { $$ = mknode("ARRAY_SIZE", $1, $2, $3, NULL); }
	| complex_expression { $$ = mknode("ARRAY_SIZE", $1, NULL, NULL, NULL); }
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
	: STRING { $$ = mknode("TYPE", $1, NULL, NULL, NULL); }
	| BOOLEAN_TYPE { $$ = mknode("TYPE", $1, NULL, NULL, NULL); }
	| CHAR_TYPE { $$ = mknode("TYPE", $1, NULL, NULL, NULL); }
	| INT { $$ = mknode("TYPE", $1, NULL, NULL, NULL); }
	| INTP { $$ = mknode("TYPE", $1, NULL, NULL, NULL); }
	| CHARP { $$ = mknode("TYPE", $1, NULL, NULL, NULL); }
	;


operator
	: MINUS_OP { $$ = mknode(yytext, $1, NULL, NULL, NULL); }
	| PLUS_OP { $$ = mknode(yytext, $1, NULL, NULL, NULL); }
	| DIVISION_OP { $$ = mknode(yytext, $1, NULL, NULL, NULL); }
	| MULT_OP { $$ = mknode(yytext, $1, NULL, NULL, NULL); }
	;

bitwize_operators
	: BITWISE_AND { $$ = mknode(yytext, $1, NULL, NULL, NULL); }
	| BITWISE_XOR { $$ = mknode(yytext, $1, NULL, NULL, NULL); }
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

int main(){yydebug=1; return yyparse(); }


node* mknode(char* token, node* first, node* second, node* third, node* four) {
	node* newNode = (node *) malloc (sizeof(node));
	/*
	char* newStr = (char *) malloc (sizeof(token)+1);  
	strcpy(newStr, token);
	newNode->token = newStr;
	*/
	newNode->token = strdup(token);
	newNode->first = first;
	newNode->second = second;
	newNode->third = third;
	newNode->four = four;
	
	return newNode;
}

void printTree(node* tree, int space) {
	int i;
	for (i= 0; i< space; i++) { printf("   "); }
	printf("%s\n", tree->token);
	if (tree->first) {   printTree(tree->first, ++space); }
	if (tree->second){   printTree(tree->second, ++space); }
	if (tree->third){   printTree(tree->third, ++space); }
	if (tree->four){   printTree(tree->four, ++space); }
}