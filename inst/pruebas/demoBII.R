data(trainB)
e<-EXPERIMENT(trainB, execute=c(0,0,0,0,1,0,0))
print(e$e)
print(mean(e$e))
