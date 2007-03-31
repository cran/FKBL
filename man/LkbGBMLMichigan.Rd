\name{LkbGBMLMichigan}
\alias{LkbGBMLMichigan}
\alias{LkbGMi}
\title{Creates a knowledge base}
\description{This is the implementation of Michigan genetic method. This is a genetic algorithm where each individual represents a rule. With the given probability, the crossing operation is performed by swapping two partition labels between two individuals. With the given probability, the mutation is performed by with a 50\% of probability changing to a random appropriate value each of the partitions labels. "label" means a reference to a division in the partition, coded as a positive integer. This two operations are done the number of iterations specified. This makes the population grow and diversify. The final result is a knowledge base made by gathering in a base the actual pupulation of rules. Described in chapter 5, pages 105-117 at Ishibuchi et al.\
}
\usage{
 LkbGBMLMichigan(P, gen=1000, cross=0.9, muta=0.01,  train)
}
\arguments{

  Takes the vector of partitions, the number of generations, the 
crossing probability, the mutation probability and the train data.

  \item{P}{The vector of partitions.}
  \item{gen}{The number of generations.}
  \item{cross}{The cross probability up to 1.}
  \item{muta}{The mutation probability up to 1.}
  \item{train}{The train dataset.}

}

\value{Returns a knowledge base with the partitions and the rules.}

\examples{
 data(P)
 data(trainA)
 LkbGBMLMichigan(P,1000,0.9,0.01,trainA)
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
