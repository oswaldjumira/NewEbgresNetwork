/***************************************************************************
 * file:        CommunicationLinkVector.h
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
 ***************************************************************************/

#ifndef COMMUNICATION_LINK_VECTOR_H
#define COMMUNICATION_LINK_VECTOR_H

#include"ItemVector.h"
#include"CommunicationLink.h"

class CommunicationLinkVector : public ItemVector
{
	protected:
		
	public:
		CommunicationLinkVector()
		{
		}
		
		~CommunicationLinkVector();
		
		void addCommunicationLink(CommunicationLink communicationLink);

		CommunicationLink& getCommunicationLink(int index);

		void removeCommunicationLink(int index);
		
		void recordRouteLatencyAndThroughput(int sourceAddress, int destinationAddress, double latency, double timeArrived);
		
		void recordRoute(int sourceAddress, int destinationAddress, int path[]);
		
		int findCommunicationLink(int sAddress, int dAddress);
		
		int findMostUsedRoute(int sourceAddress, int destinationAddress);
        
        int findMostUsedCommunicationLink();
		
		void getMiddleRouteAddresses(int sourceAddress, int destinationAddress, int mostUsedRoute, int &linkNode1, int &linkNode2);
		
		void resetValuesForNewTimeInterval();

	friend std::ostream &operator<<(std::ostream& stream, CommunicationLinkVector &cLinkVector);
};

#endif


