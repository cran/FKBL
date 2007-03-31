LkbGBMLMichigan <- function(P, gen=1000, cross=0.9, muta=0.01, 
	train)
{
 return( .Call("Michigan", train, P, as.integer(gen), cross, muta));
}

LkbGMi <- LkbGBMLMichigan
