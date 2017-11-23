#ifndef lint
static const char yysccsid[] = "@(#)yaccpar	1.9 (Berkeley) 02/21/93";
#endif

#define YYBYACC 1
#define YYMAJOR 1
#define YYMINOR 9
#define YYPATCH 20140101

#define YYEMPTY        (-1)
#define yyclearin      (yychar = YYEMPTY)
#define yyerrok        (yyerrflag = 0)
#define YYRECOVERING() (yyerrflag != 0)

#define YYPREFIX "yy"

#define YYPURE 0

#line 3 "project.y"
	#define YYPRINT(file, type, value) fprint(file, "%d", value);

#line 22 "y.tab.c"

#ifndef YYSTYPE
typedef int YYSTYPE;
#endif

/* compatibility with bison */
#ifdef YYPARSE_PARAM
/* compatibility with FreeBSD */
# ifdef YYPARSE_PARAM_TYPE
#  define YYPARSE_DECL() yyparse(YYPARSE_PARAM_TYPE YYPARSE_PARAM)
# else
#  define YYPARSE_DECL() yyparse(void *YYPARSE_PARAM)
# endif
#else
# define YYPARSE_DECL() yyparse(void)
#endif

/* Parameters sent to lex. */
#ifdef YYLEX_PARAM
# define YYLEX_DECL() yylex(void *YYLEX_PARAM)
# define YYLEX yylex(YYLEX_PARAM)
#else
# define YYLEX_DECL() yylex(void)
# define YYLEX yylex()
#endif

/* Parameters sent to yyerror. */
#ifndef YYERROR_DECL
#define YYERROR_DECL() yyerror(const char *s)
#endif
#ifndef YYERROR_CALL
#define YYERROR_CALL(msg) yyerror(msg)
#endif

extern int YYPARSE_DECL();

#define MINUS_OP 257
#define PLUS_OP 258
#define DIVISION_OP 259
#define MULT_OP 260
#define BOOLEAN_TYPE 261
#define CHAR_TYPE 262
#define VOID 263
#define INT 264
#define STRING 265
#define INTP 266
#define CHARP 267
#define IF 268
#define ELSE 269
#define WHILE 270
#define DO 271
#define FOR 272
#define RETURN 273
#define _NULL 274
#define AND 275
#define ASSIGNMENT 276
#define EQUAL 277
#define GREAT_THEN 278
#define GREAT_EQUAL 279
#define LESS_THEN 280
#define LESS_EQUAL 281
#define NOT 282
#define NOT_EQUAL 283
#define OR 284
#define BITWISE_AND 285
#define BITWISE_XOR 286
#define IDENTIFIER 287
#define STRING_VALUE 288
#define CHAR_LITERAL 289
#define POINTER_ADDRESS 290
#define INT_CONSTANT_VALUE 291
#define BOOL_CONSTANT_VALUE 292
#define BIN_CONSTANT_VALUE 293
#define OCT_CONSTANT_VALUE 294
#define HEX_CONSTANT_VALUE 295
#define user_function 296
#define YYERRCODE 256
static const short yylhs[] = {                           -1,
    0,    1,    1,    2,    2,    5,    3,    3,    3,    3,
    4,    4,   10,   10,   12,   12,   12,   11,   11,   11,
   11,   17,   17,   15,   15,   14,   14,   13,   13,   18,
   18,   21,   20,   20,   19,   19,   16,   16,   16,   23,
   23,   23,   23,    7,    7,    8,    8,   22,   22,   22,
   22,    9,    9,    9,   26,   26,   26,   26,   26,   28,
   28,   30,   30,   29,   29,   29,   29,   29,   29,   31,
   31,   25,   25,   25,   25,   25,   32,   32,   32,   32,
   33,   33,    6,    6,    6,    6,    6,    6,    6,   27,
   27,   27,   27,   24,   24,   24,   24,   24,   24,   24,
   34,   34,
};
static const short yylen[] = {                            2,
    1,    1,    2,    1,    1,    2,    2,    1,    1,    2,
    1,    1,    1,    1,    1,    1,    1,    5,    7,    6,
    8,    2,    4,    5,    7,    7,    9,    9,   11,    1,
    3,    3,    3,    5,    1,    3,    1,    3,    3,    1,
    3,    5,    6,    1,    3,    3,    1,    2,    2,    1,
    1,    3,    1,    3,    1,    1,    1,    4,    3,    3,
    4,    1,    3,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    3,    4,    3,    4,    1,    3,    2,    4,
    3,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,
};
static const short yydefred[] = {                         0,
   83,   84,   85,   86,   89,   87,   88,    0,    0,    0,
    0,    0,   72,   12,    0,    1,    0,    0,    5,    8,
    0,    9,   11,   13,   14,   15,   16,   17,    0,    0,
    0,    0,    0,    0,    0,   71,   70,   64,   65,   66,
   67,   68,    0,    0,   10,    0,   55,   56,   69,    3,
    7,    0,   44,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,   90,   91,   92,   93,    0,    0,   50,    0,    0,
   51,   46,   73,    0,    0,   75,   82,    0,    0,    0,
  101,   94,   97,   95,   98,   96,   99,  102,    0,  100,
    0,    0,    0,    0,    0,    0,    0,    0,    0,   60,
    0,    0,    0,   52,   59,   54,   45,   48,   49,   79,
   74,    0,    0,   76,    0,    0,   41,    0,    0,   38,
   39,    0,    0,    0,    0,   32,    0,    0,   31,    0,
   61,   58,    0,   81,    0,    0,    0,    0,   20,    0,
    0,    0,    0,    0,   63,   80,    0,   42,    0,    0,
    0,   25,    0,   26,   36,    0,    0,   43,   21,    0,
    0,    0,    0,   23,   27,    0,    0,    0,    0,    0,
   34,   29,
};
static const short yydgoto[] = {                         15,
   16,   17,   18,   19,   20,   21,   52,   22,   59,   23,
   24,   25,   26,   27,   28,  137,  149,   66,  138,  167,
   67,   82,   61,   99,   29,   46,   76,   47,   48,  112,
   49,   85,   88,  100,
};
static const short yysindex[] = {                       300,
    0,    0,    0,    0,    0,    0,    0,  -23,  -10, -114,
   -4,  204,    0,    0,    0,    0,  300,  -20,    0,    0,
 -246,    0,    0,    0,    0,    0,    0,    0,  -37,  168,
  168,  300,  -55, -243,  -29,    0,    0,    0,    0,    0,
    0,    0,  204, -240,    0, -236,    0,    0,    0,    0,
    0,    5,    0,  -40,  -39,  322,   10,  204, -173,   11,
 -255,   15,  -74,   18, -221,    6,   20,  195, -232,   25,
  -57,    0,    0,    0,    0,  204, -246,    0, -218, -216,
    0,    0,    0, -211,  -13,    0,    0,  -30,  204,  133,
    0,    0,    0,    0,    0,    0,    0,    0,  168,    0,
  -98,  168,  168,  -85, -193,  168,  -40,  168, -243,    0,
   35,   39,   -8,    0,    0,    0,    0,    0,    0,    0,
    0,  256, -208,    0, -173,  168,    0,  300,  -53,    0,
    0,  300,  -20,   47,   48,    0,   44,   32,    0,  204,
    0,    0, -195,    0,  168,   52,  -28,  -70,    0,  -27,
  168,   40,  168, -192,    0,    0,   59,    0, -168,  300,
  -20,    0,   68,    0,    0, -164,   74,    0,    0,  -11,
   57,  -40,  282,    0,    0,   75,  300,  -20, -192,   -7,
    0,    0,
};
static const short yyrindex[] = {                         0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    8,  113,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,   73,    0,
    0,    0,    0,    0,    1,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,   37,    0,    0,    0,    0,
    0,   86,    0,    0,    0,    0,    0,    0,  -26,    0,
  -25,    0,    0,    0,    0,    0,   61,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,   -9,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
   81,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,  131,    0,
    0,    0,  158,    0,    0,    0,   65,    0,    0,    0,
    0,    0,   -1,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,  171,    0,
  207,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,   84,    0,  243,    0,    0,
    0,    0,
};
static const short yygindex[] = {                         0,
   -5,    0,   36,    0,    0,  -48,    0,  -16,   14,    0,
    0,    0,    0,    0,    0,  434,  -31,   26,  -24,  -45,
    0,  -97,    0,  -77,    0,    0,    0,    0,    0,   -2,
    0,    0,    0,    0,
};
#define YYTABLESIZE 617
static const short yytable[] = {                         43,
   57,   83,   55,   51,   53,   51,   84,    2,   32,  136,
   68,   50,  126,  123,   40,   37,   30,   40,   37,  102,
   72,   73,   74,   75,  128,   45,   63,  121,  103,   31,
  122,   77,   40,   37,   77,   34,   53,  132,   51,   78,
   13,   57,   78,   65,   57,   33,   71,  145,   77,   89,
  105,  101,  160,   56,  107,  104,   70,  106,  113,   57,
  117,   69,  124,  109,  108,  114,  115,   81,  118,   87,
  119,   90,   47,  143,  176,  120,  134,   53,  140,  141,
   53,  111,  144,   44,  142,    6,  151,  153,  152,  116,
  154,  156,  158,   57,  166,   53,  159,  162,  164,  168,
  148,   91,  125,   92,   93,   94,   95,   96,  171,   97,
   98,  172,    4,  174,  173,  175,   47,  182,  179,   30,
   81,   62,  147,   35,   33,   57,  150,  169,  165,   53,
   18,   47,    2,  181,  139,    0,  129,  155,    0,  133,
    0,    0,    0,    0,    6,    0,    1,    2,    3,    4,
    5,    6,    7,  111,  170,    0,    0,   24,   12,    0,
    0,   53,    1,    2,    3,    4,    5,    6,    7,    0,
   19,  180,   13,  114,   12,    1,    2,    3,    4,    5,
    6,    7,    0,  161,    0,   81,    0,   12,   13,    0,
    1,    2,    3,    4,    5,    6,    7,   47,    0,    0,
    0,   13,   12,    0,    0,    0,   22,   58,  178,    0,
    6,    0,    0,    0,   64,  148,   13,    0,    0,    0,
    0,    1,    2,    3,    4,    5,    6,    7,    0,    0,
    0,    0,    0,   78,   43,  110,    0,    4,   54,    0,
    0,    0,   28,   43,   79,   80,   35,   36,   37,    0,
   38,   39,   40,   41,   42,   18,    0,   57,   57,   57,
   57,   57,   57,   57,   57,   57,   57,   57,   57,   57,
   57,   57,   57,   57,    0,   57,    0,   57,   57,   57,
   57,   57,   24,   57,   57,    0,    0,   57,    0,    0,
    0,   44,    0,    0,    0,   19,   57,   53,   53,   53,
   53,   53,   53,   53,   53,   53,   53,   53,   53,   53,
    0,   53,    0,   53,   53,   53,   53,   53,   44,   53,
   53,    0,    0,   53,    0,    0,    0,   44,    0,    0,
    0,   22,   53,   47,   47,   47,   47,   47,   47,   47,
   47,   47,   47,   47,   47,   47,    6,    6,    6,    6,
    6,    6,    6,    6,    6,    6,    6,    6,    6,   47,
    0,   43,    0,    0,    0,    0,    0,   28,   47,    0,
    0,    0,    6,    4,    4,    4,    4,    4,    4,    4,
    4,    6,    4,    4,    4,    4,    0,    0,    0,    0,
    0,   18,   18,   18,   18,   18,   18,   18,   18,    4,
   18,   18,   18,   18,  177,    0,    0,   91,    4,   92,
   93,   94,   95,   96,   86,   97,   98,   18,   24,   24,
   24,   24,   24,   24,   24,   24,   18,   24,   24,   24,
   24,   19,   19,   19,   19,   19,   19,   19,   19,    0,
   19,   19,   19,   19,   24,   44,    0,    0,    0,   57,
    0,    0,    0,   24,   35,   36,   37,   19,   38,   39,
   40,   41,   42,   60,   62,    0,   19,   22,   22,   22,
   22,   22,   22,   22,   22,    0,   22,   22,   22,   22,
    0,   35,   36,   37,    0,   38,   39,   40,   41,   42,
   35,   36,   37,   22,   38,   39,   40,   41,   42,    0,
    0,    0,   22,   28,   28,   28,   28,   28,   28,   28,
   28,    0,   28,   28,   28,   28,    1,    2,    3,    4,
    5,    6,    7,    0,    0,    0,    0,    0,    0,   28,
    0,    0,  127,    0,    0,  130,  131,    0,   28,  135,
    0,    0,    1,    2,    3,    4,    5,    6,    7,    0,
    0,    0,    0,    0,   12,    0,    0,    0,    0,  146,
    1,    2,    3,    4,    5,    6,    7,    8,   13,    9,
   10,   11,   12,    0,    0,    0,    0,    0,  157,    0,
    0,    0,    0,    0,  163,    0,   13,    0,    0,    0,
    0,    0,    0,    0,    0,   14,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,   35,   36,
   37,    0,   38,   39,   40,   41,   42,
};
static const short yycheck[] = {                         40,
    0,   41,   40,   59,   21,   59,   55,    0,  123,  107,
   40,   17,   90,   44,   41,   41,   40,   44,   44,  275,
  257,  258,  259,  260,  123,   12,   32,   41,  284,   40,
   44,   41,   59,   59,   44,   40,    0,  123,   59,   41,
  287,   41,   44,  287,   44,   10,  287,  125,   44,   40,
  125,   41,  123,   91,  276,   41,   43,   40,  291,   59,
   77,   91,   93,   44,   59,   41,  124,   54,  287,   56,
  287,   58,    0,  122,  172,  287,  270,   41,   44,   41,
   44,   68,  291,  124,   93,    0,   40,   44,   41,   76,
   59,  287,   41,   93,  287,   59,  125,  125,   59,   41,
  269,  275,   89,  277,  278,  279,  280,  281,   41,  283,
  284,  276,    0,  125,   41,   59,   44,  125,   44,   59,
  107,   41,  128,   59,   41,  125,  132,  159,  153,   93,
    0,   59,  125,  179,  109,   -1,  101,  140,   -1,  104,
   -1,   -1,   -1,   -1,   59,   -1,  261,  262,  263,  264,
  265,  266,  267,  140,  160,   -1,   -1,    0,  273,   -1,
   -1,  125,  261,  262,  263,  264,  265,  266,  267,   -1,
    0,  177,  287,   41,  273,  261,  262,  263,  264,  265,
  266,  267,   -1,  148,   -1,  172,   -1,  273,  287,   -1,
  261,  262,  263,  264,  265,  266,  267,  125,   -1,   -1,
   -1,  287,  273,   -1,   -1,   -1,    0,   40,  173,   -1,
  125,   -1,   -1,   -1,  270,  269,  287,   -1,   -1,   -1,
   -1,  261,  262,  263,  264,  265,  266,  267,   -1,   -1,
   -1,   -1,   -1,  274,   40,   41,   -1,  125,  276,   -1,
   -1,   -1,    0,   40,  285,  286,  287,  288,  289,   -1,
  291,  292,  293,  294,  295,  125,   -1,  257,  258,  259,
  260,  261,  262,  263,  264,  265,  266,  267,  268,  269,
  270,  271,  272,  273,   -1,  275,   -1,  277,  278,  279,
  280,  281,  125,  283,  284,   -1,   -1,  287,   -1,   -1,
   -1,  124,   -1,   -1,   -1,  125,  296,  261,  262,  263,
  264,  265,  266,  267,  268,  269,  270,  271,  272,  273,
   -1,  275,   -1,  277,  278,  279,  280,  281,  124,  283,
  284,   -1,   -1,  287,   -1,   -1,   -1,  124,   -1,   -1,
   -1,  125,  296,  261,  262,  263,  264,  265,  266,  267,
  268,  269,  270,  271,  272,  273,  261,  262,  263,  264,
  265,  266,  267,  268,  269,  270,  271,  272,  273,  287,
   -1,   40,   -1,   -1,   -1,   -1,   -1,  125,  296,   -1,
   -1,   -1,  287,  261,  262,  263,  264,  265,  266,  267,
  268,  296,  270,  271,  272,  273,   -1,   -1,   -1,   -1,
   -1,  261,  262,  263,  264,  265,  266,  267,  268,  287,
  270,  271,  272,  273,  123,   -1,   -1,  275,  296,  277,
  278,  279,  280,  281,   93,  283,  284,  287,  261,  262,
  263,  264,  265,  266,  267,  268,  296,  270,  271,  272,
  273,  261,  262,  263,  264,  265,  266,  267,  268,   -1,
  270,  271,  272,  273,  287,  124,   -1,   -1,   -1,  282,
   -1,   -1,   -1,  296,  287,  288,  289,  287,  291,  292,
  293,  294,  295,   30,   31,   -1,  296,  261,  262,  263,
  264,  265,  266,  267,  268,   -1,  270,  271,  272,  273,
   -1,  287,  288,  289,   -1,  291,  292,  293,  294,  295,
  287,  288,  289,  287,  291,  292,  293,  294,  295,   -1,
   -1,   -1,  296,  261,  262,  263,  264,  265,  266,  267,
  268,   -1,  270,  271,  272,  273,  261,  262,  263,  264,
  265,  266,  267,   -1,   -1,   -1,   -1,   -1,   -1,  287,
   -1,   -1,   99,   -1,   -1,  102,  103,   -1,  296,  106,
   -1,   -1,  261,  262,  263,  264,  265,  266,  267,   -1,
   -1,   -1,   -1,   -1,  273,   -1,   -1,   -1,   -1,  126,
  261,  262,  263,  264,  265,  266,  267,  268,  287,  270,
  271,  272,  273,   -1,   -1,   -1,   -1,   -1,  145,   -1,
   -1,   -1,   -1,   -1,  151,   -1,  287,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,  296,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  287,  288,
  289,   -1,  291,  292,  293,  294,  295,
};
#define YYFINAL 15
#ifndef YYDEBUG
#define YYDEBUG 0
#endif
#define YYMAXTOKEN 296
#define YYTRANSLATE(a) ((a) > YYMAXTOKEN ? (YYMAXTOKEN + 1) : (a))
#if YYDEBUG
static const char *yyname[] = {

"end-of-file",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,"'('","')'",0,0,"','",0,0,0,0,0,0,0,0,0,0,0,0,0,0,"';'",0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"'['",0,"']'",0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"'{'","'|'","'}'",0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,"MINUS_OP","PLUS_OP","DIVISION_OP","MULT_OP","BOOLEAN_TYPE","CHAR_TYPE",
"VOID","INT","STRING","INTP","CHARP","IF","ELSE","WHILE","DO","FOR","RETURN",
"_NULL","AND","ASSIGNMENT","EQUAL","GREAT_THEN","GREAT_EQUAL","LESS_THEN",
"LESS_EQUAL","NOT","NOT_EQUAL","OR","BITWISE_AND","BITWISE_XOR","IDENTIFIER",
"STRING_VALUE","CHAR_LITERAL","POINTER_ADDRESS","INT_CONSTANT_VALUE",
"BOOL_CONSTANT_VALUE","BIN_CONSTANT_VALUE","OCT_CONSTANT_VALUE",
"HEX_CONSTANT_VALUE","user_function","illegal-symbol",
};
static const char *yyrule[] = {
"$accept : main",
"main : program",
"program : head_declaration",
"program : head_declaration program",
"head_declaration : line_statement",
"head_declaration : functions",
"declaration : type list_of_declarators",
"line_statement : line_statement ';'",
"line_statement : declaration",
"line_statement : declarator_initialization",
"line_statement : RETURN complex_expression",
"functions : builtin_functions",
"functions : user_function",
"builtin_functions : if_block",
"builtin_functions : loop_functions",
"loop_functions : for_block",
"loop_functions : do_while_block",
"loop_functions : while_block",
"if_block : IF '(' boolean_expr ')' line_statement",
"if_block : IF '(' boolean_expr ')' '{' program '}'",
"if_block : IF '(' boolean_expr ')' line_statement else_block",
"if_block : IF '(' boolean_expr ')' '{' program '}' else_block",
"else_block : ELSE line_statement",
"else_block : ELSE '{' program '}'",
"while_block : WHILE '(' boolean_expr ')' line_statement",
"while_block : WHILE '(' boolean_expr ')' '{' program '}'",
"do_while_block : DO line_statement WHILE '(' boolean_expr ')' ';'",
"do_while_block : DO '{' program '}' WHILE '(' boolean_expr ')' ';'",
"for_block : FOR '(' for_block_inits ';' for_block_boolean_expr ';' for_block_inits_update ')' line_statement",
"for_block : FOR '(' for_block_inits ';' for_block_boolean_expr ';' for_block_inits_update ')' '{' program '}'",
"for_block_inits : for_block_single_init",
"for_block_inits : for_block_single_init ',' for_block_inits",
"for_block_single_init : IDENTIFIER ASSIGNMENT initializator",
"for_block_inits_update : IDENTIFIER ASSIGNMENT initializator",
"for_block_inits_update : IDENTIFIER ASSIGNMENT initializator ',' for_block_inits_update",
"for_block_boolean_expr : boolean_expr",
"for_block_boolean_expr : boolean_expr ',' for_block_boolean_expr",
"boolean_expr : boolean_expr_simple",
"boolean_expr : boolean_expr_simple AND boolean_expr",
"boolean_expr : boolean_expr_simple OR boolean_expr",
"boolean_expr_simple : complex_expression",
"boolean_expr_simple : complex_expression boolean_operator boolean_expr",
"boolean_expr_simple : '(' complex_expression boolean_operator boolean_expr ')'",
"boolean_expr_simple : NOT '(' complex_expression boolean_operator boolean_expr ')'",
"list_of_declarators : declarator_initialization",
"list_of_declarators : list_of_declarators ',' declarator_initialization",
"declarator_initialization : declarator ASSIGNMENT initializator",
"declarator_initialization : declarator",
"initializator : BITWISE_AND IDENTIFIER",
"initializator : BITWISE_XOR IDENTIFIER",
"initializator : _NULL",
"initializator : complex_expression",
"complex_expression : '(' complex_expression ')'",
"complex_expression : basic_expression",
"complex_expression : basic_expression operator complex_expression",
"basic_expression : function_result",
"basic_expression : terminal_const_values",
"basic_expression : IDENTIFIER",
"basic_expression : IDENTIFIER '[' INT_CONSTANT_VALUE ']'",
"basic_expression : '|' IDENTIFIER '|'",
"function_result : IDENTIFIER '(' ')'",
"function_result : IDENTIFIER '(' parameters_list ')'",
"parameters_list : complex_expression",
"parameters_list : complex_expression ',' parameters_list",
"terminal_const_values : INT_CONSTANT_VALUE",
"terminal_const_values : BOOL_CONSTANT_VALUE",
"terminal_const_values : BIN_CONSTANT_VALUE",
"terminal_const_values : OCT_CONSTANT_VALUE",
"terminal_const_values : HEX_CONSTANT_VALUE",
"terminal_const_values : literals",
"literals : CHAR_LITERAL",
"literals : STRING_VALUE",
"declarator : IDENTIFIER",
"declarator : declarator '(' ')'",
"declarator : declarator '(' params_types_list ')'",
"declarator : declarator '[' ']'",
"declarator : declarator '[' array_size ']'",
"params_types_list : type",
"params_types_list : params_types_list ',' type",
"params_types_list : type IDENTIFIER",
"params_types_list : params_types_list ',' type IDENTIFIER",
"array_size : array_size ',' INT_CONSTANT_VALUE",
"array_size : complex_expression",
"type : BOOLEAN_TYPE",
"type : CHAR_TYPE",
"type : VOID",
"type : INT",
"type : INTP",
"type : CHARP",
"type : STRING",
"operator : MINUS_OP",
"operator : PLUS_OP",
"operator : DIVISION_OP",
"operator : MULT_OP",
"boolean_operator : EQUAL",
"boolean_operator : GREAT_EQUAL",
"boolean_operator : LESS_EQUAL",
"boolean_operator : GREAT_THEN",
"boolean_operator : LESS_THEN",
"boolean_operator : NOT_EQUAL",
"boolean_operator : OR_AND_DELIMITER",
"OR_AND_DELIMITER : AND",
"OR_AND_DELIMITER : OR",

};
#endif

int      yydebug;
int      yynerrs;

int      yyerrflag;
int      yychar;
YYSTYPE  yyval;
YYSTYPE  yylval;

/* define the initial stack-sizes */
#ifdef YYSTACKSIZE
#undef YYMAXDEPTH
#define YYMAXDEPTH  YYSTACKSIZE
#else
#ifdef YYMAXDEPTH
#define YYSTACKSIZE YYMAXDEPTH
#else
#define YYSTACKSIZE 10000
#define YYMAXDEPTH  10000
#endif
#endif

#define YYINITSTACKSIZE 200

typedef struct {
    unsigned stacksize;
    short    *s_base;
    short    *s_mark;
    short    *s_last;
    YYSTYPE  *l_base;
    YYSTYPE  *l_mark;
} YYSTACKDATA;
/* variables for the parser stack */
static YYSTACKDATA yystack;
#line 269 "project.y"
#include "lex.yy.c"

void yyerror(const char *s)
{
	fflush(stdout);
	printf("*** %s\n", s);
}

int main(){yydebug=1; return yyparse(); }
#line 504 "y.tab.c"

#if YYDEBUG
#include <stdio.h>		/* needed for printf */
#endif

#include <stdlib.h>	/* needed for malloc, etc */
#include <string.h>	/* needed for memset */

/* allocate initial stack or double stack size, up to YYMAXDEPTH */
static int yygrowstack(YYSTACKDATA *data)
{
    int i;
    unsigned newsize;
    short *newss;
    YYSTYPE *newvs;

    if ((newsize = data->stacksize) == 0)
        newsize = YYINITSTACKSIZE;
    else if (newsize >= YYMAXDEPTH)
        return -1;
    else if ((newsize *= 2) > YYMAXDEPTH)
        newsize = YYMAXDEPTH;

    i = (int) (data->s_mark - data->s_base);
    newss = (short *)realloc(data->s_base, newsize * sizeof(*newss));
    if (newss == 0)
        return -1;

    data->s_base = newss;
    data->s_mark = newss + i;

    newvs = (YYSTYPE *)realloc(data->l_base, newsize * sizeof(*newvs));
    if (newvs == 0)
        return -1;

    data->l_base = newvs;
    data->l_mark = newvs + i;

    data->stacksize = newsize;
    data->s_last = data->s_base + newsize - 1;
    return 0;
}

#if YYPURE || defined(YY_NO_LEAKS)
static void yyfreestack(YYSTACKDATA *data)
{
    free(data->s_base);
    free(data->l_base);
    memset(data, 0, sizeof(*data));
}
#else
#define yyfreestack(data) /* nothing */
#endif

#define YYABORT  goto yyabort
#define YYREJECT goto yyabort
#define YYACCEPT goto yyaccept
#define YYERROR  goto yyerrlab

int
YYPARSE_DECL()
{
    int yym, yyn, yystate;
#if YYDEBUG
    const char *yys;

    if ((yys = getenv("YYDEBUG")) != 0)
    {
        yyn = *yys;
        if (yyn >= '0' && yyn <= '9')
            yydebug = yyn - '0';
    }
#endif

    yynerrs = 0;
    yyerrflag = 0;
    yychar = YYEMPTY;
    yystate = 0;

#if YYPURE
    memset(&yystack, 0, sizeof(yystack));
#endif

    if (yystack.s_base == NULL && yygrowstack(&yystack)) goto yyoverflow;
    yystack.s_mark = yystack.s_base;
    yystack.l_mark = yystack.l_base;
    yystate = 0;
    *yystack.s_mark = 0;

yyloop:
    if ((yyn = yydefred[yystate]) != 0) goto yyreduce;
    if (yychar < 0)
    {
        if ((yychar = YYLEX) < 0) yychar = 0;
#if YYDEBUG
        if (yydebug)
        {
            yys = yyname[YYTRANSLATE(yychar)];
            printf("%sdebug: state %d, reading %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
    }
    if ((yyn = yysindex[yystate]) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yychar)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: state %d, shifting to state %d\n",
                    YYPREFIX, yystate, yytable[yyn]);
#endif
        if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack))
        {
            goto yyoverflow;
        }
        yystate = yytable[yyn];
        *++yystack.s_mark = yytable[yyn];
        *++yystack.l_mark = yylval;
        yychar = YYEMPTY;
        if (yyerrflag > 0)  --yyerrflag;
        goto yyloop;
    }
    if ((yyn = yyrindex[yystate]) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yychar)
    {
        yyn = yytable[yyn];
        goto yyreduce;
    }
    if (yyerrflag) goto yyinrecovery;

    yyerror("syntax error");

    goto yyerrlab;

yyerrlab:
    ++yynerrs;

yyinrecovery:
    if (yyerrflag < 3)
    {
        yyerrflag = 3;
        for (;;)
        {
            if ((yyn = yysindex[*yystack.s_mark]) && (yyn += YYERRCODE) >= 0 &&
                    yyn <= YYTABLESIZE && yycheck[yyn] == YYERRCODE)
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: state %d, error recovery shifting\
 to state %d\n", YYPREFIX, *yystack.s_mark, yytable[yyn]);
#endif
                if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack))
                {
                    goto yyoverflow;
                }
                yystate = yytable[yyn];
                *++yystack.s_mark = yytable[yyn];
                *++yystack.l_mark = yylval;
                goto yyloop;
            }
            else
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: error recovery discarding state %d\n",
                            YYPREFIX, *yystack.s_mark);
#endif
                if (yystack.s_mark <= yystack.s_base) goto yyabort;
                --yystack.s_mark;
                --yystack.l_mark;
            }
        }
    }
    else
    {
        if (yychar == 0) goto yyabort;
#if YYDEBUG
        if (yydebug)
        {
            yys = yyname[YYTRANSLATE(yychar)];
            printf("%sdebug: state %d, error recovery discards token %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
        yychar = YYEMPTY;
        goto yyloop;
    }

yyreduce:
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: state %d, reducing by rule %d (%s)\n",
                YYPREFIX, yystate, yyn, yyrule[yyn]);
#endif
    yym = yylen[yyn];
    if (yym)
        yyval = yystack.l_mark[1-yym];
    else
        memset(&yyval, 0, sizeof yyval);
    switch (yyn)
    {
case 1:
#line 29 "project.y"
	{printf("FINAL DONE\n");}
break;
case 2:
#line 32 "project.y"
	{printf("head_declaration\n");}
break;
case 3:
#line 33 "project.y"
	{printf("head_declaration recursion\n");}
break;
#line 718 "y.tab.c"
    }
    yystack.s_mark -= yym;
    yystate = *yystack.s_mark;
    yystack.l_mark -= yym;
    yym = yylhs[yyn];
    if (yystate == 0 && yym == 0)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: after reduction, shifting from state 0 to\
 state %d\n", YYPREFIX, YYFINAL);
#endif
        yystate = YYFINAL;
        *++yystack.s_mark = YYFINAL;
        *++yystack.l_mark = yyval;
        if (yychar < 0)
        {
            if ((yychar = YYLEX) < 0) yychar = 0;
#if YYDEBUG
            if (yydebug)
            {
                yys = yyname[YYTRANSLATE(yychar)];
                printf("%sdebug: state %d, reading %d (%s)\n",
                        YYPREFIX, YYFINAL, yychar, yys);
            }
#endif
        }
        if (yychar == 0) goto yyaccept;
        goto yyloop;
    }
    if ((yyn = yygindex[yym]) && (yyn += yystate) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yystate)
        yystate = yytable[yyn];
    else
        yystate = yydgoto[yym];
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: after reduction, shifting from state %d \
to state %d\n", YYPREFIX, *yystack.s_mark, yystate);
#endif
    if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack))
    {
        goto yyoverflow;
    }
    *++yystack.s_mark = (short) yystate;
    *++yystack.l_mark = yyval;
    goto yyloop;

yyoverflow:
    yyerror("yacc stack overflow");

yyabort:
    yyfreestack(&yystack);
    return (1);

yyaccept:
    yyfreestack(&yystack);
    return (0);
}
