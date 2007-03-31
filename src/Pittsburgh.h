/*
 *  Pittsburgh.h
 *
 *  FKBL in R
 *  Fuzzy Knowledge Base Learning
 *
 */

#ifndef _PITTSBURGH_H
#define _PITTSBURGH_H

#include "InferenciaBorrosa.h"
#include "Michigan.h"

class IndividuoPittsburgh
{

  // Un individuo Pittsburgh es una base de reglas borrosas

  vector < IndividuoMichigan > vr;

public:

  const IndividuoMichigan & operator[] (unsigned int n) const
  {
    return vr[n];
  }
  IndividuoMichigan & operator[] (int n)
  {
    return vr[n];
  }
  int size () const
  {
    return (int) vr.size ();
  }

  IndividuoPittsburgh (const vector < vector <
		       short int > >&A, const int numclases,
		       const vector < particion > &vp,
		       const vector < vector <
		       float > >&datos,
		       const vector < int >&clases);
  IndividuoPittsburgh (const vector < IndividuoMichigan >
		       &vm)
  {
    vr = vm;
  }

};


class GBML_Pittsburgh
{

  // Algoritmo Genetico tipo Pittsburgh hibrido

  vector < IndividuoPittsburgh > poblacion;
  vector < vector < float > >fitness;

  static bool menor_fitness (const vector < float >&a,
			     const vector < float >&b);


public:

  const IndividuoPittsburgh & operator[] (int n) const;


  int size () const;
  float getFitnessMich (int i, int j) const;
  void showFitness (float &mejorf, float &avgf,
		    int &elite) const;


    GBML_Pittsburgh (int size,
		     const int numreglas,
		     const int numclases,
		     const vector < particion > &vp,
		     const vector < vector < float > >&datos,
		     const vector < int >&clases);

    vector <
    float >evaluaIndividuo (const IndividuoPittsburgh & ip,
			    const vector < vector <
			    float > >&datos,
			    const vector < int >&clases,
			    const vector < particion > &vp,
			    int numclases);

  void evaluaPoblacion (const vector < vector <
			float > >&datos,
			const vector < int >&clases,
			const vector < particion > &vp,
			int numclases);


  void generacion (int reemplazar,
		   float prob_cruce,
		   float prob_muta,
		   float prob_cruceM,
		   float prob_mutaM,
		   const vector < particion > &vp,
		   const vector < vector < float > >&datos,
		   const vector < int >&clases,
		   int numclases);

  void mutacionMichigan (IndividuoPittsburgh & pob,
			 int reemplazar,
			 float prob_cruce,
			 float prob_muta,
			 const vector < particion > &vp,
			 const vector < vector <
			 float > >&datos,
			 const vector < int >&clases,
			 int numclases);


};

#endif
