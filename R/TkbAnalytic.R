TkbAnalytic <- function(kB, itera, e, train) 
{
 return( .Call("analitico", kB, train, as.integer(itera), 
as.double(e)) );
}

TkbAnalyticL <- function(lis, train)
{
  TkbAnalytic(lis$sb,lis$itera,lis$e,train)
}

TkbAnalyticP <-function(kB,itera,e)
{
 list(sb=kB,itera=itera,e=e)
}

TkbAn <- TkbAnalytic
TkbAnl <- TkbAnalyticL
TkbAnp <- TkbAnalyticP

