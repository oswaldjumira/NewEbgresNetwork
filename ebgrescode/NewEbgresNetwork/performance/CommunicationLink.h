/***************************************************************************
 * file:        CommunicationLink.h
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
 * description: A communication link object records different routes for a source, destination pair.
                The object also records statistics etc.
 ***************************************************************************/

#ifndef COMMUNICATION_LINK_H
#define COMMUNICATION_LINK_H

#include"Configuration.h"
#include"RouteVector.h"

class CommunicationLink : public Item
{
	protected:
		int sourceAddress;
		int destinationAddress;
		int numberOfObservations;
		double meanLatency;
		double meanThroughput;
		double firstArrival;
		double lastArrival;
		
		RouteVector routeVector;

	public:
		CommunicationLink(int sAddress, int dAddress)
		{
			setSourceAddress(sAddress);
			setDestinationAddress(dAddress);
			meanLatency = 0;
			meanThroughput = 0;
            firstArrival = 0;
            lastArrival = 0;
			setNumberOfObservations(0);
		}

		CommunicationLink(const CommunicationLink& comLink) 
		{ 
			sourceAddress = comLink.sourceAddress;
			destinationAddress = comLink.destinationAddress;
			meanLatency = 0;
            meanThroughput = 0;
			firstArrival = 0;
			lastArrival = 0;
			setNumberOfObservations(0);
		}

		void setSourceAddress(int sAddress) { sourceAddress = sAddress; }
		int getSourceAddress() { return sourceAddress; }

		void setDestinationAddress(int dAddress) { destinationAddress = dAddress; }
		int getDestinationAddress() { return destinationAddress; }

		void setNumberOfObservations(int nOfObservations) { numberOfObservations = nOfObservations; }
		int getNumberOfObservations() { return numberOfObservations; }

		void recordLatencyAndThroughput(double latency, double arrivalTime);
		double getMeanLatency() { return meanLatency; }
		double getMeanThroughput() { return meanThroughput; }
		
		void recordRoute(int path[]);
		
		RouteVector& getRouteVector()
		{
			return routeVector;
		}
		
		void resetValuesForNewTimeInterval();
		
	friend std::ostream &operator<<(std::ostream& stream, CommunicationLink &cLink);
};


#endif

