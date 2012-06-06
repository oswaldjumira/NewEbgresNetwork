

#include "EbgresRouter.h"

int EbgresRouter::getNextHopAddr()
{
	return nextHopAddr;
}

void EbgresRouter::setNextHopAddr(int nHopAddr)
{
	nextHopAddr = nHopAddr;
}
