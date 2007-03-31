getErrors <- function(class1, class2) {

 i=1;
 errores=0;
 if(length(class1)!=length(class2)) print("error")
 while( i<=length(class1) && i<=length(class2) )
 {
   if(class1[i]==class2[i])
	errores=errores+0
   else
	errores=errores+1
   i=i+1
 }
return( errores);
}

gE <- getErrors
