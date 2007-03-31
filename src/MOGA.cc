/*
 *
 *  MOGA.cc
 *  Multi Objective Genetic Algorithm
 *
 *  FKBL in R
 *  Fuzzy Knowledge Base Learning
 *
 */

#include "MOGA.h"
#include <iostream>

#include <algorithm>

using namespace std;

MOGA::MOGA (unsigned int size):
ind (size), fitness (3, 0)	//3 == error, size, clausules
{
  for (unsigned int i = 0; i < size; i++)
    ind[i] = (rand () / (RAND_MAX + 1.0) < 0.5) ? 1 : 0;
}

MOGA::MOGA (vector < bool > i):ind (i), fitness (3, 0)
{
}

MOGA::MOGA ():fitness (3, 0)
{
}

bool
MOGA::operator< (MOGA der)
{
  double wt = 0, f1 = 0, f2 = 0;
  vector < double >wi (fitness.size ());

  for (unsigned int i = 0; i < wi.size (); i++)
    {
      wi[i] = rand ();
      wt += wi[i];
    }

  for (unsigned int i = 0; i < wi.size (); i++)
    wi[i] /= wt;

  for (unsigned int i = 0; i < wi.size (); i++)
    {
      f1 += fitness[i] * wi[i];
      f2 += der.fitness[i] * wi[i];
    }

  return f1 < f2;
}

GBML_MOGA::GBML_MOGA (unsigned int Npop, unsigned int Nelite, 
SistemaBorroso & sb):sizeReglas (sb.sizeR (),0)
//, poblacion(Npop,MOGA(sb.sizeR()))
{
  unsigned int
    size = sb.sizeR ();
  for (unsigned int i = 0; i < size; i++)
    {
      BReglas.push_back (sb.getR (i));
      for (unsigned int j = 0;
	   j < BReglas[i].getAntecedente ().size (); j++)
	if (BReglas[i].getAntecedente ()[j] >= 0)
	  sizeReglas[i]++;
    }

  for (unsigned int i = 0; i < Npop; i++)
    poblacion.push_back (MOGA (sb.sizeR ()));


  // for(unsigned int i = 0; i<Npop; i++)
  //  cout << poblacion[i] <<endl;
}

void
GBML_MOGA::iniciaElite ()
{
  vector < bool > EsElite (poblacion.size (), 1);
  //buscar los no dominados y meterlos en la poblacion elite
  for (unsigned int i = 0; i < poblacion.size (); i++)
    {
      for (unsigned int j = i + 1; j < poblacion.size ();
	   j++)
	if (EsElite[i] && EsElite[j])
//Si uno de ellos se sabe que es dominado, 
// no se realiza la comparacion
	  switch (EsDominado
		  (poblacion[i].getFitness (),
		   poblacion[j].getFitness ()))
	    {
	    case DOMINA:
	      EsElite[j] = 0;
	      break;
	    case ESDOMINADO:
	      EsElite[i] = 0;
	      break;
	    };
      if (EsElite[i])
	elite.push_back (poblacion[i]);
    }
}

void
GBML_MOGA::actualizaElite ()
{
  //Busca soluciones no dominadas por la elite 
  //y las añade a la elite, 
  //Al añadir, borra las de elite que sean 
  //dominadas por este nuevo elite
  bool EstaDominado = 0;

  for (unsigned int i = 0; i < poblacion.size (); i++)
    {
      EstaDominado = 0;

      for (unsigned int j = 0;
	   j < elite.size () && !EstaDominado; j++)
	{
	  switch (EsDominado
		  (poblacion[i].getFitness (),
		   elite[j].getFitness ()))
	    {
	    case DOMINA:
	      elite.erase (elite.begin () + j);
	      j--;
	      break;
	    case ESDOMINADO:
	      EstaDominado = 1;
	    };
	}
      if (!EstaDominado)
	elite.push_back (poblacion[i]);
    }
}

void
GBML_MOGA::evaluaPoblacion (train & tr, SistemaBorroso & sb)
{				//TODO
  // Calcula el fitness de todos los individuos de la poblacion
  float maximportancia;
  int reglaganadora;

  for (unsigned int i = 0; i < poblacion.size (); i++)
    for (unsigned int j = 0;
	 j < poblacion[i].getFitness ().size (); j++)
      poblacion[i].getFitness ()[j] = 0;

  for (unsigned int i = 0; i < poblacion.size (); i++)
    for (unsigned int r = 0; r < BReglas.size (); r++)
      if (poblacion[i].getInd ()[r])
	{
	  poblacion[i].getFitness ()[2] -= sizeReglas[r];
	  //STARGATE does this work? 2 == size rules
	  poblacion[i].getFitness ()[1] -= 1;
	  //STARGATE does this work? 1 == # rules
	}

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
		poblacion[i].getFitness ()[0]++;	//STARGATE does this work?
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

  // cout << "Evalua poblacion"<<endl;
  // for(unsigned int i = 0; i<poblacion.size(); i++)
  //   cout << poblacion[i] <<endl;
}

//const regla & GBML_MOGA::operator[](int n) 
//const { return BReglas[n]; }

unsigned int
     GBML_MOGA::sizeE () const 
     {
       return elite.size ();
     }

     unsigned int GBML_MOGA::sizeP () const 
     {
       return poblacion.size ();
     }

     unsigned int GBML_MOGA::sizeR () const
     {
       return BReglas.size ();
     }

     vector < double >GBML_MOGA::getFitness (int n) const 
     {
       return poblacion[n].getFitness ();
     }

     void
       GBML_MOGA::generacion (int reemplazar,
			      float prob_cruce,
			      float prob_muta)
{
  // Hacemos una generacion 

  // Poblacion que se genera
  vector < MOGA > intermedia;

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
      if (poblacion[p1] < poblacion[p2])
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
      if (poblacion[p1] < poblacion[p2])
	padre2 = p1;
      else
	padre2 = p2;

      //cout << "Seleccionado el segundo padre" << endl;

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
      intermedia.push_back (MOGA (hijo1));
      intermedia.push_back (MOGA (hijo2));
    }

  // poblacion.clear();  //FALLA STARGATE
  // poblacion.resize(0);

  poblacion = intermedia;
}


short int
GBML_MOGA::EsDominado (const vector < double >&a,
		       const vector < double >&b)
{
  //DOMINA >
  //ESDOMINADO <
  unsigned int i = 0;
  bool Bdomina = 0,		// 1 si y solo si existe a[i]<b[i]
    Bdominado = 0;


  for (; i < a.size (); i++)
    {
      if (a[i] < b[i])
	break;
      if (!Bdomina && a[i] > b[i])
	Bdomina = 1;
    }

  if (Bdomina && i == a.size ())
    return DOMINA;

  Bdomina = 0;

  for (i = 0; i < a.size (); i++)
    {
      if (a[i] > b[i])
	break;
      if (!Bdominado && a[i] < b[i])
	Bdominado = 1;
    }

  if (Bdominado && i == a.size ())
    return ESDOMINADO;

  return 0;
}


void
GBML_MOGA::mezclaElitePoblacion (unsigned int Nelite)
{
  for (unsigned int i = 0; i < Nelite; i++)
    poblacion.
      push_back (elite
		 [(unsigned int) (rand () /
				  (RAND_MAX +
				   1.0) * elite.size ())]);
}

SistemaBorroso
  GBML_MOGA::getElite (SistemaBorroso & sb,
		       unsigned int index)
{
  SistemaBorroso
    sbAprendido (sb.getP (), vector < regla > (0),
		 sb.getNumClases ());

  for (unsigned int i = 0; i < BReglas.size (); i++)
    if (elite[index].getInd ()[i])
      sbAprendido.anhade (BReglas[i]);

  //  elite[index];

  return sbAprendido;
}

ostream & operator<< (ostream & os, const MOGA & m)
{
  os << '[' << m.ind[0];
  for (unsigned int i = 1; i < m.ind.size (); i++)
    os << ',' << m.ind[i];
  os << ']';
  for (unsigned int i = 0; i < m.fitness.size (); i++)
    os << ' ' << m.fitness[i];

  return os;
}
