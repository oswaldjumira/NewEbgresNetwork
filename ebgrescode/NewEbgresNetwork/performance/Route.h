/***************************************************************************
 * file:        Route.h
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
 * description: The route object records statistics of a single route.
 ***************************************************************************/

#ifndef ROUTE_H
#define ROUTE_H

#include "Item.h"
#include "LinkedList.h"

class Route : public Item
{
	protected:
		int sourceAddress;
		int destinationAddress;
        int numberOfMessagesSent;
        double firstMessageSent;
        double lastMessageSent;
		int numberOfObservations;
		double meanLatency;
		double meanThroughput;
		double firstArrival;
		double lastArrival;
        
        double meanDataRateDemanded;

	public:
		Route(int sAddress, int dAddress)
		{
			setSourceAddress(sAddress);
			setDestinationAddress(dAddress);
			meanLatency = 0;
			meanThroughput = 0;
            firstArrival = 0;
            lastArrival = 0;
			setNumberOfObservations(0);
            
            numberOfMessagesSent = 0;
            firstMessageSent = 0;
            lastMessageSent = 0;
            meanDataRateDemanded = 0;
		}

		Route(const Route& route) 
		{ 
			sourceAddress = route.sourceAddress;
			destinationAddress = route.destinationAddress;
			meanLatency = 0;
            meanThroughput = 0;
			firstArrival = 0;
			lastArrival = 0;
			setNumberOfObservations(0);
            
            numberOfMessagesSent = 0;
            firstMessageSent = 0;
            lastMessageSent = 0;
            meanDataRateDemanded = 0;
		}

		void setSourceAddress(int sAddress) { sourceAddress = sAddress; }
		int getSourceAddress() { return sourceAddress; }

		void setDestinationAddress(int dAddress) { destinationAddress = dAddress; }
		int getDestinationAddress() { return destinationAddress; }

		void setNumberOfObservations(int nOfObservations) { numberOfObservations = nOfObservations; }
		int getNumberOfObservations() { return numberOfObservations; }
        
        void setNumberOfMessagesSent(int nOfMessagesSent)
        {
            numberOfMessagesSent = nOfMessagesSent;
        }
        
        int getNumberOfMessagesSent()
        {
            return numberOfMessagesSent;
        }

		void recordLatencyAndThroughput(double latency, double arrivalTime);
        void recordMessageSent(double sentMessageTime);
        
		double getMeanLatency() { return meanLatency; }
		double getMeanThroughput() { return meanThroughput; }
        double getMeanDataRateDemanded() { return meanDataRateDemanded; }
};

class RouteList : public LinkedList
{
	protected:

	public:
		RouteList() {}

		void addRoute(Route route)
		{
			addItem(new Route(route));
		}

		Route &getRoute(int index)
		{
			return *( (Route*) getItem(index) );
		}

		int findRoute(int sourceAddress, int destinationAddress)
		{
			for (int i=0; i<getListSize(); i++)
			{
				Route &route = getRoute(i);
				if ( (route.getSourceAddress() == sourceAddress) && (route.getDestinationAddress() == destinationAddress) )
				{
					ev << "Returning : " << i << endl;
					return i;
				}
			}
			return -1;
		}
        
        void recordMessageSent(int sourceAddress, int destinationAddress, double sentMessageTime)
        {
            int index = findRoute(sourceAddress, destinationAddress);
            if (index != -1) getRoute(index).recordMessageSent(sentMessageTime);
            else 
            {
                Route route(sourceAddress, destinationAddress);
                addRoute(route);
                index = findRoute(sourceAddress, destinationAddress);
                if (index != -1) getRoute(index).recordMessageSent(sentMessageTime);
            }
        }
        
		void recordRouteLatencyAndThroughput(int sourceAddress, int destinationAddress, double latency, double arrivalTime)
		{
			int index = findRoute(sourceAddress, destinationAddress);
			if (index != -1) getRoute(index).recordLatencyAndThroughput(latency, arrivalTime);
			else 
			{
				Route route(sourceAddress, destinationAddress);
				addRoute(route);
				index = findRoute(sourceAddress, destinationAddress);
				if (index != -1) getRoute(index).recordLatencyAndThroughput(latency, arrivalTime);
			}
		}
};

#endif
