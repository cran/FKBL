/*
 *  Michigan.cc
 *
 *  FKBL in R
 *  Fuzzy Knowledge Base Learning
 *
 */

#include "Michigan.h"
#include <iostream>

#include <algorithm>

using namespace std;

IndividuoMichigan::IndividuoMichigan (const regla & r_):
r (r_)
{
}

IndividuoMichigan::IndividuoMichigan (const vector <
				      short int >&A,
				      const int numclases,
				      const vector <
				      particion > &vp,
				      const vector <
				      vector <
				      float > >&datos,
				      const vector <
				      int >&clases)
{
  float confianza, soporte, maxconfianza =
    -1, segundaconfianza = -1, savesoporte = 0;
  int mejorC = 0;

  static vector < float >C (numclases, 0);

  // Calculamos consecuente (maxima confianza - segunda)
  r.setAntecedente (A);
  for (int cc = 0; cc < numclases; cc++)
    {
      for (int i = 0; i < numclases; i++)
	C[i] = 0;
      C[cc] = 1;
      r.setConsecuente (C);
      r.calculaConfianzaSoporte (vp, datos, clases,
				 confianza, soporte);

// Almacenamos la confianza mas alta y la siguiente
      if (confianza > maxconfianza)
	{
	  mejorC = cc;
	  segundaconfianza = maxconfianza;
	  maxconfianza = confianza;
	  savesoporte = soporte;
	}
      else if (confianza > segundaconfianza)
	{
	  segundaconfianza = confianza;
	}

    }

  // Asignamos consecuente y peso
  for (int i = 0; i < numclases; i++)
    C[i] = 0;
  C[mejorC] = maxconfianza - segundaconfianza;
  r.setConsecuente (C);

}

// #define HEURISTICO_SAMPLE

GBML_Michigan::GBML_Michigan (SistemaBorroso & sb)
{
  unsigned int size = sb.sizeR ();
  for (unsigned int i = 0; i < size; i++)
    poblacion.push_back (sb.getR (i));

}

GBML_Michigan::GBML_Michigan (unsigned int size,
			      const int numclases,
			      const vector < particion >
			      &vp,
			      const vector < vector <
			      float > >&datos,
			      const vector < int >&clases):
fitness (size)
{

  // Se seleccionan aleatoriamente varios ejemplos
  // del conjunto de entrenamiento

  for (unsigned int i = 0; i < size; i++)
    {
#ifdef HEURISTICO_SAMPLE
      int pos =
	(int) (rand () / (RAND_MAX + 1.0) * datos.size ());
      // Se busca el antecedente que mejor se ajuste a datos[pos]
      static vector < short int >A (datos[pos].size ());
      float maxp = -1;
      for (int coor = 0; coor < datos[pos].size (); coor++)
	{
	  for (int term = 0; term < vp[coor].size ();
	       term++)
	    {
	      float p = vp[coor].pertenencia (term,
					      datos[pos]
					      [coor]);
	      if (p > maxp)
		{
		  maxp = p;
		  A[coor] = term;
		}
	    }
	}
#else
      static vector < short int >A (datos[0].size ());
      for (unsigned int j = 0; j < A.size (); j++)
	A[j] =
	  (short int) (rand () / (RAND_MAX + 1.0) *
		       (vp[j].size () + 1)) + NOIMPORTA;
#endif



      IndividuoMichigan IM (A, numclases, vp, datos,
			    clases);



      poblacion.push_back (IM);


    }



}


void
GBML_Michigan::evaluaPoblacion (const vector < vector <
				float > >&datos,
				const vector < int >&clases,
				const vector < particion >
				&vp, int numclases)
{

  // Calcula el fitness de todos los individuos de la poblacion
  float maximportancia;
  int reglaganadora;

  for (unsigned int i = 0; i < fitness.size (); i++)
    fitness[i] = 0;

  int nocubiertos = 0;
  for (unsigned int d = 0; d < datos.size (); d++)
    {

      // Solamente una regla puede recibir puntos en caso de empate

      maximportancia = 0;
      reglaganadora = -1;
      int claseganadora = 0;

      // Para cada individuo de la poblacion
      for (unsigned int i = 0; i < poblacion.size (); i++)
	{

	  // Se calcula el grado hasta el que es cierta la regla
	  float matching =
	    poblacion[i].getRegla ().match (vp, datos[d]);

	  // Si la regla es compatible con un ejemplo, al menos
	  if (matching > 0)
	    {
	      float importancia = 0, tmpi;
	      int tmpc = 0;
	      for (int j = 0; j < numclases; j++)
		{
		  tmpi =
		    poblacion[i].getRegla ().
		    getConsecuente (j) * matching;
		  if (importancia < tmpi)
		    {
		      importancia = tmpi;
		      tmpc = j;
		    }
		}
	      if (importancia > maximportancia)
		{
		  maximportancia = importancia;
		  reglaganadora = i;
		  claseganadora = tmpc;
		}
	    }

	}

      if (claseganadora == clases[d])
	{
	  // Sumamos un punto a la regla ganadora
	  if (reglaganadora >= 0)
	    fitness[reglaganadora]++;
	}

      if (reglaganadora == -1)
	{
	  // Puntos no cubiertos
	  nocubiertos++;
	}
    }

#ifdef DEBUG
  cout << "Discovered=" << nocubiertos * 1.0 /
    datos.size () << endl;
#endif
}

bool
  GBML_Michigan::menor_fitness (const vector < int >&a,
				const vector < int >&b)
{
  return b[1] < a[1];
}


void
GBML_Michigan::generacion (int reemplazar,
			   float prob_cruce,
			   float prob_muta,
			   const vector < particion > &vp,
			   const vector < vector <
			   float > >&datos,
			   const vector < int >&clases,
			   int numclases)
{
  // Hacemos una generacion con Michigan

  // Poblacion que se genera
  vector < IndividuoMichigan > intermedia;

  for (int r = 0; r < reemplazar / 2; r++)
    {
      int p1, p2, padre1, padre2;

      // Seleccionamos primer padre
      p1 =
	(int) (rand () / (RAND_MAX + 1.0) *
	       poblacion.size ());
      p2 =
	(int) (rand () / (RAND_MAX + 1.0) *
	       poblacion.size ());
      if (fitness[p1] > fitness[p2])
	padre1 = p1;
      else
	padre1 = p2;

      // Seleccionamos segundo padre
      p1 =
	(int) (rand () / (RAND_MAX + 1.0) *
	       poblacion.size ());
      p2 =
	(int) (rand () / (RAND_MAX + 1.0) *
	       poblacion.size ());
      if (fitness[p1] > fitness[p2])
	padre2 = p1;
      else
	padre2 = p2;

      // Obtenemos los padres
      vector < short int >hijo1 =
	poblacion[padre1].getRegla ().getAntecedente ();
      vector < short int >hijo2 =
	poblacion[padre2].getRegla ().getAntecedente ();

      // Cruzamos los hijos
      if (rand () / (RAND_MAX + 1.0) < prob_cruce)
	for (unsigned int i = 0; i < hijo1.size (); i++)
	  if (rand () / (RAND_MAX + 1.0) < 0.5)
	    swap (hijo1[i], hijo2[i]);

      // Mutamos la descendencia
      for (unsigned int i = 0; i < hijo1.size (); i++)
	if (rand () / (RAND_MAX + 1.0) < prob_muta)
	  // introducimos simbolos 'NOIMPORTA'
	  hijo1[i] =
	    (int) (rand () / (RAND_MAX + 1.0) *
		   (vp[i].size () + 1)) + NOIMPORTA;

      for (unsigned int i = 0; i < hijo2.size (); i++)
	if (rand () / (RAND_MAX + 1.0) < prob_muta)
	  // introducimos simbolos 'NOIMPORTA'
	  hijo2[i] =
	    (int) (rand () / (RAND_MAX + 1.0) *
		   (vp[i].size () + 1)) + NOIMPORTA;

      // Lo almacenamos
      intermedia.
	push_back (IndividuoMichigan
		   (hijo1, numclases, vp, datos, clases));
      intermedia.
	push_back (IndividuoMichigan
		   (hijo2, numclases, vp, datos, clases));


    }


  // Ordenamos por fitness
  vector < vector < int > >indices (fitness.size (),
				   vector < int >(2));
  for (unsigned int i = 0; i < indices.size (); i++)
    {
      indices[i][0] = i;
      indices[i][1] = fitness[i];
    }
  sort (indices.begin (), indices.end (), menor_fitness);

  // Reemplazamos los peores
  for (unsigned int i = 0; i < intermedia.size (); i++)
    {
      poblacion[indices[poblacion.size () - 1 - i][0]] =
	intermedia[i];
    }


}
