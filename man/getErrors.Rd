\name{getErrors}
\alias{getErrors}
\alias{gE}
\title{Checks the errors between two vectors}
\description{It counts the number of errors between two class vectors. An error is when the inferred class is not the correct one.
}
\usage{
 getErrors(class1,class2)
}
\arguments{

  Takes two vectors.

  \item{class1}{The first class.}
  \item{class2}{The second class.}
  
}

\value{Return the number of discrepancies.}

\examples{
 data(c1)
 data(c2)
 getErrors(c1,c2)
}


\keyword{univar}
