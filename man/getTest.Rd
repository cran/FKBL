\name{getTest}
\alias{getTest}
\alias{gTe}
\title{Gets the train data from a problem}
\description{This function belongs to a pair, whose other function is 
getTrain. It divides the problem in the number 
of chunks given. And returns the i-th chunck.
}
\usage{
 getTest(data,chunks,i)
}
\arguments{

  Takes the data, the number of chunks and the test chunck.

  \item{data}{The data of the problem.}
  \item{chunks}{The number of chunks to divide the data.}
  \item{i}{The chunk to return.}
  
}

\value{A dataset with the test data.}

\examples{
 data(trainA)
 getTest(trainA,10,1)
}


\keyword{univar}
