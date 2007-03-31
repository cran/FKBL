%{
#include "lexico.h"
#include "InferenciaBorrosa.h"

SistemaBorroso *sb;

class NumeroF{public: vector<float> num;};
class NumeroI{public: vector<short int> num;};
class reglas{public: vector<regla> regs;};
class particiones{public: vector<particion> parts;};

extern int yylex();

%}
%union
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

%token	<cadena> ABRIR CERRAR BARRA DOBLE ENTERO 
%token  <cadena> TYPE LEN INTERROGA DOC SYS 
%token	<cadena> IGUAL NUM SB PART REG OTRO EX 
%token  <cadena> MIN MAX ANT CON NC XML 
%token	<cadena> VER EXCLAMA GUION STYLE HREF AUTH
%token  <cadena> DESCR ERROR_XML

%type	<cadena> meta author descripcion cadenas
%type	<numF> Reales consecuente ex
%type	<numI> antecedente
%type	<entero> numclases
%type	<reg> Regla
%type	<regs> Reglas
%type	<part> Particion
%type	<parts> Particiones

%%

Inicial: Cab SbInicial metas Particiones Reglas numclases 
extras SbFinal 
{ sb=new SistemaBorroso($4->parts,$5->regs,$6); 
  printf("\n-Correct file-\n"); 
}

metas: metas meta
	| /* nada */

meta: author { printf("Author: %s\n",$1);}
	| descripcion { printf("Description: %s\n",$1);}

author: authorI cadenas authorF 
{ strcpy($$,$2);}

authorI: ABRIR AUTH CERRAR

authorF: ABRIR BARRA AUTH CERRAR

descripcion: ABRIR DESCR CERRAR cadenas ABRIR BARRA DESCR CERRAR 
{strcpy($$,$4);}

extras: extras extra
	| /* nada */

extra: err

err: ABRIR ERROR_XML CERRAR NUM ABRIR BARRA ERROR_XML CERRAR

Cab:  cab1 cab2 cab3 

cab1: ABRIR INTERROGA XML VER IGUAL OTRO INTERROGA CERRAR 
      /* {printf("First Head OK\n");} */

cab2: ABRIR EXCLAMA DOC SB SYS OTRO CERRAR
      /* {printf("Second Head OK\n");} */

cab3: ABRIR INTERROGA XML GUION STYLE TYPE IGUAL OTRO HREF IGUAL 
OTRO INTERROGA CERRAR
      /* {printf("Third Head OK\n");} */

SbInicial: ABRIR SB CERRAR

SbFinal: ABRIR BARRA SB CERRAR

Particiones: Particiones Particion 
{
	$$ = $1;
	$$->parts.push_back(*$2);
	}
	| Particion
{
 $$ = new particiones(); 
 $$->parts.push_back(*$1)
}

Particion: PInicial ex Pfinal 
{ 
 $$ = new particion($2->num); 
}

PInicial: ABRIR PART CERRAR

Pfinal: ABRIR BARRA PART CERRAR

ex: exI Reales exF { 
 $$=$2; 
}

exI: ABRIR EX TYPE IGUAL DOBLE LEN IGUAL OTRO CERRAR

exF: ABRIR BARRA EX CERRAR


Reglas: Reglas Regla 
	{ 
	  $$=$1; 
	  $$->regs.push_back(*$2); 
	}
	| Regla 
	{ 
	  $$ = new reglas(); 
	  $$->regs.push_back(*$1);
	}


Regla: rI antecedente consecuente rF 
					{ 
				$$ = new regla(); 
				$$->setAntecedente($2->num);
				$$->setConsecuente($3->num);
					}

rI: ABRIR REG CERRAR

rF: ABRIR BARRA REG CERRAR

antecedente: aI Reales aF { 
$$=new NumeroI(); 
for(unsigned int i=0;i<$2->num.size();i++)
	$$->num.push_back((int)$2->num[i]);   
}

aI: ABRIR ANT TYPE IGUAL ENTERO LEN IGUAL OTRO CERRAR

aF: ABRIR BARRA ANT CERRAR

consecuente: cI Reales cF { $$ = $2; }

cI: ABRIR CON TYPE IGUAL DOBLE LEN IGUAL OTRO CERRAR

cF: ABRIR BARRA CON CERRAR

numclases: ncI NUM ncF { $$ = (int)atof($2); }
	

ncI: ABRIR NC CERRAR

ncF: ABRIR BARRA NC CERRAR

Reales: Reales NUM {$$ = $1; $$->num.push_back(atof($2)); }
	| /* nada */ {$$= new NumeroF();}
 
cadenas: cadenas OTRO {strcpy($1+1+strlen($1),$2); 
	$1[strlen($1)]=' '; strcpy($$,$1);}
	| OTRO {strcpy($$,$1);} //No hagais esto en casa ninios
%%

void yyerror(char *error)
{
char mensaje[80];
sprintf(mensaje, "Sintactic error in line %u. \n%s\n", yylineno, 
error);
printf(mensaje);
}

