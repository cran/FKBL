getPart <- function(train,numPart=5)
{
  dimx <- length(train)-1

  P<-vector("list",dimx)
  for( i in 1:dimx  )
    P[[i]]=CPart(numPart,min(train[,i]),max(train[,i]))

  P
}

gP <- getPart
