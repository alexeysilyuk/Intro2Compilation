
DIG   [0-9]
DIGWZ [1-9]
OCT   [0-7]
BIN   [01]
HEX   [a-fA-F0-9]
HEXPREF 0[xX]
LETTER [a-zA-Z]
WHITESPACE [ \t\n\r]

%{
#include <stdio.h>
#include "y.tab.h"


extern void yyerror(const char *);  /* prints grammar violation message */
static void comment_check(void);

%}

%option yylineno

%%

boolean return BOOLEAN_TYPE;
char return CHAR_TYPE;
void return VOID;
int return INT;
string return STRING;
intp return INTP;
charp return CHARP;
main return MAIN;


if return IF;
else return ELSE;
do return DO;
while return WHILE;
for return FOR;


return return RETURN;
null return _NULL;




true|false 		{ return BOOL_CONSTANT_VALUE;}
{BIN}+"b"    		{ return BIN_CONSTANT_VALUE;}
{DIGWZ}{DIG}*|0 	{ return INT_CONSTANT_VALUE;}
'0'{OCT}*    		{ return OCT_CONSTANT_VALUE;}
{HEXPREF}{HEX}+		{ return HEX_CONSTANT_VALUE;}

{LETTER}({LETTER}|{DIG}|[_])*  {/*yylval.string = strdup(yytext);*/ return IDENTIFIER; }



"\""([\\\?!.,/@#$%^&*+=-_<>`~]|{LETTER}|{DIG}|{WHITESPACE})*"\""  return STRING_VALUE;
"\'"([\\\ ?!.,/@#$%^&*\n+=-_<>`~]|{LETTER}|{DIG})"\'"	return CHAR_LITERAL; /* check if whitespace allowed*/

'&'{HEXPREF}{HEX}+	return POINTER_ADDRESS;


[;,\|\(\)\{\}\[\]]	{ /*yylval.string = strdup(yytext[0]);*/ return yytext[0]; }

"&&" return AND;
"/" return DIVISION_OP;
"==" return EQUAL;
"=" return ASSIGNMENT;
">=" return GREAT_EQUAL;
"<=" return LESS_EQUAL;
">" return GREAT_THEN;
"<" return LESS_THEN;
"!=" return NOT_EQUAL;
"!" return NOT;
"||" return OR;
"+" return PLUS_OP;
"*" return MULT_OP;
"&" return BITWISE_AND;
"^" return BITWISE_XOR;
"-" return MINUS_OP;


"/*"                                    { comment_check(); }
"//".*                                  {  }



{WHITESPACE}+				{ /* ignore spaces */ };
.					{  printf("Unknown token "); yyerror(yytext);/* ignore bad symbols and new line */ };



%%
int yywrap(void)
{
    return 1;
}



void comment_check()
{
char c=input();
while(c != EOF ){
	
	if(c=='*'){
		while((c=input())=='*');
		if(c=='/')
			{
			c=input();
			return;
		}
	}	


	c=input();
}
yyerror("Comment block not closed");
}

void yyerror(const char *s)
{
	fflush(stdout);
	printf("\'%s\' at line %d  \n",s, yylineno);
	exit(1);
}
