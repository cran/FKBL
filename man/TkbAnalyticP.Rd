\name{TkbAnalyticP}
\alias{TkbAnalyticP}
\alias{TkbAnp}
\title{Creates a set of parameters for TkbAnalyticL}
\description{Creates a set of parameters for TkbAnalyticL.}
\usage{
 TkbAnalyticP(kB, itera, e)
}
\arguments{

  Takes the knowledge base, the maximum number of iterations and the e.

  \item{kB}{The knowledge base to tweak.}
  \item{itera}{The maximum number of iterations.}
  \item{e}{The e parameter for analytic.} 
}

\value{Returns a list, with the parameters given.
}

\examples{
 data(kB)
 TkbAnalyticP(kB, 1000, 0.1)
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
