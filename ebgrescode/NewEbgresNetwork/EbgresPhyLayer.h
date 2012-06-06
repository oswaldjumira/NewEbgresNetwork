/*
 * Date: 11 September 2011
 */

#include "PhyLayerBattery.h"

#ifndef EBGRES_PHY_LAYER_H_
#define EBGRES_PHY_LAYER_H_

class EbgresPhyLayer : public PhyLayerBattery
{
	protected:
		virtual double calcTXCurrentForPacket(MacPkt* pkt, MacToPhyControlInfo* cInfo)
		{ return -1.0; }
};

#endif /* EBGRES_PHY_LAYER_H_ */
