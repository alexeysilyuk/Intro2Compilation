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
    3,    3,    3,    5,    1,    3,    1,    0,    3,    1,
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
    0,    0,    0,    0,    0,    0,    0,    0,   60,    0,
    0,    0,   52,   59,   54,   45,   48,   49,   79,   74,
    0,    0,   76,    0,    0,   41,    0,    0,   39,    0,
    0,    0,    0,   32,    0,    0,   31,    0,   61,   58,
    0,   81,    0,    0,    0,    0,   20,    0,    0,    0,
    0,    0,   63,   80,    0,   42,    0,    0,    0,   25,
    0,   26,   36,    0,    0,   43,   21,    0,    0,    0,
    0,   23,   27,    0,    0,    0,    0,    0,   34,   29,
};
static const short yydgoto[] = {                         15,
   16,   17,   18,   19,   20,   21,   52,   22,   59,   23,
   24,   25,   26,   27,   28,  135,  147,   66,  136,  165,
   67,   82,   61,   99,   29,   46,   76,   47,   48,  111,
   49,   85,   88,  100,
};
static const short yysindex[] = {                       300,
    0,    0,    0,    0,    0,    0,    0,  -10,   -4, -114,
    3,  204,    0,    0,    0,    0,  300,  -19,    0,    0,
 -240,    0,    0,    0,    0,    0,    0,    0,  -37,  168,
  168,  300,  -55, -239,  -27,    0,    0,    0,    0,    0,
    0,    0,  204, -237,    0, -236,    0,    0,    0,    0,
    0,    7,    0,  -40,  -39,  322,   12,  204, -180,   14,
 -231,   15,  -68,   18, -215,    6,   22,  195, -229,   26,
  -54,    0,    0,    0,    0,  204, -240,    0, -218, -213,
    0,    0,    0, -211,  -13,    0,    0,  -30,  204,  133,
    0,    0,    0,    0,    0,    0,    0,    0,  168,    0,
  -97,  168,  -84, -198,  168,  -40,  168, -239,    0,   35,
   39,  -11,    0,    0,    0,    0,    0,    0,    0,    0,
  -70, -208,    0, -180,  168,    0,  300,  -53,    0,  300,
  -19,   45,   46,    0,   47,   30,    0,  204,    0,    0,
 -194,    0,  168,   64,  -18,  282,    0,  -17,  168,   50,
  168, -181,    0,    0,   70,    0, -157,  300,  -19,    0,
   74,    0,    0, -162,   75,    0,    0,   -6,   62,  -40,
  317,    0,    0,   78,  300,  -19, -181,   -1,    0,    0,
};
static const short yyrindex[] = {                         0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    8,  113,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,   73,   84,
   84,    0,    0,    0,    1,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,   37,    0,    0,    0,    0,
    0,   86,    0,    0,    0,    0,    0,    0,  -25,    0,
  -24,    0,    0,    0,    0,    0,   68,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,  -12,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,  -34,    0,
    0,  -34,    0,    0,   84,    0,  -26,    0,    0,   87,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,   84,    0,    0,  131,    0,    0,
  158,    0,    0,    0,   76,    0,    0,    0,    0,    0,
   -3,    0,   84,    0,    0,    0,    0,    0,   84,    0,
  -26,    0,    0,    0,    0,    0,  171,    0,  207,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,   88,    0,  243,    0,    0,    0,    0,
};
static const short yygindex[] = {                         0,
   27,    0,   17,    0,    0,  -50,    0,   -9,   34,    0,
    0,    0,    0,    0,    0,  487,  -23,   28,  -14,  -38,
    0,  -95,    0,  -75,    0,    0,    0,    0,    0,    4,
    0,    0,    0,    0,
};
#define YYTABLESIZE 636
static const short yytable[] = {                         43,
   57,   83,   55,   51,   84,   51,   38,    2,   32,   38,
  134,   53,   68,  122,  125,   40,   37,   38,   40,   37,
   72,   73,   74,   75,   38,  127,   33,  120,   77,   30,
  121,   77,   38,   40,   37,   31,   53,   78,  130,   51,
   78,   57,   34,   50,   57,   45,   13,   65,  143,   71,
   77,   89,  102,   56,  101,  103,  104,  105,   63,   57,
  106,  112,  123,   69,  107,  108,  113,  116,  117,  114,
  141,  132,   47,  118,  174,  119,   70,   53,  138,  139,
   53,  140,  142,   44,  149,    6,  150,   81,  152,   87,
  151,   90,  154,   57,   91,   53,   92,   93,   94,   95,
   96,  110,   97,   98,  156,  164,  157,  160,  162,  115,
  166,  146,    4,  170,  169,  171,   47,  128,  172,  131,
  173,  177,  124,  180,   38,   57,   30,   62,   33,   53,
   18,   47,    2,  167,   35,  137,  163,    0,  179,   81,
    0,  153,    0,    0,    6,    0,    1,    2,    3,    4,
    5,    6,    7,  145,    0,    0,  148,   24,   12,    0,
    0,   53,  159,    1,    2,    3,    4,    5,    6,    7,
   19,  110,   13,  113,    0,   12,    1,    2,    3,    4,
    5,    6,    7,    0,  168,    0,    0,  176,   12,   13,
    1,    2,    3,    4,    5,    6,    7,   47,    0,    0,
    0,  178,   13,   81,    0,    0,   22,   58,    0,    0,
    6,    0,    0,    0,   64,  146,    0,    0,    0,    0,
    0,    1,    2,    3,    4,    5,    6,    7,    0,    0,
    0,    0,    0,   78,   43,  109,    0,    4,   54,    0,
    0,    0,   28,   43,   79,   80,   35,   36,   37,   38,
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
   18,   18,   18,   18,  158,    0,    0,   91,    4,   92,
   93,   94,   95,   96,   86,   97,   98,   18,   24,   24,
   24,   24,   24,   24,   24,   24,   18,   24,   24,   24,
   24,   19,   19,   19,   19,   19,   19,   19,   19,  175,
   19,   19,   19,   19,   24,   44,    0,    0,    0,   57,
    0,    0,    0,   24,   35,   36,   37,   19,   38,   39,
   40,   41,   42,    0,    0,    0,   19,   22,   22,   22,
   22,   22,   22,   22,   22,    0,   22,   22,   22,   22,
    0,   35,   36,   37,    0,   38,   39,   40,   41,   42,
   35,   36,   37,   22,   38,   39,   40,   41,   42,    0,
    0,    0,   22,   28,   28,   28,   28,   28,   28,   28,
   28,    0,   28,   28,   28,   28,   60,   62,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,   28,
    0,    0,    0,    0,    0,    0,    0,    0,   28,    0,
    0,    0,    1,    2,    3,    4,    5,    6,    7,    0,
    0,    0,    0,    0,   12,    0,    0,    0,    0,    0,
    1,    2,    3,    4,    5,    6,    7,    8,   13,    9,
   10,   11,   12,    0,    0,    0,    0,    1,    2,    3,
    4,    5,    6,    7,    0,  126,   13,    0,  129,   12,
    0,  133,    0,    0,    0,   14,    0,    0,    0,    0,
    0,    0,    0,   13,    0,    0,    0,    0,   35,   36,
   37,  144,   38,   39,   40,   41,   42,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,  155,
    0,    0,    0,    0,    0,  161,
};
static const short yycheck[] = {                         40,
    0,   41,   40,   59,   55,   59,   41,    0,  123,   44,
  106,   21,   40,   44,   90,   41,   41,   44,   44,   44,
  257,  258,  259,  260,   59,  123,   10,   41,   41,   40,
   44,   44,   59,   59,   59,   40,    0,   41,  123,   59,
   44,   41,   40,   17,   44,   12,  287,  287,  124,  287,
   44,   40,  284,   91,   41,   41,  125,   40,   32,   59,
  276,  291,   93,   91,   59,   44,   41,   77,  287,  124,
  121,  270,    0,  287,  170,  287,   43,   41,   44,   41,
   44,   93,  291,  124,   40,    0,   41,   54,   59,   56,
   44,   58,  287,   93,  275,   59,  277,  278,  279,  280,
  281,   68,  283,  284,   41,  287,  125,  125,   59,   76,
   41,  269,    0,  276,   41,   41,   44,  101,  125,  103,
   59,   44,   89,  125,   41,  125,   59,   41,   41,   93,
    0,   59,  125,  157,   59,  108,  151,   -1,  177,  106,
   -1,  138,   -1,   -1,   59,   -1,  261,  262,  263,  264,
  265,  266,  267,  127,   -1,   -1,  130,    0,  273,   -1,
   -1,  125,  146,  261,  262,  263,  264,  265,  266,  267,
    0,  138,  287,   41,   -1,  273,  261,  262,  263,  264,
  265,  266,  267,   -1,  158,   -1,   -1,  171,  273,  287,
  261,  262,  263,  264,  265,  266,  267,  125,   -1,   -1,
   -1,  175,  287,  170,   -1,   -1,    0,   40,   -1,   -1,
  125,   -1,   -1,   -1,  270,  269,   -1,   -1,   -1,   -1,
   -1,  261,  262,  263,  264,  265,  266,  267,   -1,   -1,
   -1,   -1,   -1,  274,   40,   41,   -1,  125,  276,   -1,
   -1,   -1,    0,   40,  285,  286,  287,  288,  289,  284,
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
  273,  261,  262,  263,  264,  265,  266,  267,  268,  123,
  270,  271,  272,  273,  287,  124,   -1,   -1,   -1,  282,
   -1,   -1,   -1,  296,  287,  288,  289,  287,  291,  292,
  293,  294,  295,   -1,   -1,   -1,  296,  261,  262,  263,
  264,  265,  266,  267,  268,   -1,  270,  271,  272,  273,
   -1,  287,  288,  289,   -1,  291,  292,  293,  294,  295,
  287,  288,  289,  287,  291,  292,  293,  294,  295,   -1,
   -1,   -1,  296,  261,  262,  263,  264,  265,  266,  267,
  268,   -1,  270,  271,  272,  273,   30,   31,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  287,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  296,   -1,
   -1,   -1,  261,  262,  263,  264,  265,  266,  267,   -1,
   -1,   -1,   -1,   -1,  273,   -1,   -1,   -1,   -1,   -1,
  261,  262,  263,  264,  265,  266,  267,  268,  287,  270,
  271,  272,  273,   -1,   -1,   -1,   -1,  261,  262,  263,
  264,  265,  266,  267,   -1,   99,  287,   -1,  102,  273,
   -1,  105,   -1,   -1,   -1,  296,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,  287,   -1,   -1,   -1,   -1,  287,  288,
  289,  125,  291,  292,  293,  294,  295,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  143,
   -1,   -1,   -1,   -1,   -1,  149,
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
"boolean_expr :",
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
#line 505 "y.tab.c"

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
#line 719 "y.tab.c"
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
