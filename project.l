/* DECLARATIONS */
DIG   [0-9]
DIGWZ [1-9]
OCT   [0-7]
BIN   [01]
HEX   [a-fA-F0-9]
HEXPREF 0[xX]
LETTER [a-zA-Z]
VARPREF ([a-zA-Z_])

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


&& return AND;
/ return RIGHT_SLASH;
= return ASSIGNMENT;
== return COMPARATION;
> return GREAT;
>= return GREAT_EQUAL;
< return LESS;
<= return LESS_EQUAL;
- return MINUS;
! return NOT;
!= return NOT_EQUAL;
|| return OR;
+ return PLUS;
* return MULT;
& return BITWISE_AND;
^ return BITWISE_XOR



true|false 		return CONSTANT_VALUE;
"'"{LETTER}"'" 		return CONSTANT_VALUE;
{BIN}+"b"    		return CONSTANT_VALUE;
'0'{OCT}*    		return CONSTANT_VALUE;
{DIGWZ}{DIG}*		return CONSTANT_VALUE;
{HEXPREF}{HEX}+		return CONSTANT_VALUE;

{VARPREF}({LETTER}|{DIG}|[_])* return ID;


([ \?!.,/@#$%^&*\n+=-_<>`~]|{LETTER}|{DIG})* return STRING_VALUE;





. return yytext[0];




%%
