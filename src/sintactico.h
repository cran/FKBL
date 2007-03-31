/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton interface for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

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

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     ABRIR = 258,
     CERRAR = 259,
     BARRA = 260,
     DOBLE = 261,
     ENTERO = 262,
     TYPE = 263,
     LEN = 264,
     INTERROGA = 265,
     DOC = 266,
     SYS = 267,
     IGUAL = 268,
     NUM = 269,
     SB = 270,
     PART = 271,
     REG = 272,
     OTRO = 273,
     EX = 274,
     MIN = 275,
     MAX = 276,
     ANT = 277,
     CON = 278,
     NC = 279,
     XML = 280,
     VER = 281,
     EXCLAMA = 282,
     GUION = 283,
     STYLE = 284,
     HREF = 285,
     AUTH = 286,
     DESCR = 287,
     ERROR_XML = 288
   };
#endif
/* Tokens.  */
#define ABRIR 258
#define CERRAR 259
#define BARRA 260
#define DOBLE 261
#define ENTERO 262
#define TYPE 263
#define LEN 264
#define INTERROGA 265
#define DOC 266
#define SYS 267
#define IGUAL 268
#define NUM 269
#define SB 270
#define PART 271
#define REG 272
#define OTRO 273
#define EX 274
#define MIN 275
#define MAX 276
#define ANT 277
#define CON 278
#define NC 279
#define XML 280
#define VER 281
#define EXCLAMA 282
#define GUION 283
#define STYLE 284
#define HREF 285
#define AUTH 286
#define DESCR 287
#define ERROR_XML 288




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 16 "sintactico.y"
{ 
  class NumeroF *numF;
  class NumeroI *numI;
  class regla *reg;
  class reglas *regs;
  class particion *part;
  class particiones *parts;
  int entero;
  char caracter;
  char cadena[100];
}
/* Line 1489 of yacc.c.  */
#line 127 "sintactico.h"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;

