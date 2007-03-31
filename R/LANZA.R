LANZA <-function(train, ejecuta=c(1,1,1,1,1,1,1), chuncks=10)
{ 
  #Inicio
  dimx <- length(train)-1
  
  p<-CPart(5,min(train),max(train))

  P<-vector("list",dimx)
  for( i in 1:dimx  )
    P[[i]]=p

  sb<-LkbConfidenceSupport(P,0,train)
  #FIN Inicio

  e<-1:10
  e[1:chuncks]=1
  
  f<-data.frame(trustS0=e,trustS1=e,trustS2=e,trustS3=e,
			trustS4=e,anali=e,rew=e)

  conP<-LkbConfidenceSupportP(P,0)
  if(ejecuta[1])
  f[,1]<-BARAJA(LkbConfidenceSupportL,conP,train,chuncks)
  
  conP$pes=1
  if(ejecuta[2])
  f[,2]<-BARAJA(LkbConfidenceSupportL,conP,train,chuncks)

  conP$pes=2
  if(ejecuta[3])
  f[,3]<-BARAJA(LkbConfidenceSupportL,conP,train,chuncks)
  
  conP$pes=3
  if(ejecuta[4])
  f[,4]<-BARAJA(LkbConfidenceSupportL,conP,train,chuncks)

  conP$pes=4
  if(ejecuta[5])
  f[,5]<-BARAJA(LkbConfidenceSupportL,conP,train,chuncks)
  
  if(ejecuta[6]) 
  {
    anaP<-TkbAnaliticP(sb,1000,0.01)
    f[,6]<-BARAJA(TkbAnaliticL,anaP,train,chuncks)
  }

  if(ejecuta[7]) 
  {
  rewP<-TkbRewardPunishmentP(sb,1000,0.001,0.1)
  f[,7]<-BARAJA(TkbRewardPunishmentL,rewP,train,chuncks)
  }
 
  f
}
