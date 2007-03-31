checkXML <- function(file) 
{
 train<- .Call("checkXML", file);
 return (train);
}


