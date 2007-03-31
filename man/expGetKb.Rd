\name{expGetKb}
\alias{expGetKb}
\title{Makes kBs from a train set}
\description{This eases the realization of an experiment, recieves a train set and returns a kB for every algorithm.
}
\usage{
 expGetKb(train,P, execute=NULL, 
	iteraA=1000,e=0.01, 
	genS=100, crossS=0.5, mutaS=0.01, kS=0.01, pobS=20, 
	iteraR=1000, etaMore=0.001, etaLess=0.1, 
	crossH=0.9, mutaH=0.8, genH=50, replaceH=2,
	mutaP=0.8, crossP=0.9, genP=50,  crossM=0.9, 
	mutaM=0.01,  genM=1000)

}
\arguments{

  Takes the train data, the vector of activations of algorithms, the numbers of 
iterations, e, etaMore, etaLess, the list of partitions, cross and mutation 
probability for PittsBurgh,the number of generations for PittsBurgh, the number 
of generations of the ErrorSize algorithm, the cross and mutation probability for ErrorSize, 
the weight for the Size in ErrorSize, the size of the initial population in ErrorSize, cross and 
mutation probability for Hybrid, cross and mutation probability for 
Michigan, the generations for Hybrid and the generations for Michigan.


 
  \item{train}{The train dataset.}
  \item{execute}{The vector of activations for the algorithms, here it is posible to determinate which algorithms are executed. If none is provided, a default one with all algorithms activated is created.}
  \item{iteraR}{The number of iterations for rewardPunishment.}
  \item{iteraA}{The number of iterations for analytic.}
  \item{e}{The e parameter for analytic.}
  \item{etaMore}{The etaMore parameter for rewardPunishment.}
  \item{etaLess}{The etaLess parameter for rewardPunishment.}
  \item{P}{The vector of partitions.}
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

\value{Returns a dataset with the knowledge bases.}

\examples{
 data(trainM)
 print(trainM)
 out<-expGetKb(trainM,P=getPart(trainM))

 #Shows the first knowledge Base
 print(out[[1]]);
}


\keyword{univar}

