getTrain <- function(data,chunks=10,i=1)
{
  len<-length(data[,1]);
  size<-as.integer(len/chunks);

#  print(size);

  if(i<=1) tr<-data[size:len,]
  else if(i>=chunks) tr<-data[1:(len-chunks),]
  else 
  {
	tr<-data[1:(i*size-size),];
	tr[(i*size-size+1):(len-size),]<-data[(i*size+1):len,];
  }
tr
}

getTrainOLD <- function(data,chuncks=10,i=1)
{
  l<-length(data[,1])
  s<-l/chunks

  if(1>(i*s-s)) tr=data[(i*s+1):l,]
  else if(l<(i*s+1)) tr=data[1:(i*s-s),]
  else
  {
   tr=data[1:(i*s-s),]
   tr[(s*i-s+1):(l-s),]=data[(s*i+1):l,]
  }
 tr
}

gTr <-getTrain
