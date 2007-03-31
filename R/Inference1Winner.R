Inference1Winner <- function(kB, train) 
{

 return( 
         .Call("inferencia1ganador", kB, train)
       );
}

I1W <- Inference1Winner
