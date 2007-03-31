/*
 *  SeleccGen.cc
 *
 *  FKBL in R
 *  Fuzzy Knowledge Base Learning
 *
 */

#include "SeleccGen.h"
#include <iostream>

#include <algorithm>

using namespace std;

SeleccGen::SeleccGen (unsigned int size):
ind (size)
{
  for (unsigned int i = 0; i < size; i++)
    ind[i] = (rand () / (RAND_MAX + 1.0) < 0.5) ? 1 : 0;
}


GBML_SeleccGen::GBML_SeleccGen (int pSize,
				SistemaBorroso & sb):
fitness (pSize)
{

  // Se seleccionan aleatoriamente varios ejemplos
  // del conjunto de entrenamiento

  unsigned int size = sb.sizeR ();
  for (unsigned int i = 0; i < size; i++)
    BReglas.push_back (sb.getR (i));

  vector < bool > A (size, 1);

  poblacion.push_back (A);

  for (int i = 0; i < pSize - 1; i++)
    {
      for (unsigned int j = 0; j < A.size (); j++)
	A[j] = ((rand () / (RAND_MAX + 1.0)) < 0.5) ? 0 : 1;

      poblacion.push_back (A);

    }


}

void
GBML_SeleccGen::evaluaPoblacion (train & tr,
				 SistemaBorroso & sb,
				 double k)
{				//TODO
  // Calcula el fitness de todos los individuos de la poblacion
  float maximportancia;
  int reglaganadora;

  for (unsigned int i = 0; i < fitness.size (); i++)
    fitness[i] = 0;

  for (unsigned int i = 0; i < poblacion.size (); i++)
    for (unsigned int r = 0; r < BReglas.size (); r++)
      if (poblacion[i].getInd ()[r])
	fitness[i] -= k;

  int nocubiertos = 0;
  for (unsigned int d = 0; d < tr.datos.size (); d++)
    {

      // Para cada individuo de la poblacion
      for (unsigned int i = 0; i < poblacion.size (); i++)
	{

	  maximportancia = 0;
	  reglaganadora = -1;
	  int claseganadora = 0;


	  for (unsigned int r = 0; r < BReglas.size (); r++)
	    if (poblacion[i].getInd ()[r])
	      {

		// Se calcula el grado hasta el que es cierta la regla
		float matching =
		  BReglas[r].match (sb.getP (),
				    tr.datos[d]);

		// Si la regla es compatible con un ejemplo, al menos
		if (matching > 0)
		  {
		    float importancia = 0, tmpi;
		    int tmpc = 0;
		    for (int j = 0; j < sb.getNumClases ();
			 j++)
		      {
			tmpi =
			  BReglas[r].getConsecuente (j) *
			  matching;
			if (importancia < tmpi)
			  {
			    importancia = tmpi;
			    tmpc = j;
			  }
		      }		//for NumClases

		    if (importancia > maximportancia)
		      {
			maximportancia = importancia;
			reglaganadora = i;
			claseganadora = tmpc;
		      }
		  }		//If matching

	      }			//for regla

	  if (claseganadora == tr.clases[d])
	    {
	      // Sumamos un punto a la regla ganadora y que falle
	      if (reglaganadora >= 0)
		fitness[i]++;
	    }

	  if (reglaganadora == -1)
	    {
	      // Puntos no cubiertos
	      nocubiertos++;
	    }

	}			//for poblacion

    }				//for datos

#ifdef DEBUG
  cout << "Discovered=" << nocubiertos * 1.0 /
    tr.datos.size () << endl;
#endif
}

bool
  GBML_SeleccGen::mayor_fitness (const pair < int,
				 double >&a,
				 const pair < int,
				 double >&b)
{
  return b.second < a.second;
}


void
GBML_SeleccGen::generacion (int reemplazar,
			    float prob_cruce,
			    float prob_muta)
{
  // Hacemos una generacion con Michigan

  // Poblacion que se genera
  vector < SeleccGen > intermedia;

  //cout << "Antes de hacer nada" <<endl;

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
      if (fitness[p1] < fitness[p2])
	padre1 = p1;
      else
	padre1 = p2;

      //cout << "Seleccionado el primer padre" << endl;

      // Seleccionamos segundo padre
      p1 =
	(int) (rand () / (RAND_MAX + 1.0) *
	       poblacion.size ());
      p2 =
	(int) (rand () / (RAND_MAX + 1.0) *
	       poblacion.size ());
      if (fitness[p1] < fitness[p2])
	padre2 = p1;
      else
	padre2 = p2;

      //cout << "Seleccionado el segundo padre" << endl;

      // Obtenemos los padres
      vector < bool > hijo1 = poblacion[padre1].getInd ();
      vector < bool > hijo2 = poblacion[padre2].getInd ();

      //cout << "Padres obtenidos" <<endl;

      // Cruzamos los hijos
      if (rand () / (RAND_MAX + 1.0) < prob_cruce)
	for (unsigned int i = 0; i < hijo1.size (); i++)
	  if (rand () / (RAND_MAX + 1.0) < 0.5)
	    {
	      bool auxB;
	      auxB = hijo1[i];
	      hijo1[i] = hijo2[i];
	      hijo2[i] = auxB;
	    }

      //cout << "Hijos cruzados " << endl;

      // Mutamos la descendencia
      for (unsigned int i = 0; i < hijo1.size (); i++)
	if (rand () / (RAND_MAX + 1.0) < prob_muta)
	  hijo1[i] =
	    (rand () / (RAND_MAX + 1.0) < 0.5) ? 0 : 1;

      for (unsigned int i = 0; i < hijo2.size (); i++)
	if (rand () / (RAND_MAX + 1.0) < prob_muta)
	  hijo2[i] =
	    (rand () / (RAND_MAX + 1.0) < 0.5) ? 0 : 1;

      //cout << "Mutado" <<endl;

      // Lo almacenamos
      intermedia.push_back (SeleccGen (hijo1));
      intermedia.push_back (SeleccGen (hijo2));

      //cout << "Almacenado" <<endl;
    }

  //cout << "fitness " << fitness.size() << endl;

  // Ordenamos por fitness
  vector < pair < int, double > >indices (fitness.size ());
  for (unsigned int i = 0; i < indices.size (); i++)
    {
      indices[i].first = i;
      indices[i].second = fitness[i];
    }

#ifdef DEBUG
  cout << "Antes:";
  for (unsigned int i = 0; i < indices.size (); i++)
    cout << " " << indices[i].second;
  cout << endl;
#endif

  sort (indices.begin (), indices.end (), mayor_fitness);

  //cout << "Ordenado" <<endl;

#ifdef DEBUG
  cout << "Despu:";
  for (unsigned int i = 0; i < indices.size (); i++)
    cout << " " << indices[i].second;
  cout << "####" << endl;
#endif

  // Reemplazamos los peores
  for (unsigned int i = 0; i < intermedia.size (); i++)
    {
      poblacion[indices[indices.size () - 1 - i].first] =
	intermedia[i];
    }

  if (indices.size ())
    mejorPob = indices[0].first;

  //cout << "Despues de todo " <<endl;

}
