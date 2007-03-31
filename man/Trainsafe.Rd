\name{TrainSafe}
\alias{TrainSafe}
\alias{Ts}
\title{Makes a train set safer}
\description{Takes a train set, and makes some transformations to make it automatically more compatible for being processed by the package. Basically it ensures every variable is a double, and that the every class is an integer, which begin at 0.


}
\usage{
 TrainSafe(train)
}
\arguments{

  Takes the train set.

  \item{train}{The train set to be processed.}
 
  
}

\value{Returns a safer train set}

\examples{
data(cancer)
cancer=TrainSafe(cancer)
}


\keyword{univar}
