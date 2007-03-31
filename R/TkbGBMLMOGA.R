TkbGBMLMoga <- function(kB, gen=50, cross=0.8, muta=0.01, train, 
			pobl=20, elite=5)
{
 return ( 
	.Call("MOGA", train, kB, as.integer(gen), cross, muta, 
			as.integer(pobl), as.integer(elite)) 
	);
}

TkbGM <- TkbGBMLMoga
