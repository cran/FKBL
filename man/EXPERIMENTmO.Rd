\name{EXPERIMENTmO}
\alias{EXPERIMENTmO}
\title{Makes an EXPERIMENT with the Multiobjective algorithms}
\description{This eases the realization of an experiment with the Multiobjective algorithms, ErrorSize and MOGA. This function is exactly to EXPERIENT, but in the multiobjective real. If EXPERIMENT eases experiments with the 11 single objetive algorithms, EXPERIMENTmO does the same with the 2 multiobjective algorithms. As a multobjective algorithm}
\usage{
 
EXPERIMENTmO(data, chunks=10, numPart=5, 
	genM=100, crossM=0.8, mutaM=0.1, kB=NULL, P=NULL,
	genMo=50, crossMo=0.8, mutaMo=0.01, popuMo=20, eliteMo=5,
	genS=100, crossS=0.5, mutaS=0.01, kS=0.01, popuS=20)
}
\arguments{

  Takes the train data, the number of chunks, the number of divisions 
of a partition, the number of generations for the Michigan algorithm,
the cross and mutation probability of the Michigan algorithm, the initial kB, 
the vector of Partitions. For MOGA there are: the number of generations, the cross and mutation probability, the size of the initial population and the size of the elite population. And for ErrorSize there are: the number of generations, the cross probability, the mutation probability, the weight for the size and the initial population.

As ErrorSize and MOGA are tweaking algorithms, they need an initial knowledge base (kB), if none is provided, the Michigan algorithm is used to create an appropriate default kB. The same happens with the vector of partitions (P), if none is provided "getPart" is used to generate one. A set of default parameters are provided to serve as an example to the user. The only parameter with no default is the problem dataset.
 
  \item{data}{The problem dataset.}
  \item{chunks}{The number of chunks for getTrain and getTest.}
  \item{numPart}{The number of divisions for the getPart algorithm.}
  \item{genM}{The number of Michigan generations.}
  \item{crossM}{The cross probability up to 1, at Michigan.}
  \item{mutaM}{The mutation probability up to 1, at Michigan.}

  \item{kB}{the initial kB, if none is provided, the Michigan algorithm is used.}
  \item{P}{the vector of Partitions, if none is provided, one is created automatically.}
  \item{genMo}{The number of generations for the MOGA.}
  \item{crossMo}{The crossing probability for the MOGA.}
  \item{mutaMo}{The mutations probability for the MOGA.}
  \item{popuMo}{The initial population for the MOGA.}
  \item{eliteMo}{The elite size of the MOGA.}
  \item{genS}{The number of ErrorSize generations.}
  \item{crossS}{The cross probability up to 1, at ErrorSize.}
  \item{mutaS}{The mutation probability up to 1, at ErrorSize.}
  \item{kS}{The ponderation between the Size and the Error.}
 \item{popuS}{The initial population for the ErrorSize.}
}

\value{Returns a list, with the knowledge bases, the inferred 
classes, and the test errors. The structure of the list is:

list(eS=errorS, kS=kBsS, cS=classesS,
	eM=errorM, kM=kBsM, cM=classesM)

Where eS and eM, are referred to the error at "ErrorSize" and "MOGA" respectively. kS and kM, store the knowledge bases, and cS and cM, store the class vectors.
}	   

\examples{
 data(trainM)
 out<-EXPERIMENTmO(trainM)

 # Show the distribution of errors of each 
 # iteration in ErrorSize
 errorS=data.frame(t(out$eS))
 boxplot(errorS)

 # Show the distribution of errors of each 
 # iteration in MOGA
 errorM=data.frame(t(out$eM))
 boxplot(errorM)
}


\keyword{univar}

