\name{TkbGBMLMoga}
\alias{TkbGBMLMoga}
\alias{TkbGM}
\title{Creates a knowledge base}
\description{This is the implementation of MOGA, Multi Objective Genetic Algorithm genetic method. Described in chapter 6, pages 134-139 at Ishibuchi et al.\ The three objectives of this algorithm are to minimize, the size of the rules, the number of rules and the error in training. The size is related with the number of consequents which are not marked as "no matter". This means that the actual variable labeled with "no matter", is totally independent from the actual rule. The objective of looking for rules with less dependant variables, is to produce more human readable rules, as this way it is easier to understand the relationship between the variables found by the algorithm. As there are there three different objectives, this algorithm creates a set of not dominated knowledge bases. It is an elitist algorithm, this means that the best solutions are stored apart from the actual population, so they are never lost. Periodically this elite population polutes the ordinary population, this way there is a balance between the evolution of the normal population and the elite driven evolution. The evolution of the normal population is an standard genetic driven algorithm, with crossing and mutation operations.
}
\usage{
 TkbGBMLMoga(kB, gen=50, cross=0.8, muta=0.01, train, 
                        pobl=20, elite=5)
}
\arguments{

  Takes knowledge base, the number of generations, the 
crossing and mutation probability, the train data, the initial population and the initial elite population.

  \item{kB}{The knowledge base to tweak.}
  \item{gen}{The number of generations.}
  \item{cross}{The cross probability up to 1.}
  \item{muta}{The mutation probability up to 1.}
  \item{train}{The train dataset.}
  \item{pobl}{The initial population of the algorithm.}
  \item{elite}{The size of the elite population.}
}

\value{Returns the set of not dominated knowledge bases.}

\examples{
 data(kB)
 data(trainA)
 TkbGBMLMoga(kB, 50, 0.8, 0.01, trainA, 20, 5)
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
