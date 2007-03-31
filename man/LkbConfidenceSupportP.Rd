\name{LkbConfidenceSupportP}
\alias{LkbConfidenceSupportP}
\alias{LkbCSp}
\title{Creates a set of parameters for LkbConfidenceSupportL}
\description{Creates a set of parameters for 
LkbConfidenceSupportL. It is a wrapper for the "list" function, which creates the appropriate list with the appropriate codes.}
\usage{
 LkbConfidenceSupportP(P,weight)
}
\arguments{

  Takes the partitions and the weight.

  \item{P}{The partitions.}
  \item{weight}{The weight of the method.}
  
}

\value{Returns a list.

 list(p=P,we=weight) 

p is for Partitions and we is for weight.
}

\examples{
 data(P)
 LkbConfidenceSupportP(P,0)
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
