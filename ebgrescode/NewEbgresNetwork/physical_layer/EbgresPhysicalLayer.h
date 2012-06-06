// Filename: EbgresPhysicalLayer.cc
// Date: 06/11/2011
// Author: Oswald and Daniel

#ifndef EBGRES_PHYLAYERBATTERY_H_
#define EBGRES_PHYLAYERBATTERY_H_

#include "PhyLayerBattery.h"

class EbgresPhysicalLayer : public PhyLayerBattery{
	virtual void initialize(int stage);

	virtual void setRadioCurrent(int rs);

};

#endif /* EBGRES_PHYLAYERBATTERY_H_ */
