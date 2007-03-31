
/*
 *  SeleccGen.h
 *
 *  FKBL in R
 *  Fuzzy Knowledge Base Learning
 *
 */

#ifndef _SELECCGEN_H
#define _SELECCGEN_H

#include "InferenciaBorrosa.h"
#include "train.h"

class SeleccGen
{
  vector < bool > ind;
public:
  vector < bool > &getInd ()
  {
    return ind;
  }
//      const vector<bool> &getInd(){ return ind; }

  SeleccGen ()
  {
  }
  SeleccGen (unsigned int size);
SeleccGen (vector < bool > i_):ind (i_)
  {
  }
};

class GBML_SeleccGen
{

  // Algoritmo Genetico de Seleccion Genetica

  vector < regla > BReglas;
  vector < SeleccGen > poblacion;
  vector < double >fitness;
  int mejorPob;

  static bool mayor_fitness (const pair < int, double >&a,
			     const pair < int, double >&b);


public:

  const regla & operator[] (int n) const
  {
    return BReglas[n];
  }
  int sizeR () const
  {
    return BReglas.size ();
  }

  bool getMejor (int index)
  {
    return poblacion[mejorPob].getInd ()[index];
  }

  float getFitness (int n) const
  {
    return (float) fitness[n];
  }
  float getSumaFitness () const
  {
    float suma = 0;
    for (unsigned int i = 0; i < fitness.size (); i++)
        suma += fitness[i];
      return suma;
  }


  GBML_SeleccGen (int, SistemaBorroso &);

  void evaluaPoblacion (train & tr, SistemaBorroso & sb,
			double k = 0.01);

  void generacion (int reemplazar,
		   float prob_cruce, float prob_muta);

};

#endif
