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


#ifndef EBGRES_APPL_LAYER_H
#define EBGRES_APPL_LAYER_H

#include <TestApplLayer.h>

#include "EbgresApplLayerMessage_m.h"

#include "NodeInformation.h"


/**
 * @brief Application layer to test lower layer implementations
 *
 * This application layer does exactly the same as the
 * TestApplLayer. The only difference is that is sends a burst of
 * broadcast messages instead of just one. The burst size is specified
 * in burstSize and can be set in omnetpp.ini
 *
 * @sa TestApplALyer
 * @ingroup applLayer
 * @author Daniel Willkomm
 **/
class ebgresApplLayer : public TestApplLayer
{

    enum EbgresApplMessageKinds{
    	SEND_APPL_DATA_MESSAGE,
    	APPL_DATA_MESSAGE
    };

 public:
  /** @brief Initialize module parameters*/
  virtual void initialize(int);

 protected:
  NodeInformation *nodeInformationPtr;

  cMessage *sendApplDataMessage;
  /** @brief Handle self messages such as timer... */
  virtual void handleSelfMsg(cMessage*);

  void scheduleStartMessage();

  void handleSendApplDataMessage();

  int getNetwAddr();

  int getHostIndex();


  /** @brief Number of messages to send in a burst*/
  int burstSize;

  virtual int numInitStages() const {
  			return 6;
  		}
};

#endif
