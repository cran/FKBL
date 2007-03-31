/*
 *  InferenciaBorrosa.cc
 * 
 *  FKBL in R
 *  Fuzzy Knowledge Base Learning
 *
 */

#include "InferenciaBorrosa.h"

using namespace std;

particion::particion (int elem, float min_, float max_):
ex (elem)
{
  this->setUniforme (min_, max_);
}


particion::particion ()
{
}

void
particion::setRandom ()
{
  size_t elem = ex.size ();
  double max = ex[ex.size () - 1];

  // Generacion de particiones Random
  //ex[0]=rand()/(float)RAND_MAX;

  for (unsigned int i = 0; i < (elem); i++)
    {
      ex[i] =
	(rand () / (float) RAND_MAX) * (max - ex[i - 1]) +
	ex[i - 1];
    }
}

int
particion::size () const
{
  return ex.size ();
}

ostream & operator<< (ostream & os, const particion & c)
{
  os << '[' << c.ex[0];
  for (unsigned int i = 1; i < c.ex.size (); i++)
    os << ',' << c.ex[i];
  os << ']';

  return os;
}

void
particion::setUniforme (double min, double max)
{
  size_t elem = ex.size ();
  // Generacion de particiones uniformes
  for (unsigned int i = 0; i < elem; i++)
    {
      ex[i] = i / (elem - 1.0) * (max - min) + min;
    }
}

void
particion::toXML (ofstream & f)
{
  f << "<Partition>" << endl;

  f << "<ex type=\"double\" len=\"" << ex.size () << "\">";

  if (ex.size () > 0)
    f << ex[0];
  for (unsigned int i = 1; i < ex.size (); i++)
    f << " " << ex[i];

  f << "</ex>" << endl;

  f << "</Partition>" << endl;
}


float
particion::pertenencia (int t, float x) const
{
  // Pertenencia del valor x al termino t de la particion
  int s = (int) ex.size ();

  if (t >= s - 1)
    return 0;
  if (t == NOIMPORTA)
    return 1;
  if (t == 0)			// Primera
    {
      // Trapecio izquierda
      if (x <= ex[0])
	return 1;
      else if (x >= ex[1])
	return 0;
      else
	return 1 - (x - ex[0]) / (ex[1] - ex[0]);
    }
  else if (t == s - 1)		// Ultima
    {
      // Trapecio derecha
      if (x >= ex[s - 1])
	return 1;
      else if (x <= ex[s - 2])
	return 0;
      else
	return (x - ex[s - 2]) / (ex[s - 1] - ex[s - 2]);
    }
  else
    {				// Resto
      // Triangulo
      if (x <= ex[t - 1])
	return 0;
      else if (x >= ex[t + 1])
	return 0;
      else if (x <= ex[t])
	{
	  return (x - ex[t - 1]) / (ex[t] - ex[t - 1]);
	}
      else
	{
	  return 1 - (x - ex[t]) / (ex[t + 1] - ex[t]);
	}

    }

}

void
SistemaBorroso::setError (double e)
{
  error = e;
}

regla::regla ():antecedente (0), consecuente (0)
{

}

regla::regla (vector < short int >&a, vector < float >&c):
antecedente (a),
consecuente (c)
{
}

void
regla::calculaConfianzaSoporte (const vector < particion >
				&vp,
				const vector < vector <
				float > >&car,
				const vector < int >&cl,
				float &confianza,
				float &soporte)
{

  // Calcula el grado de confianza y el soporte de una regla sobre
  // un conjunto de datos y un conjunto de particiones
  float denconfianza = 0;
  confianza = 0;
  soporte = 0;
  for (unsigned int i = 0; i < car.size (); i++)
    {
      float ma = match (vp, car[i]);
      float mc = consecuente[cl[i]];
      confianza += ma * mc;
      denconfianza += ma;
      soporte += ma * mc;
    }
  if (denconfianza > 0)
    confianza /= denconfianza;
  soporte /= car.size ();
}

void
regla::toXML (ofstream & f)
{
  f << "<Rule>" << endl;

  f << "<antecedent type=\"int\" len=\"" << antecedente.
    size () << "\">";

  if (antecedente.size () > 0)
    f << antecedente[0];
  for (unsigned int i = 1; i < antecedente.size (); i++)
    f << " " << antecedente[i];

  f << "</antecedent>" << endl;

  f << "<consecuent type=\"double\" len=\"" << consecuente.
    size () << "\">";

  if (consecuente.size () > 0)
    f << consecuente[0];
  for (unsigned int i = 1; i < consecuente.size (); i++)
    f << " " << consecuente[i];

  f << "</consecuent>" << endl;


  f << "</Rule>" << endl;
}

SistemaBorroso::SistemaBorroso (const vector < particion >
				&p,
				const vector < regla > &r,
				int nc):
P (p),
R (r),
numclases (nc),
error (1)
{
}

float
regla::match (const vector < particion > &vp,
	      const vector < float > &x) const
{
  float m = 1;
  for (unsigned int i = 0; i < antecedente.size (); i++)
    {
      float m1 = vp[i].pertenencia (antecedente[i], x[i]);
      // El operador AND es el producto
      m *= m1;
      //cout << "<m=" << m << " m1=" << m << ">";
//              if(m1<m)m=m1;
    }
  //cout << " ## ";

  return m;
}


vector < float >
SistemaBorroso::inferenciaf (const vector < float >&x)
{
  static vector < float >activacion (numclases, 0);

  for (unsigned int j = 0; j < numclases; j++)
    activacion[j] = 0;

  // Para cada regla de la base de conocimiento
  for (unsigned int i = 0; i < R.size (); i++)
    {

      // Se calcula el grado hasta el que es cierta
      float matching = R[i].match (P, x);

      // Se actualiza la fuerza del consecuente de la regla
      for (unsigned int j = 0; j < numclases; j++)
	activacion[j] += R[i].getConsecuente (j) * matching;
    }

  // Devolvemos el vector de activaciones
  return activacion;

}

int
SistemaBorroso::inferencia (const vector < float >&x)
{

  // Se calcula el vector de activaciones
  vector < float >result = inferenciaf (x);

  // Se busca la clase para la que la activacion es maxima
  int max = 0;
  float vmax = result[0];
  for (unsigned int i = 0; i < result.size (); i++)
    if (vmax < result[i])
      {
	vmax = result[i];
	max = i;
      }

  return max;
}

int
SistemaBorroso::inferencia1ganador (const vector <
				    float >&x,
				    float &maximportancia,
				    int &reglaganadora)
{
  // Inferencia con un unico ganador
  maximportancia = 0;
  reglaganadora = -1;
  int claseganadora = 0;

  // Para cada regla de la base de conocimiento
  for (unsigned int i = 0; i < R.size (); i++)
    {
      // Se calcula el grado hasta el que es cierta
      float matching = R[i].match (P, x);

      // Si la regla es compatible con un ejemplo, al menos
      if (matching > 0)
	{
	  float importancia = 0, tmpi = 0;
	  int tmpc = 0;
	  for (unsigned int j = 0; j < numclases; j++)
	    {
	      tmpi = R[i].getConsecuente (j) * matching;
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

  return claseganadora;
}

void
SistemaBorroso::toXML (ofstream & f, Meta & mt)
{

  f << "<KnowledgeBase>" << endl;

  for (map < char *, char *>::iterator itr =
       mt.datos.begin (); itr != mt.datos.end (); itr++)
    f << '<' << itr->first << '>' << itr->
      second << "</" << itr->first << '>' << endl;

  for (unsigned int i = 0; i < P.size (); i++)
    P[i].toXML (f);

  for (unsigned int i = 0; i < R.size (); i++)
    R[i].toXML (f);

  f << "<numclasses>" << numclases << "</numclasses>" <<
    endl;

  f << "<Error>" << error * 100 << "</Error>" << endl;

  f << "</KnowledgeBase>" << endl;
}
