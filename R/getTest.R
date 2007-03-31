getTest <- function(data,chunks=10,i=0)
{
 s<-as.integer(length(data[,1])/chunks)

 data[(i*s-s+1):(s*i),]
}

gTe <-getTest
