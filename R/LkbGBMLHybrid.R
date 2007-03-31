LkbGBMLHybrid <- function(P, gene=50, cross=0.9, muta=0.8, 
	crossM=0.9, mutaM=0.01, replaceH=2, train)
{
 return( .Call("Hibrido", train, P, as.integer(gene), cross, muta, 
	crossM, mutaM, as.integer(replaceH)) );
}

LkbGHy <- LkbGBMLHybrid	
