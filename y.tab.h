#define MINUS_OP 257
#define PLUS_OP 258
#define DIVISION_OP 259
#define MULT_OP 260
#define LP 261
#define RP 262
#define BOOLEAN_TYPE 263
#define CHAR_TYPE 264
#define INT 265
#define VOID 266
#define STRING 267
#define INTP 268
#define CHARP 269
#define IF 270
#define ELSE 271
#define WHILE 272
#define DO 273
#define FOR 274
#define RETURN 275
#define _NULL 276
#define MAIN 277
#define AND 278
#define ASSIGNMENT 279
#define EQUAL 280
#define GREAT_THEN 281
#define GREAT_EQUAL 282
#define LESS_THEN 283
#define LESS_EQUAL 284
#define NOT 285
#define NOT_EQUAL 286
#define OR 287
#define BITWISE_AND 288
#define BITWISE_XOR 289
#define IDENTIFIER 290
#define STRING_VALUE 291
#define CHAR_LITERAL 292
#define POINTER_ADDRESS 293
#define INT_CONSTANT_VALUE 294
#define BOOL_CONSTANT_VALUE 295
#define BIN_CONSTANT_VALUE 296
#define OCT_CONSTANT_VALUE 297
#define HEX_CONSTANT_VALUE 298
#ifdef YYSTYPE
#undef  YYSTYPE_IS_DECLARED
#define YYSTYPE_IS_DECLARED 1
#endif
#ifndef YYSTYPE_IS_DECLARED
#define YYSTYPE_IS_DECLARED 1
typedef union {
  char* string;
  node* node;
  int integer;
} YYSTYPE;
#endif /* !YYSTYPE_IS_DECLARED */
extern YYSTYPE yylval;
