/*
 *  Pittsburgh.cc
 *  
 *  FKBL in R
 *  Fuzzy Knowledge Base Learning
 *
 */

#include "Pittsburgh.h"
#include "Michigan.h"
#include <iostream>

#include <algorithm>

using namespace std;

IndividuoPittsburgh::IndividuoPittsburgh (const vector <
					  vector <
					  short int > >&A,
					  const int
					  numclases,
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
  static vector < float >C (numclases);


  for (unsigned int nr = 0; nr < A.size (); nr++)
    {

      IndividuoMichigan r;

      // Calculamos consecuente (maxima confianza - segunda)
      r.getRegla ().setAntecedente (A[nr]);
      for (int cc = 0; cc < numclases; cc++)
	{

	  for (int i = 0; i < numclases; i++)
	    C[i] = 0;
	  C[cc] = 1;
	  r.getRegla ().setConsecuente (C);

	  r.getRegla ().calculaConfianzaSoporte (vp, datos,
						 clases,
						 confianza,
						 soporte);

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
      r.getRegla ().setConsecuente (C);

      vr.push_back (r);
    }
}

// #define HEURISTICO_SAMPLE

GBML_Pittsburgh::GBML_Pittsburgh (int size,
				  const int numreglas,
				  const int numclases,
				  const vector < particion >
				  &vp,
				  const vector < vector <
				  float > >&datos,
				  const vector <
				  int >&clases):
fitness (size, vector < float >(numreglas))
{

  for (int nr = 0; nr < numreglas; nr++)
    {

      // Se seleccionan aleatoriamente varios ejemplos
      // del conjunto de entrenamiento

      vector < IndividuoMichigan > ind;

      for (int i = 0; i < size; i++)
	{
#ifdef HEURISTICO_SAMPLE
	  int pos =
	    (int) (rand () / (RAND_MAX + 1.0) *
		   datos.size ());
	  // std::cout << "** P=" << pos << " ";
	  // Se busca el antecedente que mejor se ajuste a datos[pos]
	  vector < int >A (datos[pos].size ());
	  float maxp = -1;
	  for (int coor = 0; coor < datos[pos].size ();
	       coor++)
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
	  vector < short int >A (datos[0].size ());
	  for (unsigned int j = 0; j < A.size (); j++)
	    A[j] =
	      (int) (rand () / (RAND_MAX + 1.0) *
		     (vp[j].size () + 1)) + NOIMPORTA;
#endif

	  IndividuoMichigan IM (A, numclases, vp, datos,
				clases);
	  ind.push_back (IM);

	}
      poblacion.push_back (IndividuoPittsburgh (ind));

    }

}

vector < float >
GBML_Pittsburgh::

evaluaIndividuo (const IndividuoPittsburgh & ip,
		 const vector < vector < float > >&datos,
		 const vector < int >&clases,
		 const vector < particion > &vp,
		 int numclases)
{

  // Calcula el fitness de un individuo
  float maximportancia;
  int reglaganadora;


  vector < float >fit (ip.size ());


  for (unsigned int d = 0; d < datos.size (); d++)
    {

      // Solamente una regla puede recibir puntos en caso de empate

      maximportancia = 0;
      reglaganadora = -1;
      int claseganadora = 0;

      // Para cada individuo de la poblacion
      for (int i = 0; i < ip.size (); i++)
	{

	  // Se calcula el grado hasta el que es cierta la regla
	  float matching =
	    ip[i].getRegla ().match (vp, datos[d]);

	  // Si la regla es compatible con un ejemplo, al menos
	  if (matching > 0)
	    {
	      float importancia = 0, tmpi;
	      int tmpc = 0;
	      for (int j = 0; j < numclases; j++)
		{
		  tmpi =
		    ip[i].getRegla ().getConsecuente (j) *
		    matching;
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
	    fit[reglaganadora]++;
	}
    }

  return fit;

}


void
GBML_Pittsburgh::evaluaPoblacion (const vector < vector <
				  float > >&datos,
				  const vector <
				  int >&clases,
				  const vector < particion >
				  &vp, int numclases)
{
  for (unsigned int i = 0; i < poblacion.size (); i++)
    fitness[i] =
      evaluaIndividuo (poblacion[i], datos, clases, vp,
		       numclases);

}

bool
  GBML_Pittsburgh::menor_fitness (const vector < float >&a,
				  const vector < float >&b)
{
  return b[1] < a[1];
}


void
GBML_Pittsburgh::
mutacionMichigan (IndividuoPittsburgh & pob, int reemplazar,
		  float prob_cruce, float prob_muta,
		  const vector < particion > &vp,
		  const vector < vector < float > >&datos,
		  const vector < int >&clases,
		  int numclases)
{

  // Evaluamos el individuo como si fuese una poblacion Michigan
  vector < float >fit =
    evaluaIndividuo (pob, datos, clases, vp, numclases);

  // Poblacion que se genera
  vector < IndividuoMichigan > intermedia;

  for (int r = 0; r < reemplazar / 2; r++)
    {

      int p1, p2, padre1, padre2;

      // Seleccionamos primer padre
      p1 = (int) (rand () / (RAND_MAX + 1.0) * pob.size ());
      p2 = (int) (rand () / (RAND_MAX + 1.0) * pob.size ());
      if (fit[p1] > fit[p2])
	padre1 = p1;
      else
	padre1 = p2;

      // Seleccionamos segundo padre
      p1 = (int) (rand () / (RAND_MAX + 1.0) * pob.size ());
      p2 = (int) (rand () / (RAND_MAX + 1.0) * pob.size ());
      if (fit[p1] > fit[p2])
	padre2 = p1;
      else
	padre2 = p2;

      // Cruzamos los padres
      vector < short int >hijo1 =
	pob[padre1].getRegla ().getAntecedente ();
      vector < short int >hijo2 =
	pob[padre2].getRegla ().getAntecedente ();

      // Cruzamos los hijos
      if (rand () / (RAND_MAX + 1.0) < prob_cruce)
	{
	  for (unsigned int i = 0; i < hijo1.size (); i++)
	    {
	      if (rand () / (RAND_MAX + 1.0) < 0.5)
		{
		  swap (hijo1[i], hijo2[i]);
		}
	    }
	}

      // Mutamos la descendencia
      for (unsigned int i = 0; i < hijo1.size (); i++)
	{
	  if (rand () / (RAND_MAX + 1.0) < prob_muta)
	    {
	      // introducimos simbolos 'NOIMPORTA'
	      hijo1[i] =
		(short int) (rand () / (RAND_MAX + 1.0) *
			     (vp[i].size () + 1)) +
		NOIMPORTA;
	    }
	}

      for (unsigned int i = 0; i < hijo2.size (); i++)
	{
	  if (rand () / (RAND_MAX + 1.0) < prob_muta)
	    {
	      // introducimos simbolos 'NOIMPORTA'
	      hijo2[i] =
		(short int) (rand () / (RAND_MAX + 1.0) *
			     (vp[i].size () + 1)) +
		NOIMPORTA;
	    }
	}

      // Lo almacenamos
      intermedia.
	push_back (IndividuoMichigan
		   (hijo1, numclases, vp, datos, clases));
      intermedia.
	push_back (IndividuoMichigan
		   (hijo2, numclases, vp, datos, clases));

    }

  // Ordenamos por fitness
  vector < vector < float > >indices (pob.size (),
				     vector < float >(2));
  for (unsigned int i = 0; i < indices.size (); i++)
    {
      indices[i][0] = i;
      indices[i][1] = fit[i];
    }
  sort (indices.begin (), indices.end (), menor_fitness);

  // Reemplazamos los peores
  for (unsigned int i = 0; i < intermedia.size (); i++)
    {
      pob[(int) (indices[poblacion.size () - 1 - i][0])] =
	intermedia[i];
    }

}

void
GBML_Pittsburgh::generacion (int reemplazar,
			     float prob_cruce,
			     float prob_muta,
			     float prob_cruceM,
			     float prob_mutaM,
			     const vector < particion > &vp,
			     const vector < vector <
			     float > >&datos,
			     const vector < int >&clases,
			     int numclases)
{

  // Hacemos una generacion con Pittsburgh, 
  // y una mutacion con Michigan
  vector < float >sumafit (fitness.size ());

  vector < IndividuoPittsburgh > intermedia;

  for (unsigned int i = 0; i < sumafit.size (); i++)
    for (unsigned int j = 0; j < fitness[i].size (); j++)
      sumafit[i] += fitness[i][j];

  // Buscamos la elite y la guardamos en la poblacion intermedia
  int elite = 0;
  float max = -1;
  for (unsigned int i = 0; i < fitness.size (); i++)
    {
      if (sumafit[i] > max)
	{
	  max = sumafit[i];
	  elite = i;
	}
    }
  intermedia.push_back (poblacion[elite]);

  int p1, p2, padre1, padre2;
  do
    {

      // Seleccionamos primer padre
      p1 =
	(int) (rand () / (RAND_MAX + 1.0) *
	       poblacion.size ());
      p2 =
	(int) (rand () / (RAND_MAX + 1.0) *
	       poblacion.size ());
      if (sumafit[p1] > sumafit[p2])
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
      if (sumafit[p1] > sumafit[p2])
	padre2 = p1;
      else
	padre2 = p2;

      // Generamos padres
      IndividuoPittsburgh hijo1 = poblacion[padre1];
      IndividuoPittsburgh hijo2 = poblacion[padre2];

      // Los cruzamos
      if (rand () / (RAND_MAX + 1.0) < prob_cruce)
	{
	  for (int i = 0; i < hijo1.size (); i++)
	    {
	      if (rand () / (RAND_MAX + 1.0) < 0.5)
		{
		  swap (hijo1[i], hijo2[i]);
		}
	    }
	}

      // Mutamos el resultado
      if (rand () / (RAND_MAX + 1.0) < prob_muta)
	mutacionMichigan (hijo1, reemplazar, prob_cruceM,
			  prob_mutaM, vp, datos, clases,
			  numclases);

      intermedia.push_back (hijo1);
      if (intermedia.size () >= poblacion.size ())
	break;

      if (rand () / (RAND_MAX + 1.0) < prob_muta)
	mutacionMichigan (hijo2, reemplazar, prob_cruceM,
			  prob_mutaM, vp, datos, clases,
			  numclases);

      intermedia.push_back (hijo2);

    }
  while (intermedia.size () < poblacion.size ());

  // Reemplazamos la poblacion por la poblacion intermedia
  poblacion = intermedia;


}

const IndividuoPittsburgh &
GBML_Pittsburgh::operator[] (int n)
     const
     {
       return
	 poblacion[n];
     }

     int
     GBML_Pittsburgh::size () const
     {
       return (int)
	 poblacion.
       size ();
     }

     float
     GBML_Pittsburgh::getFitnessMich (int i, int j) const
     {
       return
	 fitness[i][j];
     }

     void
     GBML_Pittsburgh::showFitness (float &mejorf,
				   float &avgf,
				   int &elite) const
       
     {

       vector < float >
       suma (fitness.size ());
       float
	 mejor = 0, media = 0;
       int
	 ind = 0;
       for (unsigned int i = 0; i < fitness.size (); i++)
	 {
	   suma[i] = 0;
	   for (unsigned int j = 0; j < fitness[i].size ();
		j++)
	     suma[i] +=
	       fitness[i][j];
	   if (suma[i] > mejor)
	     {
	       mejor = suma[i];
	       ind = i;
	     }
	   media +=
	     suma[i];
	 }
       mejorf = suma[ind];
       avgf = media / fitness.size ();
       elite = ind;
     }
