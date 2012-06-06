/***************************************************************************
 * file:        RouteVector.cc
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
 * description: The route vector stores routes from a source node to a destination.
 *
 ***************************************************************************/

#include"RouteVector.h"

std::ostream &operator<<(std::ostream& stream, PacketRoute &rte)
{
	stream << " Route : ";
	for (int i=0; i<rte.getRouteLength()-1; i++) stream << rte.getRouteArray()[i] << " -> ";
	stream << rte.getRouteArray()[rte.getRouteLength()-1] << "\n";
	stream << "Packets Received : " << rte.getPacketsReceived() << "\n";
	return stream;
}

std::ostream &operator<<(std::ostream& stream, RouteVector &rVector)
{
	stream << "Printing Route List\n";
	stream << "List size : " << rVector.getSize() << "\n";
	for (int i=0; i<rVector.getSize(); i++) stream << i << rVector.getRoute(i);
	return stream;
}

void PacketRoute::getMiddleLinkAddresses(int &linkNode1, int &linkNode2)
{
	int linkBreakIndex = (getRouteLength()/2)-1;
	linkNode1 = getRouteArray()[linkBreakIndex];
	linkNode2 = getRouteArray()[linkBreakIndex+1];
}

void RouteVector::addRoute(PacketRoute packetRoute)
{
	PacketRoute *packetRoutePtr = new PacketRoute(packetRoute);
	itemVec.push_back(packetRoutePtr);
}

PacketRoute& RouteVector::getRoute(int index)
{
	PacketRoute *packetRoutePtr = dynamic_cast<PacketRoute*>(itemVec[index]);
	return *(packetRoutePtr);
}

void RouteVector::removeRoute(int index)
{
	removeItem(index);
}

int RouteVector::findRoute(int path[])
{
	for (int i=0; i<getSize(); i++)
	{
		if (getRoute(i).compareRoute(path)) return i;
	}
	return -1;
}

void RouteVector::recordRoute(int path[])
{
	int index = findRoute(path);
	
	if (index == -1)
	{
		PacketRoute pRoute=PacketRoute(path);
		addRoute(pRoute);
		index = findRoute(path);
	}
	
	if (index != -1)
	{
		getRoute(index).increasePacketsReceived();
		getRoute(index).increasePacketsReceivedInTimeInterval();
	}
}

int RouteVector::findMostUsedRoute()
{
	int index = -1;
	int routeUsed = 0;
	for (int i=0; i<getSize(); i++)
	{
		if ( getRoute(i).getPacketsReceived()>routeUsed )
		{
			routeUsed = getRoute(i).getPacketsReceived();
			index = i;
		}
	}
	return index;
}
