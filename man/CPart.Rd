\name{CPart}
\alias{CPart}
\alias{CP}
\title{Creates a fuzzy partition}
\description{This is the implementation in R of a fuzzy partition, described in, chapter 1, pages 005-009 at Ishibuchi et al.\ . It has a sister function, with different parameter, but with the same objective. It provides a wrapper to create the appropriate list with the appropriate codes. A partition is defined by a set of values which mark the limits and top point of every triangular division. The divisions are in a chain, the left and right limit of a division, are the top points of its neighbors. And in the same way, the top point of a given partition is the limit of its neighbors. Graphically this is a succession of mixed triangles, where the projection of a height of a given triangle marks the point where two triangles join. 


  }
\usage{
 CPart(elem, min, max)
}
\arguments{

  Takes the number of elements and the minimum and maximum value of the 
partition.

  \item{elem}{The number of elements of the partition.}
  \item{min}{The minimum value of the partition.}
  \item{max}{The maximum value of the partition.}
  
}

\value{Returns a list, the first three elements (numElem, numMin and 
numMax) are the arguments given to the function. The fourth one, is the 
actual partition.

         list(numMin=x1, numMax=x2, part=x3, numElem=x5)
}

\examples{
 CPart(3,0.0,1.0) # 0.0 0.5 1.0
}


\keyword{univar}
