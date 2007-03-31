
source("script.R")
IRIS=read.table("../data/IRIS.tab")
#data(IRIS)
salida<-EXPERIMENT(IRIS)
salida$e