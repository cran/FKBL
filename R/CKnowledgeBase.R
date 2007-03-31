CKnowledgeBase <- function(R, P, ncls=NULL, error=1)
{
  if(length(R)==0) { return (NULL); }
  if(length(R)>=2)
  {
   if( is.null(ncls))
   { ncls=length(R[[1]]$cons); }
   for( i in (1:length(R)))
   {   
# Every rule must have the same amount on antecedents 
# and consecuents
	if(
             (length(R[[1]]$antec) != length(R[[i]]$antec)) ||
	     (length(R[[1]]$cons) != length(R[[i]]$antec))
	  )
	{ return (NULL); }
   }
  }
  if(length(P)!=length(R[[1]]$antec)) 
  {   # There must be enough partitions
	return( NULL);
  }

  return(
	  list(Rules=R, Partitions=P, numClasses=as.integer(ncls), 
		error=as.double(error))
	);
}

CKB <-CKnowledgeBase
