LkbConfidenceSupport <- function(P, weight=0, train) 
{
 return( .Call("confianzasoporte", P, as.integer(weight), train) );
}

LkbConfidenceSupportL <- function(lis,train)
{
  LkbConfidenceSupport(lis$p, lis$we, train)
}

LkbConfidenceSupportP <- function(P,weight=0)
{
 list(p=P,we=weight)
}

LkbCS <-LkbConfidenceSupport
LkbCSp <-LkbConfidenceSupportP
LkbCSl <-LkbConfidenceSupportL

