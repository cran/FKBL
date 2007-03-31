\name{getTrain}
\alias{getTrain}
\alias{gTr}
\title{Gets the train data from a problem}
\description{This function belongs to a pair, whose other function is getTest. 
It divides the problem in the number 
of chunks given. It returns all the data except the i-th chunk, as the i-th 
chunk will be the test data.}
\usage{
 getTrain(data,chunks,i)
}
\arguments{

  Takes the data, the number of chunks and the test chunk.

  \item{data}{The data of the problem.}
  \item{chunks}{The number of chunks to divide the data.}
  \item{i}{The chunk reserved to be the test data.}
  
}

\value{A dataset with the train data.}

\examples{
 data(trainA)
 getTrain(trainA,10,1)
}


\keyword{univar}
