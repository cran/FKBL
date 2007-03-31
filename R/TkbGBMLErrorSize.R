TkbGBMLErrorSize <- function(kB, gen=50, cross=0.8, 
	muta=0.01, k=0.01, train, popu=20)
{
 if(popu<1) popu=20;
 return ( 
	.Call("SeleccGen", train, kB, as.integer(gen), cross, 
		muta, k, as.integer(popu)) 
	);
}

TkbGES <- TkbGBMLErrorSize
