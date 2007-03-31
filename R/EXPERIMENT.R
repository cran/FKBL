EXPERIMENT <- function(data,chunks=10, initchunk=1, numPart=5, 
        execute=NULL, 
	errorfunc=NULL,
	trainfunc=NULL,
	testfunc=NULL,
	inferencefunc=NULL,
	iteraA=1000, e=0.01,
	iteraR=1000, etaMore=0.001, etaLess=0.1, 
	P=NULL, genS=100, crossS=0.5, mutaS=0.01, kS=0.01, 
	pobS=20, mutaP=0.8, crossP=0.9, genP=50, 
	crossH=0.9, mutaH=0.8, genH=50,	replaceH=2,
	crossM=0.9, mutaM=0.01, genM=1000)
{
#
# To add a new algorithm, you must add at:
# 1) getExecute
# 2) names just below this
# 3) error<-data.frame in expGetKb
# 4) execute=list in expGetKb
# 5) execute$ in expGetKb where the actual algorithm is executed
# 6) error<-data.frame in  expGetE
#
 
 chunks=min(length(data[,1]), chunks)
 # 'chunks' mustn't be bigger than the length of the 'data'
 
namesA=c("confS0","confS1","confS2","confS3","confS4","ana",
		"rew","mich","hyb", "pitt", "es")

  if(is.null(execute))execute<-getExecute()

  if(is.null(errorfunc))errorfunc<-getErrors

  if(is.null(trainfunc))trainfunc<-getTrain

  if(is.null(testfunc))testfunc<-getTest

  if(is.null(inferencefunc))inferencefunc<-Inference1Winner

  # Permitir inicializar P con funcion o con una dada
  if(is.null(P))P<-getPart(data,numPart)

  #kB inicial permitir ser iniciada por funcion o por una dada

  kBs<-vector("list",chunks)
  classes<-vector("list",chunks)

  e=numeric(chunks)
  e[1:chunks]=1

error<-data.frame(confS0=e,confS1=e,confS2=e,confS3=e,
	confS4=e,anali=e,rew=e,mich=e,hyb=e, pitt=e,es=e)

  for( i in (initchunk:chunks) )
  {
   train=trainfunc(data,chunks,i) 
   test=testfunc(data,chunks,i)


   kBs[[i]]<-expGetKb(train,P,execute,
	iteraA,e,
	genS, crossS, mutaS, kS, pobS,
	iteraR,etaMore,etaLess, 
	crossH, mutaH,  genH,  replaceH, 
	mutaP, crossP, genP, 
	crossM, mutaM, genM)
if(length(kBs[[i]])>0) names(kBs[[i]])=namesA[1:length(kBs[[i]])]

   classes[[i]]<-expGetCl(test,kBs[[i]],inferencefunc)
if(length(classes[[i]])>0) names(classes[[i]])=
	namesA[1:length(classes[[i]])]

   error[i,]<-expGetE(test,classes[[i]],errorfunc) 
  }

 return (list(e=error, k=kBs, c=classes));
}

expGetKb <- function(train,P, execute=NULL, 
	iteraA=1000,e=0.01, 
	genS=100, crossS=0.5, mutaS=0.01, kS=0.01, pobS=20, 
	iteraR=1000, etaMore=0.001, etaLess=0.1, 
	crossH=0.9, mutaH=0.8, genH=50, replaceH=2,
	mutaP=0.8, crossP=0.9, genP=50,  crossM=0.9, 
	mutaM=0.01,  genM=1000)
{

namesA=c("confS0","confS1","confS2","confS3","confS4","ana",
                "rew","mich","hyb", "pitt", "es")

  kBs<-vector("list",length(namesA))

  if(is.null(execute))execute<-getExecute()

  if(!is.null(execute$confS0))
  {
    kBs[[1]]<-LkbConfidenceSupport(P,0,train)
    kBsAux<-kBs[[1]]
  }
  else
  {
    kBsAux<-LkbGBMLMichigan(P,genM,crossM,
			mutaM,train);
  }  

  if(!is.null(execute$confS1))
  {
    kBs[[2]]<-LkbConfidenceSupport(P,1,train)
  }
  if(!is.null(execute$confS2))
  {
    kBs[[3]]<-LkbConfidenceSupport(P,2,train)
  }
  if(!is.null(execute$confS3))
  {
    kBs[[4]]<-LkbConfidenceSupport(P,3,train)
  }
  if(!is.null(execute$confS4))
  {
    kBs[[5]]<-LkbConfidenceSupport(P,4,train)
  }
  if(!is.null(execute$ana)) 
  {
    kBs[[6]]<-TkbAnalytic(kBsAux,iteraA,e,train)
  }
  if(!is.null(execute$rew)) 
  {
  kBs[[7]]<-TkbRewardPunishment(kBsAux,iteraR,
		etaMore,etaLess,train)
  }
  if(!is.null(execute$mich))
  {
	if(!is.null(kBsAux)) kBs[[8]]<-kBsAux
	else kBs[[8]]<-LkbGBMLMichigan(P,genM,crossM,
				mutaM,train);
  }
  if(!is.null(execute$hyb))
  {
  kBs[[9]]<-LkbGBMLHybrid(P,genH,crossH,mutaH,crossM,
			mutaM,replaceH,train)
  }
  if(!is.null(execute$pitt))
  {
  kBs[[10]]<-LkbGBMLPittsBurgh(P,genP,crossP,mutaP,train) 
  }
  if(!is.null(execute$es))
  {
  kBs[[11]]<-TkbGBMLErrorSize(kBsAux,gen=genS, cross=crossS, 
			muta=mutaS, k=kS, train, pobS)
  }

 return (kBs);
}

expGetCl <- function(test,kBs,inferencefunc=NULL)
{
  if(is.null(inferencefunc))inferencefunc<-Inference1Winner

  classes<-list()
  len=length(kBs)
for(i in (1:len))
  if(!(is.null(kBs[[i]])))
  {
    classes[[i]]<-inferencefunc(kBs[[i]],test)
  }

 return (classes);
}

expGetE <- function(test, classes, errorfunc=NULL)
{
  if(is.null(errorfunc))errorfunc<-getErrors

  lt=length(test[,1])
  lclase=length(test)
 
error<-data.frame(confS0=1,confS1=1,confS2=1,confS3=1,
	confS4=1,ana=1,rew=1,mich=1,hyb=1,pitt=1,es=1)

  len=length(classes)

if(len>0)
  for(i in (1:len))
  if(!(is.null(classes[[i]])))
  {
    error[i]<-errorfunc(classes[[i]],test[,lclase])/lt
  }

return (error);
}

