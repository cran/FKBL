\name{expGetCl}
\alias{expGetCl}
\title{Creates the class vector}
\description{This eases the realization of an experiment. It gets a class set from a set of knowledge bases.
}
\usage{
 expGetCl(test,kBs, inferencefunc=NULL)

}
\arguments{

  Takes the test data, the kB vector and the inference function.
 
  \item{test}{The test dataset.}
  \item{kBs}{The vector of knowledge bases.}
  \item{inferencefunc}{The inference function to be used. If none is provided the default one is used. The function provided 
must respect the original function input format.}

}

\value{Returns a dataset with the inferred 
classes.

Here is the expected result for the example. As the test is only one case, only one class is infered.

\begin{ExampleCode}
[[1]]
[1] 0

[[2]]
[1] 0

[[3]]
[1] 0

[[4]]
[1] 0

[[5]]
[1] 0

[[6]]
[1] 0

[[7]]
[1] 0

[[8]]
[1] 0

[[9]]
[1] 0

[[10]]
[1] 0

[[11]]
[1] 0

\end{ExampleCode}

}

\examples{
 data(trainM)
 print(trainM)
 kBs<-expGetKb(trainM[1:8,],P=getPart(trainM))
 out<-expGetCl(trainM[9,],kBs)
  
 #Shows the result
 print(out)
 
}


\keyword{univar}

