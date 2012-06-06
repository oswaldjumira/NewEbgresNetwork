/* -*- mode:c++ -*- ********************************************************
 * file:        BurstApplLayer.cc
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


#include "ebgresApplLayer.h"
#include "NewEbgresNetwLayer.h"
#include "NetwControlInfo.h"

Define_Module(ebgresApplLayer);

// do some initialization
void ebgresApplLayer::initialize(int stage)
{
	BaseApplLayer::initialize(stage);

    //TestApplLayer::initialize(stage);

    if(stage==0){
        if(hasPar("burstSize"))
            burstSize = par("burstSize");
        else
            burstSize = 3;

    }
    else if (stage==5)
    {
        EV << "Network layer address " << getNetwAddr() << "\n";
        nodeInformationPtr = dynamic_cast<NodeInformation*>(getParentModule()->getSubmodule("nodeInfo"));

        EV << "Source Address : " << nodeInformationPtr->getSourceAddress() << "\n";
        if (nodeInformationPtr->isSourceNode()) scheduleStartMessage();
    }
}

void ebgresApplLayer::scheduleStartMessage()
{
	//Create a new data message.

	EV << "Scheduling start message.\n";
	sendApplDataMessage = new cMessage( "Send data appl message", SEND_APPL_DATA_MESSAGE );

	scheduleAt(simTime() + dblrand() * 10, sendApplDataMessage);
}


void ebgresApplLayer::handleSelfMsg(cMessage *msg)
{
    switch(msg->getKind())
    {
    case SEND_APPL_DATA_MESSAGE:
    	handleSendApplDataMessage();
        break;
    default:
        EV <<" Unkown selfmessage! -> delete, kind: "<<msg->getKind()<<endl;
    }
    delete msg;
}

void ebgresApplLayer::handleSendApplDataMessage()
{
	EbgresApplMessage* message = new EbgresApplMessage("Application data message", APPL_DATA_MESSAGE);

	DataApplMessage dataApplMessage;

	message->setDataApplMessage(0, dataApplMessage);

	NetwControlInfo* info = new NetwControlInfo(nodeInformationPtr->getSinkAddress());
	message->setControlInfo(info);
	message->setByteLength(sizeof dataApplMessage);
	sendDown(message);

	//Schedule a new message for recurring.

	sendApplDataMessage = new cMessage( "Send data appl message", SEND_APPL_DATA_MESSAGE );
	scheduleAt(simTime() + 11, sendApplDataMessage);
}

int ebgresApplLayer::getNetwAddr()
{
	NewEbgresNetwLayer *netwModule = dynamic_cast<NewEbgresNetwLayer*>(getParentModule()->getSubmodule("net"));
	return netwModule->getNetwAddr();
}

int ebgresApplLayer::getHostIndex()
{
	return getParentModule()->getIndex();
}
