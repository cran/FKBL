\name{expGetE}
\alias{expGetE}
\title{Creates the ERROR vector}
\description{This eases the realization of an experiment. It gets an error vector, from a vector of classes. 
}
\usage{
 expGetE(test,classes,errorfunc=NULL)

}
\arguments{

  Takes the test data, the classes vector and the error function.

  \item{test}{The test dataset.}
  \item{classes}{The vector of classes.}
    \item{errorfunc}{The error function to be used. If none is provided the default one is used. The function provided 
must respect the original function input format.}

}

\value{Returns a dataset with the errors.

Here is the expected result for the example.
 \begin{ExampleCode} 
   confS0 confS1 confS2 confS3 confS4 ana rew mich hyb pitt es
 1      0      0      0      0      0   0   0    0   0    0  0
 \end{ExampleCode}
}

\examples{
 data(trainM)
 print(trainM)


 kBs<-expGetKb(trainM[1:8,],P=getPart(trainM[1:8,],10))
 cl<-expGetCl(trainM[9,],kBs)
 error<-expGetE(trainM[9,],cl)

 #prints the actual error dataset
 print(error);
}


\keyword{univar}

