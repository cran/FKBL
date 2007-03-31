\name{TkbGBMLMoErrorSize}
\alias{TkbGBMLMoErrorSize}
\alias{TkbGMES}
\title{Creates a knowledge base}
\description{This is the implementation of multiobjective, Error Size Algorith genetic method. It is a multiobjective version of the Error Size algorithm. Instead of a single fitness function, there are two. The fitness functions take in consideration the train error and the number of rules (size). The first fitness function would be higher as there are fewer wrong infered cases (error) in training. The second function would be higher as there are fewer rules in the knowledge base. As it is multiobjective it returns a set of knowledge bases. Described in chapter 5, pages 127-130 at Ishibuchi et al.\


}
\usage{
 TkbGBMLMoErrorSize(kB, gen=100, cross=0.5, muta=0.01, train, 
                      k=0.01, popu=20)

}
\arguments{

  Takes knowledge base, the number of generations, the 
crossing and mutation probability, the train data, the size weight 
and the initial population.

  \item{kB}{The knowledge base to tweak.}
  \item{gen}{The number of generations.}
  \item{cross}{The cross probability up to 1.}
  \item{muta}{The mutation probability up to 1.}
  \item{train}{The train dataset.}
  \item{k}{The weight of the size in the algorithm.}
  \item{popu}{The initial population of the algorithm.}
}

\value{Returns the set of not dominated knowledge bases.}

\examples{
 data(kB)
 data(trainA)
 TkbGBMLMoErrorSize(kB, 50, 0.8,0.01, trainA,0.01, 20)
}


\keyword{univar}
