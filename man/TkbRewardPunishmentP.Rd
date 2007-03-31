\name{TkbRewardPunishmentP}
\alias{TkbRewardPunishmentP}
\alias{TkbRPp}
\title{Creates a set of parameters for TkbRewardPunishmentL}
\description{Creates a set of parameters for TkbRewardPunishmentL.}
\usage{
 TkbRewardPunishmentP(kB, itera, etaMore, etaLess)
}
\arguments{

  Takes the knowledge base, the maximum number of iterations, the etaMore and
the etaLess.

  \item{kB}{The knowledge base to tweak.}
  \item{itera}{The maximum number of iterations.}
  \item{etaMore}{The reward to a rule.}
  \item{etaLess}{The punishment to a rule.}

}

\value{Returns a list, with the parameters given.}

\examples{
 data(kB)
 TkbRewardPunishmentP(kB, 1000, 0.001, 0.1)
}


\keyword{univar}
