LkbGBMLPittsBurgh <- function(P, gene=50, cross=0.9, muta=0.8, 
				train)
{
 return( .Call("Hibrido", train, P, as.integer(gene), cross, muta, 
	0, 0, as.integer(0)) );
}

LkbGPtt <- LkbGBMLPittsBurgh
