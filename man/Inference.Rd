\name{Inference}
\alias{Inference}
\alias{I}
\title{Gets the vector of classes}
\description{Uses a knowledge base to infer the vector of classes for a given dataset problem. For every case in the problem, the rules at the knowledge base are used to determinate the most appropriate class. It uses the Voting-based method. Described in chapter 2, pages 022-025 at Ishibuchi et al.\ }
\usage{
 Inference(kB,train)
}
\arguments{

  Takes the knowledge base and the train dataset.

  \item{kB}{The knowledge base.}
  \item{train}{The train data.}
  
}

\value{Returns the vector of classes.
}

\examples{
 data(kB)
 data(trainA)
 Inference(kB,trainA)
}


\keyword{univar}
