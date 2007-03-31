

BARAJA <- function(meto,params,train,chuncks=10)
{
 l<-length(train[,1])
 s<-l/chuncks
 i<-1
 e<-1.0:(chuncks)
 while(i<=chuncks)
 {

  if(1>(i*s-s)) tr=train[(i*s+1):l,]
  else if(l<(i*s+1)) tr=train[1:(i*s-s),]
  else
  {
   tr=train[1:(i*s-s),]
   tr[(s*i-s+1):(l-s),]=train[(s*i+1):l,]
  }
 
  sob<-meto(params,tr)
  c1<-Inference1winner(sob,train[(i*s-s+1):(s*i),])

  
e[i]=getErrors(c1,train[(i*s-s+1):(s*i),length(train)])/(length(c1))
  i=i+1
 }
 e
}
