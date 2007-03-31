\name{CRule}
\alias{CRule}
\alias{CR}
\title{Creates a rule}
\description{This is the implementation in R of a rule.  It provides a wrapper to create the appropriate list with the appropriate codes. Described in chapter 2, pages 011-025 at Ishibuchi et al.\
}
\usage{
 CRule(c,a)
}
\arguments{

  Takes the consequent and the antecedent.
 
  \item{c}{The weight of each class of the rule.}
  \item{a}{The antecedent of the rule.}
  
}

\value{Returns a list, with the consequent, the antecedent and the length of 
the antecedet and consequent.

  list(cons=as.double(c), antec=as.integer(a), 
	elemA=length(a), elemC=length(c))
}

\examples{
 c<-list(0.5,0.75)
 a<-list(0,1,0)
 CRule(c,a)
}


\keyword{univar}
