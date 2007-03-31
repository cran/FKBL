\name{Inference1Winner}
\alias{Inference1Winner}
\alias{I1W}
\title{Gets the vector of classes}
\description{Uses a knowledge base to infer the vector of classes for a given dataset problem, with the method of only one winner. For every case in the problem, the rules at the knowledge base are used to determinate the most appropriate class. Described in chapter 2, pages 021-022 at Ishibuchi et al.\  }
\usage{
 Inference1Winner(kB,train)
}
\arguments{

  Takes the knowledge base and the dataset.

  \item{kB}{The knowledge base.}
  \item{train}{The train data.}
  
}

\value{Returns the vector of classes.
}

\examples{
 data(kB)
 data(trainA)
 Inference1Winner(kB,trainA)
}


\keyword{univar}
