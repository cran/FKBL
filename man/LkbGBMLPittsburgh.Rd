\name{LkbGBMLPittsBurgh}
\alias{LkbGBMLPittsBurgh}
\alias{LkbGPtt}
\title{Creates a knowledge base}
\description{This is the implementation of Pittsburgh genetic method. This is a genetic algorithm, where each rule is a set of rules. This algorithm is as the Hybrid algorithm, but PittsBurgh does not use the Michigan algorithm as a mutation operation. Described in chapter 5, pages 117-122 at Ishibuchi et al.\
}
\usage{
 LkbGBMLPittsBurgh(P, gene=50, cross=0.9, muta=0.8, train)
}
\arguments{

  Takes the vector of partitions, the number of generations, the 
crossing and mutation probability in PittsBurgh method and the train data.

  \item{P}{The vector of partitions.}
  \item{gene}{The number of generations.}
  \item{cross}{The cross probability up to 1.}
  \item{muta}{The mutation probability up to 1.}
  \item{train}{The train dataset.}

}

\value{Returns a knowledge base with the partitions and the rules.}

\examples{
 data(P)
 data(trainA)
 LkbGBMLPittsBurgh(P,1000,0.9,0.8,trainA)
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
