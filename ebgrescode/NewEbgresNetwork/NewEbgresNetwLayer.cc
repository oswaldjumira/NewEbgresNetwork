/***************************************************************************
 * file:        EbgresNetwLayer.cc
 *
 * author:      Oswald Jumira
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
 * description: network layer: general class for the network layer
 *              subclass to create your own network layer
 ***************************************************************************/

#include <stdio.h>
#include "NewEbgresNetwLayer.h"
#include "NetwControlInfo.h"
#include "NetwToMacControlInfo.h"
#include "BaseMacLayer.h"
#include "AddressingInterface.h"

#include <cassert>

Define_Module(NewEbgresNetwLayer);

#define EV_NET ev << "Host " << myNetwAddr << " Network Layer : "

void NewEbgresNetwLayer::initialize(int stage)
{
    BaseLayer::initialize(stage);

    if(stage==0){
        headerLength= par("headerLength");
        arp = FindModule<ArpInterface*>::findSubModule(findHost());

        nodeInformationPtr = dynamic_cast<NodeInformation*>(getParentModule()->getSubmodule("nodeInfo"));

        configurationPtr = dynamic_cast<Configuration*>(getParentModule()->getParentModule()->getSubmodule("configuration"));

        dataMessageStorage = NULL;
    }
    else if(stage == 1) {
    	// see if there is an addressing module available
    	// otherwise use module id as network address
        AddressingInterface* addrScheme = FindModule<AddressingInterface*>
													::findSubModule(findHost());
        if(addrScheme) {
        	myNetwAddr = addrScheme->myNetwAddr(this);
        } else {
        	myNetwAddr = getId();
        }

        EV_NET << " myNetwAddr " << myNetwAddr << endl;

        //Calculate distance to destination.

        Coord hostCoord = nodeInformationPtr->getHostCoordinates();

        //Initialize module properties.
        messageTransmissionState = IDLE;

        waitingForAckTimer = NULL;

        waitingForSelectTimer = NULL;
    }
    else if (stage == 5)
    {
    }
}

void NewEbgresNetwLayer::cancelSelfMessage(cMessage **selfMessagePtrPtr)
{
	if (*selfMessagePtrPtr != NULL)
	{
		if ((*selfMessagePtrPtr)->isScheduled())
		{
			cancelEvent(*selfMessagePtrPtr);
			delete *selfMessagePtrPtr;
			*selfMessagePtrPtr = NULL;
		}
	}
}

Coord NewEbgresNetwLayer::calculateIdealPosition(Coord sinkPos, Coord hostCoord, double range)
{

    double distanceToDestination = hostCoord.distance(sinkPos);

    Coord idealPosition = (sinkPos - hostCoord)*((range)/(distanceToDestination)) + hostCoord;

    return idealPosition;
}

/**
 * Decapsulates the packet from the received Network packet
 **/
cMessage* NewEbgresNetwLayer::decapsMsg(EbgresNetwMessage *msg)
{
	cMessage *m = msg->decapsulate();
    m->setControlInfo(new NetwControlInfo(msg->getDestAddr()));
    // delete the netw packet
    delete msg;
    return m; //return the pointer after removing thr address
}


/**
 * Encapsulates the received ApplPkt into a NetwPkt and set all needed
 * header fields.
 **/
EbgresNetwMessage* NewEbgresNetwLayer::encapsMsg(EbgresApplMessage *appPkt) {
    int netwAddr; //Final destination address.

    EV_NET <<"in encaps...\n";

    EbgresNetwMessage *pkt = new EbgresNetwMessage(appPkt->getName(), NETW_DATA_MESSAGE);

    pkt->setBitLength(headerLength);

    NetwControlInfo* cInfo = dynamic_cast<NetwControlInfo*>(appPkt->removeControlInfo());

    if(cInfo == 0){
    EV_NET << "warning: Application layer did not specifiy a destination L3 address\n"
	   << "\tusing broadcast address instead\n";
	netwAddr = L3BROADCAST;
    } else {
	EV <<"CInfo removed, netw addr="<< cInfo->getNetwAddr()<<endl;
        netwAddr = cInfo->getNetwAddr();

    std::cout << "Network control info deleted.\n";
	delete cInfo;
    }

    //encapsulate the application packet
    pkt->encapsulate(appPkt);
    EV_NET <<" pkt encapsulated\n";

    //Prepare data packet.
    prepareDataPacket(netwAddr, pkt);
    dataMessageStorage = pkt;
    return pkt;
}

void NewEbgresNetwLayer::prepareDataPacket(int finalDestination, EbgresNetwMessage *packet)
{
	int macAddr;
    //Create data message portion setting host source position host position ideal position.

	EV_NET << "Preparing data message.\n";

    //Creating new data message.
    DataMessage dataMessage;

    dataMessage.setDestinationPos(nodeInformationPtr->getSinkCoordinates());
    dataMessage.setSourcePos(nodeInformationPtr->getHostCoordinates());

    Coord idealPosition = calculateIdealPosition(nodeInformationPtr->getSinkCoordinates(), nodeInformationPtr->getHostCoordinates(), 80);

    EV_NET << "Calculating Ideal next hop position.\n";
    EV_NET << "Current position " << nodeInformationPtr->getHostCoordinates().info() << "\n";
    EV_NET << "Ideal position " << idealPosition.info() << "\n";
    EV_NET << "Final destination position " << nodeInformationPtr->getSinkCoordinates().info() << "\n";

    dataMessage.setIdealPos(idealPosition);
    dataMessage.setResidualEnergySender(0);

    packet->setDataMessage(0, dataMessage);

    packet->setType(0);

    nodeInformationPtr->increaseDataMessageId();
    packet->setDataMessageId(nodeInformationPtr->getDataMessageId());

    packet->setSrcAddr(myNetwAddr);
    packet->setDestAddr(finalDestination);

    currentSendingMessageId = packet->getDataMessageId();
    currentSendingOriginatorAddress = packet->getSrcAddr();

    int nextHopAddr = router.getNextHopAddr();
    int receivedFromAddr = myNetwAddr;

    packet->setNextHopAddr(nextHopAddr);
    packet->setReceivedFromAddr(receivedFromAddr);

    EV_NET << " netw "<< myNetwAddr << " sending packet" <<endl;
    if(finalDestination == L3BROADCAST) {
        EV << "sendDown: nHop=L3BROADCAST -> message has to be broadcasted"
           << " -> set destMac=L2BROADCAST\n";
        macAddr = L2BROADCAST;
    }
    else{
        EV <<"sendDown: get the MAC address\n";
        //macAddr = arp->getMacAddr(nextHopAddr);
        macAddr = L2BROADCAST;
    }

    packet->setControlInfo(new NetwToMacControlInfo(macAddr));

    //Set the packet to the correct byte length: make sure how encapsulation affects the packet length.
    packet->setByteLength(1024);
}

void NewEbgresNetwLayer::handleSelfMsg(cMessage* msg)
{
    switch(msg->getKind())
    {
    case SEND_ACK_MESSAGE:
    	sendAckMessageToLower();
        break;
    case WAITING_FOR_ACK_MESSAGE:
    	//Resend data message.
            break;
    case WAITING_FOR_SELECT_MESSAGE:
    	//Resend the ack message.
            break;

    default:
        EV <<" Unkown selfmessage! -> delete, kind: "<<msg->getKind()<<endl;
    }
    delete msg;
}

void NewEbgresNetwLayer::sendAckMessageToLower()
{
	EV << "Host " << myNetwAddr << "sending acknowledge message\n";
	outputHostEnergy();
	//Change State Property
	messageTransmissionState = WAITING_FOR_SELECT;

	//Set Select Time-Out Timer

	waitingForSelectTimer = new cMessage( "Waiting For Select Self Message", WAITING_FOR_SELECT_MESSAGE );
	double selectTimeOutTime = 0.5;
	scheduleAt(simTime() + selectTimeOutTime, waitingForSelectTimer);

	EbgresNetwMessage *packet = new EbgresNetwMessage("ACK MESSAGE", NETW_ACK_MESSAGE );

	AckMessage ackMessage;

	ackMessage.setIntermediatePos(nodeInformationPtr->getHostCoordinates());
	ackMessage.setIntermediateNodeAddress(myNetwAddr);

	packet->setAckMessage(0, ackMessage);

	packet->setType(1);
	packet->setDataMessageId(dataMessageStorage->getDataMessageId());

	packet->setControlInfo(new NetwToMacControlInfo(L2BROADCAST));
	sendDown(packet);
}

void NewEbgresNetwLayer::sendSelectMessageToLower(int intermediateNodeAddress)
{
	EV << "Host " << myNetwAddr << "sending select message\n";
	outputHostEnergy();
	EbgresNetwMessage *packet = new EbgresNetwMessage("SELECT MESSAGE", NETW_SELECT_MESSAGE );

	SelectMessage selectMessage;

	selectMessage.setSelectNodeAddress(intermediateNodeAddress);
	packet->setSelectMessage(0, selectMessage);

	packet->setType(2);

	packet->setControlInfo(new NetwToMacControlInfo(L2BROADCAST));
	sendDown(packet);
}

void NewEbgresNetwLayer::sendDataMessageToLower(EbgresNetwMessage *message)
{
	EV << "Host " << myNetwAddr << "sending data message\n";
	outputHostEnergy();

	messageTransmissionState = WAITING_FOR_ACK;

	waitingForAckTimer = new cMessage( "Waiting For Ack Self Message", WAITING_FOR_ACK_MESSAGE );
	double ackTimeOutTime = 1.5; //Maximum waiting time for ack delay*1.5.
	scheduleAt(simTime() + ackTimeOutTime, waitingForAckTimer);
    sendDown(message);
}
/**
 * Redefine this function if you want to process messages from lower
 * layers before they are forwarded to upper layers
 *
 *
 * If you want to forward the message to upper layers please use
 * @ref sendUp which will take care of decapsulation and the like
 **/
void NewEbgresNetwLayer::handleLowerMsg(cMessage* msg)
{
	std::cout << "Node " << myNetwAddr << " handle lower message\n";
	EbgresNetwMessage *message = static_cast<EbgresNetwMessage *>(msg);
    EV << " handling packet received from " << message->getReceivedFromAddr() << endl;
    std::cout << " handling packet received from " << message->getReceivedFromAddr() << endl;
    std::cout << " message type is " << message->getType() << "\n";

    if (message->getType() == 0)
    {
    	handleDataMessage(message);
    }
    else if (message->getType() == 1)
    {
    	handleAckMessage(message);
    }
    else if (message->getType() == 2)
    {
    	handleSelectMessage(message);
    }

    /*
    if (myNetwAddr == message->getDestAddr())
    {
    	std::cout << "message arrived!\n";
    	EV << "message arrived!\n";

    }
    else handleForwardMessage(message);
	*/

    //sendUp(decapsMsg(m));
}

void NewEbgresNetwLayer::handleDataMessage(EbgresNetwMessage *message)
{
	EV << "Handling data message\n";
	DataMessage dataMessage = message->getDataMessage(0);

	Coord idealPosition = dataMessage.getIdealPos();

	cObject* cInfo = message->removeControlInfo();

	delete cInfo;
	//Test if receiving node is in relay search region.

	double relaySearchRadius = configurationPtr->getSearchRadius();
	double distanceFromIdeal = idealPosition.distance(nodeInformationPtr->getHostCoordinates());

	EV << "Host distance from ideal " << distanceFromIdeal << "\n";
	if (distanceFromIdeal < relaySearchRadius)
	{
		EV << "Node " << myNetwAddr << " in relay search region.\n";
		double fullAckDelayTime = 1;
		double ackDelayTime = (distanceFromIdeal/relaySearchRadius)*fullAckDelayTime;

		scheduleSendAckMessage(ackDelayTime);

		dataMessageStorage = message;

		if (myNetwAddr == message->getDestAddr())
		{
			EV_NET << "\n\n Message Arrived at final destination :) !!! \n\n";
		}
	}
	//include select delay

}

void NewEbgresNetwLayer::scheduleSendAckMessage(double ackDelayTime)
{
	sendAckMessage = new cMessage( "Send return ack message", SEND_ACK_MESSAGE );
	scheduleAt(simTime() + ackDelayTime, sendAckMessage);
}

void NewEbgresNetwLayer::scheduleSendSelectMessage(double selectDelayTime)
{
	sendSelectMessage = new cMessage( "Send return select message", SEND_SELECT_MESSAGE );
	scheduleAt(simTime() + selectDelayTime, sendSelectMessage);
}

void NewEbgresNetwLayer::handleAckMessage(EbgresNetwMessage *message)
{
	EV << "handling ACK message.\n";

	//Strip ackMessage

	//Confirm dataMessageId and original source to make sure we are handling the right packet.

	EV << "Message data id : " << message->getDataMessageId() << "\n";

	EV << "Current Sending message id " << currentSendingMessageId << "\n";
	EV << "MessdataMessageStorageage src address : " << message->getSrcAddr() << "\n";

	EV << "Current sending originator address : " << currentSendingOriginatorAddress << "\n";

	//Make sure if message is coming from the final destination.
	//If it is coming from the final destination no further select message should be sent, because the
	//data was successfully delivered.

	//Other conditions as well.

	if (dataMessageStorage != NULL)
	{
		EV << "Final Destination Address " << dataMessageStorage->getDestAddr() << "\n";

		EV << "Intermediate node address" << message->getAckMessage(0).getIntermediateNodeAddress() << "\n";
		if (
				(message->getDataMessageId() == currentSendingMessageId)
				&& (dataMessageStorage->getDestAddr() != message->getAckMessage(0).getIntermediateNodeAddress()) /* && (message->getSrcAddr() == currentSendingOriginatorAddress) */)
		{
			//Cancel Waiting for ack timeout timer.
			cancelSelfMessage(&waitingForAckTimer);
			messageTransmissionState = IDLE;
			AckMessage ackMessage = message->getAckMessage(0);

			int intermediateNodeAddress = ackMessage.getIntermediateNodeAddress();

			sendSelectMessageToLower(intermediateNodeAddress);
		}
	}
}

void NewEbgresNetwLayer::handleSelectMessage(EbgresNetwMessage *message)
{
	EV <<"handle SELECT message.\n";
	std::cout << "handle SELECT message.\n";
    //Create data message portion setting host source position host position ideal position.

	if (myNetwAddr == message->getSelectMessage(0).getSelectNodeAddress())
	{
		//Go into idle state.
		messageTransmissionState = IDLE;
		//Cancel select timeout message.
		cancelSelfMessage(&waitingForSelectTimer);


		EV << "Preparing data message.\n";

		prepareDataPacket(dataMessageStorage->getDestAddr(), dataMessageStorage);

		sendDataMessageToLower(dataMessageStorage);
	}
}


void NewEbgresNetwLayer::handleForwardMessage(EbgresNetwMessage *message)
{
	std::cout << "Forwarding message!\n";
	cMessage *msg = decapsMsg(message);
	EbgresApplMessage *forwardMessage = dynamic_cast<EbgresApplMessage*>(msg);

	sendDown(encapsMsg(forwardMessage));
}

/**
 * Redefine this function if you want to process messages from upper
 * layers before they are send to lower layers.
 *
 * For the BaseNetwLayer we just use the destAddr of the network
 * message as a nextHop
 *
 * To forward the message to lower layers after processing it please
 * use @ref sendDown. It will take care of anything needed
 **/
void NewEbgresNetwLayer::handleUpperMsg(cMessage* msg)
{
	assert(dynamic_cast<EbgresApplMessage*>(msg));
	EbgresApplMessage *message = dynamic_cast<EbgresApplMessage*>(msg);

	sendDataMessageToLower(encapsMsg(message));
}

/**
 * Redefine this function if you want to process control messages
 * from lower layers.
 *
 * This function currently handles one messagetype: TRANSMISSION_OVER.
 * If such a message is received in the network layer it is deleted.
 * This is done as this type of messages is passed on by the BaseMacLayer.
 *
 * It may be used by network protocols to determine when the lower layers
 * are finished sending a message.
 **/
void NewEbgresNetwLayer::handleLowerControl(cMessage* msg)
{
	switch (msg->getKind())
	{
	case BaseMacLayer::TX_OVER:
		delete msg;
		break;
	default:
		EV << "BaseNetwLayer does not handle control messages called "
		   << msg->getName() << endl;
		delete msg;
	}
}

int NewEbgresNetwLayer::getNetwAddr()
{
	return myNetwAddr;
}

void NewEbgresNetwLayer::outputHostEnergy()
{
	EV << "Energy " << std::setprecision(10) << nodeInformationPtr->getResidualEnergy() << "mAh?\n";
}
