CPart <- function(elem, min, max) {

 x <- 0:(elem-1);
 x=x*(max-min)/(elem-1);
 x=x+min;

 return( 
         list(numMin=as.double(min), numMax=as.double(max), 
	        part=as.double(x),numElem=as.integer(elem))
       );
}

CP <-CPart

CPart2 <- function(x) {

 x=sort(x);
 Nelem=length(x);

 return(
         list(numMin=as.double(x[1]), numMax=as.double(x[Nelem]),
part=as.double(x),
              numElem=as.integer(Nelem))
       );
}

CP2 <- CPart2
