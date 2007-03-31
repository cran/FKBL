\name{TkbAnalytic}
\alias{TkbAnalytic}
\alias{TkbAn}
\title{Analytic algorithm. Tweaks a kB}
\description{This algorithm is called Analytic.  It is the same as TkbAnalyticL, but it has not the parameters packed in a list. It takes a knowledge base and 
tweaks its weights to fit better a given train data. It is based in the idea of checking every training case, and for the cases whose class wasn't correctly inferred, it tries to improve the rule set. This improvement is done by examining three different solutions. First, lowering the winning rule's weight so it is no longer the winning rule in this situation. Second, find a non winning rule which wouldn't have made a mistake, and rise its weight up to the value which makes it to win. Third, leave it as is. The situation which gives less error with the whole training set, would be the chosen one. This algorithm is described in chapter 3, pages 048-057 at Ishibuchi et al.\ }
\usage{
 TkbAnalytic(kB, itera, e, train)
}
\arguments{

  Takes knowledge base, the maximum number of iterations, the e and the train 
data.

  \item{kB}{The knowledge base to tweak.}
  \item{itera}{The maximum number of iterations.}
  \item{e}{The e parameter for analytic.} 
  \item{train}{The train data.}
}

\value{Returns the tweaked knowledge base.
}

\examples{
 data(kB)
 data(trainA)
 TkbAnalytic(kB, 1000, 0.1, trainA)
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
