/***************************************************************************
 * file:        NodeData.h
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
 * description: The nodeData object is used by nodes to record individual node statitistics.
 *
 ***************************************************************************/

#ifndef NODE_DATA_H
#define NODE_DATA_H

#include<iostream>

enum MESSAGE_DROP_TYPE
{
	MAC_ERROR,
	UNABLE_TO_ROUTE,
	FULL_BUFFER,
	NO_CLUSTER_TRANSMISSION_HANDLER
};

class NodeData
{	
	protected:
		long bytesControlData;
		long bytesControlDataWithoutToken;
		long bytesHelloControlData;
		long bytesClusterTableMessageControlData;
		long bytesTokenControlData;
        
        int dataMessagesSent;
		
		int messagesDropped;
		int messagesDroppedMacError;
		int messagesDroppedUnableToRoute;
		int messagesDroppedFullBuffer;
		int messagesDroppedNoClusterTransmissionHandler;
		
		int totalClusterTableTimeOuts;
		
		int tokenPacketsSent;
		int tokenPacketTimeOuts;
        
        double averageClusterCycleTime;
        double previousSimulationTime;
        int clusterCycleTimeSamples;

	public:
		NodeData()
		{
			bytesControlData = 0;
			bytesControlDataWithoutToken = 0;
			bytesHelloControlData = 0;
			bytesClusterTableMessageControlData = 0;
			bytesTokenControlData = 0;
            
            dataMessagesSent = 0;
			
			messagesDropped = 0;
			messagesDroppedMacError = 0;
			messagesDroppedUnableToRoute = 0;
			messagesDroppedFullBuffer = 0;
			messagesDroppedNoClusterTransmissionHandler = 0;
			
			totalClusterTableTimeOuts = 0;
			
			tokenPacketsSent = 0;
			tokenPacketTimeOuts = 0;
            
            averageClusterCycleTime = 0;
            previousSimulationTime = 0;
            clusterCycleTimeSamples = -1;
		}
        
        

		void increaseMessagesDropped(MESSAGE_DROP_TYPE type)
		{
			messagesDropped++;
			switch(type)
			{
				case MAC_ERROR:
					messagesDroppedMacError++;
					break;
				case UNABLE_TO_ROUTE:
					messagesDroppedUnableToRoute++;
					break;
				case FULL_BUFFER:
					messagesDroppedFullBuffer++;
					break;
				case NO_CLUSTER_TRANSMISSION_HANDLER:
					messagesDroppedNoClusterTransmissionHandler++;
					break;
				default:
				break;
			}
		}
        
        void increaseDataMessagesSent()
        {
            dataMessagesSent++;
        }
		
		int getTotalClusterTableTimeOuts()
		{
			return totalClusterTableTimeOuts;
		}
		
		void setTotalClusterTableTimeOuts(int tClusterTableTimeOuts)
		{
			totalClusterTableTimeOuts = tClusterTableTimeOuts;
		}
		
		void increaseControlData(int controlDataType, int bytes)
		{
			switch(controlDataType)
			{
				case 0 : //Hello Message
				{
					bytesHelloControlData += bytes;
					bytesControlDataWithoutToken += bytes;
					break;
				}
				case 1 : //Cluster Table Message
				{
					bytesClusterTableMessageControlData += bytes;
					bytesControlDataWithoutToken += bytes;
					break;
				}
				case 2 : //Token Message
				{
					bytesTokenControlData += bytes;
					break;
				}
				default:
				{
					std::cout << "Unknown Control Data Type";
					break;
				}
			}
			bytesControlData += bytes;
		}
        
        int getDataMessagesSent()
        {
            return dataMessagesSent;
        }
		
		int getMessagesDropped()
		{
			return messagesDropped;
		}
        
        int getMessagesDroppedMacError()
        {
            return messagesDroppedMacError;
        }
		
		int getMessagesDroppedUnableToRoute()
		{
			return messagesDroppedUnableToRoute;
		}
		
		int getMessagesDroppedFullBuffer()
		{
			return messagesDroppedFullBuffer;
		}
		
		int getMessagesDroppedNoClusterTransmissionHandler()
		{
			return messagesDroppedNoClusterTransmissionHandler;
		}
		
		int getBytesControlData()
		{
			return bytesControlData;
		}
		
		int getBytesControlDataWithoutToken()
		{
			return bytesControlDataWithoutToken;
		}
		
		int getBytesHelloControlData()
		{
			return bytesHelloControlData;
		}
		
		int getBytesClusterTableMessageControlData()
		{
			return bytesClusterTableMessageControlData;
		}
		
		int getBytesTokenControlData()
		{
			return bytesTokenControlData;
		}
		
		void increaseTokenPacketsSent()
		{
			tokenPacketsSent++;
		}
		
		void increaseTokenPacketTimeOuts()
		{
			tokenPacketTimeOuts++;
		}
		
		int getTokenPacketsSent()
		{
			return tokenPacketsSent;
		}
		
		int getTokenPacketTimeOuts()
		{
			return tokenPacketTimeOuts;
		}
        
        void recordStartOfCycle(double simulationTime)
        {
            if (clusterCycleTimeSamples == -1)
            {
                previousSimulationTime = simulationTime;
            }
            else
            {
                averageClusterCycleTime = ((clusterCycleTimeSamples*averageClusterCycleTime) + (simulationTime - previousSimulationTime))/(clusterCycleTimeSamples+1);
                previousSimulationTime = simulationTime;
            }
            clusterCycleTimeSamples++;
        }
        
        double getAverageClusterCycleTime()
        {
            return averageClusterCycleTime;
        }
        
        int getClusterCycleTimeSamples()
        {
            return clusterCycleTimeSamples;
        }
		
		friend std::ostream &operator<<(std::ostream& stream, NodeData &nodeDataObject);
};

#endif
