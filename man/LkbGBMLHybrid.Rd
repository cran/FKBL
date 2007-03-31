\name{LkbGBMLHybrid}
\alias{LkbGBMLHybrid}
\alias{LkbGHy}
\title{Creates a knowledge base}
\description{This is the implementation of Hybrid, Pittsburgh-Michigan genetic method. This is a genetic algorithm, each individual represents a set of rules. With the given probability, the crossing operation for an individual is performed by, first selecting two different individuals, and then rule by rule with a 50\% of probability, each one is swapped, i.e. every rule has 50% of probabilities of being exchanged with the other individual's rule. With the given probability, the mutation operation is performed, by using a Michigan iteration. This is done by treating the actual individual as a population itself, so an iteration over the selected set of rules is performed, crossing and mutating the given rules.  This two operations are done the number of iterations especified. Described in chapter 5, pages 122-130 at Ishibuchi et al.\
}
\usage{
 LkbGBMLHybrid(P, gene=50, cross=0.9, muta=0.8, crossM=0.9, 
			mutaM=0.01, replaceH=2, train)
}
\arguments{

  Takes the vector of partitions, the number of generations, the 
crossing and mutation probability in Hybrid method, crossing and 
mutation probability in the Michigan method, the number of individuals to replace, the train data.

  \item{P}{The vector of partitions.}
  \item{gene}{The number of generations.}
  \item{cross}{The cross probability up to 1.}
  \item{muta}{The mutation probability up to 1.}
  \item{crossM}{The cross probability for Michigan up to 1.}
  \item{mutaM}{The mutation probability for Michigan up to 1.}
  \item{replaceH}{The number of individuals to replace.}
  \item{train}{The train dataset.}

}

\value{Returns a knowledge base with the partitions and the rules.}

\examples{
 data(P)
 data(trainA)
 LkbGBMLHybrid(P,1000,0.9,0.8,0.9,0.01,2,trainA)
}

\source{
\begin{itemize}
\item Ishibuchi, H., Nakashima, T., Nii, M.
\item  "Classification and modeling with linguistic information granules." 
\item Soft Computing Approaches to Linguistic Data Mining. 
\item Springer-Verlag, 2003
\end{itemize}
}

\keyword{univar}
