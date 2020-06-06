/* A Bison parser, made by GNU Bison 2.7.  */

/* Bison interface for Yacc-like parsers in C
   
      Copyright (C) 1984, 1989-1990, 2000-2012 Free Software Foundation, Inc.
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.
   
   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif
/* "%code requires" blocks.  */
/* Line 2058 of yacc.c  */
#line 27 "bison.y"

	#include <vector>
	#include <map>
	using namespace std;


/* Line 2058 of yacc.c  */
#line 53 "y.tab.h"

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     identifier = 258,
     int_value = 259,
     float_value = 260,
     boolean = 261,
     relop = 262,
     boolean_op = 263,
     semi_colon = 264,
     equals = 265,
     int_word = 266,
     float_word = 267,
     boolean_word = 268,
     mulop = 269,
     addop = 270,
     if_term = 271,
     else_term = 272,
     round_open = 273,
     round_close = 274,
     curly_open = 275,
     curly_close = 276,
     while_token = 277
   };
#endif
/* Tokens.  */
#define identifier 258
#define int_value 259
#define float_value 260
#define boolean 261
#define relop 262
#define boolean_op 263
#define semi_colon 264
#define equals 265
#define int_word 266
#define float_word 267
#define boolean_word 268
#define mulop 269
#define addop 270
#define if_term 271
#define else_term 272
#define round_open 273
#define round_close 274
#define curly_open 275
#define curly_close 276
#define while_token 277



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{
/* Line 2058 of yacc.c  */
#line 35 "bison.y"

	int int_val;
	float float_val;
	char * id_val;
	struct {
		vector<int> *true_list;
		vector<int> *false_list;
	} bool_expression;
	struct {
        	int type;
        } expression_type;
        int id_type;
	char* operation;
	int boolean_val;
	struct {
	vector<int> *next_list;
	} statement_type;


/* Line 2058 of yacc.c  */
#line 132 "y.tab.h"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;

#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
