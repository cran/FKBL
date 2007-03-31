source("script.R")


IRIS=read.table("../data/IRIS.tab")
#data(IRIS)
#salida<-EXPERIMENT(IRIS,numPart=3)

#save(salida,file="IRIS.results")

wine=read.table("../data/wine.tab")
#data(wine)
wine[,5]=wine[,5]/100
wine[,13]=wine[,13]/100
wine[,14]=as.integer(wine[,14])-as.integer(1)
salida<-EXPERIMENT(wine,numPart=3)

save(salida,file="WINE.results")

pima=read.table("../data/pima.tab")
#data(pima)
pima[,1]=pima[,1]/10
pima[,2]=pima[,2]/10
pima[,3]=pima[,3]/10
pima[,4]=pima[,4]/10
pima[,5]=pima[,5]/10
pima[,8]=pima[,8]/10
#salida<-EXPERIMENT(pima,numPart=3)

#save(salida,file="PIMA.results")

source("script.R")
glass=read.table("../data/glass.tab")
#data(glass)
glass[,11]=as.integer(glass[,11])-as.integer(1)
glass[,1]=glass[,1]/10
#salida<-EXPERIMENT(glass,numPart=3)

#save(salida,file="GLASS.results")
