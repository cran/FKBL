source("script.R")
glass=read.table("../data/glass.tab")
#data(glass)
glass[,11]=as.integer(glass[,11])-as.integer(1)
glass[,1]=glass[,1]/10
salida<-EXPERIMENT(glass,execute=list(mich=1,hyb=1,pitt=1))
print(salida$e)
boxplot(salida$e,na.rm=TRUE)