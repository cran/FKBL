TkbGBMLMoErrorSize <- function(kB, gen=100, cross=0.5, muta=0.01, 
train, 	k=0.01, popu=20)
{
 return ( 
	.Call("SeleccGenMO", train, kB, as.integer(gen), 
		cross, muta, k, as.integer(popu)) 
	);
}

TkbGMES <- TkbGBMLMoErrorSize
