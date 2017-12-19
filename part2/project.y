%{
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "semantic.c"


node* mknode (char* token, node* left, node* right, int printHeader, Type type);

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
%token <string>  BOOLEAN, CHAR, INT, VOID, STRING,  INTP, CHARP
%token <string>  IF, ELSE, WHILE, DO, FOR
%token <string>  RETURN,  _NULL, MAIN
%token <string>  AND, DIVISION_OP, ASSIGNMENT, EQUAL, GREAT_THEN, GREAT_EQUAL, LESS_THEN
%token <string>  LESS_EQUAL, MINUS_OP, NOT, NOT_EQUAL, OR, PLUS_OP, MULT_OP,BITWISE_AND, BITWISE_XOR
%token <string>  IDENTIFIER
%token <string>  STRING_VALUE, CHAR_LITERAL, POINTER_ADDRESS
%token <integer> INT_CONSTANT_VALUE
%token <string>  BOOL_CONSTANT_VALUE, BIN_CONSTANT_VALUE, OCT_CONSTANT_VALUE, HEX_CONSTANT_VALUE

%type <node> program head_declaration code_block functions line_statement declaration
%type <node> builtin_functions loop_functions if_block else_block while_block do_while_block for_block
%type <node> for_block_inits for_block_single_init for_block_inits_update for_block_boolean_expr boolean_expr
%type <node> boolean_expr_complex boolean_expr_simple bool_binary_op bool_unary_op user_function function_call
%type <node> function_call_parameters_list  list_of_declarators declarator_initialization initializator complex_expression
%type <node> basic_expression integer  terminal_const_values literals declarator params_types_list
%type <node> array_size  type operator bitwise_operators expression other ID lp rp inc_dec 
%%



main : program {printf("Parsing done successfully. \n"); runSemantic($1);  };


program
	: head_declaration { $$ = mknode("PROGRAM", $1, NULL,0,UNTYPED); }
	| head_declaration program { $$ = mknode("PROGRAM", $1, $2,0,UNTYPED); }
	;


head_declaration
	: code_block { $$ = mknode("BLOCK", $1, NULL, 0,UNTYPED); }
	| functions  { $$ = mknode("FUNCTION_DECLARATION", $1, NULL, 0,UNTYPED); }
	| line_statement  { $$ = mknode("LINE_STATEMENT", $1, NULL, 0,UNTYPED); }
	;

code_block
	: '{' program '}' { $$ = mknode("_", $2, mknode("}", NULL, NULL, 1,UNTYPED), 1,UNTYPED); }
	| '{' '}' { $$ = mknode("(BLOCK", NULL, mknode("}", NULL, NULL, 1,UNTYPED), 1,UNTYPED); }
	;

functions
	: builtin_functions { $$ = mknode("BUILTIN_FUNCTIONS", $1, NULL, 0,UNTYPED); }
	| user_function  { $$ = mknode("USER_FUNCTION", $1, NULL,0,$1->type); }
	;

user_function
		: type ID lp rp code_block
{ $$ = mknode($2->token,
			  mknode($2->token, $1, $2, 0,$1->type),  $5, 0,$1->type); 	}
| type ID lp params_types_list rp code_block
{ $$ = mknode($2->token, mknode("params_types_list", mknode($2->token, $1, $2,0,$1->type), $4,0,$1->type), 	$6,0,$1->type);
}
/*|VOID MAIN lp params_types_list rp code_block
    { $$ = mknode("(VOID MAIN",mknode("(",$3,$4,0,UNTYPED),mknode(")",$6,$5,0,UNTYPED),1,UNTYPED);   }
| VOID MAIN lp  rp code_block
    { $$ = mknode("(VOID MAIN",$3,mknode(")",$4,$5,0,UNTYPED),1,UNTYPED);  }*/
;



line_statement
	: declaration { $$ = mknode("DECLARATION", $1, NULL, 0,$1->type); }  
	| declarator_initialization ';' { $$ = mknode("DECLARATION_INIT", $1, NULL,0,$1->type); }
	| RETURN ';' { $$ = mknode("return", NULL, NULL,1,UNTYPED); } 
	| RETURN expression ';' { $$ = mknode("return", $2, NULL, 1,$2->type); }
	| function_call ';' { $$ = mknode("function_call", $1, NULL,0,UNTYPED); }
	;


declaration
	: type list_of_declarators ';' 
		{$$ = mknode("RECURSIVE_DECLARATION", $1, $2, 0, $1->type); }
	;

builtin_functions
	: if_block { $$ = mknode("if_block", $1, NULL, 0,UNTYPED); }
	| loop_functions { $$ = mknode("loop_functions", $1, NULL,0,UNTYPED); }
	;

loop_functions
	: for_block { $$ = mknode("for_block", $1, NULL, 0,UNTYPED); }
	| do_while_block { $$ = mknode("do_while_block", $1, NULL, 0,UNTYPED); }
	| while_block { $$ = mknode("while_block", $1, NULL, 0,UNTYPED); }
	;

if_block
	: IF lp boolean_expr rp line_statement  else_block 
		{ $$ = mknode("(IF", mknode("(", $2, $3, 0,UNTYPED), mknode(")", 
			mknode("(BLOCK",$5,mknode("}",NULL,NULL,1,UNTYPED),1,UNTYPED)		
			, $6, 1,UNTYPED), 1,UNTYPED); }
	| IF lp boolean_expr rp code_block else_block	
		{ $$ = mknode("(IF", mknode("(", $2, $3, 0,UNTYPED), mknode("_", $5, $6, 1,UNTYPED), 1,UNTYPED); }
	;

else_block
	: ELSE line_statement 
		{ $$ = mknode("BLOCK", $2, mknode("}", NULL, NULL, 0,UNTYPED), 0,UNTYPED); }
	| ELSE code_block 
		{ $$ = mknode("BLOCK", $2, NULL, 0,UNTYPED); }
	|  { $$ = mknode("epsilon", NULL, NULL, 0,UNTYPED); }
	;

while_block
	: WHILE lp boolean_expr rp line_statement { $$ = mknode("(WHILE", $3, mknode(" ",$5,mknode("}",NULL,NULL,1,UNTYPED),1,UNTYPED), 1,UNTYPED); }
	| WHILE lp boolean_expr rp code_block { $$ = mknode("WHILE", $3, $5, 1,UNTYPED); }
	;

do_while_block
	: DO line_statement  WHILE lp boolean_expr rp ';' { $$ = mknode("(DO_WHILE", mknode(" ",$2,mknode("}",NULL,NULL,1,UNTYPED),1,UNTYPED), $5, 0,UNTYPED); }
	| DO code_block  WHILE lp boolean_expr rp ';' { $$ = mknode("(DO_WHILE", $2, $5, 0,UNTYPED); }
	;

for_block
	: FOR lp for_block_inits ';' for_block_boolean_expr ';' for_block_inits_update rp
line_statement 
	{ $$ = mknode("FOR", 
		mknode("FOR", mknode("FOR", $3, $5, 0,UNTYPED), $7, 0,UNTYPED), 
			    mknode(" ",$9,mknode("}",NULL,NULL,1,UNTYPED),1,UNTYPED), 0,UNTYPED); 
	}
	| FOR lp for_block_inits ';' for_block_boolean_expr ';' for_block_inits_update rp code_block 		{ $$ = mknode("FOR", 
		mknode("FOR", mknode("FOR", $3, $5, 0,UNTYPED), $7, 0,UNTYPED), 
			    $9, 0,UNTYPED); }
	;

for_block_inits
	: for_block_single_init { $$ = mknode("FOR_INIT", $1, NULL,0,UNTYPED); }
	| for_block_single_init ',' for_block_inits { $$ = mknode("FOR_INIT", $1, $3, 0,UNTYPED); }
	;

for_block_single_init
	:ID ASSIGNMENT initializator { $$ = mknode("=", $1, $3, 1,UNTYPED); }
	;

for_block_inits_update
	: ID ASSIGNMENT initializator 
		{ $$ = mknode("=", $1, $3, 1,UNTYPED);  }
	| ID ASSIGNMENT initializator ',' for_block_inits_update 
		{ $$ = mknode(", ", mknode("=", $1, $3, 1,UNTYPED), $5, 1,UNTYPED);  }
	| ID inc_dec
		{ $$ = mknode($2->token, $1, NULL, 1,UNTYPED);  }
	| ID inc_dec ',' for_block_inits_update 
		{ $$ = mknode($2->token, $1, $4, 1,UNTYPED);  }
	;

for_block_boolean_expr
	: boolean_expr { $$ = mknode("for_block_boolean_expr", $1,  NULL,0,UNTYPED); }
	| boolean_expr ',' for_block_boolean_expr { $$ = mknode("for_block_boolean_expr", $1, $3, 0,UNTYPED); }
	;

expression
        : /*complex_expression
	|*/ boolean_expr { $$ = mknode("EXPRESSION", $1, NULL, 0,$1->type);  }
;


boolean_expr
		: boolean_expr AND boolean_expr_complex { $$ = mknode("&&", $1,  $3, 1,BOOLEAN_TYPE); }
		| boolean_expr OR boolean_expr_complex { $$ = mknode("||", $1,  $3, 1,BOOLEAN_TYPE); }
		| boolean_expr_complex { $$ = mknode("BOOLEAN_EXPR", $1, NULL, 0,UNTYPED); }
		| bool_unary_op boolean_expr_complex { $$ = mknode("!", NULL, $2, 1,BOOLEAN_TYPE); }
		;

boolean_expr_complex
		: boolean_expr_simple bool_binary_op boolean_expr_complex
			{ $$ = mknode($2->token, $1, $3, 1,$1->type); }
		| boolean_expr_simple 
			{ $$ = mknode("BOOLEAN_EXPR_COMPLEX", $1, NULL, 0,$1->type); }
		;


boolean_expr_simple
		: complex_expression { $$ = mknode("complex_expression", $1, NULL,1,$1->type); }
		| other  { $$ = mknode("OTHER", $1, NULL,0,UNTYPED); }
		;

bool_binary_op
		: EQUAL 	{ $$ = mknode($1, NULL,  NULL,1,UNTYPED); }
		| NOT_EQUAL 	{ $$ = mknode($1, NULL,  NULL,1,UNTYPED); }
		| LESS_THEN 	{ $$ = mknode($1, NULL,  NULL,1,UNTYPED); }
		| LESS_EQUAL 	{ $$ = mknode($1, NULL,  NULL,1,UNTYPED); }
		| GREAT_THEN 	{ $$ = mknode($1, NULL,  NULL,1,UNTYPED); }
		| GREAT_EQUAL	{ $$ = mknode($1, NULL,  NULL,1,UNTYPED); }
		;

bool_unary_op
		: NOT { $$ = mknode($1, NULL, NULL,1,UNTYPED); }
		;




function_call
	: ID lp rp 
		{ $$ = mknode($1->token, NULL, NULL,1,$1->type); }
	| ID lp function_call_parameters_list rp 
		{ $$ = mknode($1->token, NULL, $3,1,$1->type); }
	;

function_call_parameters_list 
	: complex_expression 
		{ $$ = mknode("FUNC_PARAM", $1, NULL, 1,$1->type); }
	| complex_expression ',' function_call_parameters_list
		{ $$ = mknode("FUNC_PARAM", $1, $3, 1,$1->type); }
	;
	

list_of_declarators
	: declarator_initialization 
		{ $$ = mknode("DECLARATION_INIT", $1, NULL, 0,UNTYPED); }
	| declarator_initialization ',' list_of_declarators 
		{ $$ = mknode($1->token, $1, $3, 0,$1->type); }
	;

declarator_initialization
	: declarator ASSIGNMENT initializator 
		{ $$ = mknode("DECL_INIT", $1, $3, 1,$3->type); }
	| declarator 
		{ $$ = mknode("DECL", $1, NULL, 0,UNTYPED); }
	;


initializator
	: expression { $$ = mknode("INIT", $1, NULL,0,$1->type); }
	;



complex_expression
	: basic_expression 
		{ $$ = mknode("complex_expression", $1,  NULL,0,$1->type); }
	| basic_expression operator complex_expression 
		{
            $$ = mknode("complex_expression", $1, $3, 1, $2->type);

             }
	| operator complex_expression 
		{ $$ = mknode("complex_expression", NULL, $2, 1,$2->type); }
	
	;

basic_expression
	: function_call 
		{ $$ = mknode("function_call", $1,  NULL,0,UNTYPED); }
	| terminal_const_values
		{ $$ = mknode($1->token, $1, NULL,0,$1->type); }
	| ID '[' integer ']' 
		{ $$ = mknode("EXPR_ID[]", mknode($1->token,NULL,mknode("[",mknode($3->token,NULL,NULL,1,UNTYPED),NULL,1,UNTYPED),0,UNTYPED),
			mknode("]",NULL,NULL,1,UNTYPED),1,UNTYPED);
		 } 
	| ID 
		{ $$ = mknode("EXPR_ID", $1, NULL, 1,UNTYPED); }
	| '|' ID '|' 
		{ $$ = mknode("|ID|", $2, NULL,0,UNTYPED); }
	| lp boolean_expr rp 
		{ $$ = mknode("SIMPLE_EXPRESSION", NULL, $2, 0,UNTYPED); }
	| bitwise_operators  basic_expression 
		{ $$ = mknode("bitwise_operator", $1, $2, 0,UNTYPED); } 
	;
 
integer
	: INT_CONSTANT_VALUE { $$ = mknode(yytext,NULL,NULL,1,INT_TYPE);};

/*
parameters_list
	: complex_expression { $$ = mknode("PARAM_LIST", $1,  NULL,0,UNTYPED); }
	| type complex_expression { $$ = mknode("PARAM_LIST", $1, $2, 1,UNTYPED); }
	| complex_expression ',' parameters_list 
		{ $$ = mknode("PARAM_LIST", $1, $3, 0,UNTYPED); }
	| type complex_expression ',' parameters_list 
		{ $$ = mknode("PARAM_LIST", 
				mknode("PARAM_LIST", $1, $2, 0,UNTYPED), $4, 0,UNTYPED); }
	;
*/
terminal_const_values
	: INT_CONSTANT_VALUE { $$ = mknode(yytext, NULL, NULL,  1,INT_TYPE);}
	| BOOL_CONSTANT_VALUE { $$ = mknode(yytext, NULL, NULL, 1,BOOLEAN_TYPE);}
	| BIN_CONSTANT_VALUE { $$ = mknode(yytext, NULL, NULL, 1,BIN_TYPE);}
	| OCT_CONSTANT_VALUE { $$ = mknode(yytext, NULL, NULL, 1,OCT_TYPE);}
	| HEX_CONSTANT_VALUE { $$ = mknode(yytext, NULL, NULL, 1,HEX_TYPE);}
	| literals { $$ = mknode($1->token, $1, NULL, 0,$1->type); }
	;

literals
	: CHAR_LITERAL { $$ = mknode(yytext, NULL, NULL, 1,CHAR_TYPE); }
	| STRING_VALUE { $$ = mknode(yytext, NULL, NULL, 1,STRING_TYPE);}
	;


declarator
	: ID { $$ = mknode("ID", $1, NULL, 0,UNTYPED); }
	| declarator '[' ']' 
		{ $$ = mknode("ARRAY", $1, NULL,0,UNTYPED); }
	| declarator '[' array_size ']'  
		{ $$ = mknode("ID-ARRAY[size]", $1,  $3, 0,UNTYPED); }
	| bitwise_operators ID 
		{ $$ = mknode("BIT_OP", $1,  $2, 0,UNTYPED); }
	;

params_types_list
	: type { $$ = mknode($1->token, $1, NULL,0,$1->type); }
	| type ',' params_types_list  { $$ = mknode("TYPE", $1, $3, 0,$1->type); }
	| type ID { $$ = mknode("TYPE", $1, $2, 0,$1->type); }
	| type ID ',' params_types_list
		{ $$ = mknode($1->token, mknode("TYPE", $1, $2, 0,UNTYPED),$4, 0,$1->type); }
	;
	


array_size
	: array_size ',' INT_CONSTANT_VALUE 
		{ $$ = mknode("ARRAY_SIZE", $1, mknode(yytext, NULL, NULL,  1,UNTYPED), 1,UNTYPED); }
	| complex_expression 
		{ $$ = mknode("ARRAY_SIZE", $1, NULL,0,UNTYPED); }
	;


type
	: STRING { $$ = mknode($1, NULL, NULL, 1,STRING_TYPE); }
	| BOOLEAN { $$ = mknode($1, NULL, NULL, 1,BOOLEAN_TYPE);}
	| CHAR { $$ = mknode($1, NULL, NULL, 1,CHAR_TYPE);}
	| INT { $$ = mknode($1, NULL, NULL, 1,INT_TYPE); }
	| INTP { $$ = mknode($1, NULL, NULL, 1,INTP_TYPE);}
	| CHARP { $$ = mknode($1, NULL, NULL, 1,CHARP_TYPE); }
	| VOID { $$ = mknode($1, NULL, NULL, 1,VOID_TYPE); }
	;


operator
	: MINUS_OP { $$ = mknode($1, NULL, NULL, 1,INT_TYPE); }
	| PLUS_OP { $$ = mknode($1, NULL, NULL, 1,INT_TYPE); }
	| DIVISION_OP { $$ = mknode($1, NULL, NULL, 1,INT_TYPE); }
	| MULT_OP { $$ = mknode($1, NULL, NULL, 1,INT_TYPE); }
	;

bitwise_operators
	: BITWISE_AND { $$ = mknode($1, NULL, NULL, 1,UNTYPED); }
	| BITWISE_XOR { $$ = mknode($1, NULL, NULL, 1,UNTYPED); }
	;



other
	: RETURN { $$ = mknode($1, NULL, NULL, 1,UNTYPED); }
	| _NULL  { $$ = mknode($1, NULL, NULL, 1,UNTYPED); }
	;

lp
	: LP  		{ $$ = mknode($1, NULL, NULL, 1,UNTYPED); }
	;
rp
	: RP		{ $$ = mknode($1, NULL, NULL, 1,UNTYPED); }
	;

ID
	: IDENTIFIER { $$ = mknode($1, NULL, NULL,1,ID_TYPE); }
	| MAIN	{ $$ = mknode($1, NULL, NULL,1,UNTYPED); }
	;
inc_dec
	: INCR { $$ = mknode($1, NULL, NULL,1,UNTYPED); }
	| DECR { $$ = mknode($1, NULL, NULL,1,UNTYPED); }
%%
#include "lex.yy.c"

int main()
	{yydebug=1; return yyparse(); }


node* mknode(char* token, node* left, node* right, int printHeader, Type type) {
	node* newNode = (node *) malloc (sizeof(node));
	newNode->token = strdup(token);
	newNode->left = left;
	newNode->right = right;
	newNode->printHeader = printHeader;
	newNode->type = type;
	return newNode;
}

