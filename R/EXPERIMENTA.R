EXPERIMENTA <- function(data,chunks=10,numPart=5, 
		execute=c(1,1,1,1,1,1,1), itera=1000, e=0.01,
		etaMore=0.001, etaLess=0.1)
{
  maxAlg=10 #Number of Algorithms, right now they are 7

  # Permitir inicializar P con funcion o con una dada
  P<-getPart(data,numPart)

  #kB inicial permitir ser iniciada por funcion o por una dada

  e<-vector("list",maxAlg)
  kBs<-list(confS0=e,confS1=e,confS2=e,confS3=e,confS4=e,
					anali=e,rew=e)  
  classes<-list(confS0=e,confS1=e,confS2=e,confS3=e,confS4=e,
					anali=e,rew=e)

  e<-1:chunks
  e[1:chunks]=1
  error<-data.frame(confS0=e,confS1=e,confS2=e,confS3=e,
				confS4=e,anali=e,rew=e)

  for( i in (1:chunks) )
  {
   train=getTrain(data,chunks,i)
   test=getTest(data,chunks,i)

  if(execute[1])
  {
    kBs$confS0[[i]]<-LkbConfidenceSupport(P,0,train)
    classes$confS0[[i]]<-Inference1winner(kBs$confS0[[i]],test)
    error[i,1]=getErrors(classes$confS0[[i]],
	test[,length(train)])/(length(test[,1]))

  }
  if(execute[2])
  {
    kBs$confS1[[i]]<-LkbConfidenceSupport(P,1,train)
    classes$confS1[[i]]<-Inference1winner(kBs$confS1[[i]],test)
   error[i,2]=getErrors(classes$confS1[[i]],
	test[,length(train)])/(length(test[,1]))

  }
  if(execute[3])
  {
    kBs$confS2[[i]]<-LkbConfidenceSupport(P,2,train)
    classes$confS2[[i]]<-Inference1winner(kBs$confS2[[i]],test)
   error[i,3]=getErrors(classes$confS2[[i]],
	test[,length(train)])/(length(test[,1]))

  }
  if(execute[4])
  {
    kBs$confS3[[i]]<-LkbConfidenceSupport(P,3,train)
    classes$confS3[[i]]<-Inference1winner(kBs$confS3[[i]],test)
   error[i,4]=getErrors(classes$confS3[[i]],
		test[,length(train)])/(length(test[,1]))

  }
  if(execute[5])
  {
    kBs$confS4[[i]]<-LkbConfidenceSupport(P,4,train)
    classes$confS4[[i]]<-Inference1winner(kBs$confS4[[i]],test)
   error[i,5]=getErrors(classes$confS4[[i]],
		test[,length(train)])/(length(test[,1]))

  }
  if(execute[6]) 
  {
    kBs$ana[[i]]<-TkbAnalitic(kBs$confS0[[i]],itera,e,train)
    classes$ana[[i]]<-Inference1winner(kBs$ana[[i]],test)
   
error[i,6]=getErrors(classes$ana[[i]],
		test[,length(train)])/(length(test[,1]))
  }

  if(execute[7]) 
  {
   
kBs$rew[[i]]<-TkbRewardPunishment(kBs$confS0[[i]],
   itera,etaMore,etaLess,train)
   classes$rew[[i]]<-Inference1winner(kBs$rew[[i]],test)
   
error[i,7]=getErrors(classes$rew[[i]],
		test[,length(train)])/(length(test[,1]))

  }

  }

 return (list(e=error, k=kBs, c=classes));
}




