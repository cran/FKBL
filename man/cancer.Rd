\name{Cancer}
\docType{data}
\alias{cancer}
\title{Wisconsin Breast Cancer Database (January 8, 1991)}
\description{
  This is a matrix with 10 columns. Each row is a point, there are 699 points. The 9 first columns are the value of a dimension (or attribute) of the point, the 10th is the class of that point. The attributes are:
     
 \begin{enumerate}
	\item Sample code number
	 \item Clump Thickness
	 \item Uniformity of Cell Size 
 	 \item Uniformity of Cell Shape
	 \item Marginal Adhesion
 	 \item Single Epithelial Cell Size
	 \item Bare Nuclei (this item had several values marked as "?", the points with those values have been comented out)


	 \item Bland Chromatin
 	 \item Normal Nucleoli 
 	 \item Mitoses
 \end{enumerate}
 
}
\usage{data(cancer)}
\format{A matrix.}
\references{
\begin{enumerate}
\item O. L. Mangasarian and W. H. Wolberg: "Cancer diagnosis via linear 
      programming", SIAM News, Volume 23, Number 5, September 1990, pp 1 & 18.

\item William H. Wolberg and O.L. Mangasarian: 

"Multisurface method of 
      pattern separation for medical diagnosis applied to breast cytology", 
      

Proceedings of the National Academy of Sciences, U.S.A., Volume 87, 
      

December 1990, pp 9193-9196.
\end{enumerate}

}
\source{
\begin{itemize}
\item UCI ML Repository
\item Dr. WIlliam H. Wolberg (physician)
      University of Wisconsin Hospitals
      Madison, Wisconsin USA
\item Donor: Olvi Mangasarian (mangasarian@cs.wisc.edu)
      Received by David W. Aha 
      (aha@cs.jhu.edu)
\item Date: 15 July 1992
 \end{itemize}}
\keyword{datasets}

