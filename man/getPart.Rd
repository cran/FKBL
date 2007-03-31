\name{getPart}
\alias{gP}
\alias{getPart}
\title{Partition O matic}
\description{It creates automatically a set of partitions for the given 
train data. Detects the maximum and minimum value of a given variable across all the cases of the problem, and sets them as the limits of the partition (the minimum as the lowest limit, the maximum as the highest limit. Then it divides the partition in the given numPart. }
\usage{
 getPart(train,numPart)
}
\arguments{

  Takes the train data and the number of partitions.

  \item{train}{The train data.}
  \item{numPart}{The number of divisions.}
  
}

\value{Returns the set of partitions created.

 The fourth partition created at the example is:

\begin{ExampleCode}
[[4]]
[[4]]$numMin
[1] 0.0591831

[[4]]$numMax
[1] 0.893645

[[4]]$part
[1] 0.0591831 0.2677986 0.4764140 0.6850295 0.8936450
\end{ExampleCode}

The minimum,  0.0591831, is the minimum value of the 4th variable. And the maximum, 0.8936450, is the maximum value of the 4th variable. The values among them are uniformly distributed between them.
}

\examples{
 data(trainM)
 out<-getPart(trainM,5)

 print(out)
}


\keyword{univar}
