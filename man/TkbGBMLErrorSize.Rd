\name{TkbGBMLErrorSize}
\alias{TkbGBMLErrorSize}
\alias{TkbGES}
\title{Creates a knowledge base}
\description{This is the implementation of Error Size Algorithm genetic method. It is a single objective genetic algorithm. The fitness function takes in consideration the train error and the number of rules (size). The fitness function would be higher as there are fewer wrong inferred cases (error) in training and as there are fewer rules in the knowledge base. The "k" parameter is the ponderation between the error and the size. 

$$ fitness = w_1 * error + w_2 * size $$
$$ fitness = error + k * size$$
$$ k=  \frac{w_2}{w_1} $$

This parameter makes the algorithm single objective, so it returns only one single knowledge base. This knowledge base would have a higher error, but a smaller number of rules. A smaller number of rules is desired to make the knowledge base more understandable for the user.

Described in chapter 5, pages 127-130 at Ishibuchi et al.\
}
\usage{
 TkbGBMLErrorSize(kB, gen=50, cross=0.8, muta=0.01, 
	k=0.01, train, popu=20)
}
\arguments{

  Takes knowledge base, the number of generations, the 
crossing and mutation probability, the train data, the size weight 
and the initial population.

  \item{kB}{The knowledge base to tweak.}
  \item{gen}{The number of generations.}
  \item{cross}{The cross probability up to 1.}
  \item{muta}{The mutation probability up to 1.}
  \item{k}{The weight of the size in the algorithm.}
  \item{train}{The train dataset.}
  \item{popu}{The initial population of the algorithm.}
}

\value{Returns the set of not dominated knowledge bases.}

\examples{
 data(kB)
 data(trainA)
 TkbGBMLErrorSize(kB, 50, 0.8,0.01, 0.01, trainA, 20)
}


\keyword{univar}
