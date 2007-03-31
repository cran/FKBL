#ifndef _lexico_h_
#define _lexico_h_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//int yylex();

extern void yyerror (char *);
extern int yyparse ();

extern FILE *yyin, *yyout;
extern int yylineno;

#endif
