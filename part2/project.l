
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


extern void yyerror(const char *);
static void comment_check(void);

%}

%option yylineno

%%

boolean { yylval.string = strdup(yytext);	return BOOLEAN;};
char    { yylval.string = strdup(yytext);	return CHAR;};
void    { yylval.string = strdup(yytext);	return VOID;};
int     { yylval.string = strdup(yytext);	return INT;};
string  { yylval.string = strdup(yytext);	return STRING;};
intp    { yylval.string = strdup(yytext);	return INTP;};
charp   { yylval.string = strdup(yytext);	return CHARP;};
main    { yylval.string = strdup(yytext);	return MAIN;};


if return IF;
else return ELSE;
do return DO;
while return WHILE;
for return FOR;

return { yylval.string = strdup(yytext); return RETURN;}
null   { yylval.string = strdup(yytext); return _NULL;}

true|false 		{ yylval.string = strdup(yytext); return BOOL_CONSTANT_VALUE; };
{BIN}+"b"    		{ yylval.string = strdup(yytext); return BIN_CONSTANT_VALUE;};
{DIGWZ}{DIG}*|0 	{ yylval.integer = atoi(yytext);  return INT_CONSTANT_VALUE;};
'0'{OCT}*    		{ yylval.string = strdup(yytext); return OCT_CONSTANT_VALUE;};
{HEXPREF}{HEX}+		{ yylval.string = strdup(yytext); return HEX_CONSTANT_VALUE;};

{LETTER}({LETTER}|{DIG}|[_])*  {yylval.string = strdup(yytext); return IDENTIFIER; }



"\""([\\\?!.,/@#$%^&*+=-_<>`~]|{LETTER}|{DIG}|{WHITESPACE})*"\"" {yylval.string = strdup(yytext); return STRING_VALUE;};
"\'"([\\\ ?!.,/@#$%^&*\n+=-_<>`~]|{LETTER}|{DIG})"\'"	{yylval.string = strdup(yytext); return CHAR_LITERAL;};

'&'{HEXPREF}{HEX}+	return POINTER_ADDRESS;


";"|","|"|"|"{"|"}"|"["|"]" return yytext[0];
"("	{ yylval.string = strdup(yytext); return LP; };
")"	{ yylval.string = strdup(yytext); return RP; };


"&&" {yylval.string = strdup(yytext); return AND; };
"/" {yylval.string = strdup(yytext);  return DIVISION_OP;};
"==" {yylval.string = strdup(yytext); return EQUAL;};
"=" {yylval.string = strdup(yytext);  return ASSIGNMENT;};
">=" {yylval.string = strdup(yytext); return GREAT_EQUAL;};
"<=" {yylval.string = strdup(yytext); return LESS_EQUAL;};
">" {yylval.string = strdup(yytext);  return GREAT_THEN;};
"<" {yylval.string = strdup(yytext);  return LESS_THEN;};
"!=" {yylval.string = strdup(yytext); return NOT_EQUAL;};
"!" {yylval.string = strdup(yytext);  return NOT;};
"||" {yylval.string = strdup(yytext); return OR;};
"++" {yylval.string = strdup(yytext); return INCR;};
"+" {yylval.string = strdup(yytext);  return PLUS_OP;};
"*" {yylval.string = strdup(yytext);  return MULT_OP;};
"&" {yylval.string = strdup(yytext);  return BITWISE_AND;};
"^" {yylval.string = strdup(yytext);  return BITWISE_XOR;};
"--" {yylval.string = strdup(yytext); return DECR;};
"-" {yylval.string = strdup(yytext);  return MINUS_OP;};


"/*"                                    { comment_check(); }
"//".*                                  {  }



{WHITESPACE}+				{ /* ignore spaces */ };
.					{  printf("Unknown token "); 
						yyerror(yytext); /* detect unknown tokens */ };



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
