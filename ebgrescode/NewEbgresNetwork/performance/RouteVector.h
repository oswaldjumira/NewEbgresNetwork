/***************************************************************************
 * file:        RouteVector.h
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
 ***************************************************************************/

#ifndef ROUTE_VECTOR_H
#define ROUTE_VECTOR_H

#include"ItemVector.h"

#include<iostream>


#define MAX_ROUTE_PATH_LENGTH 21
class PacketRoute : public Item
{
	protected:
		int routeLength;
		int route[MAX_ROUTE_PATH_LENGTH];
		int packetsReceivedInTimeInterval;
		int packetsReceived;
		
	public:
		PacketRoute()
		{
			setRouteLength(0);
			setPacketsReceivedInTimeInterval(0);
			setPacketsReceived(0);
		}
		
		PacketRoute(int path[])
		{
			//If program gives errors do more error checking here
			int counter = 0;
			while ((path[counter] != -1) && (counter < MAX_ROUTE_PATH_LENGTH))
			{
				route[counter] = path[counter];
				counter++;
			}
			route[counter] = -1;
			setRouteLength(counter);
			setPacketsReceivedInTimeInterval(0);
			setPacketsReceived(0);
		}
		
		PacketRoute(const PacketRoute& pRoute)
		{
			//If program gives errors do more error checking here
			int counter = 0;
			while ((pRoute.route[counter] != -1) && (counter < MAX_ROUTE_PATH_LENGTH))
			{
				route[counter] = pRoute.route[counter];
				counter++;
			}
			route[counter] = -1;
			setRouteLength(pRoute.routeLength);
			setPacketsReceivedInTimeInterval(pRoute.packetsReceivedInTimeInterval);
			setPacketsReceived(pRoute.packetsReceived);
		}
		
		int getRouteLength()
		{
			return routeLength;
		}
		
		void setRouteLength(int rLength)
		{
			routeLength = rLength;
		}
		
		int *getRouteArray()
		{
			return route;
		}
		
		void setRouteArray(int length, int rte[])
		{
			for (int i=0; i<length; i++)
			{
				route[i] = rte[i];
			}
		}
		
		bool compareRoute(int path[])
		{
			int counter = 0;
			bool same = true;
			while ( (counter<routeLength) && (path[counter] != -1) ) 
			{
				if (route[counter] != path[counter])
				{
					same = false;
					break;
				}
				counter++;
			}
			return same;
		}
		
		int getPacketsReceivedInTimeInterval()
		{
			return packetsReceivedInTimeInterval;
		}
		
		void setPacketsReceivedInTimeInterval(int pReceivedInTimeInterval)
		{
			packetsReceivedInTimeInterval = pReceivedInTimeInterval;
		}
		
		void increasePacketsReceivedInTimeInterval()
		{
			packetsReceivedInTimeInterval++;
		}
		
		int getPacketsReceived()
		{
			return packetsReceived;
		}
		
		void setPacketsReceived(int pReceived)
		{
			packetsReceived = pReceived;
		}
		
		void increasePacketsReceived()
		{
			packetsReceived++;
		}
		
		void getMiddleLinkAddresses(int &linkNode1, int &linkNode2);
		
	friend std::ostream &operator<<(std::ostream& stream, PacketRoute &rte);
};

class RouteVector : public ItemVector
{
	protected:
		
		
	public:
		RouteVector()
		{
		};
		
		void addRoute(PacketRoute packetRoute);
		
		PacketRoute& getRoute(int index);
		
		void removeRoute(int index);
		
		void recordRoute(int path[]);
		
		int findRoute(int path[]);
		
		int findMostUsedRoute();
        
	friend std::ostream &operator<<(std::ostream& stream, RouteVector &rVector);
};

#endif
