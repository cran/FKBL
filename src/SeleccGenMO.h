
/*
 *  SeleccGenMO.h
 *  Seleccion Genetica Multi Objetivo
 *
 *  FKBL in R
 *  Fuzzy Knowledge Base Learning
 *
 */

#ifndef _SELECCGENMO_H
#define _SELECCGENMO_H

#include "SeleccGen.h"
#include "train.h"

#define OBJETIVOS 2

#define DOMINA 1
#define ESDOMINADO 2

class GBML_SeleccGenMO
{

  // Algoritmo Genetico de Seleccion Genetica MO

  SistemaBorroso sb;
    vector < regla > BReglas;
    vector < SeleccGen > poblacion;
    vector < vector < double > >fitness;

    vector < int >mejorPob;

  short int EsDominado (const vector < double >&a,
			const vector < double >&b);

  static bool nodominados (const pair < int, bool > &a,
			   const pair < int, bool > &b);
public:

  unsigned int size ()
  {
    return mejorPob.size ();
  }

  const regla & operator[] (int n) const
  {
    return BReglas[n];
  }
  int sizeR () const
  {
    return BReglas.size ();
  }

  SistemaBorroso getSB (SistemaBorroso & sb, int index);

  float getFitness (int n) const
  {
    return fitness[n][0] + fitness[n][1];
  }
  float getSumaFitness () const
  {
    float suma = 0;
    for (unsigned int i = 0; i < fitness.size (); i++)
        suma += fitness[i][0] + fitness[i][1];
      return suma;
  }


  GBML_SeleccGenMO (int, SistemaBorroso &);

  void evaluaPoblacion (train &, SistemaBorroso &,
			double k = 0.01);

  void generacion (int reemplazar,
		   float prob_cruce, float prob_muta);

};

#endif
