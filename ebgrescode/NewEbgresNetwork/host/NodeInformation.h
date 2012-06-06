/* -*- mode:c++ -*- ********************************************************
 * file:        BurstApplLayer.h
 *
 * author:      Daniel Willkomm
 *
 * copyright:   (C) 2004 Telecommunication Networks Group (TKN) at
 *              Technische Universitaet Berlin, Germany.
 *
 *              This program is free software; you can redistribute it
 *              and/or modify it under the terms of the GNU General Public
 *              License as published by the Free Software Foundation; either
 *              version 2 of the License, or (at your option) any later
 *              version.
 *              For further information see file COPYING
 *              in the top level directory
 ***************************************************************************
 * part of:     framework implementation developed by tkn
 * description: application layer like the TestApplLayer but sends burst of
 *               messages
 **************************************************************************/


#ifndef NODE_INFORMATION_H
#define NODE_INFORMATION_H

#include <Coord.h>
#include "SimpleBattery.h"
#include "BaseMobility.h"
#include "Move.h"
#include "BaseUtility.h"
#include "NewEbgresNetwLayer.h"
#include "Configuration.h"

/*
 * Class Prototypes
 */
class NewEbgresNetwLayer;
class Configuration;

class NodeInformation : public cSimpleModule
{
 public:
    virtual void initialize(int);

    Coord getHostCoordinates();

    void setHostCoordinates(Coord coordinates);

    Coord getSinkCoordinates();

    void setSinkCoordinates(Coord coordinates);

    int getSinkAddress();

    void setSinkAddress(int sAddress);

    int getSourceAddress();

    void setSourceAddress(int sAddress);

    double getResidualEnergy();
    void setResidualEnergy(double rEnergy);
    bool isSinkHost();
    void setSinkHost(bool sHost);

    long getDataMessageId() const;

    void setDataMessageId(long  dataMessageId);

    void increaseDataMessageId();

    int getNetworkAddress();

    void setNetworkAddress(int nAddress);

    BaseUtility* getHostUtilityPtr()
		{
			return hostUtilityPtr;
		};

    virtual int numInitStages() const {
    			return 5;
    		}

    virtual bool isSourceNode();

protected:
	Coord hostCoordinates;

	Coord sinkCoordinates;

	int sinkAddress;

	int sourceAddress;

	double residualEnergy;

	SimpleBattery *simpleBatteryPtr;

	BaseUtility *hostUtilityPtr;

	bool sinkHost;

	long dataMessageId;

	int networkAddress;

};

#endif
