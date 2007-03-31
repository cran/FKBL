/*
 *  train.cc
 *
 *  FKBL in R
 *  Fuzzy Knowledge Base Learning
 *
 */

#include "train.h"

train::train (char *file):
nc (0)
{
  unsigned int i = 0;
  double auxD = 0;
  char auxC = ' ';

  datos.push_back (vector < float >(0));

  ifstream f (file);
  if (f)
    {
      while ((auxC = f.peek ()) != EOF)
	if (((auxC >= '0') && (auxC <= '9')))
	  {
	    f >> auxD;
	    auxC = f.get ();
	    if (auxC == ' ')
	      datos[i].push_back (auxD);
	    else if (auxC == '\r')
	      {
		if (nc < (unsigned int) auxD)
		  nc = 1 + (int) auxD;
		clases.push_back ((int) auxD);
		i++;
		datos.push_back (vector < float >(0));
	      }
	  }
	else
	  f.get ();

      f.close ();

      datos.pop_back ();
      dimx = datos[0].size ();
      numtrain = datos.size ();

      /*      cout <<"dimx: " <<dimx << " numtrain: " << numtrain 
         <<" nc: " << nc <<endl;
         for(unsigned int j=0; j<datos.size(); j++)
         {
         cout << j+1 << " ";
         for(unsigned int k=0; k<datos[j].size(); k++)
         cout <<datos[j][k] << " ";
         cout << clases[j] << endl;
         } */
    }
  else
    cout << "File " << file << " not found" << endl;

}

train::train (SEXP list)
{
  SEXP datosA;

  dimx = Rf_length (list) - 1;
// La ultima columna es la clase ¿cambiar?
  datosA = VECTOR_ELT (list, 0);
  numtrain = Rf_length (datosA);
  nc = 0;

  datos.resize (numtrain, vector < float >(dimx));

  //  if(Rf_isReal(datosA)) cout << "ES REAL" <<endl;

  //Para cada columna  
  for (unsigned int i = 0; i < dimx; i++)
    {
      for (unsigned int j = 0; j < numtrain; j++)
	datos[j][i] = REAL (datosA)[j];
      datosA = VECTOR_ELT (list, i + 1); //siguiente columna
    }

  clases.resize (numtrain,0);

  if (Rf_isInteger (datosA)) // ultima columna
    {
      for (unsigned int j = 0; j < numtrain; j++)
	{
	  clases[j] = INTEGER (datosA)[j];

	  if (nc < (unsigned int) clases[j])	//La clase maxima
	    nc = clases[j];
	}
      nc++;			//Uno mas porque las clases comienzan en 0
    }
  else
    {
      cout << "La clases deben de ser numericas" << endl;
    }

  /*    cout <<"dimx: " <<dimx << " numtrain: " << numtrain
     <<" nc: " << nc <<endl;

     for(unsigned int j=0; j<datos.size(); j++)
     {
     cout << j+1 << " ";
     for(unsigned int k=0; k<datos[j].size(); k++)
     cout <<datos[j][k] << " ";
     cout << clases[j] << endl;
     }

     cout <<"dimx: " <<dimx << " numtrain: " << numtrain
     <<" nc: " << nc <<endl; 
   */

}

SEXP train::toR ()
{
  SEXP *
    RdatosA = new SEXP[dimx + 1];
  SEXP
    Rdatos;

  Rf_protect (Rdatos = Rf_allocVector (VECSXP, dimx + 1));
  for (unsigned int i = 0; i < dimx; i++)
    {
      Rf_protect (RdatosA[i] =
		  Rf_allocVector (REALSXP, numtrain));
      for (unsigned int j = 0; j < numtrain; j++)
	REAL (RdatosA[i])[j] = datos[j][i];
      SET_VECTOR_ELT (Rdatos, i, RdatosA[i]);
    }

  Rf_protect (RdatosA[dimx] =
	      Rf_allocVector (REALSXP, numtrain));
  for (unsigned int j = 0; j < numtrain; j++)
    REAL (RdatosA[dimx])[j] = clases[j];
  SET_VECTOR_ELT (Rdatos, dimx, RdatosA[dimx]);

  Rf_unprotect (2 + dimx);
  delete
    RdatosA;

  return Rdatos;
}
