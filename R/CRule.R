CRule <- function(c, a) {

 return( 
         list(cons=as.double(c), antec=as.integer(a), 
	elemA=length(a), elemC=length(c))
       );
}

CR <- CRule
