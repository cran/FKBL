Classes2Numbers <- function(train)
{
 lengthAux <- length(train)
 auxL <- train[,lengthAux]
 train[,lengthAux]= as.integer(train[,lengthAux])-as.integer(1)

 train
}

C2N <- Classes2Numbers

Numbers2Classes <- function(train, classes)
{
  lengthAux <- length(train)
  train[,lengthAux]<-classes

  train
}

N2C <- Numbers2Classes
