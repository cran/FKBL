TrainSafe <- function(train)
{
  len=length(train);

  for (i in (1:(len-1)) )
  { train[,i]=as.double(train[,i]);
  }

  train[,len]=as.integer(train[,len])
  train[,len]=abs(train[,len])-min(abs(train[,len]))
  
train
}

Ts<-TrainSafe
