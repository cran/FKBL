data(IRIS)
data(Pl)
e<-EXPERIMENT(IRIS,P=.Call("getRandPart",Pl))
print(e$e)
print(mean(e$e))

