#source("script.R")
#wine=read.table("../data/wine.tab")
data(wine)
wine[,5]=wine[,5]/100
wine[,13]=wine[,13]/100
wine[,14]=as.integer(wine[,14])-as.integer(1)
salida<-EXPERIMENTmO(wine)
