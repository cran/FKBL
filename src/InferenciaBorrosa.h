/*
 *  InferenciaBorrosa.h
 *  
 *  FKBL in R
 *  Fuzzy Knowledge Base Learning 
 *
 */

#ifndef _InferenciaBorrosa_h
#define _InferenciaBorrosa_h

//for compatibility between iostream and Rinternals
#define R_NO_REMAP 1

#define NOIMPORTA -1

#include <iostream>
#include <fstream>

#include <time.h>

#include <vector>
#include <map>

using namespace std;

#include <R.h>
#include <Rinternals.h>

// Particion linguistica de una variable borrosa
// Los conjuntos primero y ultimo son trapezoidales
// Los restantes conjuntos son triangulares

class particion
{
  vector < float >ex;
public:
    particion (int elem,	// Numero de elementos 
	       float min,	// Rango minimo 
	       float max	// Rango maximo 
    );
    particion ();
    particion (SEXP list);
    particion (vector < float >ex_):ex (ex_)
  {
  }
  float pertenencia (int t, float x) const;
  // Pertenencia del valor x al termino t (empezando en cero)
  void setUniforme (double, double);
  void setRandom ();
  int size () const;

  friend ostream & operator<< (ostream & os,
			       const particion & p);

  SEXP toR ();

  void toXML (ofstream & f);
};


// Regla borrosa (sin peso) para problemas de clasificacion
// El antecedente es una combinacion con AND de asertos borrosos de
// la forma "VARIABLE es VALOR". El indice de A codifica la variable
// y el contenido es la etiqueta. Por ejemplo:
// Variable X: valores P, M, G
// Variable Y: valores P, G
// El antecedente "Si (X es G) AND (Y es P)" se codifica con el
// vector A= { 2, 0 }


class regla
{
  vector < short int >antecedente;	
  // Terminos linguisticos combinados con AND
  vector < float >consecuente;	
  // consecuente[i] es el grado de 
  // certeza de la regla i
public:

    regla (SEXP r);
    regla ();
    regla (vector < short int >&a, vector < float >&c);
  void setAntecedente (const vector < short int >&A)
  {
    antecedente = A;
  }
  void setConsecuente (const vector < float >&C)
  {
    consecuente = C;
  }
  vector < short int >getAntecedente () const
  {
    return antecedente;
  }
  vector < float >getConsecuente () const
  {
    return consecuente;
  }
  float getConsecuente (int c) const
  {
    return consecuente[c];
  }
  float match (const vector < particion > &vp,
	       const vector < float >&x) const;

  //NO COMMENT
  void setConsecuente (int c, float v)
  {
    consecuente[c] = v;
  }

  void calculaConfianzaSoporte (const vector < particion >
	    &vp, const vector < vector < float > >&car,
				const vector < int >&cl,
				float &confianza,
				float &soporte);


  SEXP toR ();

  void toXML (ofstream & f);
};

class Meta
{
public:
  map <const char *, const char *>datos;
    Meta (SEXP mt_);
    Meta ();
};

// Sistema borroso con inferencia min/max
// Consta de dos vectores, que contienen las 
// definiciones de las particiones borrosas
// de las variables y las reglas borrosas de la base de conocimiento

class SistemaBorroso
{

  vector < particion > P;	// Definicion de las particiones borrosas
  vector < regla > R;		// Base de conocimiento
  unsigned int numclases;	// Numero de clases del problema
  double error;
public:

    SistemaBorroso ():numclases (0), error (1)
  {
  }

  // Constructor: recibe las particiones, 
  // la base de conocimiento y el numero de clases
  SistemaBorroso (const vector < particion > &p,
		  const vector < regla > &r, int nc);

  // Constructor: recibe un sistema borroso de R
  SistemaBorroso (SEXP sysbor);

  // Inferencia: devuelve un vector en el que cada 
  // componente es la compatibilidad
  // de la clase correspondiente con el vector x
  vector < float >inferenciaf (const vector < float >&x);

  // Clasifica el vector x de acuerdo con la base de conocimiento
  int inferencia (const vector < float >&x);

  int getNumClases ()
  {
    return numclases;
  }

  // Clasifica el vector x de acuerdo con la base de conocimiento 
  // (inferencia por unico ganador)
  int inferencia1ganador (const vector < float >&x,
			  float &maximportancia,
			  int &reglaganadora);

  //Devuelve la particion dada
  particion & getP (int i)
  {
    return P[i];
  }

  vector < particion > &getP ()
  {
    return P;
  }

  unsigned int sizeP ()
  {
    return P.size ();
  }

  //Devuelve la regla dada
  regla & getR (int i)
  {
    return R[i];
  }

  vector < regla > &getR ()
  {
    return R;
  }

  //Numero de reglas
  unsigned int sizeR () const
  {
    return R.size ();
  }

  void setError (double e);

  void anhade (const regla & r)
  {
    R.push_back (r);
  }

  SEXP toR ();

  void toXML (ofstream & f, Meta & mt);
};

#endif
