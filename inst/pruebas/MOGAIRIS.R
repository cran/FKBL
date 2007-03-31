source("script.R")
IRIS=read.table("../data/IRIS.tab")
#data(IRIS)
salida<-EXPERIMENTmO(IRIS)

save(salida,file="MOGAIris.Results")

