\name{LkbConfidenceSupport}
\alias{LkbConfidenceSupport}
\alias{LkbCS}
\title{Creates a Knowledge Base}
\description{This is the implementation of confidence and support method. Similar to LkbConfidenceSupportL. It is based in exploring every rule possibility, and test its confidence and its support. Support is a concept related with the amount of points covered by the rule. Confidence is related with the predominant class in the area covered by the rule. Only rules with any amount of support are included. The inferred class of a rule is set so the confidence is maximized.  There is a weight associated with a rule, and there are 4 different heuristic methods to obtain it, plus a fifth method which simply states an standard value of $\frac{1}{2} $. Described in chapter 2, pages 018-025 at Ishibuchi et al.\ 
}
\usage{
 LkbConfidenceSupport(P,weight,train)
}
\arguments{

  Takes the vector of partitions, the weight of the method and the train dataset.

 
  \item{P}{The vector of partitions.}
  \item{weight}{The weight of the method.}
  \item{train}{The train dataset.}

}

\value{Returns a knowledge base with the partitions and the rules.}

\examples{
 data(P)
 data(trainA)
 LkbConfidenceSupport(P,0,trainA)
}

\source{
\begin{itemize}
\item Ishibuchi, H., Nakashima, T., Nii, M.
\item  "Classification and modeling with linguistic information granules." 
\item Soft Computing Approaches to Linguistic Data Mining. 
\item Springer-Verlag, 2003
\end{itemize}
}


\keyword{univar}
