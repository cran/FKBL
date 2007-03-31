\name{CPart2}
\alias{CPart2}
\alias{CP2}
\title{Creates a fuzzy partition}

\description{This is the implementation in R of a fuzzy partition, described in, chapter 1, pages 005-009 at Ishibuchi et al.\ . It has a sister function, with different parameter, but with the same objective. It provides a wrapper to create the appropriate list with the appropriate codes. A partition is defined by a set of values which mark the limits and top point of every triangular division. The divisions are in a chain, the left and right limit of a division, are the top points of its neighbors. And in the same way, the top point of a given partition is the limit of its neighbors. Graphically this is a succession of mixed triangles, where the projection of a height of a given triangle, marks the point where two other triangles join. 


  }

\usage{
 CPart2(x)
}
\arguments{

  Takes a vector of doubles. It need not to be sorted, as the function 
sorts it by default.
 
  \item{x}{The vector of doubles.}
  
}

\value{Return a list, the first three elements (numElem, numMin and numMax) are the number of elements, the minimum value and the maximum. The fourth one, is the actual partition.

   list(numMin=x1, numMax=x2, part=x3, numElem=x5)
}

\examples{
 vectr<-vector("numeric",3);
 vectr[1]=0.0;
 vectr[2]=0.5;
 vectr[3]=1;
 CPart2(vectr) 
}


\keyword{univar}
