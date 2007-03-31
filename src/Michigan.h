
/*
 *  Michigan.h
 *
 *  FKBL in R
 *  Fuzzy Knowledge Base Learning
 *
 */

#ifndef _MICHIGAN_H
#define _MICHIGAN_H

#include "InferenciaBorrosa.h"

class IndividuoMichigan
{

  // Un individuo Michigan es una regla borrosa

  regla r;

public:

    regla & getRegla ()
  {
    return r;
  }
  const regla & getRegla () const
  {
    return r;
  }

  IndividuoMichigan ()
  {
  }

  IndividuoMichigan (const regla &);

  IndividuoMichigan (const vector < short int >&A,
		     const int numclases,
		     const vector < particion > &vp,
		     const vector < vector < float > >&datos,
		     const vector < int >&clases);

};


class GBML_Michigan
{

  // Algoritmo Genetico tipo Michigan

  vector < IndividuoMichigan > poblacion;
  vector < int >fitness;

  static bool menor_fitness (const vector < int >&a,
			     const vector < int >&b);


public:

  const IndividuoMichigan & operator[] (int n) const
  {
    return poblacion[n];
  }
  int size () const
  {
    return (int) poblacion.size ();
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

  GBML_Michigan (SistemaBorroso & sb);

    GBML_Michigan (unsigned int size,
		   const int numclases,
		   const vector < particion > &vp,
		   const vector < vector < float > >&datos,
		   const vector < int >&clases);

  void evaluaPoblacion (const vector < vector <
			float > >&datos,
			const vector < int >&clases,
			const vector < particion > &vp,
			int numclases);
//      void evaluaTamanyo(double k);
  void generacion (int reemplazar,
		   float prob_cruce,
		   float prob_muta,
		   const vector < particion > &vp,
		   const vector < vector < float > >&datos,
		   const vector < int >&clases,
		   int numclases);

};

#endif
