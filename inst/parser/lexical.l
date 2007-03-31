/* Fichero de lexico */
%option noyywrap

%{
#include "lexico.h"
#include "sintactico.h"

%}

letra [A-Za-z]
digito [0-9]
alfanumerico [A-Za-z0-9]
abrir "<"
cerrar ">"
interroga "?"
exclama "!"
guion "-"
identificador {letra}{alfanumerico}*
igual "="
cadena \"[^\"]*\"
comentario "//"[^\n]*
num {digito}+
real (\+|-)?{num}(\.{num})?(E(\+|-){num})?
%%

{abrir}		{ yylval.caracter='<';
		  return ABRIR;
		}
{cerrar}	{ yylval.caracter='>';
		  return CERRAR;
		}
"/"		{ yylval.caracter='/';
		  return BARRA;
		}
{interroga}	{
		  yylval.caracter='?';
		  return INTERROGA;
		}
{guion}		{
		  yylval.caracter='-';
		  return GUION;
		}
{exclama}	{
		  yylval.caracter='!';
		  return EXCLAMA;
		}
{cadena}	{ yytext[strlen(yytext)-1]='\0';
		  strcpy(yylval.cadena,yytext+1);

		if(!strcmp(yylval.cadena,"double"))
			return DOBLE;
		if(!strcmp(yylval.cadena,"int"))
                        return ENTERO;
		else return OTRO;
		}
{identificador}	{strcpy(yylval.cadena, yytext);
		if(!strcmp(yytext,"type"))
                        return TYPE;
		if(!strcmp(yytext,"len"))
                        return LEN;
		if(!strcmp(yytext,"KnowledgeBase"))
                        return SB;
		if(!strcmp(yytext,"Partition"))
                        return PART;
		if(!strcmp(yytext,"ex"))
                        return EX;
                if(!strcmp(yytext,"Rule"))
                        return REG;
                if(!strcmp(yytext,"antecedent"))
                        return ANT;
                if(!strcmp(yytext,"consecuent"))
                        return CON;
     	        if(!strcmp(yytext,"numclasses"))
                        return NC;
		if(!strcmp(yytext,"xml"))
			return XML;
                if(!strcmp(yytext,"DOCTYPE"))
                        return DOC;
                if(!strcmp(yytext,"SYSTEM"))
                        return SYS;
		if(!strcmp(yytext,"version"))
			return VER;
                if(!strcmp(yytext,"stylesheet"))
                        return STYLE;
                if(!strcmp(yytext,"href"))
                        return HREF;
		if(!strcmp(yytext,"Author"))
                        return AUTH;
		if(!strcmp(yytext,"Description"))
                        return DESCR;
                if(!strcmp(yytext,"Error"))
                        return ERROR_XML;
		return OTRO;
		}
{igual}		{ yylval.caracter='=';
		  return IGUAL;
		}
{real}		{ strcpy(yylval.cadena, yytext);
		  return NUM;
		}
{comentario}	{yylineno++;}
"\n"		{yylineno++;}
[ \t]		;

%%

