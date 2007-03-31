\name{getExecute}
\alias{getExecute}
\alias{gEx}
\title{Gets a prototype execute list}
\description{This returns an execution list with all the algorithms activated, to ease the algorithms codes recall. To avoid the execution of an algorithm is only necesary to set as NULL its code value.}
\value{Returns a dataset with the knowledge bases.

list(confS0=1,confS1=1,confS2=1,confS3=1,confS4=1,ana=1,
		rew=1,mich=1,hyb=1,pitt=1, es=1)

confS0 is for confidence and support. ana is Analysis. rew is reward and punishment. mich is Michigan. hyb is Hybrid. pitt is PittsBurgh. es is ErrorSize.
}

\examples{
 getExecute()
}


\keyword{univar}

