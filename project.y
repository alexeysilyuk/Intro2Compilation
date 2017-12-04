%{
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct node {
	char* token;
	struct node* left;
	struct node* right;
	int printHeader;
	/* Max possible childs on for rule are 4
	There fore in another rules simple use NULL 
	for rest of child */
} node;


node* mknode (char* token, node* left, node* right, int printHeader);

void printTree (node* tree, int space);


/*#define YYSTYPE struct node**/

%}

%union {
  char* string;
  node* node;
  int integer;
} 

%start main
%{
	#define YYPRINT(file, type, value) fprint(file, "%d", value);
%}

%left MINUS_OP,  PLUS_OP
%left DIVISION_OP, MULT_OP

%token <string>  LP , RP, INCR, DECR
%token <string>  BOOLEAN_TYPE, CHAR_TYPE, INT, VOID, STRING,  INTP, CHARP
%token <string>  IF, ELSE, WHILE, DO, FOR
%token <string>  RETURN,  _NULL, MAIN
%token <string>  AND, DIVISION_OP, ASSIGNMENT, EQUAL, GREAT_THEN, GREAT_EQUAL, LESS_THEN
%token <string>  LESS_EQUAL, MINUS_OP, NOT, NOT_EQUAL, OR, PLUS_OP, MULT_OP,BITWISE_AND, BITWISE_XOR
%token <string>  IDENTIFIER
%token <string>  STRING_VALUE, CHAR_LITERAL, POINTER_ADDRESS
%token <integer> INT_CONSTANT_VALUE
%token <string>  BOOL_CONSTANT_VALUE, BIN_CONSTANT_VALUE, OCT_CONSTANT_VALUE, HEX_CONSTANT_VALUE
/*
%type <node> BOOLEAN_TYPE CHAR_TYPE INT VOID STRING  INTP CHARP
%type <node>  IF  ELSE  WHILE  DO  FOR
%type <node>  RETURN   _NULL  MAIN
%type <node>  AND  DIVISION_OP  ASSIGNMENT  EQUAL  GREAT_THEN  GREAT_EQUAL  LESS_THEN
%type <node>  LESS_EQUAL  MINUS_OP  NOT  NOT_EQUAL  OR  PLUS_OP  MULT_OP BITWISE_AND  BITWISE_XOR
%type <node> IDENTIFIER
%type <node>  STRING_VALUE  CHAR_LITERAL  POINTER_ADDRESS
%type <node>  INT_CONSTANT_VALUE  BOOL_CONSTANT_VALUE  BIN_CONSTANT_VALUE  OCT_CONSTANT_VALUE  HEX_CONSTANT_VALUE
*/
%type <node> program head_declaration code_block functions line_statement declaration
%type <node> builtin_functions loop_functions if_block else_block while_block do_while_block for_block
%type <node> for_block_inits for_block_single_init for_block_inits_update for_block_boolean_expr boolean_expr
%type <node> boolean_expr_complex boolean_expr_simple bool_binary_op bool_unary_op user_function function_call
%type <node> function_call_parameters_list  list_of_declarators declarator_initialization initializator complex_expression
%type <node> basic_expression integer parameters_list  terminal_const_values literals declarator params_types_list
%type <node> array_size  type operator bitwise_operators expression other ID lp rp inc_dec  main_program
%%



main : main_program {printf("DONE!!! \n"); printTree($1, 0);  };

main_program 
	: VOID MAIN lp params_types_list rp code_block 
		{ $$ = mknode("VOID MAIN",mknode("(",$3,$4,0),mknode(")",$6,$5,0),1);   }
	| VOID MAIN lp  rp code_block	
		{ $$ = mknode("VOID MAIN",$3,mknode(")",$4,$5,0),1);  }
	;

program
	: head_declaration { $$ = mknode("PROGRAM", $1, NULL,0); }
	| head_declaration program { $$ = mknode("PROGRAM", $1, $2,0); }
	;


head_declaration
	: code_block { $$ = mknode("HEAD", $1, NULL, 0); }
	| functions  { $$ = mknode("HEAD", $1, NULL, 0); }
	| line_statement  { $$ = mknode("HEAD", $1, NULL, 0); }
	;

code_block
	: '{' program '}' { $$ = mknode("(BLOCK", $2, mknode(")", NULL, NULL, 1), 1); }
	| '{' '}' { $$ = mknode("(BLOCK", NULL, NULL, 1); }
	;

functions
	: builtin_functions { $$ = mknode("FUNCTION", $1, NULL, 0); }
	| user_function  { $$ = mknode("FUNCTION", $1, NULL,0); }
	;

line_statement
	: declaration { $$ = mknode("LINE_STATEMENT", $1, NULL, 0); }  
	| declarator_initialization ';' { $$ = mknode("LINE_STATEMENT", $1, NULL,0); }  
	| RETURN ';' { $$ = mknode("return", NULL, NULL,1); } 
	| RETURN expression ';' { $$ = mknode("return", $2, NULL, 1); }  
	| function_call ';' { $$ = mknode("LINE_STATEMENT", $1, NULL,0); }
	;



declaration
	: type list_of_declarators ';' 
		{$$ = mknode("(", $1, mknode(")",$2,mknode(")",NULL,NULL,1),0), 1); }
	;

builtin_functions
	: if_block { $$ = mknode("if_block", $1, NULL, 0); }
	| loop_functions { $$ = mknode("loop_functions", $1, NULL,0); }
	;

loop_functions
	: for_block { $$ = mknode("for_block", $1, NULL, 0); }
	| do_while_block { $$ = mknode("do_while_block", $1, NULL, 0); }
	| while_block { $$ = mknode("while_block", $1, NULL, 0); }
	;

if_block
	: IF lp boolean_expr rp line_statement  else_block 
		{ $$ = mknode("(IF", mknode("(", $2, $3, 0), mknode(")", 
			mknode("(BLOCK",$5,mknode(")",NULL,NULL,1),1)		
			, $6, 1), 1); }
	| IF lp boolean_expr rp code_block else_block	
		{ $$ = mknode("(IF", mknode("(", $2, $3, 0), mknode(")", $5, $6, 1), 1); }
	;

else_block
	: ELSE line_statement { $$ = mknode("(BLOCK", $2, NULL, 0); }
	| ELSE code_block { $$ = mknode("(BLOCK", $2, NULL, 0); }
	|  { $$ = mknode("epsilon", NULL, NULL, 0); }
	;

while_block
	: WHILE lp boolean_expr rp line_statement { $$ = mknode("(WHILE", $3, $5, 1); }
	| WHILE lp boolean_expr rp code_block { $$ = mknode("WHILE", $3, $5, 1); }
	;

do_while_block
	: DO line_statement  WHILE lp boolean_expr rp ';' { $$ = mknode("(DO_WHILE", $2, $5, 0); }
	| DO code_block  WHILE lp boolean_expr rp ';' { $$ = mknode("(DO_WHILE", $2, $5, 0); }
	;

for_block
	: FOR lp for_block_inits ';' for_block_boolean_expr ';' for_block_inits_update rp
line_statement 
	{ $$ = mknode("FOR", 
		mknode("FOR", mknode("FOR", $3, $5, 0), $7, 0), 
			    $9, 0); 
	}
	| FOR lp for_block_inits ';' for_block_boolean_expr ';' for_block_inits_update rp code_block 		{ $$ = mknode("FOR", 
		mknode("FOR", mknode("FOR", $3, $5, 0), $7, 0), 
			    $9, 0); }
	;

for_block_inits
	: for_block_single_init { $$ = mknode("FOR_INIT", $1, NULL,0); }
	| for_block_single_init ',' for_block_inits { $$ = mknode("FOR_INIT", $1, $3, 0); }
	;

for_block_single_init
	:ID ASSIGNMENT initializator { $$ = mknode("=", $1, $3, 1); }
	;

for_block_inits_update
	: ID ASSIGNMENT initializator { $$ = mknode("=", $1, $3, 1);  }
	| ID ASSIGNMENT initializator ',' for_block_inits_update 
		{ $$ = mknode(", ", mknode("=", $1, $3, 1), $5, 1);  }
	| ID inc_dec
		{ $$ = mknode($2->token, $1, NULL, 1);  }
	| ID inc_dec ',' for_block_inits_update 
		{ $$ = mknode($2->token, $1, $4, 1);  }
	;

for_block_boolean_expr
	: boolean_expr { $$ = mknode("FOR_EXPRESION", $1,  NULL,0); }
	| boolean_expr ',' for_block_boolean_expr { $$ = mknode("FOR_EXPRESION", $1, $3, 0); }
	;


boolean_expr
		: boolean_expr AND boolean_expr_complex { $$ = mknode("&&", $1,  $3, 1); }
		| boolean_expr OR boolean_expr_complex { $$ = mknode("||", $1,  $3, 1); }
		| boolean_expr_complex { $$ = mknode("BOOLEAN_EXPR", $1, NULL, 0); }
		| bool_unary_op boolean_expr_complex { $$ = mknode("!", NULL, $2, 1); }
		;
/* OP must print operator */
boolean_expr_complex
		: boolean_expr_complex bool_binary_op boolean_expr_simple 
			{ $$ = mknode($2->token, $1, $3, 1); }
		| boolean_expr_simple 
			{ $$ = mknode("BOOLEAN_EXPR_COMPLEX", $1, NULL, 0); }
		;


boolean_expr_simple
		: complex_expression { $$ = mknode("BOOLEAN_EXPR_SIMPLE", $1, NULL,0); }
		| other  { $$ = mknode("BOOLEAN_EXPR_SIMPLE", $1, NULL,0); }
		;

bool_binary_op
		: EQUAL 	{ $$ = mknode($1, NULL, NULL,1); }
		| NOT_EQUAL 	{ $$ = mknode($1, NULL, NULL,1); }
		| LESS_THEN 	{ $$ = mknode($1, NULL,  NULL,1); }
		| LESS_EQUAL 	{ $$ = mknode($1, NULL,  NULL,1); }
		| GREAT_THEN 	{ $$ = mknode($1, NULL,  NULL,1); }
		| GREAT_EQUAL	{ $$ = mknode($1, NULL,  NULL,1); }
		;

bool_unary_op
		: NOT { $$ = mknode($1, NULL, NULL,1); }
		;


user_function
	: type ID lp rp code_block 
		{ $$ = mknode($2->token, 
				mknode("(USER_FUNC", $1, $2, 0),  $5, 0); 	}
	| type ID lp params_types_list rp code_block 
		{ $$ = mknode("USER_FUNC", 
				mknode("USER_FUNC", mknode("USER_FUNC", $1, $2,0), $4,0), 
				  	$6,0); 
		}
	
	;


function_call
	: ID lp rp 
		{ $$ = mknode($1->token, $2, $3,1); }
	| ID lp function_call_parameters_list rp 
		{ $$ = mknode($1->token, $2, mknode("",$3,$4,0),1); }
	;

function_call_parameters_list 
	: complex_expression 
		{ $$ = mknode("FUNC_PARAM", $1, NULL, 0); }
	| complex_expression ',' parameters_list 
		{ $$ = mknode("FUNC_PARAM", $1, $3, 0); }
	;
	

list_of_declarators
	: declarator_initialization 
		{ $$ = mknode("LIST_DECL", $1, NULL, 0); }
	| list_of_declarators ',' declarator_initialization 
		{ $$ = mknode("LIST_DECL", $1, $3, 0); }
	;

declarator_initialization
	: declarator ASSIGNMENT initializator 
		{ $$ = mknode("=", $1, $3, 1); }
	| declarator 
		{ $$ = mknode("DECL_INIT", $1, NULL, 0); }
	;


initializator
	: expression { $$ = mknode("INIT", $1, NULL,0); }
	;



complex_expression
	: basic_expression 
		{ $$ = mknode("EXPRESSION", $1,  NULL,0); }
	| basic_expression operator complex_expression 
		{ $$ = mknode($2->token, $1, $3, 1); }
	| operator complex_expression 
		{ $$ = mknode($1->token, NULL, $2, 1); }
	
	;

basic_expression
	: function_call 
		{ $$ = mknode("SIMPLE_EXPRESSION", $1,  NULL,0); }
	| terminal_const_values 
		{ $$ = mknode($1->token, $1, NULL,0); }
	| ID '[' integer ']' 
		{ $$ = mknode($1->token, mknode("[",mknode($3->token,NULL,NULL,1),NULL,1),
			mknode("]",NULL,NULL,1),1);
		 }
	| ID 
		{ $$ = mknode($1->token, NULL, NULL, 1); }
	| '|' ID '|' 
		{ $$ = mknode("|ID|",  NULL, NULL,0); }
	| lp boolean_expr rp 
		{ $$ = mknode("SIMPLE_EXPRESSION", NULL, $2, 0); }
	| bitwise_operators  basic_expression 
		{ $$ = mknode("bitwise_operator", $1, $2, 0); } 
	;
 
integer
	: INT_CONSTANT_VALUE { $$ = mknode(yytext,NULL,NULL,1); };


parameters_list
	: complex_expression { $$ = mknode("PARAM_LIST", $1,  NULL,0); }
	| type complex_expression { $$ = mknode("PARAM_LIST", $1, $2, 1); }
	| complex_expression ',' parameters_list 
		{ $$ = mknode("PARAM_LIST", $1, $3, 0); }
	| type complex_expression ',' parameters_list 
		{ $$ = mknode("PARAM_LIST", 
				mknode("PARAM_LIST", $1, $2, 0), $4, 0); }
	;

terminal_const_values
	: INT_CONSTANT_VALUE { $$ = mknode(yytext, NULL, NULL,  1); }
	| BOOL_CONSTANT_VALUE { $$ = mknode(yytext, NULL, NULL, 1); }
	| BIN_CONSTANT_VALUE { $$ = mknode(yytext, NULL, NULL, 1); }
	| OCT_CONSTANT_VALUE { $$ = mknode(yytext, NULL, NULL, 1); }
	| HEX_CONSTANT_VALUE { $$ = mknode(yytext, NULL, NULL, 1); }
	| literals { $$ = mknode("CONST", $1, NULL, 0); }
	;

literals
	: CHAR_LITERAL { $$ = mknode(yytext, NULL, NULL, 1); }
	| STRING_VALUE { $$ = mknode(yytext, NULL, NULL, 1); }
	;


declarator
	: ID { $$ = mknode("ID", $1, NULL, 0); }
	| declarator '[' ']' 
		{ $$ = mknode("ARRAY", $1, mknode("[]", NULL,  NULL, 1),0); }
	| declarator '[' array_size ']'  
		{ $$ = mknode("ID-ARRAY[size]", $1,  mknode("[", $3,  mknode("]", NULL,  NULL, 1), 1), 0); }
	| bitwise_operators ID 
		{ $$ = mknode("BIT_OP", $1,  $2, 0); }
	;

params_types_list
	: type { $$ = mknode("TYPE", $1, NULL,0); }
	| params_types_list ',' type { $$ = mknode("PARAM_TYPE_LIST", $1, $3, 0); }
	| type ID { $$ = mknode("PARAM_TYPE_LIST", $1, $2, 0); }
	| params_types_list ',' type ID 
		{ $$ = mknode("PARAM_TYPE_LIST", $1, mknode("PARAM_TYPE_LIST", $3, $4, 0), 0); }
	;
	


array_size
	: array_size ',' INT_CONSTANT_VALUE 
		{ $$ = mknode("ARRAY_SIZE", $1, mknode(yytext, NULL, NULL,  1), 1); }
	| complex_expression 
		{ $$ = mknode("ARRAY_SIZE", $1, NULL,0); }
	;

/*numeric_expression
	: lp numeric_expression rp
	| lp numeric_expression rp operator numeric_expression
	| numeric_expression PLUS_OP numeric_expression {$$=$1+$3;}
	| numeric_expression MINUS_OP numeric_expression {$$=$1-$3;}
	| numeric_expression MULT_OP numeric_expression {$$=$1*$3;}
	| numeric_expression DIVISION_OP numeric_expression {$$=$1/$3;}
	| INT_CONSTANT_VALUE {$$=$1;}
	; 
*/



type
	: STRING { $$ = mknode($1, NULL, NULL, 1); }
	| BOOLEAN_TYPE { $$ = mknode($1, NULL, NULL, 1); }
	| CHAR_TYPE { $$ = mknode($1, NULL, NULL, 1); }
	| INT { $$ = mknode($1, NULL, NULL, 1); }
	| INTP { $$ = mknode($1, NULL, NULL, 1); }
	| CHARP { $$ = mknode($1, NULL, NULL, 1); }
	;


operator
	: MINUS_OP { $$ = mknode($1, NULL, NULL, 1); }
	| PLUS_OP { $$ = mknode($1, NULL, NULL, 1); }
	| DIVISION_OP { $$ = mknode($1, NULL, NULL, 1); }
	| MULT_OP { $$ = mknode($1, NULL, NULL, 1); }
	;

bitwise_operators
	: BITWISE_AND { $$ = mknode($1, NULL, NULL, 1); }
	| BITWISE_XOR { $$ = mknode($1, NULL, NULL, 1); }
	;

/* not done */
expression
	: /*complex_expression
	|*/ boolean_expr { $$ = mknode("EXPRESSION", $1, NULL, 0); }
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

other
	: RETURN { $$ = mknode($1, NULL, NULL, 1); }
	| _NULL  { $$ = mknode($1, NULL, NULL, 1); }
	;

lp
	: LP  		{ $$ = mknode($1, NULL, NULL, 1); }
	;
rp
	: RP		{ $$ = mknode($1, NULL, NULL, 1); }
	;

ID
	: IDENTIFIER { $$ = mknode($1, NULL, NULL,1); }
	;
inc_dec
	: INCR { $$ = mknode($1, NULL, NULL,1); }
	| DECR { $$ = mknode($1, NULL, NULL,1); }
%%
#include "lex.yy.c"

int main(){yydebug=1; return yyparse(); }


node* mknode(char* token, node* left, node* right, int printHeader) {
	node* newNode = (node *) malloc (sizeof(node));
	/*
	char* newStr = (char *) malloc (sizeof(token)+1);  
	strcpy(newStr, token);
	newNode->token = newStr;
	*/
	newNode->token = strdup(token);
	newNode->left = left;
	newNode->right = right;
	newNode->printHeader = printHeader;
	return newNode;
}

void printTree(node* tree, int space) {
	int i;
		if(tree->printHeader==1)
		{	
			for (i= 0; i< space; i++) 
				{ printf("   "); }
			printf("%s\n", tree->token);
			space++;
			
			if (tree->left) 
				{   printTree(tree->left, space);  }
			if (tree->right)
				{   printTree(tree->right, space);}
			
			
		}
		else{
			if (tree->left) {   printTree(tree->left, space); }
			if (tree->right){   printTree(tree->right, space); }

		}
	
}
