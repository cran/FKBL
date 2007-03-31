\name{checkXML}
\alias{checkXML}
\title{checks a XML from disc}
\description{It takes the name of the file and checks if it is a valid XML 
containing a valid Knowledge Base.
}
\usage{
 checkXML(file)
}
\arguments{

  Takes the file.

  \item{file}{The name of the file.}
 
}

\value{Return FALSE 0 if fails and TRUE 1 otherwise.
A valid XML file would be:

\begin{ExampleCode}
<?xml version="1.0"?>
<!DOCTYPE KnowledgeBase SYSTEM "FKBL.dtd">
<?xml-stylesheet type="text/xsl" href="FKBL.xsl"?>
<KnowledgeBase>
<Author>Alvaro Gonzalez Alvarez</Author>
<Description>Here comes the desired description</Description>
<Partition>
<ex type="double" len="2">0 1 </ex>
</Partition>
<Partition>
<ex type="double" len="2">0 1 </ex>
</Partition>
<Partition>
<ex type="double" len="2">0 1 </ex>
</Partition>
<Rule>
<antecedent type="int" len="3">0 0 0 </antecedent>
<consecuent type="double" len="3">0.65252 0 0 </consecuent>
</Rule>
<numclasses>3</numclasses>
<Error>0.34</Error>
</KnowledgeBase>
\end{ExampleCode}


}

\examples{

 checkXML("sb1.xml")
# -Correct file-
# [1] 1

}
\keyword{univar}
