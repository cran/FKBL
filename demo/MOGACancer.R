#source("script.R")
#cancer=read.table("../data/cancer.tab")
data(cancer)

cancer[,1:10]=cancer[1:10]/10
cancer[,11]=cancer[,11]/2
cancer[,11]=as.integer(cancer[,11])


salida<-EXPERIMENTmO(cancer)

save(salida,file="MOGACancer.Results")
