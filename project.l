
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

{LETTER}({LETTER}|{DIG}|[_])*  return IDENTIFIER; 



"\""([\\\?!.,/@#$%^&*+=-_<>`~]|{LETTER}|{DIG}|{WHITESPACE})*"\""  return STRING_VALUE;
"\'"([\\\ ?!.,/@#$%^&*\n+=-_<>`~]|{LETTER}|{DIG})"\'"	return CHAR_LITERAL; /* check if whitespace allowed*/

'&'{HEXPREF}{HEX}+	return POINTER_ADDRESS;


[;,\|\(\)\{\}\[\]]	return yytext[0]; 

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
.					{  printf("unknown token : %s\n",yytext);/* ignore bad symbols and new line */ };



%%
int yywrap(void)
{
    return 1;
}

static void comment_check()
{
    int current_character;

    while ((current_character = input()) != 0){ /* if have chars in input stream, not null */

		if (current_character == '*')		/* find comment block closing template */
		{		
		    while ((current_character = input()) == '*'); /* ignote more than one '*' character */
		        
		    if (current_character == '/')		/* comment block closed correctly */
		        return;

		    if (current_character == 0)			/* if detected null character */
			break;
			
		}

	}
yyerror("comment not closed properly !");

}

void yyerror(const char *s)
{
	fflush(stdout);
	printf("At line %d %s \n", yylineno, s);
}
