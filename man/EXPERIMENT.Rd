\name{EXPERIMENT}
\alias{EXPERIMENT}
\title{Makes an EXPERIMENT}
\description{This eases the realization of an experiment. It takes a dataset, and divides it in several parts or "chunks". It uses by turns each chunk as the test set and the rest of the dataset as train set, to make an experiment with all single objective  learning and tweaking algorithms. This means that, if a dataset is divided in 10 chunks, it makes the whole experiment 10 times, each of them with a different test set. }

\usage{
 EXPERIMENT(data,chunks=10, initchunk=1, numPart=5, 
        execute=NULL, 
	errorfunc=NULL,
	trainfunc=NULL,
	testfunc=NULL,
	inferencefunc=NULL,
	iteraA=1000, e=0.01,
	iteraR=1000, etaMore=0.001, etaLess=0.1, 
	P=NULL, genS=100, crossS=0.5, mutaS=0.01, kS=0.01, 
	pobS=20, mutaP=0.8, crossP=0.9, genP=50, 
	crossH=0.9, mutaH=0.8, genH=50,	replaceH=2,
	crossM=0.9, mutaM=0.01, genM=1000)
}

\arguments{

  Takes the train data, the number of chunks, the initial chunk, the number of divisions 
of a partition, the vector of activations of algorithms, the error function, the train function, the inference function, the numbers of 
iterations, e, etaMore, etaLess, the list of partitions, cross and mutation 
probability for PittsBurgh,the number of generations for PittsBurgh, the number 
of generations of the ErrorSize algorithm, the cross and mutation probability for ErrorSize, 
the weight for the Size in ErrorSize, the size of the initial population in ErrorSize, cross and mutation probability for Hybrid, cross and mutation probability for Michigan, the generations for Hybrid and the generations for Michigan.


 
 
  \item{data}{The train dataset, this is the only argument which must be supplied, the rest are optional.}
  \item{chunks}{The number of chunks for getTrain and getTest.}
  \item{initchunk}{The initial chunk to be processed.}
  \item{numPart}{The number of divisions for the getPart algorithm.}
  \item{execute}{The vector of activations for the algorithms, here it is possible to determinate which algorithms are executed. If none is provided, a default one with all algorithms activated is created.}
  \item{errorfunc}{The error function to be used. If none is provided the default one is used. The function provided must respect the original function input format.}
  \item{trainfunc}{The function to obtain a train set from the actual problem. If none is provided the default one is used.  The function provided must respect the original function input format.}
  \item{testfunc}{The function to obtain a test set from the actual problem. If none is provided the default one is used.}
  \item{inferencefunc}{The inference function to be used. If none is provided the default one is used. The function provided must respect the original function input format.}
  \item{iteraA}{The number of iterations for analytic.}
  \item{iteraR}{The number of iterations for rewardPunishment.}
  \item{e}{The e parameter for analytic.}
  \item{etaMore}{The etaMore parameter for rewardPunishment.}
  \item{etaLess}{The etaLess parameter for rewardPunishment.}
  \item{P}{The vector of partitions, if none is given one is created with getPart.}
  \item{mutaP}{The mutation probability in the PittsBurgh algorithm.}
  \item{crossP}{The cross probability in the PittsBurgh algorithm.}
  \item{genP}{The number of generations in the PittsBurgh algorithm.}
  \item{genS}{The number of generations in the ErrorSize algorithm.}
  \item{crossS}{The crossing probability in the ErrorSize algorithm.}
  \item{mutaS}{The mutation probability in the ErrorSize algorithm.}
  \item{kS}{The weight of the size in the ErrorSize algorithm.}
  \item{pobS}{Size of the initial population for ErrorSize.}
  \item{crossH}{The cross probability up to 1, at Hybrid.}
  \item{mutaH}{The mutation probability up to 1, at Hybrid.}
  \item{crossM}{The cross probability up to 1, at Michigan.}
  \item{mutaM}{The mutation probability up to 1, at Michigan.}
  \item{genH}{The number of Hybrid generations.}
  \item{replaceH}{The number of individuals to replace.}
  \item{genM}{The number of Michigan generations.}

}

\value{Returns a list, with the knowledge bases, the inferred classes, and the test errors. The structure of the list is this:

list(e=error, k=kBs, c=classes)

e is for error, KbS is for knowledge Bases and c is for classes.}

\examples{
 data(trainM)
 print(trainM)
 out<-EXPERIMENT(trainM)

 #Shows the actual results, and its mean
 print(out$e)
 print(mean(out$e))

 #Shows the graphical boxplot
 boxplot(out$e)
}


\keyword{univar}

