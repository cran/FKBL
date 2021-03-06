\title{fuzzy Knowledge Base Learning}
\name{FKBL-package} 
\alias{FKBL-package}
\description{This is the implementation in R+C of a  \strong{F}uzzy \strong{K}nowledge \strong{B}ase 
\strong{L}earning engine. It combines the speed of compiled C/C++ code, and the versatility of R in statistics and graphical representation. It supports several inference methods. 

\subsection*{Install}
To install this package, only two steps must be made:
\begin{enumerate}
\item A privileged user must install the package file to the GNU R file tree by executing this:
\begin{ExampleCode}
R CMD INSTALL FKBL_'version'.tar.gz
\end{ExampleCode}
Where 'version' must be changed with the correct one.

\item Once at the R environment, any given user, can load the library by executing:
\begin{ExampleCode}
> library(FKBL)
\end{ExampleCode}
\end{enumerate}

\subsection*{Parser modification}
To modify the parser's behavior you need some bison and flex 
compatible utilities, and the source code of the parser itself. The 
source code is located in the  \strong{parser} directory located itself 
in the \strong{inst} directory of this package. I also supply my 
\strong{Makefile.hide} to easy the compilation. I assume that 
everyone who wants to modify the parser, knows, how to do it, or where 
to ask about it. 

}

\docType{package}

\keyword{univar}
