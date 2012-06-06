/***************************************************************************
 * file:        CommunicationLinkVector.cc
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
 * description: The communication link vector stores communication link objects.
 ***************************************************************************/

#include"CommunicationLinkVector.h"

std::ostream &operator<<(std::ostream& stream, CommunicationLinkVector &cLinkVector)
{
	stream << "\n";
	stream << "Printing Communication Link List" << "\n";
	stream << "List size : " << cLinkVector.getSize() << "\n";
	for (int i=0; i<cLinkVector.getSize(); i++) stream << i << cLinkVector.getCommunicationLink(i);
	stream << "\n";
	return stream;
}

void CommunicationLinkVector::addCommunicationLink(CommunicationLink communicationLink)
{
	CommunicationLink *communicationLinkPtr = new CommunicationLink(communicationLink);
	itemVec.push_back(communicationLinkPtr);
}

CommunicationLink& CommunicationLinkVector::getCommunicationLink(int index)
{
	CommunicationLink *communicationLinkPtr = dynamic_cast<CommunicationLink*>(itemVec[index]);
	return *(communicationLinkPtr);
}

void CommunicationLinkVector::removeCommunicationLink(int index)
{
	removeItem(index);
}

int CommunicationLinkVector::findCommunicationLink(int sAddress, int dAddress)
{
	for (int i=0; i<getSize(); i++)
	{
		CommunicationLink cLink = getCommunicationLink(i);
		if ((sAddress == cLink.getSourceAddress()) && (dAddress == cLink.getDestinationAddress()))
		{
			return i;
		}
	}
	return -1;
}

void CommunicationLinkVector::recordRouteLatencyAndThroughput(int sourceAddress, int destinationAddress, double latency, double timeArrived)
{
	int index = findCommunicationLink(sourceAddress,destinationAddress);
	if (index == -1)
	{
		CommunicationLink cLink = CommunicationLink(sourceAddress, destinationAddress);
		addCommunicationLink(cLink);
		index = findCommunicationLink(sourceAddress,destinationAddress);
	}
	
	if (index != -1)
	{
		getCommunicationLink(index).recordLatencyAndThroughput(latency, timeArrived);
	}
}

void CommunicationLinkVector::recordRoute(int sourceAddress, int destinationAddress, int path[])
{
	int index = findCommunicationLink(sourceAddress, destinationAddress);
	if (index != -1)
	{
		CommunicationLink &cLink = getCommunicationLink(index);
		cLink.recordRoute(path);
	}
}

int CommunicationLinkVector::findMostUsedRoute(int sourceAddress, int destinationAddress)
{
	int cLinkIndex = findCommunicationLink(sourceAddress, destinationAddress);
	int routeIndex = -1;
	if (-1 != cLinkIndex)
	{
		routeIndex = getCommunicationLink(cLinkIndex).getRouteVector().findMostUsedRoute();
	}
	return routeIndex;
}

int CommunicationLinkVector::findMostUsedCommunicationLink()
{
    int index = -1;
    int communicationLinkUsed = 0;
    for (int i=0; i<getSize(); i++)
    {
        if ( getCommunicationLink(i).getNumberOfObservations()>communicationLinkUsed )
        {
            communicationLinkUsed = getCommunicationLink(i).getNumberOfObservations();
            index = i;
        }
    }
    return index;    
}

void CommunicationLinkVector::getMiddleRouteAddresses(int sourceAddress, int destinationAddress, int mostUsedRoute, int &linkNode1, int &linkNode2)
{
	int cLinkIndex = findCommunicationLink(sourceAddress, destinationAddress);
	if (-1 != cLinkIndex)
	{
		getCommunicationLink(cLinkIndex).getRouteVector().getRoute(mostUsedRoute).getMiddleLinkAddresses(linkNode1, linkNode2);
	}
}

void CommunicationLinkVector::resetValuesForNewTimeInterval()
{
	for (int i=0; i<getSize(); i++)
	{
		getCommunicationLink(i).resetValuesForNewTimeInterval();
	}
}

CommunicationLinkVector::~CommunicationLinkVector()
{
	while (getSize()>0)
	{
		removeCommunicationLink(0);
	}
}

