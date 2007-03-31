
/*
 *  auxR.cc
 *
 *  FKBL in R
 *  Fuzzy Knowledge Base Learning
 *
 */

#include "InterfazR.h"

SEXP
CtoR (vector < int >v)
{
  SEXP Rv;
  Rf_protect (Rv = Rf_allocVector (INTSXP, v.size ()));

  for (unsigned int i = 0; i < v.size (); i++)
    INTEGER (Rv)[i] = v[i];

  Rf_unprotect (1);

  return Rv;
}

SEXP
CtoR (int v)
{
  SEXP Ri;
  Rf_protect (Ri = Rf_allocVector (INTSXP, 1));

  INTEGER (Ri)[0] = v;

  Rf_unprotect (1);

  return Ri;
}

SEXP
CtoR (vector < unsigned int >v)
{
  SEXP Rv;
  Rf_protect (Rv = Rf_allocVector (INTSXP, v.size ()));

  for (unsigned int i = 0; i < v.size (); i++)
    INTEGER (Rv)[i] = v[i];

  Rf_unprotect (1);

  return Rv;
}

int
errores (vector < int >c1, vector < int >c2)
{
  int e = 0;
  for (unsigned int i = 0; i < c1.size () && i < c2.size ();
       i++)
    if (c1[i] != c2[i])
      e++;

  return e;
}

vector < int >
inferencia (SistemaBorroso sb, train tr)
{
  vector < int >c (tr.numtrain);

  for (unsigned int i = 0; i < tr.numtrain; i++)
    c[i] = sb.inferencia (tr.datos[i]);
  return c;
}

vector < int >
inferencia1ganador (SistemaBorroso & sb,
		    train & tr, float maximportancia,
		    int reglaganadora)
{
  vector < int >c (tr.numtrain);

  for (unsigned int i = 0; i < tr.numtrain; i++)
    c[i] = sb.inferencia1ganador (tr.datos[i],
				  maximportancia,
				  reglaganadora);

  return c;
}

int
RtoC_int (SEXP ent)
{
  return INTEGER (ent)[0];
}

const char *
RtoC_char (SEXP cad)
{
  return CHAR (STRING_ELT (cad, 0));
}

double
RtoC_double (SEXP dob)
{
  return REAL (dob)[0];
}

//Particion
particion::particion (SEXP list)
{
  double *exA;
  int elem;


//  min = REAL( VECTOR_ELT(list, 0) )[0];
//  max = REAL( VECTOR_ELT(list, 1) )[0];
  exA = REAL (VECTOR_ELT (list, 2));
  elem = INTEGER (VECTOR_ELT (list, 3))[0];

  for (int i = 0; i < elem; i++)
    ex.push_back (exA[i]);


}

SEXP
particion::toR ()
{
  SEXP obj, Rnombres;
  SEXP RnumMin, RnumMax, Rpart, RnumElem;
  const char *nombres[4] =
    { "numMin", "numMax", "part", "numElem" };

  Rf_protect (RnumMin = Rf_allocVector (REALSXP, 1));
  Rf_protect (RnumMax = Rf_allocVector (REALSXP, 1));

  REAL (RnumMin)[0] = 0;	//min;
  REAL (RnumMax)[0] = 0;	//max;

  Rf_protect (Rpart = Rf_allocVector (REALSXP, ex.size ()));
  for (unsigned int i = 0; i < ex.size (); i++)
    REAL (Rpart)[i] = ex[i];

  Rf_protect (RnumElem = Rf_allocVector (INTSXP, 1));

  INTEGER (RnumElem)[0] = ex.size ();

  Rf_protect (Rnombres = Rf_allocVector (STRSXP, 4));
  for (int i = 0; i < 4; i++)
    SET_STRING_ELT (Rnombres, i, Rf_mkChar (nombres[i]));

  Rf_protect (obj = Rf_allocVector (VECSXP, 4));
  SET_VECTOR_ELT (obj, 0, RnumMin);
  SET_VECTOR_ELT (obj, 1, RnumMax);
  SET_VECTOR_ELT (obj, 2, Rpart);

  SET_VECTOR_ELT (obj, 3, RnumElem);

  Rf_setAttrib (obj, R_NamesSymbol, Rnombres);

  Rf_unprotect (6);

  return obj;
}

//Fin particion

//Regla
regla::regla (SEXP r)
{
  int *antecedenteA = INTEGER (VECTOR_ELT (r, 1));
  double *consecuenteA = REAL (VECTOR_ELT (r, 0));
  int elemA = INTEGER (VECTOR_ELT (r, 2))[0];
  int elemC = INTEGER (VECTOR_ELT (r, 3))[0];

  for (int i = 0; i < elemA; i++)
    antecedente.push_back (antecedenteA[i]);
  for (int i = 0; i < elemC; i++)
    consecuente.push_back (consecuenteA[i]);

}


SEXP
regla::toR ()
{
  SEXP obj, Rnombres;
  SEXP Rcons, Rantec, RelemA, RelemC;
  char *nombres[4] = { "cons", "antec", "elemA", "elemC" };

  Rf_protect (Rcons =
	      Rf_allocVector (REALSXP,
			      consecuente.size ()));
  for (unsigned int i = 0; i < consecuente.size (); i++)
    REAL (Rcons)[i] = consecuente[i];

  Rf_protect (Rantec =
	      Rf_allocVector (INTSXP, antecedente.size ()));
  for (unsigned int i = 0; i < antecedente.size (); i++)
    INTEGER (Rantec)[i] = antecedente[i];

  Rf_protect (RelemA = Rf_allocVector (INTSXP, 1));
  INTEGER (RelemA)[0] = antecedente.size ();

  Rf_protect (RelemC = Rf_allocVector (INTSXP, 1));
  INTEGER (RelemC)[0] = consecuente.size ();

  Rf_protect (Rnombres = Rf_allocVector (STRSXP, 4));
  for (int i = 0; i < 4; i++)
    SET_STRING_ELT (Rnombres, i, Rf_mkChar (nombres[i]));

  Rf_protect (obj = Rf_allocVector (VECSXP, 4));
  SET_VECTOR_ELT (obj, 0, Rcons);
  SET_VECTOR_ELT (obj, 1, Rantec);
  SET_VECTOR_ELT (obj, 2, RelemA);
  SET_VECTOR_ELT (obj, 3, RelemC);


  Rf_setAttrib (obj, R_NamesSymbol, Rnombres);

  Rf_unprotect (6);

  return obj;

}

//Fin Regla


//SistemaBorroso
SistemaBorroso::SistemaBorroso (SEXP sysbor):error (1)
{
  unsigned int
    nReglas,
    nParticiones;
  SEXP
    Reglas = VECTOR_ELT (sysbor, 0), Particiones =
    VECTOR_ELT (sysbor, 1);
  numclases = INTEGER (VECTOR_ELT (sysbor, 2))[0];
  nReglas = Rf_length (VECTOR_ELT (sysbor, 0));
  nParticiones = Rf_length (VECTOR_ELT (sysbor, 1));
  error = REAL (VECTOR_ELT (sysbor, 3))[0];

  for (unsigned int i = 0; i < nReglas; i++)
    R.push_back (VECTOR_ELT (Reglas, i));

  for (unsigned int i = 0; i < nParticiones; i++)
    P.push_back (VECTOR_ELT (Particiones, i));

}


SEXP
SistemaBorroso::toR ()
{


  SEXP obj, Rnombres;
  SEXP Rp, Rr, Rnumclases, Rerror;
  const int len = 4;
  char *nombres[len] =
    { "Reglas", "Particiones", "numClases", "error" };



  Rf_protect (Rr = Rf_allocVector (VECSXP, R.size ()));
  for (unsigned int i = 0; i < R.size (); i++)
    SET_VECTOR_ELT (Rr, i, R[i].toR ());


  Rf_protect (Rp = Rf_allocVector (VECSXP, P.size ()));
  for (unsigned int i = 0; i < P.size (); i++)
    SET_VECTOR_ELT (Rp, i, P[i].toR ());

  Rf_protect (Rnumclases = Rf_allocVector (INTSXP, 1));
  INTEGER (Rnumclases)[0] = numclases;

  Rf_protect (Rerror = Rf_allocVector (REALSXP, 1));
  REAL (Rerror)[0] = error;

  Rf_protect (Rnombres = Rf_allocVector (STRSXP, len));
  for (int i = 0; i < len; i++)
    SET_STRING_ELT (Rnombres, i, Rf_mkChar (nombres[i]));

  Rf_protect (obj = Rf_allocVector (VECSXP, len));
  SET_VECTOR_ELT (obj, 0, Rr);
  SET_VECTOR_ELT (obj, 1, Rp);
  SET_VECTOR_ELT (obj, 2, Rnumclases);
  SET_VECTOR_ELT (obj, 3, Rerror);

  Rf_setAttrib (obj, R_NamesSymbol, Rnombres);

  Rf_unprotect (6);



  return obj;
}

//Fin SistemaBorroso

//Meta
Meta::Meta (SEXP mt_)
{
  SEXP Rnombres = Rf_getAttrib (mt_, R_NamesSymbol);
  unsigned int len = Rf_length (Rnombres);

  for (unsigned int i = 0; i < len; i++)
    datos[CHAR (STRING_ELT (Rnombres, i))] =
      CHAR (STRING_ELT (VECTOR_ELT (mt_, i), 0));
}

Meta::Meta ()
{
}

//Fin Meta
