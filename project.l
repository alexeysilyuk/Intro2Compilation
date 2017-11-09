/* DECLARATIONS */
DIG   [0-9]
DIGWZ [1-9]
OCT   [0-7]
BIN   [01]
HEX   [a-fA-F0-9]
HEXPREF 0[xX]
LETTER [a-zA-Z]
VARPREF [a-zA-Z_]
WHITESPACE [ \t\n]

%{
#include <stdio.h>
#include "y.tab.h"

extern void yyerror(const char *);

static void comment(void);

%}
%%

boolean return BOOLEAN_TYPE;
char return CHAR_TYPE'
void return VOID;
int return INT;
string return STRING;
intp return INTP;
charp return CHARP;


if return IF;
else return ELSE;
while return WHILE;
do return DO;
for return FOR;


return return RETURN;
null return NULL;


"&&" return AND;
"/" return RIGHT_SLASH;
"=" return ASSIGNMENT;
"==" return COMPARATION;
">" return GREAT_THEN;
">=" return GREAT_EQUAL;
"<" return LESS_THEN;
"<=" return LESS_EQUAL;
"-" return MINUS;
"!" return NOT;
"!=" return NOT_EQUAL;
"||" return OR;
"+" return PLUS;
"*" return MULT;
"&" return BITWISE_AND;
"^" return BITWISE_XOR



true|false 		return CONSTANT_VALUE;
"\'"{LETTER}"\'" 	return CONSTANT_VALUE;
{BIN}+"b"    		return CONSTANT_VALUE;
'0'{OCT}*    		return CONSTANT_VALUE;
{DIGWZ}{DIG}*		return CONSTANT_VALUE;
{HEXPREF}{HEX}+		return CONSTANT_VALUE;

{VARPREF}({LETTER}|{DIG}|[_])* return IDENTIFIER;


([\\\ ?!.,/@#$%^&*\n+=-_<>`~]|{LETTER}|{DIG})* return STRING_VALUE;

'&'{HEXPREF}{HEX}+	return POINTER;


";" 	return ';';
"," 	return ',';
"|" 	return '|';
"("	return '('; 
")"	return ')'; 
"{"	return '{'; 
"}"	return '}'; 
"["	return '['; 
"]"	return ']'; 


"/*"                                    { comment(); }
"//".*                                  { /* ignore text after // */ }


{WHITESPACE}+				{ /* ignore spaces */ }
.					{ /* ignore bad symbols */ }



%%

static void comment()
{
    int current_char;

    while ((current_char = input()) != 0)	/* if have chars in input stream, not null */
	{
      	  if (current_char == '*') 		/* find comment block closing template */
	  {
     	    while ((current_char = input()) == '*'); /* ignote more than one '*' character */

            if (current_char == '/')		/* comment block closed correctly */
                return;

            if (current_char == 0)		/* if detected null character */
                break;
          }
	}
	
    yyerror("comment not closed properly !");
}
