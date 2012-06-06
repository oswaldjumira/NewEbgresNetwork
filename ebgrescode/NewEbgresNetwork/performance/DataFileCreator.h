/***************************************************************************
 * file:        DataFileCreator.h
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
 * description: - The datafilecreator objects writes output data to the simulation output folder.
 *
 ***************************************************************************/

#ifndef DATA_FILE_CREATOR_H
#define DATA_FILE_CREATOR_H

#include "GraphFileCreator.h"
#include "Route.h"
#include "NodeData.h"

#include "CommunicationLinkVector.h"
#include "LinkBreak.h"

#include "omnetpp.h"

class DataFileCreator : public FileCreator
{
	protected:

	public:
		DataFileCreator(){};

		void writeRouteListToFile(RouteList &routeList)
		{
			outputFileStream << "Simulation" << endl;
			for (int i=0; i<routeList.getListSize(); i++)
			{
				outputFileStream << "route," << i << endl;
				outputFileStream <<  "SourceAddress" << "," << routeList.getRoute(i).getSourceAddress() << endl;
				outputFileStream <<  "DestinationAddress" << "," << routeList.getRoute(i).getDestinationAddress() << endl;
				outputFileStream <<  "MeanLatency" << "," << routeList.getRoute(i).getMeanLatency() << endl;
				outputFileStream <<  "MeanThroughput" << "," << routeList.getRoute(i).getMeanThroughput() << endl;
                outputFileStream << "Observations" << "," << routeList.getRoute(i).getNumberOfObservations() << endl;
                outputFileStream <<  "MeanDataRateDemanded" << "," << routeList.getRoute(i).getMeanDataRateDemanded() << endl;
                outputFileStream << "MessagesSent" << "," << routeList.getRoute(i).getNumberOfMessagesSent() << endl;
			}
			outputFileStream << "EndSimulation" << endl;
		}
		
		void writePacketRoute(char route[])
        {
            outputFileStream << route << endl;
        }
		
		void writeTotalNodeClusterTimeOuts(int totalNodeClusterTableTimeOuts)
		{
			outputFileStream << "Total Node ClusterTable TimeOuts :" << totalNodeClusterTableTimeOuts << "\n";
		}
		
		void writeConnectivity(double time, double connectivity)
		{
			outputFileStream << time << "," << connectivity << "\n";
		}
		
		void writeTestNetworkData(int numberOfClusters, int numberOfForwarderNodes, int numberOfNodes, int clusterSizesSum, double lastClusterHeadElectionTime, double endOfSimulationTime)
		{
			//outputFileStream << numberOfClusters << "," << numberOfForwarderNodes << "," << numberOfNodes << "," << lastClusterHeadElectionTime << "," << endOfSimulationTime << "\n";
			outputFileStream << numberOfClusters << " & " << ( ( (double) clusterSizesSum) / ( (double) numberOfClusters) ) << " & " << numberOfForwarderNodes << " & " << ( ( (double) numberOfForwarderNodes) / ( (double) numberOfNodes) ) 
			<< " & " << lastClusterHeadElectionTime << "\n";
		}
		
		void writeNodeDataToFile(NodeData &nodeData)
		{
			outputFileStream << nodeData;
		}
		
		
		void writeTotalControlOverheadToFile(int totalControlOverhead, int totalControlOverheadWithoutToken, int totalHelloMessageControlOverhead, int totalClusterTableMessageControlOverhead, int totalTokenMessageControlOverhead, int numberOfNodes)
		{
			outputFileStream << "Total Control Overhead : " << totalControlOverhead << "\n";
			outputFileStream << "Total Control Overhead (without token): " << totalControlOverheadWithoutToken << "\n";
			outputFileStream << "Total Hello Message Control Overhead : " << totalHelloMessageControlOverhead << "\n";
			outputFileStream << "Total Cluster Table Message Control Overhead : " << totalClusterTableMessageControlOverhead << "\n";
			outputFileStream << "Total Token Message Control Overhead : " << totalTokenMessageControlOverhead << "\n";
			
			double totalControlOverheadPerNode = ((double) totalControlOverhead)/((double) numberOfNodes);
			double totalControlOverheadWithoutTokenPerNode = ((double) totalControlOverheadWithoutToken)/((double) numberOfNodes);
			double totalHelloMessageControlOverheadPerNode = ((double) totalHelloMessageControlOverhead)/((double) numberOfNodes);
			double totalClusterTableMessageControlOverheadPerNode = ((double) totalClusterTableMessageControlOverhead)/((double) numberOfNodes);
			double totalTokenMessageControlOverheadPerNode = ((double) totalTokenMessageControlOverhead)/((double) numberOfNodes);
			
			outputFileStream << "\n";
			
			outputFileStream << "Total Control Overhead Per Node : " << totalControlOverheadPerNode << "\n";
			outputFileStream << "Total Control Overhead Per Node (without token): " << totalControlOverheadWithoutTokenPerNode << "\n";
			outputFileStream << "Total Hello Message Control Overhead Per Node : " << totalHelloMessageControlOverheadPerNode << "\n";
			outputFileStream << "Total Cluster Table Message Control Overhead Per Node : " << totalClusterTableMessageControlOverheadPerNode << "\n";
			outputFileStream << "Total Token Message Control Overhead Per Node : " << totalTokenMessageControlOverheadPerNode << "\n";
		}
		
		void writeControlOverheadData(double simulationEndTime, int numberOfClusters, int numberOfForwarderNodes, int numberOfNodes, int totalControlOverhead, int totalControlOverheadWithoutToken, int totalHelloMessageControlOverhead, int totalClusterTableMessageControlOverhead, int totalTokenMessageControlOverhead)
		{
			double totalControlOverheadPerNode = ((double) totalControlOverhead)/((double) numberOfNodes);
			double totalControlOverheadWithoutTokenPerNode = ((double) totalControlOverheadWithoutToken)/((double) numberOfNodes);
			double totalHelloMessageControlOverheadPerNode = ((double) totalHelloMessageControlOverhead)/((double) numberOfNodes);
			double totalClusterTableMessageControlOverheadPerNode = ((double) totalClusterTableMessageControlOverhead)/((double) numberOfNodes);
			double totalTokenMessageControlOverheadPerNode = ((double) totalTokenMessageControlOverhead)/((double) numberOfNodes);
            
            double totalControlOverheadPerNodePerSecond = totalControlOverheadPerNode/simulationEndTime;
            double totalControlOverheadWithoutTokenPerNodePerSecond = totalControlOverheadWithoutTokenPerNode/simulationEndTime;
            double totalHelloMessageControlOverheadPerNodePerSecond = totalHelloMessageControlOverheadPerNode/simulationEndTime;
            double totalClusterTableMessageControlOverheadPerNodePerSecond = totalClusterTableMessageControlOverheadPerNode/simulationEndTime;
            double totalTokenMessageControlOverheadPerNodePerSecond = totalTokenMessageControlOverheadPerNode/simulationEndTime;
			
			outputFileStream << numberOfNodes << "," << numberOfClusters << "," << numberOfForwarderNodes << "," << totalControlOverheadPerNodePerSecond << "," << totalControlOverheadWithoutTokenPerNodePerSecond << "," << totalHelloMessageControlOverheadPerNodePerSecond << "," << totalClusterTableMessageControlOverheadPerNodePerSecond << "," << totalTokenMessageControlOverheadPerNodePerSecond << "\n";
		}
		
		void writeLatencyData(bool append, bool tokenPriority, cDoubleHistogram &packetLatencyStats, cDoubleHistogram hopLatencyStats[], int totalBufferPacketsDropped)
		{
			if (!append)
			{
				outputFileStream << "//Token Priority, Packet Latency Mean, Packet Latency Min, Packet Latency Max, Packet Latency StdDev, Packet Latency Samples,";
				outputFileStream << " Hops, Hops Latency Mean, Hops Latency Min, Hops Latency Max, Hops Latency StdDev, Hops Latency Samples, ... , total buffer messages dropped\n";
			}
			outputFileStream << tokenPriority << "," << packetLatencyStats.getMean() << "," << packetLatencyStats.getMin() << "," << packetLatencyStats.getMax() << "," << packetLatencyStats.getStddev() << "," << packetLatencyStats.getCount();
			
			outputFileStream << ",start";
			for(int i=0; i<10; i++)
			{
				if (hopLatencyStats[i].getCount()>0)
				{
					outputFileStream << "," << i << "," << hopLatencyStats[i].getMean() << "," << hopLatencyStats[i].getMin() << "," << hopLatencyStats[i].getMax() << "," << hopLatencyStats[i].getStddev() << "," << hopLatencyStats[i].getCount();
				}
			}
			outputFileStream << ",stop,";
			
			outputFileStream << totalBufferPacketsDropped << "\n";
		}
		
		void writeSuccessExecutionNumber(int runNumber)
		{
			outputFileStream << "Run " << runNumber << " has been successfully executed!!\n";
		}
		
		void writeSimulationTime(double simulationTime)
		{
			outputFileStream << "Simulation Time : " << simulationTime << "\n";
		}
		
		void writeCommunicationLinkVectorTimeInterval(double simulationTime, CommunicationLinkVector &communicationLinkVector)
		{
			for (int i = 0; i<communicationLinkVector.getSize(); i++)
			{
				RouteVector &rVector = communicationLinkVector.getCommunicationLink(i).getRouteVector();
				for (int j = 0; j<rVector.getSize(); j++)
				{
					outputFileStream << simulationTime << "," << i << "," << j << "," << rVector.getRoute(j).getPacketsReceivedInTimeInterval() << "\n";
				}
			}
		}
		
		void writeCommunicationLinkRoutesToFile(CommunicationLinkVector &communicationLinkVector)
		{
			outputFileStream << "CommunicationLinkRoutes\n";
			for (int i = 0; i<communicationLinkVector.getSize(); i++)
			{
				RouteVector &rVector = communicationLinkVector.getCommunicationLink(i).getRouteVector();
				for (int j = 0; j<rVector.getSize(); j++)
				{
					outputFileStream << "CommunicationLink," << i << ",Route," << j << ",RouteAddresses";
					PacketRoute &pRoute = rVector.getRoute(j);
					for (int k = 0; k<pRoute.getRouteLength(); k++)
					{
						outputFileStream << "," << pRoute.getRouteArray()[k];
					}
					outputFileStream << "\n";
				}
			}
		}
		
		void writeBrokenLinkToFile(LinkBreak &linkBreak)
		{
			outputFileStream << "LinkBroken\n";
			outputFileStream << "LinkNode1," << linkBreak.getSourceAddress() << "\n";
			outputFileStream << "LinkNode2," << linkBreak.getDestinationAddress() << "\n";
		}
		
		void writeNodePacketsLostToFile(int index, int address, int messagesDropped)
		{
			outputFileStream << "Node " << index << " (Address " << address << ") Messages Dropped : " << messagesDropped << "\n";
		}
		
		void writeQueueTimesToFile(QueueSetList queueSetList)
		{
			outputFileStream << queueSetList;
		}
        
        void writeTokenDebug(int sequenceNumber, int destinationAddress, double simulationTime)
        {
            outputFileStream << "Token " << sequenceNumber << " Passing Token to " << destinationAddress << " at " << simulationTime << "\n";
        }
        
        void writeTokenDebugTimeOut(int sequenceNumber, int destinationAddress, double simulationTime)
        {
            outputFileStream << "Token " << sequenceNumber << " sent to " << destinationAddress << " timed-out at " << simulationTime << "\n";
        }
        
        void writeStringToFile(std::string stringie)
        {
            outputFileStream << stringie;
        }
        
        void writeNumberOfNodesToPositionsFile(int numberOfNodes)
        {
            outputFileStream << "chgrp.playgroundSizeX = 600\n";
            outputFileStream << "chgrp.playgroundSizeY = 600\n\n";
            outputFileStream << "chgrp.numHosts = " << numberOfNodes << "\n";
            outputFileStream << "chgrp.host[*].numHosts = " << numberOfNodes << "\n\n";
        }
        
        void writeNodePositionsToFile(int nodeNumber, int xPos, int yPos)
        {
            outputFileStream << "chgrp.host[" << nodeNumber << "].mobility.x=" << xPos << "\n";
            outputFileStream << "chgrp.host[" << nodeNumber << "].mobility.y=" << yPos << "\n";
        }
};

#endif
