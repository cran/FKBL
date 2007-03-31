
/**********************************************
 *  MOGA.h
 *  MOGA
 *
 **********************************************/

#ifndef _MOGA_H
#define _MOGA_H

#define DOMINA 1
#define ESDOMINADO 2

#include "InferenciaBorrosa.h"
#include "train.h"

class MOGA
{
  vector < bool > ind;
  vector < double >fitness;
public:
    vector < bool > &getInd ()
  {
    return ind;
  }
  vector < double >&getFitness ()
  {
    return fitness;
  }

  vector < bool > getInd ()const
  {
    return ind;
  }
  vector < double >getFitness () const
  {
    return fitness;
  }

  bool operator< (MOGA der);
  friend ostream & operator<< (ostream & os, const MOGA &);

  MOGA ();
  MOGA (unsigned int size);
  MOGA (vector < bool > i);

};

class GBML_MOGA
{

  // Algoritmo Genetico de Seleccion Genetica

  vector < regla > BReglas;
  vector < unsigned int >sizeReglas;
    vector < MOGA > poblacion;
    vector < MOGA > elite;
  int mejorPob;
  short int EsDominado (const vector < double >&a,
			const vector < double >&b);
public:
    GBML_MOGA (unsigned int, unsigned int,
	       SistemaBorroso &);

  const regla & operator[] (int n) const;

  unsigned int sizeR () const;
  unsigned int sizeE () const;
  unsigned int sizeP () const;
  SistemaBorroso getElite (SistemaBorroso & sb,
			   unsigned int i);
    vector < double >getFitness (int n) const;
  void evaluaPoblacion (train & tr, SistemaBorroso & sb);
  void generacion (int reemplazar, float prob_cruce,
		   float prob_muta);

  void iniciaElite ();
  void actualizaElite ();
  void mezclaElitePoblacion (unsigned int Nelite);
};
#endif
