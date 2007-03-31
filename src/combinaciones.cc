/*
 *  combinaciones.cc
 *
 *  FKBL in R
 *  Fuzzy Knowledge Base Learning
 *
 */

#include "combinaciones.h"

combinacion::combinacion (vector < particion > vp_,
			  int dimx, int inicio_):
A (dimx, inicio),
BhasNext (1),
inicio (inicio_)
{
  for (unsigned int i = 0; i < vp_.size (); i++)
    vp.push_back (vp_[i].size ());
}

vector < short int >
combinacion::get ()
{
  return A;
}

vector < short int >
combinacion::operator++ (int)
{
  vector < short int >clone = A;
  operator++ ();
  return clone;
}

vector < short int >&
combinacion::operator++ ()
{
  bool seguir = 1;

  for (unsigned int i = 0; i < vp.size () && seguir; i++)
    {
      A[i]++;
      if (A[i] > vp[i])
	{
	  A[i] = inicio;
	  seguir = 1;
	}
      else
	seguir = 0;
    }
  if (seguir)
    BhasNext = 0;

  return A;
}

bool
combinacion::hasNext ()
{
  return BhasNext;
}
