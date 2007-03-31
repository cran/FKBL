\name{TkbRewardPunishmentL}
\alias{TkbRewardPunishmentL}
\alias{TkbRPl}
\title{Reward and Punishment. Tweaks a kB}
\description{This algorithm is called Reward and Punishment.  It is the same as TkbRewardPunishment, but with the parameters packed in a list. It needs the TkbRewardPunishmentP function to create the list of parameters. 


It takes a knowledge base and tweaks its weights to fit better a given train data.  It is based in the idea of checking every training case and discover which is the rule used to infer the case. If the rule was right, it is rewarded, with an "etaMore" value. If the rule did a mistake, it is punished, with an "etaLess" value. The reward and the punishment is done by lowering or rising the weight associated with a rule. By lowering a weight again and again, a rule would have less and less importance. This means that rules which make mistakes would appear less and less as the winning rules in an Inference one winner method. The same can be said with the rising of a rule's weight. The final result, is a tweaked rule set, which would be likely more adapted to the actual problem. This algorithm is described in chapter 3, pages 039-048 at Ishibuchi et al.\ }

\usage{
 TkbRewardPunishmentL(lis, train)
}
\arguments{

  Takes the list of parameters and the train data.

 \item{lis}{A list with the arguments of the function. It is created with
TkbRewardPunishmentP.}
  \item{train}{The train data.}
  
}

\value{Returns the tweaked knowledge base.}

\examples{
 data(kB)
 Params<-TkbRewardPunishmentP(kB, 1000, 0.001, 0.1)
 data(trainA)
 TkbRewardPunishmentL(Params,trainA)
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
