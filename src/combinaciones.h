#ifndef _COMBINACION_H_
#define _COMBINACION_H_

#include "InferenciaBorrosa.h"

class combinacion
{
  vector < short int >A;
    vector < int >vp;
  bool BhasNext;
  int inicio;
public:
    combinacion (vector < particion > vp_, int dimx,
		 int inicio_ = 0);
    vector < short int >get ();
    vector < short int >&operator++ ();
    vector < short int >operator++ (int);
  bool hasNext ();
};

#endif
