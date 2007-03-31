/*
 *  SeleccGenMO.cc
 *  Seleccion Genetica
 *
 *  FKBL in R
 *  Fuzzy Knowledge Base Learning
 *
 */


#include "SeleccGenMO.h"
#include <iostream>

#include <algorithm>

using namespace std;



GBML_SeleccGenMO::GBML_SeleccGenMO (int pSize,
				    SistemaBorroso & sb_):
sb (sb_),
fitness (pSize, vector < double >(OBJETIVOS)),
mejorPob (0)
{

  // Se seleccionan aleatoriamente varios ejemplos
  // del conjunto de entrenamiento

  vector < bool > A (sb.sizeR (), 1);
  poblacion.push_back (A);

  for (int i = 0; i < pSize - 1; i++)
    {
      for (unsigned int j = 0; j < A.size (); j++)
	A[j] = ((rand () / (RAND_MAX + 1.0)) < 0.5) ? 0 : 1;

      poblacion.push_back (A);
    }
}

void
GBML_SeleccGenMO::evaluaPoblacion (train & tr_,
				   SistemaBorroso & sb_,
				double k_)
{				//TODO
  // Calcula el fitness de todos los individuos de la poblacion
  float maximportancia;
  int reglaganadora;

  for (unsigned int i = 0; i < fitness.size (); i++)
    {
      fitness[i][0] = 0;	//Numero aciertos
      fitness[i][1] = 0;	//Numero unos
    }

  for (unsigned int i = 0; i < poblacion.size (); i++)
    for (unsigned int r = 0; r < BReglas.size (); r++)
      if (poblacion[i].getInd ()[r])
	fitness[i][1] -= k_;

  int nocubiertos = 0;
  for (unsigned int d = 0; d < tr_.datos.size (); d++)
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
				    tr_.datos[d]);

		// Si la regla es compatible con un ejemplo, al menos
		if (matching > 0)
		  {
		    float importancia = 0, tmpi;
		    int tmpc = 0;
		    for (int j = 0; j < sb_.getNumClases ();
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

	  if (claseganadora == tr_.clases[d])
	    {
	      // Sumamos un punto a la regla ganadora y que falle
	      if (reglaganadora >= 0)
		fitness[i][0]++;
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
    tr_.datos.size () << endl;
#endif
}

void
GBML_SeleccGenMO::generacion (int reemplazar,
			      float prob_cruce,
			      float prob_muta)
{
  // Hacemos una generacion con Michigan

  // Poblacion que se genera
  vector < SeleccGen > intermedia;

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
      if (fitness[p1] < fitness[p2])	//STARGATE
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
      if (fitness[p1] < fitness[p2])	//STARGATE
	padre2 = p1;
      else
	padre2 = p2;

      // Obtenemos los padres
      vector < bool > hijo1 = poblacion[padre1].getInd ();
      vector < bool > hijo2 = poblacion[padre2].getInd ();

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

      // Mutamos la descendencia
      for (unsigned int i = 0; i < hijo1.size (); i++)
	if (rand () / (RAND_MAX + 1.0) < prob_muta)
	  hijo1[i] =
	    (rand () / (RAND_MAX + 1.0) < 0.5) ? 0 : 1;

      for (unsigned int i = 0; i < hijo2.size (); i++)
	if (rand () / (RAND_MAX + 1.0) < prob_muta)
	  hijo2[i] =
	    (rand () / (RAND_MAX + 1.0) < 0.5) ? 0 : 1;

      // Lo almacenamos
      intermedia.push_back (SeleccGen (hijo1));
      intermedia.push_back (SeleccGen (hijo2));
    }

  // Ordenamos por fitness
  vector < pair < int, bool > >indices (fitness.size ());
  for (unsigned int i = 0; i < indices.size (); i++)
    {
      indices[i].first = i;
      indices[i].second = 1;
    }

  for (unsigned int i = 0; i < indices.size (); i++)
    for (unsigned int j = i + 1; j < indices.size (); j++)
      switch (EsDominado (fitness[i], fitness[j]))
	{
	case DOMINA:
	  indices[j].second = 0;
	  break;
	case ESDOMINADO:
	  indices[i].second = 0;
	  break;
	};

  sort (indices.begin (), indices.end (), nodominados);

  int tamanyo = indices.size ();
  for (; tamanyo > 0 && indices[tamanyo - 1].second;
       tamanyo--);

#ifdef DEBUG
  for (unsigned int i = 0; i < indices.size (); i++)
    cout << fitness[i][0] << "\t";
  cout << endl;
  for (unsigned int i = 0; i < indices.size (); i++)
    cout << fitness[i][1] << "\t";
  cout << endl;
  for (unsigned int i = 0; i < indices.size (); i++)
    cout << indices[i].second << "\t";

  static bool s = 1;
  if (s)
    s = ('q' != cin.get ());

  cout << endl;
#endif

  // Reemplazamos los peores
  for (unsigned int i = 0; i < intermedia.size (); i++)
    {
      int iAux =
	(int) (rand () / (RAND_MAX + 1.0) * tamanyo);
      poblacion[iAux] = intermedia[i];
    }

//TODO
// mejorPob sería un vector de nodominados


  mejorPob.resize (0);
  for (int i = (indices.size () - 1);
       indices[i].second && i >= 0; i--)
    {
      mejorPob.push_back (indices[indices.size () - 1].
			  first);
    }

}

SistemaBorroso
GBML_SeleccGenMO::getSB (SistemaBorroso & sb, int index)
{
  SistemaBorroso
    sbAprendido (sb.getP (), vector < regla > (0),
		 sb.getNumClases ());

  index = mejorPob[index % mejorPob.size ()];

  for (unsigned int i = 0; i < BReglas.size (); i++)
    if (poblacion[index].getInd ()[i])
      sbAprendido.anhade (BReglas[i]);

//  sbAprendido.setError (errores (tr.clases, 
//  inferencia (sbAprendido, tr)) 
// / (double) tr.clases.size ());

  return sbAprendido;
}

bool
GBML_SeleccGenMO::nodominados (const pair < int, bool > &a,
			       const pair < int, bool > &b)
{
  return a.second < b.second;
}

short int
GBML_SeleccGenMO::EsDominado (const vector < double >&a,
			      const vector < double >&b)
{
  //DOMINA >
  //ESDOMINADO <
  unsigned int i = 0;
  bool Bdomina = 0,		// 1 si y solo si existe a[i]<b[i]
    Bdominado = 0;

  for (; i < a.size (); i++)
    {
      if (a[i] <= b[i])
	break;
      if (!Bdomina && a[i] < b[i])
	Bdomina = 1;
    }

  if (Bdomina && i == a.size ())
    return DOMINA;

  for (i = 0; i < a.size (); i++)
    {
      if (a[i] >= b[i])
	break;
      if (!Bdominado && a[i] < b[i])
	Bdominado = 1;
    }

  if (Bdominado && i == a.size ())
    return ESDOMINADO;

  return 0;
}
