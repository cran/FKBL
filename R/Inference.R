Inference <- function(kB, train) 
{

 return( 
      .Call("inferencia", kB, train)
       );
}

I <- Inference
