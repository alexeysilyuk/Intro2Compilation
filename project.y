%start head_parser
%token BOOLEAN
%token CHAR
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
%token NULL
%%
head_parser
	:declaration
	|head_parser declaration 
	;

head_declaration
	:declaration
	|function_define
	;

declaration
	:

type
	:BOOLEAN {printf("boolean");}
	|CHAR {printf("char");}
	|VOID {printf("void");}
	|INT  {printf("int");}
	|STRING {printf("string");} 
	|INTP {printf("intp");}   
	|CHARP{printf("charp");}
	;
function   
	:IF   {printf("if");}   
	|ELSE {printf("else");}   
	|WHILE{printf("while");}   
	|DO   {printf("do");}   
	|FOR  {printf("for");}
	;

others
	:RETURN {printf("return");}   
	|NULL {printf("null");}
	;
%%

#include "lex.yy.c"
void yyerror(const char *s)
{
	fflush(stdout);
	fprintf(stderr, "*** %s\n", s);
}

int main(){return yyparse();}
