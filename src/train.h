
/*
 *  train.h
 *
 *  FKBL in R
 *  Fuzzy Knowledge Base Learning
 *
 */

#ifndef _TRAIN_H_
#define _TRAIN_H_

#include "InferenciaBorrosa.h"

class train
{
public:
  unsigned int dimx, nc, numtrain;

    vector < vector < float > >datos;
    vector < int >clases;

    train (char *);
    train (SEXP);
  SEXP toR ();
};
#endif

/*
  dimx
  nc
  numtrain
  datos[numtrain][dimx]
  clases[numtrain]

*/
