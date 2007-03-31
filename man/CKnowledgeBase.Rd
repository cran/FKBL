\name{CKnowledgeBase}
\alias{CKnowledgeBase}
\alias{CKB}
\title{Creates a Knowledge Base}
\description{This is the implementation in R of a Knowledge Base. It provides a wrapper to create the appropriate list with the appropriate codes. Also, it does several checks to ensure the conrcondance between the rules and partitions. Basically it checks there are at least one rule provided, the rules must have the same amount of variables and there must be a partition for each variable in the rule. }
\usage{
 CKnowledgeBase(R,P,ncls=NULL, error=1)
}
\arguments{

  Takes the rules, the partitions, and the number of classes.
 
  \item{R}{The rules.}
  \item{P}{The partitions.}
  \item{ncls}{The number of classes, optional, as it is calculated automatically.}
  \item{error}{The error obtained with the train data and the Knowledge Base.}
  
}

\value{Returns a list, with the set of rules, the set of partitions, the 
number of classes and the error in training. 

list(Rules=R, Partitions=P, numClasses=as.integer(ncls), 
		error=as.double(error))
}

\examples{
 data(R)
 data(P)
 CKnowledgeBase(R,P) # ncls=3
}


\keyword{univar}
