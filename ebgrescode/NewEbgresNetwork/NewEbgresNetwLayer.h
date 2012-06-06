/* -*- mode:c++ -*- ********************************************************
 * file:        BaseNetwLayer.h
 *
 * author:      Oswald
 *
 * copyright:   (C) 2004 Telecommunication Networks Group (TKN) at
 *              Technische Universitaecd
 *              t Berlin, Germany.
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
 **************************************************************************/


#ifndef NEW_EBGRES_NETW_LAYER_H
#define NEW_EBGRES_NETW_LAYER_H

#include <iomanip>

#include <Coord.h>

#include <BaseLayer.h>

#include <ArpInterface.h>
#include <NetwPkt_m.h>
#include <SimpleAddress.h>
#include <BaseNetwLayer.h>

#include <omnetpp.h>

#include "EbgresRouter.h"

#include "EbgresApplLayerMessage_m.h"
#include "EbgresNetwMessage_m.h"

#include "NodeInformation.h"
#include "Configuration.h"

/**
 * @brief Base class for the network layer
 *
 * @ingroup netwLayer
 * @ingroup baseModules
 * @author Daniel Willkomm
 **/

/*
 * Class Prototypes
 */
class NodeInformation;
class Configuration;

class NewEbgresNetwLayer : public BaseNetwLayer
{
public:
	enum EbgresNetwMessageKinds{
	    	NETW_DATA_MESSAGE,
	    	NETW_ACK_MESSAGE,
	    	NETW_SELECT_MESSAGE,
	    	/* Self messages follow. */
	    	SEND_ACK_MESSAGE,
	    	SEND_SELECT_MESSAGE,
	    	WAITING_FOR_ACK_MESSAGE,
	    	WAITING_FOR_SELECT_MESSAGE
	    };

	enum MessageTransmissionState
	{
		WAITING_FOR_ACK,
		IDLE,
		WAITING_FOR_SELECT
	};

protected:
    /**
     * @brief Length of the NetwPkt header
     * Read from omnetpp.ini
     **/
    int headerLength;

    /** @brief Pointer to the arp module*/
    ArpInterface* arp;

    /** @brief cached variable of my network address */
    int myNetwAddr;

    EbgresRouter router;

    NodeInformation *nodeInformationPtr;

    Configuration *configurationPtr;

    int sinkAddress;

    Coord sinkPosition;

    cMessage *sendAckMessage;

    cMessage *sendSelectMessage;

    /* Timer to wait for ack message to time out. */
    cMessage *waitingForAckTimer;

    /* Timer to wait for select message to time out.*/
    cMessage *waitingForSelectTimer;

    EbgresNetwMessage *dataMessageStorage;

    int currentSendingMessageId;
    int currentSendingOriginatorAddress;

    MessageTransmissionState messageTransmissionState;

public:
    //Module_Class_Members(BaseNetwLayer,BaseLayer,0);

    /** @brief Initialization of the module and some variables*/
    virtual void initialize(int);

    int getNetwAddr();

    virtual int numInitStages() const {
    			return 6;
    		}

  protected:
    /**
     * @name Handle Messages
     * @brief Functions to redefine by the programmer
     *
     * These are the functions provided to add own functionality to your
     * modules. These functions are called whenever a self message or a
     * data message from the upper or lower layer arrives respectively.
     *
     **/
    /*@{*/

    /** @brief Handle messages from upper layer */
    virtual void handleUpperMsg(cMessage* msg);

    /** @brief Handle messages from lower layer */
    virtual void handleLowerMsg(cMessage* msg);

    /** @brief Handle self messages */
    virtual void handleSelfMsg(cMessage* msg);

    /** @brief Handle control messages from lower layer */
    virtual void handleLowerControl(cMessage* msg);

    /** @brief Handle control messages from lower layer */
    virtual void handleUpperControl(cMessage* msg){
        error("BaseNetwLayer does not handle control messages");
    };

    /*@}*/

    /** @brief decapsulate higher layer message from NetwPkt */
    virtual cMessage* decapsMsg(EbgresNetwMessage*);

    /** @brief Encapsulate higher layer packet into an NetwPkt*/
    virtual EbgresNetwMessage* encapsMsg(EbgresApplMessage*);

    virtual void handleForwardMessage(EbgresNetwMessage*);

    virtual Coord calculateIdealPosition(Coord sinkPos, Coord hostCoord, double range);

    virtual void handleDataMessage(EbgresNetwMessage *message);

    virtual void handleAckMessage(EbgresNetwMessage *message);

    virtual void handleSelectMessage(EbgresNetwMessage *message);

    virtual void scheduleSendAckMessage(double ackDelayTime);

    virtual void sendAckMessageToLower();

    virtual void scheduleSendSelectMessage(double selectDelayTime);

    virtual void sendSelectMessageToLower(int intermediateNodeAddress);

    virtual void prepareDataPacket(int finalDestination, EbgresNetwMessage *packet);

    virtual void sendDataMessageToLower(EbgresNetwMessage *message);

    virtual void cancelSelfMessage(cMessage **selfMessagePtrPtr);

    void outputHostEnergy();
};

#endif
