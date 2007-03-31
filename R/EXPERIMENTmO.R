EXPERIMENTmO <-function(data, chunks=10, numPart=5, 
	genM=100, crossM=0.8, mutaM=0.1, kB=NULL, P=NULL,
	genMo=50, crossMo=0.8, mutaMo=0.01, popuMo=20, eliteMo=5,
	genS=100, crossS=0.5, mutaS=0.01, kS=0.01, popuS=20)
{
  
  chunks=min(chunks,length(data[,1]))
  # 'chunks' mustn't be bigger than the length of the 'data'

  kBsM<-vector("list",chunks)
  kBsS<-vector("list",chunks)
  classesM<-vector("list",chunks)
  classesS<-vector("list",chunks)

  if(is.null(P))P<-getPart(data,numPart)

  errorM<-data.frame(matrix(data=1,ncol=0,
	nrow=chunks,dimnames=NULL))
  errorS<-data.frame(matrix(data=1,ncol=0,
	nrow=chunks,dimnames=NULL))


  for( i in (1:chunks) )
  {	
    train=getTrain(data,chunks,i)
    test=getTest(data,chunks,i)
    
    lclase=length(test)
    lt=length(test[,1])

    if(is.null(kB))
    {
       #kB<-LkbConfidenceSupport(P,0,train)
	kB<-LkbGBMLMichigan(P,genM,crossM,mutaM,train)
    }

    kBsAux<-TkbGBMLMoErrorSize(kB, genS, crossS, mutaS, 
train, 	kS, popuS)

    classesAux <-vector("list",length(kBsAux))
classesAux[1]=1

    for(j in (1:length(kBsAux) ))
    {
	if(!(is.null( kBsAux[[j]] )))
        {
    	   classesAux[[j]] <- Inference1Winner(kBsAux[[j]],test)
        }
	
    	if(!(is.null(classesAux[[j]])))
    	{
       	   errorS[i,j]<-getErrors(classesAux[[j]],test[,lclase])/lt
    	}

    }

    classesS[[i]]<-classesAux
    kBsS[[i]]<-kBsAux

###########ErrorSize
###########MOGA

    kBsAux<-TkbGBMLMoga(kB, genMo, crossMo, mutaMo, train, 
					popuMo, eliteMo)

    classesAux <-vector("list",length(kBsAux))
    
    for(j in (1:length(kBsAux) ))
    {
	if(!(is.null( kBsAux[[j]] )))
        {
    	   classesAux[[j]] <- Inference1Winner(kBsAux[[j]],test)
        }
	
    	if(!(is.null(classesAux[[j]])))
    	{
       	   errorM[i,j]<-getErrors(classesAux[[j]],test[,lclase])/lt
    	}

    }
    classesM[[i]]<-classesAux
    kBsM[[i]]<-kBsAux
  }

#print(eliteMo);
#print(length(kBs[[2]]));
#print(length(kBsAux));
# print(kBs);

 return (list(eS=errorS, kS=kBsS, cS=classesS,
	eM=errorM, kM=kBsM, cM=classesM));

#return (list(e=error, c=classes));
}
