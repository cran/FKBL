TkbRewardPunishment <- function(kB, itera, etaMore, 
etaLess, train) 
{
 return( .Call("recompensacastigo", kB, train, as.integer(itera), 
as.double(etaMore), as.double(etaLess)) );
}

TkbRP <- TkbRewardPunishment

TkbRewardPunishmentL <- function(lis,train)
{
  TkbRewardPunishment(lis$kB, lis$itera, 
	lis$etaMore, lis$etaLess, train)
}

TkbRPl <- TkbRewardPunishmentL

TkbRewardPunishmentP <- function(kB, itera, etaMore, etaLess)
{
 list(kB=kB, itera=itera, etaMore=etaMore, etaLess=etaLess)
}

TkbRPp <- TkbRewardPunishmentP