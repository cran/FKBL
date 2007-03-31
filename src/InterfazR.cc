
/*
 *  InterfazR.cc
 *
 *  FKBL in R
 *  Fuzzy Knowledge Base Learning
 *
 */

#include "InterfazR.h"

//#define DEBUG

SEXP
inferencia (SEXP kB_, SEXP train_)
{
  // Necesita: una base de conocimiento (kB_) 
  // y un conjunto de entrenamiento (train_)
  // Devuelve: la lista de clases inferida
  //

  return
    CtoR (inferencia
	  (SistemaBorroso (kB_), train (train_)));
}

SEXP
inferencia1ganador (SEXP kB_, SEXP train_)
{
  // Necesita: una base de conocimiento (kB_) 
  // y un conjunto de entrenamiento (train_)
  // Devuelve: la lista de clases inferida
  //
  static float maximportancia = 0;
  static int reglaganadora = 0;
  SistemaBorroso kB (kB_);
  train tr (train_);

  return
    CtoR (inferencia1ganador
	  (kB, tr, maximportancia, reglaganadora));
}


SEXP
confianzasoporte (SEXP vp_, SEXP peso_, SEXP tr_)
{
  // Necesita: un vector de particiones adecuado (vp_) 
  //           el peso seleccionado (peso_)
  //           un conjunto de entrenamiento (tr_)
  // Devuelve: la base de conocimiento inferida 
  //

  train tr (tr_);
  unsigned int vpL = Rf_length (vp_), peso =
    RtoC_int (peso_);
  vector < particion > vp (vpL);

  //  cout << "vpL: " << vpL <<endl;

  for (unsigned int i = 0; i < vpL; i++)
    vp[i] = particion (VECTOR_ELT (vp_, i));

  //  cout << vp[0] << vp[1] << vp[2] <<endl;

  combinacion todasComb (vp, tr.dimx);

  SistemaBorroso sb (vp, vector < regla > (0), tr.nc);

  if (tr.dimx > vpL)
    {
      cout << "Insufficient number of partitions, " << tr.
	dimx << " needed, but only " << vpL << " found." <<
	endl;
      return sb.toR ();
    }
  peso %= 5;

  vector < float >C (tr.nc);

  regla rProbar;
  //Regla auxiliar que se va ahnadir

  while (todasComb.hasNext ())
    {
      float sumConfianza = 0;

      rProbar.setAntecedente (todasComb++);

      int mejorC;
      mejorC = 0;
      float confianza, soporte, maxconfianza, maxconfianza2,
	savesoporte;
      confianza = 0;
      soporte = 0;
      maxconfianza2 = 0;
      maxconfianza = 0;
      savesoporte = 0;

      for (unsigned int i = 0; i < tr.nc; i++)
	{
	  for (unsigned int j = 0; j < tr.nc; j++)
	    C[j] = 0;
	  C[i] = 1;
	  rProbar.setConsecuente (C);


	  rProbar.calculaConfianzaSoporte (vp, tr.datos,
					   tr.clases,
					   confianza,
					   soporte);

	  //C[i]=0;
	  sumConfianza += confianza;

	  if (confianza > maxconfianza)
	    {
	      mejorC = i;
	      maxconfianza2 = maxconfianza;
	      maxconfianza = confianza;
	      savesoporte = soporte;
	    }
	}			//for        
      if (savesoporte > 0)
	{
	  for (unsigned int j = 0; j < tr.nc; j++)
	    C[j] = 0;
	  switch (peso)
	    {
	    case 0:
	      C[mejorC] = 0.5;	//Sin ajuste
	      break;
	    case 1:
	      C[mejorC] = maxconfianza;
	      break;
	    case 2:
	      C[mejorC] = maxconfianza
		-
		((sumConfianza - maxconfianza) / (tr.nc -
						  1));
	      break;
	    case 3:
	      C[mejorC] = maxconfianza - maxconfianza2;
	      //cout << "C[mejorC]= " <<  C[mejorC]
	      //      << " maxconfianza " << maxconfianza
	      //      << " maxconfianza2 " << maxconfianza2
	      //      <<endl;
	      // cin.get();
	      break;
	    case 4:
	      C[mejorC] =
		maxconfianza - (sumConfianza -
				maxconfianza);
	      break;
	    };
	  rProbar.setConsecuente (C);
	  sb.anhade (rProbar);
	}

    }				//while


  sb.setError (errores (tr.clases, inferencia (sb, tr)) /
	       (double) tr.clases.size ());

  return sb.toR ();
}


SEXP
analitico (SEXP kB_, SEXP train_, SEXP iteraciones_,
	   SEXP e_)
{
  // Necesita: la base de conocimiento inicial
  //           un conjunto de entrenamiento train_
  //           el numero de interaciones iteraciones_
  //           el parámetro e de ajuste
  // Devuelve: la base de conocimiento ajustada
  //

  train tr (train_);
  unsigned int iteraciones =
    (unsigned) RtoC_int (iteraciones_);
  double e = RtoC_double (e_);

  SistemaBorroso sbAprendido (kB_);

  vector < particion > vp (sbAprendido.sizeP ());

  for (unsigned int i = 0; i < sbAprendido.sizeP (); i++)
    vp[i] = sbAprendido.getP (i);

  int prometedora = -1;
  int reglaganadora = -1;
  float maximportancia = 0;
  int errores1 = 0, errores2 = 0, errores3 = 0;

  bool cambiado = 1;
  for (unsigned int m = 0; m < iteraciones && cambiado; m++)
    {
      cambiado = 0;
      for (unsigned int k = 0; k < tr.datos.size (); k++)
	{
	  if (sbAprendido.
	      inferencia1ganador (tr.datos[k],
				  maximportancia,
				  reglaganadora) !=
	      tr.clases[k] && reglaganadora != -1)
	    {			//Si la clase no coincide
	      SistemaBorroso
		sbAprendido_ganadoraPaPajo (sbAprendido),
		sbAprendido_prometedoraPaRiba (sbAprendido);

	      maximportancia = -1;
	      prometedora = -1;
	      errores1 = 0;
	      errores2 = 0;
	      errores3 = 0;
	      //Buscar prometedora
	      // Para cada regla de la base de conocimiento
	      for (unsigned int i = 0;
		   i < sbAprendido.sizeR (); i++)
		{

		  // Se calcula el grado hasta el que es cierta
		  float matching =
		    sbAprendido.getR (i).match (vp,
						tr.
						datos[k]);

		  // Si la regla es compatible con un ejemplo, al menos
		  if (matching > 0)
		    {
		      float importancia = 0, tmpi;
		      int tmpc = 0;
		      for (unsigned int j = 0; j < tr.nc;
			   j++)
			{
			  tmpi =
			    sbAprendido.getR (i).
			    getConsecuente (j) * matching;
			  if (importancia < tmpi)
			    {
			      importancia = tmpi;
			      tmpc = j;
			    }
			}
		      if (importancia > maximportancia
			  && tmpc == tr.clases[k])
			{
			  maximportancia = importancia;
			  prometedora = i;
			}
		    }

		}
	      //Fin Prometedora

	      //Prometedora para arriba *
	      for (unsigned int j = 0;
		   j < tr.nc && prometedora != -1
		   && reglaganadora != -1; j++)
		{
		  double
		    match1 =
		    sbAprendido_ganadoraPaPajo.
		    getR (prometedora).match (vp,
					      tr.datos[k]),
		    match2 =
		    sbAprendido_ganadoraPaPajo.
		    getR (reglaganadora).match (vp,
						tr.
						datos[k]),
		    auxPeso =
		    sbAprendido_ganadoraPaPajo.
		    getR (prometedora).getConsecuente (tr.
						       clases
						       [k]);

		  if (sbAprendido_ganadoraPaPajo.
		      getR (reglaganadora).
		      getConsecuente (j) > 0)

		    sbAprendido_ganadoraPaPajo.
		      getR (prometedora).setConsecuente (tr.
							 clases
							 [k],
							 sbAprendido_ganadoraPaPajo.
							 getR
							 (reglaganadora).
							 getConsecuente
							 (j)
							 *
							 (match2
							  /
							  match1)
							 +
							 e);
		  if (sbAprendido_ganadoraPaPajo.
		      getR (prometedora).getConsecuente (tr.
							 clases
							 [k])
		      > 1)

		    sbAprendido_ganadoraPaPajo.
		      getR (prometedora).setConsecuente (tr.
							 clases
							 [k],
							 auxPeso);
		}
	      //FIN Prometedora para arriba

	      //Ganadora para abajo w
	      do
		{
		  for (unsigned int j = 0;
		       j < tr.nc && prometedora != -1
		       && reglaganadora != -1; j++)
		    {
		      double
			match1 =
			sbAprendido_prometedoraPaRiba.
			getR (prometedora).match (vp,
						  tr.
						  datos[k]),
			match2 =
			sbAprendido_prometedoraPaRiba.
			getR (reglaganadora).match (vp,
						    tr.
						    datos
						    [k]);
		      if (sbAprendido_prometedoraPaRiba.
			  getR (reglaganadora).
			  getConsecuente (j) > 0)
			sbAprendido_prometedoraPaRiba.
			  getR (reglaganadora).
			  setConsecuente (j,
					  sbAprendido_prometedoraPaRiba.
					  getR
					  (prometedora).
					  getConsecuente
					  (tr.clases[k]) *
					  (match1 /
					   match2) - e);
		      if (sbAprendido_prometedoraPaRiba.
			  getR (reglaganadora).
			  getConsecuente (j) < 0)
			sbAprendido_prometedoraPaRiba.
			  getR (reglaganadora).
			  setConsecuente (j, 0);
		    }


		  sbAprendido_prometedoraPaRiba.
		    inferencia1ganador (tr.datos[k],
					maximportancia,
					reglaganadora);
		}
	      while (prometedora != reglaganadora
		     && prometedora != -1
		     && reglaganadora != -1);
	      //Asegurarse que la ganadora ya no gana
	      //FIN Ganadora para abajo


	      //Calcular errores
	      for (unsigned int sg1 = 0;
		   sg1 < tr.datos.size (); sg1++)
		{
		  if (sbAprendido.
		      inferencia1ganador (tr.datos[sg1],
					  maximportancia,
					  reglaganadora) !=
		      tr.clases[sg1])
		    errores1++;
		  if (sbAprendido_prometedoraPaRiba.
		      inferencia1ganador (tr.datos[sg1],
					  maximportancia,
					  reglaganadora) !=
		      tr.clases[sg1])
		    errores2++;
		  if (sbAprendido_ganadoraPaPajo.
		      inferencia1ganador (tr.datos[sg1],
					  maximportancia,
					  reglaganadora) !=
		      tr.clases[sg1])
		    errores3++;
		}

	      //sustitir la mejor...
	      if (errores2 < errores1)
		{
		  sbAprendido =
		    sbAprendido_prometedoraPaRiba;
		  errores1 = errores2;
		  cambiado = 1;
		}
	      if (errores3 < errores1)
		{
		  sbAprendido = sbAprendido_ganadoraPaPajo;
		  cambiado = 1;
		}
	    }			//If no coincide
	}			//For cada dato
    }				//For iteraciones


  sbAprendido.
    setError (errores
	      (tr.clases,
	       inferencia (sbAprendido,
			   tr)) /
	      (double) tr.clases.size ());

  return sbAprendido.toR ();
}

SEXP
recompensacastigo (SEXP kB_, SEXP train_, SEXP iteraciones_,
		   SEXP etaMas_, SEXP etaMenos_)
{
  // Necesita: una base de conocimiento inicial (kB_)
  //           un conjunto de entrenamiento (train_)
  //           el numero de iteraciones (iteraciones_)
  //           el parametro etaMas (etaMas_)
  //           el parametro etaMenos (etaMenos_)
  // Devuelve: la base de conocimiento ajustada
  //

  train tr (train_);
  int iteraciones = RtoC_int (iteraciones_);
  double etaMas = RtoC_double (etaMas_), etaMenos =
    RtoC_double (etaMenos_);
  SistemaBorroso sbAprendido (kB_);

  vector < particion > vp (sbAprendido.sizeP ());

  for (unsigned int i = 0; i < sbAprendido.sizeP (); i++)
    vp[i] = sbAprendido.getP (i);

  float maximportancia = 0;
  int reglaganadora;
  // Ajustamos los pesos de las reglas del SB mediante 
  // recompensa-castigo
  for (int iteracion = 0; iteracion < iteraciones;
       iteracion++)
    {
      vector < float >auxDatos;
      int auxClases;
      int aleatorio;

      //Mezcla aleatoria
      for (unsigned int i = 0; i < tr.datos.size (); i++)
	{
	  aleatorio =
	    rand () * (tr.datos.size () / RAND_MAX);
	  auxDatos = tr.datos[i];
	  auxClases = tr.clases[i];

	  tr.datos[i] = tr.datos[aleatorio];
	  tr.clases[i] = tr.clases[aleatorio];

	  tr.datos[aleatorio] = auxDatos;
	  tr.clases[aleatorio] = auxClases;
	}

      //Se guarda el vector de ganadores
      //En principio nadie gana
      vector < bool > haGanado (sbAprendido.sizeR (),
				false);

      //Para cada dato
      for (unsigned int i = 0; i < tr.datos.size (); i++)
	{
	  if (sbAprendido.inferencia1ganador (tr.datos[i],
					      maximportancia,
					      reglaganadora)
	      != tr.clases[i])
	    {

	      // Rebajamos el peso de la regla ganadora
	      //porque FALLO
	      if (reglaganadora >= 0)
		{
		  haGanado[reglaganadora] = true;
		  for (unsigned int j = 0; j < tr.nc; j++)
		    if (sbAprendido.getR (reglaganadora).
			getConsecuente (j) > 0)
		      sbAprendido.getR (reglaganadora).
			setConsecuente (j,
					sbAprendido.
					getR
					(reglaganadora).
					getConsecuente (j) *
					(1 - etaMenos));
		}		//If reglaganadora
	    }
	  else			//Aprendido
	    {
	      // Aumentamos el peso de la regla ganadora
	      //  porque GANO
	      if (reglaganadora >= 0)
		{
		  haGanado[reglaganadora] = true;
		  for (unsigned int j = 0; j < tr.nc; j++)
		    if (sbAprendido.getR (reglaganadora).
			getConsecuente (j) > 0)
		      {
			float margen = 1
			  -
			  sbAprendido.getR (reglaganadora).
			  getConsecuente (j);
			sbAprendido.getR (reglaganadora).
			  setConsecuente (j,
					  sbAprendido.
					  getR
					  (reglaganadora).
					  getConsecuente (j)
					  +
					  margen * etaMas);
		      }		//If sbAprendido
		}		//If reglaganadora
	    }			//If sbAprendido
	}			//For datos


      // Eliminamos todas las reglas que nunca hayan ganado
      for (unsigned int r = 0; r < sbAprendido.sizeR ();
	   r++)
	if (!haGanado[r])
	  for (unsigned int j = 0; j < tr.nc; j++)
	    sbAprendido.getR (r).setConsecuente (j, 0);

      etaMas *= 0.9;
      etaMenos *= 0.9;

    }				//For iteraciones

  sbAprendido.
    setError (errores
	      (tr.clases,
	       inferencia (sbAprendido,
			   tr)) /
	      (double) tr.clases.size ());

  return sbAprendido.toR ();
}				//recompensa-castigo

// ***********************************************

SEXP
SeleccGenMO (SEXP train_, SEXP kB_, SEXP generaciones_, SEXP
	     prob_cruce_, SEXP prob_muta_, 
	    SEXP k_, SEXP tamPob_)
{
  // Necesita: un conjunto de entrenamiento (train_)
  //           una base de conocimiento (kB_)
  //           el numero de generaciones (generaciones_)
  //           la probabilidad de cruce del algoritmo 
  //                                  genetico (prob_cruce_)
  //           la probabilidad de mutacion del algoritmo 
  //                                   genetico (prob_muta_)
  //           El peso de tamaño en el algoritmo (k_)
  //           el tamanio inicial de la poblacion (tamPob_)
  // Devuelve: la base de conocimiento ajustada
  //

  int generaciones = RtoC_int (generaciones_),
    tamPob = RtoC_int (tamPob_);
  double k=RtoC_double(k_),
    prob_cruce = RtoC_double (prob_cruce_),
    prob_muta = RtoC_double (prob_muta_);

  int reemplazar = 2;

  train tr (train_);
  SistemaBorroso sb (kB_);

  srand ((unsigned int) time (0));

  vector < float >min, max;

  for (unsigned int i = 0; i < tr.numtrain; i++)
    {
      if (i == 0)
	min = max = tr.datos[0];
      else
	{
	  for (unsigned int j = 0; j < min.size (); j++)
	    {
	      if (tr.datos[i][j] < min[j])
		min[j] = tr.datos[i][j];
	      if (tr.datos[i][j] > max[j])
		max[j] = tr.datos[i][j];
	    }
	}
    }

  // Se inicia la poblacion del algoritmo
  GBML_SeleccGenMO sege (tamPob, sb);
  sege.evaluaPoblacion (tr, sb, k);

#ifdef DEBUG
  cout << "Total fitness: " << sege.getSumaFitness () /
    tr.datos.size () << endl;
#endif

  for (int gen = 0; gen < generaciones; gen++)
    {

      sege.generacion (reemplazar, prob_cruce, prob_muta);
      sege.evaluaPoblacion (tr, sb, k);
#ifdef DEBUG
      if (gen % 10 == 0)
	{
	  cout << "Gen=" << gen << " Fitness: " <<
	    sege.getSumaFitness () / sb.sizeR () << endl;
	  cin.get ();
	}
#endif
    }

  // Mostramos en pantalla la base de conocimiento 
  // que hemos aprendido
  // y los porcentajes de aciertos en entrenamiento y en test

  SEXP segeR;
  Rf_protect (segeR =
	      Rf_allocVector (VECSXP, sege.size ()));
  for (unsigned int i = 0; i < sege.size (); i++)
    SET_VECTOR_ELT (segeR, i, sege.getSB (sb, 0).toR ());

  Rf_unprotect (1);
  return segeR;
}


// ***********************************************
SEXP
SeleccGen (SEXP train_, SEXP kB_, SEXP generaciones_,
	   SEXP prob_cruce_, SEXP prob_muta_, SEXP k_,
	   SEXP tamPob_)
{
  // Necesita: un conjunto de entrenamiento (train_)
  //           una base de conocimiento (kB_)
  //           el numero de generaciones (generaciones_)
  //           la probabilidad de cruce del algoritmo 
  //                                  genetico (prob_cruce_)
  //           la probabilidad de mutacion de lalgoritmo 
  //                                  genetico (prob_muta_)
  //           el peso del tamanio en el fitness (k_)
  //           el tamanio inicial de la poblacion (tamPob_)
  // Devuelve: la base de conocimiento ajustada
  //

  int generaciones = RtoC_int (generaciones_),
    tamPob = RtoC_int (tamPob_);
  double k = RtoC_double (k_),
    prob_cruce = RtoC_double (prob_cruce_),
    prob_muta = RtoC_double (prob_muta_);

  int reemplazar = 2;

  train tr (train_);
  SistemaBorroso sb (kB_);

  //cout << "Comienza SeleccGen con poblacion " << tamPob;

  srand ((unsigned int) time (0));

  vector < float >min, max;

  for (unsigned int i = 0; i < tr.numtrain; i++)
    {
      if (i == 0)
	min = max = tr.datos[0];
      else
	{
	  for (unsigned int j = 0; j < min.size (); j++)
	    {
	      if (tr.datos[i][j] < min[j])
		min[j] = tr.datos[i][j];
	      if (tr.datos[i][j] > max[j])
		max[j] = tr.datos[i][j];
	    }
	}
    }

  //cout << endl << "Antes del inicializador";

  // Se inicia la poblacion del algoritmo
  GBML_SeleccGen sege (tamPob, sb);
  sege.evaluaPoblacion (tr, sb, k);

  //cout << endl << "Despues del inicializador";

#ifdef DEBUG
  cout << "Total fitness: " << sege.getSumaFitness () /
    tr.datos.size () << endl;
#endif

  for (int gen = 0; gen < generaciones; gen++)
    {

      sege.generacion (reemplazar, prob_cruce, prob_muta);

      //cout << endl << "Despues del paso de generacion";

      sege.evaluaPoblacion (tr, sb, k);
#ifdef DEBUG
      if (gen % 10 == 0)
	{
	  cout << "Gen=" << gen << " Fitness: " <<
	    sege.getSumaFitness () / sb.sizeR () << endl;
	  cin.get ();
	}
#endif

      //cout << endl << gen <<" generacion ";
    }

  // Mostramos en pantalla la base de conocimiento 
  // que hemos aprendido y los porcentajes de 
  // aciertos en entrenamiento y en test

  SistemaBorroso sbAprendido (sb.getP (),
			      vector < regla > (0),
			      sb.getNumClases ());

  for (int i = 0; i < sege.sizeR (); i++)
    if (sege.getMejor (i))
      sbAprendido.anhade (sege[i]);

  sbAprendido.
    setError (errores
	      (tr.clases,
	       inferencia (sbAprendido,
			   tr)) /
	      (double) tr.clases.size ());

  return sbAprendido.toR ();
}



// ********************************************************
// Ingenieria del Conocimiento
// ALGORITMO MICHIGAN
// ********************************************************

SEXP
Michigan (SEXP train_, SEXP vp_, SEXP generaciones_,
	  SEXP prob_cruce_, SEXP prob_muta_)
{
  // Necesita: un conjunto de entrenamiento (train_)
  //           un vector de particiones (vp_)
  //           el numero de generaciones (generaciones_)
  //           la probabilidad de cruce del algoritmo 
  //                                  genetico (prob_cruce_)
  //           la probabilidad de mutacion de lalgoritmo 
  //                                  genetico (prob_muta_)
  // Devuelve: la base de conocimiento generada
  //

  int generaciones = RtoC_int (generaciones_);
  double prob_cruce = RtoC_double (prob_cruce_),
    prob_muta = RtoC_double (prob_muta_);

  train tr (train_);
  static vector < particion > vp (Rf_length (vp_));

  for (int i = 0; i < Rf_length (vp_); i++)
    vp[i] = particion (VECTOR_ELT (vp_, i));

  srand ((unsigned int) time (0));

  // Base de conocimiento que se va a aprender
  SistemaBorroso sbAprendido (vp, vector < regla > (),
			      tr.nc);
  // Sistema de Clasificacion que aprendemos



  // Se inicia la poblacion del algoritmo Michigan
  GBML_Michigan mich (25, tr.nc, vp, tr.datos, tr.clases);



  mich.evaluaPoblacion (tr.datos, tr.clases, vp, tr.nc);

#ifdef DEBUG
  cout << "Total fitness: " << 1 -
    mich.getSumaFitness () / tr.datos.size () << endl;
#endif

  for (int gen = 0; gen < generaciones; gen++)
    {

      mich.generacion (2, prob_cruce, prob_muta, vp,
		       tr.datos, tr.clases, tr.nc);
      mich.evaluaPoblacion (tr.datos, tr.clases, vp, tr.nc);
#ifdef DEBUG
      if (gen % 10 == 0)
	cout << "Gen=" << gen << " Fitness: " <<
	  mich.getSumaFitness () / tr.datos.size () << endl;
#endif
    }

  // Mostramos en pantalla la base de 
  // conocimiento que hemos aprendido
  // y los porcentajes de aciertos en
  // entrenamiento y en test

  for (int i = 0; i < mich.size (); i++)
    if (mich.getFitness (i) > 0)
      sbAprendido.anhade (mich[i].getRegla ());

  sbAprendido.
    setError (errores
	      (tr.clases,
	       inferencia (sbAprendido,
			   tr)) /
	      (double) tr.clases.size ());


  return sbAprendido.toR ();
}


// ***********************************************
// Ingenieria del Conocimiento
// ALGORITMO HIBRIDO
// ***********************************************

SEXP
Hibrido (SEXP train_, SEXP vp_, SEXP generaciones_,
	 SEXP prob_cruce_, SEXP prob_muta_,
	 SEXP prob_cruceM_, SEXP prob_mutaM_,
	 SEXP reemplazar_)
{
  // Necesita: un conjunto de entrenamiento (train_)
  //           un vector de particiones (vp_)
  //           el numero de generaciones (generaciones_)
  //           la probabilidad de cruce del algoritmo 
  //                           genetico (prob_cruce_)
  //           la probabilidad de mutacion del algoritmo 
  //                           genetico (prob_muta_)
  //           la probabilidad de cruce del algoritmo 
  //                           genetico Michigan (prob_cruceM_)
  //           la probabilidad de mutacion de lalgoritmo 
  //                           genetico Michigan (prob_mutaM_)
  // Devuelve: la base de conocimiento generada
  //


  int generaciones = RtoC_int (generaciones_),
    reemplazar = RtoC_int (reemplazar_);
  double prob_cruce = RtoC_double (prob_cruce_),
    prob_muta = RtoC_double (prob_muta_),
    prob_cruceM = RtoC_double (prob_cruceM_),
    prob_mutaM = RtoC_double (prob_mutaM_);

  train tr (train_);
  int vpL = Rf_length (vp_);
  vector < particion > vp (vpL);

  for (int i = 0; i < vpL; i++)
    vp[i] = particion (VECTOR_ELT (vp_, i));

  srand ((unsigned int) time (0));

  vector < float >min, max;

  for (unsigned int i = 0; i < tr.numtrain; i++)
    {
      if (i == 0)
	{
	  min = max = tr.datos[0];
	}
      else
	{
	  for (unsigned int j = 0; j < min.size (); j++)
	    {
	      if (tr.datos[i][j] < min[j])
		min[j] = tr.datos[i][j];
	      if (tr.datos[i][j] > max[j])
		max[j] = tr.datos[i][j];
	    }
	}
    }

#ifdef DEBUG
  cout << "Variables' ranges:" << endl;
  cout << "MINIMUMS: " << min << endl;
  cout << "MAXIMUMS: " << max << endl;
#endif

  vector < int >A (tr.dimx);	
  // Almacenamiento de antecedentes
  vector < float >C (tr.nc);	
  // Almacenamiento de consecuentes

  vector < regla > vrAprendidas;	
  // Base de conocimiento que se va a aprender
  regla rProbar;		
  // Regla que vamos a anhadir
  SistemaBorroso sbAprendido (vp, vrAprendidas, tr.nc);
  // Sistema de Clasificacion que aprendemos


  // Se inicia la poblacion del algoritmo
  GBML_Pittsburgh pitt (50, 25, tr.nc, vp, tr.datos,
			tr.clases);
  pitt.evaluaPoblacion (tr.datos, tr.clases, vp, tr.nc);

  float mejor, media;
  int elite;
#ifdef DEBUG
  pitt.showFitness (mejor, media, elite);
  //#ifdef DEBUG
  cout << "Best fitness: " << mejor /
    tr.datos.size () << "medium=" << media /
    tr.datos.size () << endl;
#endif

  for (int gen = 0; gen < generaciones; gen++)
    {

      pitt.generacion (reemplazar, prob_cruce, prob_muta,
		       prob_cruceM, prob_mutaM, vp,
		       tr.datos, tr.clases, tr.nc);
      pitt.evaluaPoblacion (tr.datos, tr.clases, vp, tr.nc);
      pitt.showFitness (mejor, media, elite);
#ifdef DEBUG
      cout << "Gen=" << gen << " best fitness: " <<
	mejor / tr.datos.size () << " medium=" << media /
	tr.datos.size () << endl;
#endif
    }

  // Mostramos en pantalla la base de 
  // conocimiento que hemos aprendido
  // y los porcentajes de aciertos 
  // en entrenamiento y en test

  pitt.showFitness (mejor, media, elite);
  for (int i = 0; i < pitt[elite].size (); i++)
    if (pitt.getFitnessMich (elite, i) > 0)
      sbAprendido.anhade (pitt[elite][i].getRegla ());

  sbAprendido.
    setError (errores
	      (tr.clases,
	       inferencia (sbAprendido,
			   tr)) /
	      (double) tr.clases.size ());

  return sbAprendido.toR ();
}

SEXP
MOGA (SEXP train_, SEXP kB_, SEXP generaciones_,
      SEXP prob_cruce_, SEXP prob_muta_, SEXP Npob_,
      SEXP Nelite_)
{
  // Necesita: un conjunto de entrenamiento (train_)
  //           una base de conocimiento (kB_)
  //           el numero de generaciones (generaciones_)
  //           la probabilidad de cruce del algoritmo 
  //                               genetico (prob_cruce_)
  //           la probabilidad de mutacion del algoritmo 
  //                                genetico (prob_muta_)
  //           el tamanio de la poblacion inicial (Npob_)
  //           el tamanio de la poblacion elite (Nelite_)
  // Devuelve: las bases de conocimiento ajustadas
  //

  int generaciones = RtoC_int (generaciones_),
    Npob = RtoC_int (Npob_), Nelite = RtoC_int (Nelite_);

  double prob_cruce = RtoC_double (prob_cruce_),
    prob_muta = RtoC_double (prob_muta_);

  SistemaBorroso sb (kB_);
  train tr (train_);

  GBML_MOGA moga (Npob, Nelite, sb);

  srand ((unsigned int) time (0));

  moga.evaluaPoblacion (tr, sb);
  moga.iniciaElite ();

  for (int i = 0; i < generaciones; i++)
    {
      moga.generacion (Npob - Nelite, prob_cruce,
		       prob_muta);
      moga.evaluaPoblacion (tr, sb);
      moga.actualizaElite ();
      moga.mezclaElitePoblacion (Nelite);

      //cout <<moga.sizeE() <<' ' <<moga.sizeP() <<endl;
    }

  SEXP mogaR;
  Rf_protect (mogaR =
	      Rf_allocVector (VECSXP, moga.sizeE ()));

  for (unsigned int i = 0; i < moga.sizeE (); i++)
    SET_VECTOR_ELT (mogaR, i, moga.getElite (sb, i).toR ());

  Rf_unprotect (1);

  //cout<<"Npob: "<<Npob<<" Nelite: "<<Nelite<<" = moga.sizeE(): "
  // << moga.sizeE()<<endl;

  return mogaR;
}

SEXP
SBtoXML (SEXP file_, SEXP kB_, SEXP meta_)
{
  // Necesita: el nombre del file, en el que se debe guardar la 
  //                                base de conocimiento (file_)
  //           la base de conocimiento (kB_)
  //           la metainformacion que se le desea 
  //                                      aniadir al XML (meta_)
  // Devuelve: TRUE si hubo exito. FALSE en otro caso.
  //

  ofstream f (RtoC_char (file_));
  SistemaBorroso sb (kB_);
  Meta mt (meta_);

  if (!f)
    return CtoR (0);

  f << XMLHEADER;

  sb.toXML (f, mt);

  f.close();

  return CtoR (1);
}

SEXP
getClases (SEXP train_)
{
  // Necesita: el conjunto de entrenamiento (train_)
  // Devuelve: el vector de clases del conjunto de entrenamiento
  //
  return CtoR (train (train_).clases);
}

SEXP
checkXML (SEXP file_)
{
  // Necesita: el nombre del file XML (file_)
  // Devuelve: 1 TRUE si es correcto, 0 FALSE si no lo es

  yyin = fopen (RtoC_char (file_), "r"); 
  // Abre el fichero solo para lectura

  if (!yyin)
    return CtoR(0);
  // Comprueba que el fichero ha sido abierto 
  // correctamente
  
  
  return CtoR (!yyparse ());
  // Ejecuta el parseo
}

SEXP
SBfromXML (SEXP file)
{
  // Necesita: el nombre del fichero XML (file_)
  // Devuelve: la base de conocimiento del fichero XML
  //             si tiene éxito.
  //           retorna FALSE 0 si hay un error.

  yyin = fopen (RtoC_char (file), "r");
  if (!yyin)
    return 0;
//  yylineno=1;
  if(yyparse ()==0)
    return 0;

//return file;
  return sb->toR ();
}

SEXP
getRandPart (SEXP vP_)
{
  // Necesita: un vector de particiones (vP_)
  // Devuelve: otro vector de particiones analogo al anterior
  //

  int nParticiones = Rf_length (vP_);
  for (int i = 0; i < nParticiones; i++)
    {
      particion p (VECTOR_ELT (vP_, i));
      p.setRandom ();
      SET_VECTOR_ELT (vP_, i, p.toR ());
    }
  return vP_;
}


SEXP
COMB (SEXP vp_)
{
  // Necesita: un vector de particiones (vp_)
  // Devuelve: (por pantalla) todas las combinaciones 
  //           de ese vector de particiones 
  //           el vector de particiones (vp_)
  //

  int vpl = Rf_length (vp_);
  vector < particion > vp (vpl);

  for (int i = 0; i < vpl; i++)
    vp[i] = particion (VECTOR_ELT (vp_, i));

  combinacion todasComb (vp, 13);

  while (todasComb.hasNext ())
    {
      vector < short int >aux = todasComb++;

      for (int i = aux.size () - 1; i >= 0; i--)
	cout << aux[i];
      cout << endl;
    }

  return vp_;
}
