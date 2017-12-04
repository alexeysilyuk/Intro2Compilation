#define MINUS_OP 257
#define PLUS_OP 258
#define DIVISION_OP 259
#define MULT_OP 260
#define LP 261
#define RP 262
#define INCR 263
#define DECR 264
#define BOOLEAN_TYPE 265
#define CHAR_TYPE 266
#define INT 267
#define VOID 268
#define STRING 269
#define INTP 270
#define CHARP 271
#define IF 272
#define ELSE 273
#define WHILE 274
#define DO 275
#define FOR 276
#define RETURN 277
#define _NULL 278
#define MAIN 279
#define AND 280
#define ASSIGNMENT 281
#define EQUAL 282
#define GREAT_THEN 283
#define GREAT_EQUAL 284
#define LESS_THEN 285
#define LESS_EQUAL 286
#define NOT 287
#define NOT_EQUAL 288
#define OR 289
#define BITWISE_AND 290
#define BITWISE_XOR 291
#define IDENTIFIER 292
#define STRING_VALUE 293
#define CHAR_LITERAL 294
#define POINTER_ADDRESS 295
#define INT_CONSTANT_VALUE 296
#define BOOL_CONSTANT_VALUE 297
#define BIN_CONSTANT_VALUE 298
#define OCT_CONSTANT_VALUE 299
#define HEX_CONSTANT_VALUE 300
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
