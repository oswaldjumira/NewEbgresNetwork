/***************************************************************************
 * file:        Performance.cc
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

/*
*	1. Skryf funksies om data te verander!
*	2. Skryf kode om te toets of twee clusterheads neighbours van mekaar is.
*/

#define DATA_MESSAGE_SIZE_BYTES 1024

//#include <ctime>
#include "Performance.h"


//#define EV ev << "Performance Module >> " ==> EV is now part of <omnetpp.h>

std::ostream &operator<<(std::ostream& stream, Route &route)
{
	stream << " Route << Source Address : " << route.getSourceAddress() << " >> Destination Address : " << route.getDestinationAddress() << endl;
	stream << "\tMean Latency : " << route.getMeanLatency() << "s" << endl;
	stream << "\tMean Throughput : " << route.getMeanThroughput() << endl;
	stream << "\tNumber Of Observations : " << route.getNumberOfObservations() << endl;
    stream << "\tMean Data Rate Demanded : " << route.getMeanDataRateDemanded() << endl;
    stream << "\tNumber Of Messages Sent : " << route.getNumberOfMessagesSent() << endl;
	return stream;
}

std::ostream &operator<<(std::ostream& stream, RouteList &routeList)
{
	stream << "Printing Route List" << endl;
	stream << "List size : " << routeList.getListSize() << endl;
	for (int i=0; i<routeList.getListSize(); i++) stream << i << routeList.getRoute(i);
	return stream;
}

void Route::recordLatencyAndThroughput(double latency, double arrivalTime)
{
	meanLatency = ((meanLatency*getNumberOfObservations())+latency)/(getNumberOfObservations()+1);

	if (getNumberOfObservations() == 0) firstArrival = arrivalTime;
	else
	{
		lastArrival = arrivalTime;
		meanThroughput = (getNumberOfObservations()*DATA_MESSAGE_SIZE_BYTES*8)/(lastArrival-firstArrival);
	}

	setNumberOfObservations(getNumberOfObservations()+1);
}


void Route::recordMessageSent(double messageSentTime)
{

    if (getNumberOfMessagesSent() == 0) firstMessageSent = messageSentTime;
    else
    {
        lastMessageSent = messageSentTime;
        meanDataRateDemanded = (getNumberOfMessagesSent()*DATA_MESSAGE_SIZE_BYTES*8)/(lastMessageSent-firstMessageSent);
    }

    setNumberOfMessagesSent(getNumberOfMessagesSent()+1);
}

Define_Module(Performance);

void Performance::initialize(int stage)
{
	if (stage == 0)
	{
		setInputBitRate(-1); //Set InputBitRate in stage 0 >> it is going to be modified in stage 2 of another module
	}
	else if (stage == 1)
	{
		setup();
		//time_t theTime = time( NULL );
		//recordScalar(asctime( localtime( &theTime ) ), 0);

		messagesSent = messagesReceived = messagesLost = messagesUnroutable = 0;
		//Set up histogram for successful packet transmissions
		successPacketHopCountStats.setName("Successful Packet Transmission Hop Count Histogram");
		successPacketHopCountStats.setRangeAutoUpper(0,10,1.5);
		successPacketHopCountStats.setNumCells(10);

		lostPacketHopCountStats.setName("Total Packet Transmission Hop Count Histogram");
		lostPacketHopCountStats.setRangeAutoUpper(0,10,1.5);
		lostPacketHopCountStats.setNumCells(10);

		//Set up histogram for total attempted packet transmissions
		
		packetLatencyStats.setName("Latency Histogram");
		packetLatencyStats.setRangeAutoUpper(0,10,1.5);
		packetLatencyStats.setNumCells(70);

		packetHopCountLatencyVector.setName("Hop Count Latency Vector");

		initializeHopLatencyStatsArray();

		//Initialize times
		setStartMessagesTime(-1);
		setEndMessagesTime(-1);

		//Initialize performance module parameters
		initializeParameters();
		
		//Create performance module output directory
		{
				SystemController systemController;
				systemController.setBaseDirectory(runOutputDirectory);
				systemController.createDirectory("/Performance/");
		}
		
		
		//Test if simulation time connectivity must be measured
		if (simulationTimeConnectivity)
		{
			//Set up connectivity output file
			{
				char outputFile[255];
				strcpy(outputFile, runOutputDirectory);
				strcat(outputFile, "/Performance/connectivity.txt");
				/*
				connectivityOutputFile.setFilePath(outputFile);
				if (connectivityOutputFile.openFile())
				{
					ev << "Connectivity File Opened Successfully for Writing Data" << endl;
				}
				else ev << "Connectivity File creation failed." << endl;
				*/
			}
		
			//Set up measurement timers
			measureConnectivityTimer = new cMessage("Measure Connectivity Timer", MEASURE_CONNECTIVITY_TIMER);
			scheduleAt(simTime() + 0, measureConnectivityTimer);
		}
		
		if (writeCommunicationLinkToFile)
		{
			//Set up Communication Link File
			{
				char outputFile[255];
				strcpy(outputFile, runOutputDirectory);
				strcat(outputFile, "/Performance/communicationLink.txt");
				/*
				communicationLinkOutputFile.setFilePath(outputFile);
				if (communicationLinkOutputFile.openFile())
				{
					ev << "Communication Link File Opened Successfully for Writing Data" << endl;
				}
				else ev << "Communication Link File creation failed." << endl;
				*/
				
			}
		
			//Set up measurement timers
			writeCommunicationLinkThroughputTimer = new cMessage("WRITE_COMMUNICATION_LINK_THROUGHPUT_TIMER", WRITE_COMMUNICATION_LINK_THROUGHPUT_TIMER);
			scheduleAt(simTime() + 0, writeCommunicationLinkThroughputTimer);
		}
		
		{
			/*
			char outputFile[255];
			strcpy(outputFile, runOutputDirectory);
			strcat(outputFile, "/Performance/simulationTimeOutput.txt");
			simulationTimeOutputFile.setFilePath(outputFile);
			if (simulationTimeOutputFile.openFile())
			{
				ev << "Simulation Time Output File Opened Successfully for Writing Data" << endl;
			}
			else ev << "Simulation Time Output File creation failed." << endl;
				
			timeWriteTimer = new cMessage("Time Write Timer", TIME_WRITE_TIMER);
			scheduleAt(simTime() + 5, timeWriteTimer);
			*/
		}
		
	}
}

void Performance::setup()
{
	registerNetworkNodes();
}

void Performance::registerNetworkNodes()
{

}

void Performance::initializeHopLatencyStatsArray()
{
	char message[50];
	for (int i=0; i<HOP_LATENCY_ARRAY_SIZE; i++)
	{
		sprintf(message,"%d Hop Latency Histogram", i);
		hopLatencyStatsArray[i].setName(message);
		hopLatencyStatsArray[i].setRangeAutoUpper(0,10,1.5);
		hopLatencyStatsArray[i].setNumCells(20);
	}
}

void Performance::initializeParameters()
{
		if (hasPar("simulationOutputDirectory")) strcpy(simulationOutputDirectory, par("simulationOutputDirectory"));
		else strcpy(simulationOutputDirectory, "./SimulationOutput/Misc");
		EV << "Simulation Output Directory : " << simulationOutputDirectory << endl;
		
		if (hasPar("runOutputDirectory")) strcpy(runOutputDirectory, par("runOutputDirectory"));
		else strcpy(runOutputDirectory, "./SimulationOutput/Misc");
		EV << "Run Output Directory : " << runOutputDirectory << endl;
		
		if (hasPar("printNetworkHopsPercentage")) printNetworkHopsPercentage = par("printNetworkHopsPercentage");
		else printNetworkHopsPercentage = false;
		EV << "Print the percentage of nodes available after a certain amount of hops at finish : " << printNetworkHopsPercentage << endl;

		if (hasPar("pMessagesSentReceived")) pMessagesSentReceived = par("pMessagesSentReceived");
		else pMessagesSentReceived = false;
		EV << "Print the number of messages sent and received at the end : " << pMessagesSentReceived << endl;

		if (hasPar("pMessagesStartEndTime")) pMessagesStartEndTime = par("pMessagesStartEndTime");
		else pMessagesStartEndTime = false;
		EV << "Print the message start and end time : " << pMessagesStartEndTime << endl;

		if (hasPar("pBitRateDemandedHandled")) pBitRateDemandedHandled= par("pBitRateDemandedHandled");
		else pBitRateDemandedHandled = false;
		EV << "Print the bitrate demanded and handled : " << pBitRateDemandedHandled << endl;
		
		if (hasPar("simulationTimeConnectivity")) simulationTimeConnectivity = par("simulationTimeConnectivity");
		else simulationTimeConnectivity = false;
		EV << "Calculate the simulation time connectivity : " << simulationTimeConnectivity << endl;
		
		//Setup File Write Parameters
		if (hasPar("writeCommunicationLinkToFile")) writeCommunicationLinkToFile = par("writeCommunicationLinkToFile");
		else writeCommunicationLinkToFile = false;
		EV << "Write Communication Link information to File : " << writeCommunicationLinkToFile << endl;
		
		//Setup Recording Parameters
		if (hasPar("recordCommunicationLink")) recordCommunicationLink = par("recordCommunicationLink");
		else recordCommunicationLink = false;
		EV << "Record Communication Link information : " << recordCommunicationLink << endl;
		
		//Setup Simulation Parameters
		if (hasPar("runNumber")) runNumber = par("runNumber");
		else runNumber = false;
		EV << "Run number : " << runNumber << endl;
		
		//Initialize XML Parameters
		cXMLElement *xmlElement;
		if (hasPar("xmlParameters"))
		{
			EV << "XML File Parameter Detected" << endl;
			xmlElement = par("xmlParameters");
			readInXMLParameters(xmlElement);
		}
		else EV << "Unable get XML parameters" << endl;
}

void Performance::readInXMLParameters(cXMLElement *xmlElement)
{
	EV << "Reading in : " << xmlElement->getTagName() << endl;
	
	xmlElement = xmlElement->getFirstChild();
	EV << "Reading in : " << xmlElement->getTagName() << endl;
	
	xmlElement = xmlElement->getFirstChild();
	int sourceAddress = atoi(xmlElement->getNodeValue());
	EV << "Reading in : " << xmlElement->getTagName() << " >> " << sourceAddress << endl;
	
	xmlElement = xmlElement->getNextSibling();
	int destinationAddress = atoi(xmlElement->getNodeValue());
	EV << "Reading in : " << xmlElement->getTagName() << " >> " << destinationAddress << endl;
	
	//linkBreak.setSourceAddress(sourceAddress);
	//linkBreak.setDestinationAddress(destinationAddress);
}

// You send yourself a message -- probably a timer,
// take care of it here
void Performance::handleSelfMsg(cMessage* msg)
{
    // ENTER YOUR CODE HERE
    
    switch( msg->getKind() )
    {
        case MEASURE_CONNECTIVITY_TIMER:
        {
        	/*
			if (simulationTimeConnectivity)
			{
				measureConnectivityTimer = new cMessage("Measure Connectivity Timer", MEASURE_CONNECTIVITY_TIMER);
				connectivityOutputFile.writeConnectivity(simTime(), nodeList.calculateNetworkConnectivity());
				scheduleAt(simTime() + 0.1, measureConnectivityTimer);
			}
            delete msg;
            */
        }
        break;
		
		case WRITE_COMMUNICATION_LINK_THROUGHPUT_TIMER:
		{
			/*
			if (writeCommunicationLinkToFile)
			{
				writeCommunicationLinkThroughputTimer = new cMessage("WRITE_COMMUNICATION_LINK_THROUGHPUT_TIMER", WRITE_COMMUNICATION_LINK_THROUGHPUT_TIMER);
				communicationLinkOutputFile.writeCommunicationLinkVectorTimeInterval(simTime(), communicationLinkVector);
				communicationLinkVector.resetValuesForNewTimeInterval();
				scheduleAt(simTime() + 0.3, writeCommunicationLinkThroughputTimer);
			}
            delete msg;
            */
		}
		break;
		
		case TIME_WRITE_TIMER:
        {
        	/*
			timeWriteTimer = new cMessage("Time Write Timer", TIME_WRITE_TIMER);
			simulationTimeOutputFile.writeSimulationTime(simTime());
			simulationTimeOutputFile.flushIt();
			scheduleAt(simTime() + 5, timeWriteTimer);
            delete msg;
            */
        }
        break;

        default:
            EV << "Unkown selfmessage! -> delete, kind: "<<msg->getKind() <<endl;
        delete msg;
    }
}

void Performance::handleMessage(cMessage* msg)
{
	handleSelfMsg(msg);
}

void Performance::breakLinkRoute(LinkBreak linkBreak)
{
	std::cout << "\n\nIn breakLinkRoute function\n\n";
	int mostUsedRoute = communicationLinkVector.findMostUsedRoute(linkBreak.getSourceAddress(), linkBreak.getDestinationAddress());
	
	int linkNode1 = -1;
	int linkNode2 = -1;
	communicationLinkVector.getMiddleRouteAddresses(linkBreak.getSourceAddress(), linkBreak.getDestinationAddress(), mostUsedRoute, linkNode1, linkNode2);
	
	if ((linkNode1 != -1) && (linkNode2 != -1))
	{
		lBreak.setSourceAddress(linkNode1);
		lBreak.setDestinationAddress(linkNode2);
		int macAddress1 = getNodeAddress(linkNode1)->getMacAddress();
		int macAddress2 = getNodeAddress(linkNode2)->getMacAddress();
		
		*(getNodeAddress(linkNode1)->getBlockMacAddressPtr()) = macAddress2;
		*(getNodeAddress(linkNode2)->getBlockMacAddressPtr()) = macAddress1;
	}
}

void Performance::setTotalNodes(int tNodes)
{
	totalNodes = tNodes;
}

int Performance::getTotalNodes()
{
	return totalNodes;
}

void Performance::increaseMessagesSent()
{
	messagesSent++;
}

void Performance::increaseMessagesReceived()
{
	messagesReceived++;
}

void Performance::increaseMessagesLost()
{
	messagesLost++;
}

void Performance::increaseTransmissionsReceived()
{
	transmissionsReceived++;
}

int Performance::registerNode(int address)
{
	Node *newNode;
	int idNum;

	newNode = new Node();
	newNode->setAddress(address);
	printf("Address %d\n",newNode->getAddress());
	//idNum = nodeList.addItem(newNode);		//nodeList effectively handles the memory of newNode
	return idNum;
}

int Performance::registerPacket(double startTime)
{
	Packet *newPacket;
	long idNum;
	
	//printf("Registering new packet\n");
	newPacket = new Packet();
	newPacket->setTimeCreated(startTime);
	//idNum = packetList.addItem(newPacket);
	return idNum;
}

void Performance::increasePacketHops(int idNum)
{
	printf("Increasing number of hops 1+%d\n",((Packet*) packetList.getItemId(idNum))->getNumberOfHops());
	((Packet*) packetList.getItemId(idNum))->increaseNumberOfHops();
}

void Performance::setPacketArrivalTime(int idNum, double arriveTime)
{
	((Packet*) packetList.getItemId(idNum))->setTimeArrived(arriveTime);
}


void Performance::convertNodePathToArray(EbgresNetwMessage *packet, int path[])
{
	int routeLength = packet->getAnalysisData(0).getRouteNodesArraySize();
	if (routeLength < MAX_ROUTE_PATH_LENGTH)
	{
		for (int i=0; i<routeLength; i++)
		{
			path[i] = packet->getAnalysisData(0).getRouteNodes(i);
		}
		
		path[routeLength] = -1;
	}
}

void Performance::recordMessageGenerated(int sourceAddress, int destinationAddress)
{
    routeList.recordMessageSent(sourceAddress, destinationAddress, simTime().dbl());
}

void Performance::postProcessPacket(int idNum, EbgresNetwMessage *pkt)
{
	printf("Post Processing packet %d\n", idNum);
	Packet *packet = (Packet*) packetList.getItemId(idNum);

	int numberOfHops = packet->getNumberOfHops();
	printf("Number of packet hops: %d\n", numberOfHops);

	//Update Packet Hop Count Stats
	if (numberOfHops<=10) successPacketHopCountStats.collect(numberOfHops);

	double latency = packet->getTimeArrived()-packet->getTimeCreated();
	routeList.recordRouteLatencyAndThroughput( packet->getSource(), packet->getDestination(), latency, packet->getTimeArrived());
	if (recordCommunicationLink)
	{
		communicationLinkVector.recordRouteLatencyAndThroughput(packet->getSource(), packet->getDestination(), latency, packet->getTimeArrived());
		int path[MAX_ROUTE_PATH_LENGTH] = {0};
		convertNodePathToArray(pkt, path);
		communicationLinkVector.recordRoute(packet->getSource(), packet->getDestination(), path);
	}
	printf("Packet latency: %.5f\n",latency);
	packetLatencyStats.collect(latency);
    if (HOP_LATENCY_ARRAY_SIZE>numberOfHops) hopLatencyStatsArray[numberOfHops].collect(latency);

	packetHopCountLatencyVector.record(latency);
	packetList.removeItemId(idNum);
	//printf("Function completed\n");
}

int Performance::calculateHopsBetweenNodes(int startNodeAddress, int endNodeAddress)
{
	int currentNodeAddress = startNodeAddress;
	int hops = 0;
	int nextHopAddress = -2;
	while ((hops<12) && (currentNodeAddress != endNodeAddress) && (nextHopAddress != -1))
	{
		Node *currentNodePtr = getNodeAddress(currentNodeAddress);
		nextHopAddress = currentNodePtr->getRouterPtr()->determineNextHop(endNodeAddress);
		//Make the next hop ;-)
		currentNodeAddress = nextHopAddress;
		hops++;
	}

	if ((hops==12) || (nextHopAddress == -1)) return -1;
	
	return hops;
}

void Performance::postProcessLostPacket(int idNum)
{
	printf("\n\nPost Processing Lost packet %d\n\n", idNum);

	Packet *lostPacket = getPacketId(idNum);

	//Determine the number of total number of hops the packet would have made
	printf("Source Node : %d\n", lostPacket->getSource());

	int currentNode = lostPacket->getCurrentNode();

	printf("Current Node : %d\n", currentNode);

	int destinationNode = lostPacket->getDestination();

	printf("Destination Node : %d\n", destinationNode);

	int hopsFromDestination = calculateHopsBetweenNodes(currentNode, destinationNode);

	printf("Hops from destination : %d\n",hopsFromDestination);

	int totalHops = lostPacket->getNumberOfHops() + hopsFromDestination;

	printf("Total hops : %d\n",totalHops);

	//Update Packet Hop Count Stats
	if (hopsFromDestination != -1) lostPacketHopCountStats.collect(totalHops);
	else lostPacketHopCountStats.collect(0);

	//Remove the packet from list
	//packetList.removeItemId(idNum);
}

void Performance::increaseNodeMessagesCreated(int id)
{
	((Node*) nodeList.getItem(id))->increaseMessagesCreated();
}

void Performance::increaseNodeMessagesPassedOn(int id)
{
	((Node*) nodeList.getItem(id))->increaseMessagesPassedOn();
}

void Performance::increaseNodeMessagesArrivedDestination(int id)
{
	((Node*) nodeList.getItem(id))->increaseMessagesArrivedDestination();
}

int Performance::getNodeMessagesCreated(int id)
{
	return ((Node*) nodeList.getItem(id))->getMessagesCreated();
}

int Performance::getNodeMessagesPassedOn(int id)
{
	return ((Node*) nodeList.getItem(id))->getMessagesPassedOn();
}

int Performance::getNodeMessagesArrivedDestination(int id)
{
	return ((Node*) nodeList.getItem(id))->getMessagesArrivedDestination();
}

void Performance::printNodeData()
{
	for (int i=0; i<nodeList.getListSize(); i++)
	{
		printf("Node %d address: %d\n",i, ((Node*) nodeList.getItem(i))->getAddress());
		printf("Messages created : %d\n",((Node*) nodeList.getItem(i))->getMessagesCreated());
		printf("Messages passed on : %d\n",((Node*) nodeList.getItem(i))->getMessagesPassedOn());
		printf("Messages arrived at destination : %d\n",((Node*) nodeList.getItem(i))->getMessagesArrivedDestination());

		printf("Messages Received %d\n",((Node*) nodeList.getItem(i))->getMessagesPassedOn()+((Node*) nodeList.getItem(i))->getMessagesArrivedDestination());
		printf("Messages Sent %d\n",((Node*) nodeList.getItem(i))->getMessagesCreated()+((Node*) nodeList.getItem(i))->getMessagesPassedOn());
		
	}
}

void Performance::printMessagesSentReceived()
{
	EV << "Messages sent : " << messagesSent << endl;
	EV << "Messages received : " << messagesReceived << endl;
	EV << "Messages lost : " << messagesLost << endl;
	EV << "Transmissions Received : " << transmissionsReceived << endl;
}

void Performance::printMessagesStartEndTime()
{
	EV << "Messages start time : " << getStartMessagesTime() << endl;
	EV << "Messages end time : " << getEndMessagesTime() << endl;
}

double Performance::calculateBitRate(double bitsTransmitted, double totalTime)
{
	return bitsTransmitted/totalTime;
}

void Performance::printBitRateDemandedHandled()
{
	EV << "Bit rate demanded : " << calculateBitRate(( (double) messagesSent)*DATA_MESSAGE_SIZE_BYTES*8 /*bits in message*/, getEndMessagesTime()-getStartMessagesTime()) << endl;
	EV << "Bit rate handled : " << calculateBitRate(( (double) messagesReceived)*DATA_MESSAGE_SIZE_BYTES*8 /*bits in message*/, getEndMessagesTime()-getStartMessagesTime()) << endl;
}

void Performance::printHopCountStatistics()
{
	ev << endl << "Look at the collection of this data again NB!!! " << endl << endl;
	EV << "Minimum Number of Hops (Packets Successfully Transmitted): " << successPacketHopCountStats.getMin() << endl;
	EV << "Maximum Number of Hops (Packets Successfully Transmitted): " << successPacketHopCountStats.getMax() << endl;
	EV << "Mean Number of Hops (Packets Successfully Transmitted): " << successPacketHopCountStats.getMean() << endl;
	EV << "Number of samples : " << successPacketHopCountStats.getCount() << endl;
	
	EV << "Minimum Number of Hops (Packets Lost): " << lostPacketHopCountStats.getMin() << endl;
	EV << "Maximum Number of Hops (Packets Lost): " << lostPacketHopCountStats.getMax() << endl;
	EV << "Mean Number of Hops (Packets Lost): " << lostPacketHopCountStats.getMean() << endl;
	EV << "Number of samples : " << lostPacketHopCountStats.getCount() << endl;
}

void Performance::printPacketLatencyStatistics()
{
	EV << "Minimum Packet Latency: " << packetLatencyStats.getMin() << endl;
	EV << "Maximum Packet Latency: " << packetLatencyStats.getMax() << endl;
	EV << "Mean Packet Latency: " << packetLatencyStats.getMean() << endl;
	EV << "Number of samples : " << packetLatencyStats.getCount() << endl;
}

void Performance::recordPacketLatencyStatistics()
{
	recordScalar("Number of samples", packetLatencyStats.getCount());
	recordScalar("Minimum Packet Latency", packetLatencyStats.getMin());
	recordScalar("Maximum Packet Latency", packetLatencyStats.getMax());
	recordScalar("Mean Packet Latency", packetLatencyStats.getMean());
	recordScalar("Standard Deviation Packet Latency", packetLatencyStats.getStddev());
}

void Performance::printHopLatencyStatsArray()
{
	for (int i=0; i<HOP_LATENCY_ARRAY_SIZE; i++)
	{
		EV << i << " Hops Minimum Packet Latency: " << hopLatencyStatsArray[i].getMin() << endl;
		EV << i << " Hops Maximum Packet Latency: " << hopLatencyStatsArray[i].getMax() << endl;
		EV << i << " Hops Mean Packet Latency: " << hopLatencyStatsArray[i].getMean() << endl;
		EV << i << " Hops Number of samples : " << hopLatencyStatsArray[i].getCount() << endl;
	}
}

void Performance::recordHopLatencyStatsArray()
{
	char message[50];
	for (int i=0; i<HOP_LATENCY_ARRAY_SIZE; i++)
	{
		sprintf(message,"%d Hops Number of samples",i);
		recordScalar(message, hopLatencyStatsArray[i].getCount());
		sprintf(message,"%d Hops Minimum Packet Latency",i);
		recordScalar(message, hopLatencyStatsArray[i].getMin());
		sprintf(message,"%d Hops Maximum Packet Latency",i);
		recordScalar(message, hopLatencyStatsArray[i].getMax());
		sprintf(message,"%d Hops Mean Packet Latency",i);
		recordScalar(message, hopLatencyStatsArray[i].getMean());
		sprintf(message,"%d Hops Standard Deviation Packet Latency",i);
		recordScalar(message, hopLatencyStatsArray[i].getStddev());
	}
}

void Performance::printAndRecordPacketHopsPercentageSuccessful()
{
	printf("In function print and record packet hops percentage successful\n");
	int lostMax = (int) lostPacketHopCountStats.getMax();
	int successMax = (int) successPacketHopCountStats.getMax();
	int upperBoundry;


	if (lostMax >= successMax) upperBoundry = lostMax;
	else upperBoundry = successMax;

	if (upperBoundry>10) upperBoundry = 10;
	
	double percentagePacketsSuccessHop[upperBoundry];

	printf("Before for loop\n");

	printf("lostMax : %d\n",lostMax);
	printf("successMax : %d\n",successMax);
	printf("Upper boundry : %d\n",upperBoundry);

	for (int i=1; i<=upperBoundry; i++)
	{
		printf("Cell : %d\n",i);
		int totalPackets = (int) successPacketHopCountStats.getCellValue(i) + (int) lostPacketHopCountStats.getCellValue(i);
		printf("totalPackets : %d\n",totalPackets);
		percentagePacketsSuccessHop[i-1] = ((double) successPacketHopCountStats.getCellValue(i))/( (double) totalPackets ) * 100;
		
		
		EV << i << " Hops : " << percentagePacketsSuccessHop[i-1] << " % successful" << endl;

		char message[100];
		printf("Before sprintf\n");
		sprintf(message,"%d Hops successful",i);
		printf("Before record scalar\n");
		recordScalar(message, percentagePacketsSuccessHop[i-1]);
		printf("End of for loop\n");
	}
}

void Performance::writeLatencyValuesToFile(void)
{
	DataFileCreator latencyValues;

	char outputFile[255];
	strcpy(outputFile, simulationOutputDirectory);
	strcat(outputFile, "/latencyValues.txt");
	latencyValues.setFilePath(outputFile);

	if (latencyValues.openFileAppend())
	{
		ev << "Latency Values Data File Opened Successfully for Appending Data" << endl;
		int totalBufferPacketsDropped = nodeList.determineTotalFullBufferPacketsDropped();
	} 
	latencyValues.closeFile();
}

void Performance::writeSuccessfulExecution()
{
	DataFileCreator successExec;
	
	char outputFile[255];
	strcpy(outputFile, simulationOutputDirectory);
	strcat(outputFile, "/successExecution.txt");
	successExec.setFilePath(outputFile);

	if (successExec.openFileAppend())
	{
		ev << "Successful Execution File Opened Successfully for Appending Data" << endl;
		successExec.writeSuccessExecutionNumber(runNumber);
	} 
	successExec.closeFile();
}

void Performance::writeNodePacketsLost()
{
	DataFileCreator nodePacketsLostFile;
	
	char outputFile[255];
	strcpy(outputFile, runOutputDirectory);
	strcat(outputFile, "/Performance/nodePacketsLost.txt");
	
	nodePacketsLostFile.setFilePath(outputFile);

	if (nodePacketsLostFile.openFileAppend())
	{
		ev << "Node Packets Lost File Opened Successfully for Appending Data" << endl;
		for (int i=0; i<nodeList.getListSize(); i++)
		{
			Node *nodePtr = nodeList.getNodePtr(i);
			nodePacketsLostFile.writeNodePacketsLostToFile(i, nodePtr->getAddress(), nodePtr->getNodeDataPtr()->getMessagesDropped());
		}
	} 
	nodePacketsLostFile.closeFile();
}

void Performance::writeNodePositionsToFile()
{
    DataFileCreator nodePositions;
    {
        std::ostringstream fileName;
        fileName << runOutputDirectory << "/Performance/nodeSetup.txt";
        nodePositions.setFilePath(fileName.str().c_str());
    }
    
    if (nodePositions.openFile())
    {
        nodePositions.writeNumberOfNodesToPositionsFile(nodeList.getListSize());
        for (int i=0; i<nodeList.getListSize(); i++)
        {
            Node *nodePtr = nodeList.getNodePtr(i);
            nodePositions.writeNodePositionsToFile(i, nodePtr->getCoordinate().getX(), nodePtr->getCoordinate().getY());
        }
    }
}

void Performance::writeCommunicationLinksOnlyToFile()
{
    DataFileCreator communicationLinkFile;
    {
        std::ostringstream fileName;
        fileName << runOutputDirectory << "/Performance/communicationsLinkVector.txt";
        communicationLinkFile.setFilePath(fileName.str().c_str());
    }
    
    if (communicationLinkFile.openFile())
    {
        communicationLinkFile.writeCommunicationLinkRoutesToFile(communicationLinkVector);
    }
}

void Performance::writeLostPacketsToFile()
{
    DataFileCreator lostPacketsFile;
    {
        std::ostringstream fileName;
        fileName << simulationOutputDirectory << "/lostPackets.txt";
        lostPacketsFile.setFilePath(fileName.str().c_str());
    }
    
    if (lostPacketsFile.openFileAppend())
    {
        int totalLostPackets = 0;
        int totalLostPacketsFullBuffer = 0;
        int totalLostPacketsMacError = 0;
        for (int i=0; i<nodeList.getListSize(); i++)
        {
            NodeData *nodeDataPtr = nodeList.getNodePtr(i)->getNodeDataPtr();
            totalLostPackets += nodeDataPtr->getMessagesDropped();
            totalLostPacketsFullBuffer += nodeDataPtr->getMessagesDroppedFullBuffer();
            totalLostPacketsMacError += nodeDataPtr->getMessagesDroppedMacError();
        }
        std::ostringstream outputString;
        outputString << "totalLostPackets," << totalLostPackets << ",totalLostPacketsMacError," << totalLostPacketsMacError << ",totalLostPacketsFullBuffer," << totalLostPacketsFullBuffer << "\n";
        lostPacketsFile.writeStringToFile(outputString.str());
    }
}

void Performance::writeMostUsedRouteToFile()
{
    DataFileCreator mostUsedRouteFile;
    {
        std::ostringstream fileName;
        fileName << simulationOutputDirectory << "/mostUsedRoute.txt";
        mostUsedRouteFile.setFilePath(fileName.str().c_str());
    }
    
    if (mostUsedRouteFile.openFileAppend())
    {
        int mostUsedCommunicationLink = communicationLinkVector.findMostUsedCommunicationLink();
        int mostUsedRoute = communicationLinkVector.getCommunicationLink(mostUsedCommunicationLink).getRouteVector().findMostUsedRoute();
        
        PacketRoute packetRoutePtr = communicationLinkVector.getCommunicationLink(mostUsedCommunicationLink).getRouteVector().getRoute(mostUsedRoute);
        int routeLength = packetRoutePtr.getRouteLength();
        std::ostringstream outputString;
        outputString.precision(4);
        for (int i=0; i<routeLength; i++)
        {
            int nodeAddress = packetRoutePtr.getRouteArray()[i];
            Node *nodePtr = NULL;
            int index = nodeList.findNode(nodeAddress);
            int packetsDroppedMacError = 0;
            int packetsDroppedFullBuffer = 0;
            int dataMessagesSent = 0;
            double packetsDroppedMacErrorPer = 0;
            int longRetries = 0;
            int shortRetries = 0;
            double longRetriesPer = 0;
            double shortRetriesPer = 0;
            if (index != -1) 
            {
                nodePtr = nodeList.getNodePtr(index);
                NodeData *nodeDataPtr = nodePtr->getNodeDataPtr();
                packetsDroppedMacError = nodeDataPtr->getMessagesDroppedMacError();
                packetsDroppedFullBuffer = nodeDataPtr->getMessagesDroppedFullBuffer();
                dataMessagesSent = nodeDataPtr->getDataMessagesSent();
                if (dataMessagesSent != 0) packetsDroppedMacErrorPer = ((double) packetsDroppedMacError)/((double) dataMessagesSent);
                longRetries = *(nodePtr->getLongRetriesPtr());
                shortRetries = *(nodePtr->getShortRetriesPtr());
                if (dataMessagesSent != 0) longRetriesPer = ((double) longRetries)/((double) dataMessagesSent);
                if (dataMessagesSent != 0) shortRetriesPer = ((double) shortRetries)/((double) dataMessagesSent);
            }
            if (i==0) outputString << "hop" << i << "," ;
            else outputString << ",hop" << i << "," ;
            outputString << "address," << nodeAddress << ",dataMessages," << dataMessagesSent << ",macError," << packetsDroppedMacError << "," << packetsDroppedMacErrorPer << ",packetsDroppedFullBuffer," << packetsDroppedFullBuffer << ",longRetries," << longRetries << "," << longRetriesPer << ",shortRetries," << shortRetries << "," << shortRetriesPer;
        }
        outputString << "\n";
        mostUsedRouteFile.writeStringToFile(outputString.str());
    }
}

void Performance::finish()
{
	printf("PERFORMANCE FINISH STARTED\n");
	setTotalNodes(nodeList.getListSize());

	//Do a few calculations
	if (getEndMessagesTime() == -1) setEndMessagesTime(simTime().dbl());

	//nodeList.calculateAndSetConnectivityForAllNodes();
	//printf("Before getNeighbourTablePtr\n");
	//nodeList.getNodePtr(0)->getRouterPtr()->getNeighbourTablePtr();
	printNodeData();
	printf("AFTER PRINT NODE DATA\n");
	printf("After print NetworkNodeHops\n");
	if (pMessagesSentReceived) printMessagesSentReceived();
	if (pMessagesStartEndTime) printMessagesStartEndTime();
	if (pBitRateDemandedHandled) printBitRateDemandedHandled();

	printf("After printing statistics\n");

	//ev << "Total Network Connectivity : " << nodeList.calculateNetworkConnectivity() << endl;
	gatherNodeStatistics();
	printNodePacketsSuccess();
	recordNodePacketSuccessScalars();

	printHopCountStatistics();

	//printAndRecordPacketHopsPercentageSuccessful();

	printPacketLatencyStatistics();
	recordPacketLatencyStatistics();

	printHopLatencyStatsArray();
	recordHopLatencyStatsArray();
	
	recordScalar("Transmissions Received", transmissionsReceived);
	recordScalar("Input BitRate",getInputBitRate());
	recordScalar("Bitrate Demanded",calculateBitRate(( (double) messagesSent)*DATA_MESSAGE_SIZE_BYTES*8 /*bits in message*/, getEndMessagesTime()-getStartMessagesTime()));
	recordScalar("Bitrate Handled",calculateBitRate(( (double) messagesReceived)*DATA_MESSAGE_SIZE_BYTES*8 /*bits in message*/, getEndMessagesTime()-getStartMessagesTime()));

	ev << "Printing Communication Link Vector : \n";

	{
		DataFileCreator simulationTimeOut_Output;
		char outputFile[255];
		strcpy(outputFile, runOutputDirectory);
		strcat(outputFile, "/timeOutData.txt");
		int totalNodeClusterTableTimeOuts = 0;
		for (int i=0; i<nodeList.getListSize(); i++)
		{
			Node *nodePtr = nodeList.getNodePtr(i);
		}
		simulationTimeOut_Output.setFilePath(outputFile);
		simulationTimeOut_Output.openFile();
		simulationTimeOut_Output.writeTotalNodeClusterTimeOuts(totalNodeClusterTableTimeOuts);
		simulationTimeOut_Output.closeFile();
	}
	
	SystemController systemController;
	
	systemController.setBaseDirectory(runOutputDirectory);
	systemController.createDirectory("/DisplayGraph/");

	GraphFileCreator graphFileCreator;

	char graphFile[255];
	strcpy(graphFile, runOutputDirectory);
	strcat(graphFile, "/DisplayGraph/graph.dot");
	graphFileCreator.setFilePath(graphFile);
	if (graphFileCreator.openFile()) 
	{
		ev << "File opened successfully" << endl;
		graphFileCreator.setNodeListPtr(&nodeList);
		graphFileCreator.closeFile();
	}

	{
		DataFileCreator dataFileCreator;

		char outputFile[255];
		strcpy(outputFile, simulationOutputDirectory);
		strcat(outputFile, "/routeStats.txt");
		dataFileCreator.setFilePath(outputFile);

		if (dataFileCreator.openFileAppend())
		{
			ev << "Data File Opened Successfully for Appending Data" << endl;
			dataFileCreator.writeRouteListToFile(routeList);
		} 
		dataFileCreator.closeFile();
	}
	
	{
		DataFileCreator networkSetupTest;

		char outputFile[255];
		strcpy(outputFile, simulationOutputDirectory);
		strcat(outputFile, "/networkSetupTest.txt");
		networkSetupTest.setFilePath(outputFile);

		if (networkSetupTest.openFileAppend())
		{
			ev << "Network Setup Test Data File Opened Successfully for Appending Data" << endl;
			int clusterSizesSum = 0;
            int numberOfNodes = nodeList.getListSize();
            for (int i=0; i<numberOfNodes; i++)
            {
                Node *nodePtr = nodeList.getNodePtr(i);
            }
		} 
		networkSetupTest.closeFile();
	}
	
	{
		int totalControlOverhead = 0;
		int totalControlOverheadWithoutToken = 0;
		int totalHelloMessageControlOverhead = 0;
		int totalClusterTableMessageControlOverhead = 0; 
		int totalTokenMessageControlOverhead = 0;
		
		//Calculate Total Overhead
		{
			DataFileCreator totalControlOverheadFile;
			
			char outputFile[255];
			strcpy(outputFile, runOutputDirectory);
			strcat(outputFile, "/Performance/controlOverheadFile.txt");
			totalControlOverheadFile.setFilePath(outputFile);
			
			if (totalControlOverheadFile.openFile())
			{
				for (int i=0; i<nodeList.getListSize(); i++)
				{
					NodeData *nodeDataPtr = nodeList.getNodePtr(i)->getNodeDataPtr();
					totalControlOverhead += nodeDataPtr->getBytesControlData();
					totalControlOverheadWithoutToken += nodeDataPtr->getBytesControlDataWithoutToken();
					totalHelloMessageControlOverhead += nodeDataPtr->getBytesHelloControlData();
					totalClusterTableMessageControlOverhead += nodeDataPtr->getBytesClusterTableMessageControlData();
					totalTokenMessageControlOverhead += nodeDataPtr->getBytesTokenControlData();
				}
				
				totalControlOverheadFile.writeTotalControlOverheadToFile(totalControlOverhead, totalControlOverheadWithoutToken, totalHelloMessageControlOverhead, totalClusterTableMessageControlOverhead, totalTokenMessageControlOverhead, nodeList.getListSize());
			}
			totalControlOverheadFile.closeFile();
		}
		
		//print Control Overhead values to file
		{
			DataFileCreator controlOverheadData;

			char outputFile[255];
			strcpy(outputFile, simulationOutputDirectory);
			strcat(outputFile, "/controlOverheadData.txt");
			controlOverheadData.setFilePath(outputFile);

			if (controlOverheadData.openFileAppend())
			{
				ev << "Control Overhead Data File Opened Successfully for Appending Data" << endl;
			} 
			controlOverheadData.closeFile();
		}
	}
	
	printf("\n\n Totals: \n\n");
	printf("Packets sent %d\n",messagesSent);
	printf("Packets received %d\n",messagesReceived);
    
	double reliability = ((double) messagesReceived)/((double) messagesSent);
}


