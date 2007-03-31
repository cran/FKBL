
/*
 *  InterfazR.h
 *
 *  FKBL in R
 *  Fuzzy Knowledge Base Learning
 *
 */

#ifndef _INTERFR_H_
#define _INTERFR_H_

#include "InferenciaBorrosa.h"
#include "train.h"
#include "combinaciones.h"
#include "Michigan.h"
#include "Pittsburgh.h"
#include "lexico.h"
#include "sintactico.h"
//#include "SeleccGen.h"
#include "SeleccGenMO.h"
#include "MOGA.h"

#define XMLHEADER "<?xml version=\"1.0\"?> \
\n<!DOCTYPE KnowledgeBase SYSTEM \"FKBL.dtd\"> \
\n<?xml-stylesheet type=\"text/xsl\" href=\"FKBL.xsl\"?>"

using namespace std;

extern SistemaBorroso *sb;

extern "C"
{

  SEXP inferencia (SEXP sysbor, SEXP file_);

  SEXP inferencia1ganador (SEXP sysbor, SEXP file_);

  SEXP confianzasoporte (SEXP vp_, SEXP peso_, SEXP train);

  SEXP recompensacastigo (SEXP sb_, SEXP tr_,
			  SEXP iteraciones_, SEXP etaMas,
			  SEXP etaMenos);

  SEXP analitico (SEXP sb_, SEXP tr_, SEXP iteraciones_,
		  SEXP e_);

//SEXP getClases(SEXP file_);

  SEXP getRandPart (SEXP vP_);

  SEXP SBtoXML (SEXP file_, SEXP sb_, SEXP mt_);

  SEXP SBfromXML (SEXP file_);

  SEXP checkXML (SEXP file_);

  SEXP SeleccGen (SEXP train_, SEXP sb_, SEXP generaciones_,
		  SEXP prob_cruce_, SEXP prob_muta_,
		  SEXP k_,  SEXP tamPob_);

  SEXP SeleccGenMO (SEXP train_, SEXP sb_,
		    SEXP generaciones_, SEXP prob_cruce_,
		    SEXP prob_muta_, SEXP k_,
		    SEXP tamPob_);

  SEXP MOGA (SEXP train_, SEXP sb_, SEXP generaciones_,
	     SEXP prob_cruce_, SEXP prob_muta_, SEXP Npob_,
	     SEXP Nelite_);

  SEXP Michigan (SEXP train_, SEXP vp_, SEXP generaciones_,
		 SEXP prob_cruce_, SEXP prob_muta_);

  SEXP Hibrido (SEXP train_, SEXP vp_, SEXP generaciones_,
		SEXP prob_cruce_, SEXP prob_muta_,
		SEXP prob_cruceM_, SEXP prob_mutaM_,
		SEXP reemplazar_);

//  SEXP COMB(SEXP vp_);
}

SEXP CtoR (vector < int >v);

SEXP CtoR (int v);

SEXP CtoR (vector < unsigned int >v);

const char *RtoC_char (SEXP cad);

int RtoC_int (SEXP ent);

double RtoC_double (SEXP dob);

int errores (vector < int >c1, vector < int >c2);

vector < int >inferencia (SistemaBorroso sb, train tr);

vector < int >inferencia1ganador (SistemaBorroso & sb,
				  train & tr,
				  float maximportancia,
				  int reglaganadora);


#endif
