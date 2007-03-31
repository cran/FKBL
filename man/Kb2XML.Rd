\name{Kb2XML}
\alias{Kb2XML}
\title{Writes a kB to disc}
\description{It takes a knowledge base, the name of a file and any 
desired meta information. Then, it creates a XML with the given name, containing 
the kB and the meta information.
}
\usage{
 Kb2XML(file,kB,mt)
}
\arguments{

  Takes the file, the knowledge base and the meta information.

  \item{file}{The name of the file.}
  \item{kB}{The knowledge base.}
  \item{mt}{The meta information, it must be a list with pairs: Author="John Doe".}
  
}

\value{Return 0 if fails and 1 otherwise.}

\examples{
data(kB)
data(mt)
Kb2XML("kB.xml", kB, mt)
}


\keyword{univar}
