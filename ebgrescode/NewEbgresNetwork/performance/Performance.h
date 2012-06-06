/***************************************************************************
 * file:        Performance.h
 *
 * author:      Daniël Kotze
 *
Copyright (c) 2011 Stellenbosch University, DSP Laboratory
    This program is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the 
    Free Software Foundation; either version 2 of the License, or (at your option) any later version.
    This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or 
    FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.
    You should have received a copy of the GNU General Public License along with this program; if not, write to the Free Software Foundation, Inc., 59 Temple 
    Place, Suite 330, Boston, MA 02111-1307 USA

Contact Details:
E-mail: daniel.kotze@gmail.com
 ***************************************************************************
 * part of:     Cluster Head Gateway Routing Protocol Simulation
 * description: - The performance module provides a mechanism to publish performance data of the protocol
 *
 ***************************************************************************/

#ifndef PERFORMANCE_H
#define PERFORMANCE_H

#define COMPILE_WITH_UNIT_TESTS FALSE

#include <sstream>

#include <omnetpp.h>

//Simulation Libraries

#include "Route.h"
#include "CommunicationLinkVector.h"

#include "SystemController.h"

#include "Node.h"

#include "LinkBreak.h"

#include "EbgresNetwMessage_m.h"

#include "DataFileCreator.h"


class Packet : public cObject
{
	protected:
		double 	timeCreated;
		double 	timeArrived;
		int		numberOfHops;

		int		source;
		int		destination;
		int		currentNode;

		bool	inQueue;
		double	queueEntryTime;
		double	queueServiceTime;

	public:
		Packet()
		{
			timeCreated = -1;
			timeArrived = -1;
			numberOfHops = 0;
			setSource(0);
			setDestination(0);
			setCurrentNode(0);
			
			inQueue = false;
			queueEntryTime = -1;
			queueServiceTime = -1;
		};

		void setSource(int src)
		{
			source = src;
		};

		int getSource()
		{
			return source;
		};

		void setDestination(int dest)
		{
			destination = dest;
		};

		int getDestination()
		{
			return destination;
		};

		void setCurrentNode(int cNode)
		{
			printf("In setCurrentNode %d\n", cNode);
			currentNode = cNode;
			printf("After setting current node\n");
		}

		int getCurrentNode()
		{
			return currentNode;
		};

		void setTimeCreated(double tCreated)
		{
			timeCreated = tCreated;
		};

		void setTimeArrived(double tArrived)
		{
			timeArrived = tArrived;
		};

		double getTimeCreated()
		{
			return timeCreated;
		};

		double getTimeArrived()
		{
			return timeArrived;
		};

		void increaseNumberOfHops()
		{
			numberOfHops++;
		};

		int getNumberOfHops()
		{
			return numberOfHops;
		};
};

#define HOP_LATENCY_ARRAY_SIZE 10

class Performance : public cSimpleModule
{

	
	enum SELF_MSG_TYPES{
	MEASURE_CONNECTIVITY_TIMER,
	WRITE_COMMUNICATION_LINK_THROUGHPUT_TIMER,
	TIME_WRITE_TIMER,
	MEASURE
	};
	
	protected:
		cMessage *measureConnectivityTimer;
		cMessage *writeCommunicationLinkThroughputTimer;
		cMessage *timeWriteTimer;
		
		bool				printNetworkHopsPercentage;
		bool				pMessagesSentReceived;
		bool				pMessagesStartEndTime;
		bool				pBitRateDemandedHandled;
		
		bool				simulationTimeConnectivity;
		
		char				simulationOutputDirectory[255];
		char				runOutputDirectory[255];

		double				startMessagesTime, endMessagesTime;

		int 				messagesSent, messagesReceived;
		int					messagesLost;
		int					messagesUnroutable;
		int					transmissionsReceived;
		int					initializeNum;

		int					totalNodes;

		double				inputBitRate;

		NodeList nodeList;
		LinkedList packetList;
		RouteList routeList;
		
		CommunicationLinkVector communicationLinkVector;

		//Statistics

		cStdDev				nodesPacketsSuccess;

		cLongHistogram 		successPacketHopCountStats;			//Stores the number of hops of the packet in a histogram
		cLongHistogram		lostPacketHopCountStats;
		cDoubleHistogram	packetLatencyStats;				//Stores the latency of the packet in a histogram

		cDoubleHistogram	hopLatencyStatsArray[HOP_LATENCY_ARRAY_SIZE];

		cOutVector          packetHopCountLatencyVector;
		
		int					networkNodeHops[10];
		
		//Link Break Parameters
		LinkBreak lBreak;
		
		//Test Parameters
		
		//File Write Parameters
		bool	writeCommunicationLinkToFile;
		
		//Recording Parameters
		bool	recordCommunicationLink;
		
		//Simulation Parameters
		int	runNumber;

	public:
		virtual void initialize(int stage);

		virtual void setup();

		void registerNetworkNodes();


		void initializeParameters();
		void readInXMLParameters(cXMLElement *xmlElement);
		void initializeHopLatencyStatsArray();

		void 	setTotalNodes(int tNodes);
		int		getTotalNodes();
		
		int getRunNumber()
		{
			return runNumber;
		};

		virtual void finish();

		int registerNode(int address);

		int registerPacket(double startTime);

		void printNodeData();

		double calculateBitRate(double bitsTransmitted, double totalTime);

		double getStartMessagesTime()
		{
			return startMessagesTime;
		};

		void setStartMessagesTime(double sMessagesTime)
		{
			startMessagesTime = sMessagesTime;
		};

		double getEndMessagesTime()
		{
			return endMessagesTime;
		};

		void	setEndMessagesTime(double eMessagesTime)
		{
			endMessagesTime = eMessagesTime;
		};

		double getInputBitRate()
		{
			return inputBitRate;
		};

		void setInputBitRate(double iBitRate)
		{
			inputBitRate = iBitRate;
		};

		//Access data methods

		Node *getNode(int id)
		{
			return ((Node*) nodeList.getItem(id));
		};

		Node *getNodeAddress(int address)
		{
			for (int i=0; i<nodeList.getListSize(); i++)
			{
				if ( ((Node*) nodeList.getItem(i))->getAddress() == address)
				{
					return ((Node*) nodeList.getItem(i));
				}
			}
			return NULL;
		};
		
		Node *getNodeIndex(int index)
		{
			for (int i=0; i<nodeList.getListSize(); i++)
			{
				if ( ((Node*) nodeList.getItem(i))->getNodeIndex() == index)
				{
					return ((Node*) nodeList.getItem(i));
				}
			}
			return NULL;
		};

		Packet *getPacketId(int id)
		{
			printf("In get packet Id\n");
			return ((Packet*) packetList.getItemId(id));
		};

		NodeList *getNodeListPtr()
		{
			return &nodeList;
		};
        
        /** @brief Handle self messages such as timer... */
		virtual void handleSelfMsg(cMessage*);
		
		virtual void handleMessage(cMessage* msg);

		//Compute statistics information

		void 	increaseMessagesReceived();
		void 	increaseMessagesSent();
		void 	increaseMessagesLost();
		void 	increaseTransmissionsReceived();

		void 	increaseNodeMessagesCreated(int id);
		void 	increaseNodeMessagesPassedOn(int id);
		void 	increaseNodeMessagesArrivedDestination(int id);

		int		getNodeMessagesCreated(int id);
		int		getNodeMessagesPassedOn(int id);
		int		getNodeMessagesArrivedDestination(int id);

		int 	calculateHopsBetweenNodes(int startNodeAddress, int endNodeAddress);
        
        void    recordMessageGenerated(int sourceAddress, int destinationAddress);
		//Print Statistics functions
		void	printMessagesSentReceived();
		void	printMessagesStartEndTime();
		void	printBitRateDemandedHandled();

		void printNodePacketsSuccess()
		{
			ev << "Node Packets Successfully delivered statistic" << endl;
			ev << "Number of samples : " << nodesPacketsSuccess.getCount() << endl;
			ev << "Minimum : " << nodesPacketsSuccess.getMin() << endl;
			ev << "Maximum : " << nodesPacketsSuccess.getMax() << endl;
			ev << "Mean : " << nodesPacketsSuccess.getMean() << endl;
			ev << "Standard Deviation : " << nodesPacketsSuccess.getStddev() << endl;
		};

		void printHopCountStatistics();

		void printAndRecordPacketHopsPercentageSuccessful();

		void printPacketLatencyStatistics();
		void recordPacketLatencyStatistics();

		void recordHopLatencyStatsArray();
		void printHopLatencyStatsArray();

		void 	increasePacketHops(int idNum);
		int		getPacketHops(int idNum)
		{
			return ((Packet*) packetList.getItemId(idNum))->getNumberOfHops();
		};

		void	gatherNodeStatistics()
		{
			for (int i=0; i<nodeList.getListSize(); i++)
			{
				printf("Node %d : %d\n", i, nodeList.getNodePtr(i)->getMessagesSentSuccess());
				nodesPacketsSuccess.collect( (double) nodeList.getNodePtr(i)->getMessagesSentSuccess());
			}
		};

		void recordNodePacketSuccessScalars()
		{
			recordScalar("Number of samples", nodesPacketsSuccess.getCount());
			recordScalar("Minimum Packets Transmitted", nodesPacketsSuccess.getMin());
			recordScalar("Maximum Packets Transmitted", nodesPacketsSuccess.getMax());
			recordScalar("Mean Packets Transmitted", nodesPacketsSuccess.getMean());
			recordScalar("Standard Deviation Packets Transmitted Node", nodesPacketsSuccess.getStddev());
		};

		void	setPacketArrivalTime(int idNum, double arriveTime);
		void 	postProcessPacket(int idNum, EbgresNetwMessage *pkt);
		void 	postProcessLostPacket(int idNum);

		void 	testClusterHeadsInRange();

		void 	analyzeNodeNeighbours();

		
		void 	determineNetworkComposition();
		
		void convertNodePathToArray(EbgresNetwMessage *packet, int path[]);
		
		//Test Functions
		void 	testConnectivity();
		void 	breakLinkRoute(LinkBreak linkBreak);
		
		//File write functions
        
        void writePercentageTokensSentReceivedBackToFile();
        void writeMostUsedRouteToFile();
        void writeLostPacketsToFile();
        void writeCommunicationLinksOnlyToFile();
        void writeNodePositionsToFile(void);
		void writeNodePacketsLost(void);
		void writeLatencyValuesToFile(void);
        void writeClusterHeadTokenPacketsDataToFile(void);
		void writeSuccessfulExecution(void);
};
#endif
