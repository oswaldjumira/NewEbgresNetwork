/***************************************************************************
 * file:        CommunicationLink.cc
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

#include "CommunicationLink.h"

std::ostream &operator<<(std::ostream& stream, CommunicationLink &cLink)
{
	stream << " Communication Link << Source Address : " << cLink.getSourceAddress() << " >> Destination Address : " << cLink.getDestinationAddress() << "\n";
	stream << "\tMean Latency : " << cLink.getMeanLatency() << "s" << "\n";
	stream << "\tMean Throughput : " << cLink.getMeanThroughput() << "\n";
	stream << "\tNumber Of Observations : " << cLink.getNumberOfObservations() << "\n";
	stream << cLink.getRouteVector();
	return stream;
}

void CommunicationLink::recordLatencyAndThroughput(double latency, double arrivalTime)
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

void CommunicationLink::recordRoute(int path[])
{
	if (path[0] == getSourceAddress()) //Test
	{
		routeVector.recordRoute(path);
	}
}

void CommunicationLink::resetValuesForNewTimeInterval()
{
	for (int i=0; i<getRouteVector().getSize(); i++)
	{
		getRouteVector().getRoute(i).setPacketsReceivedInTimeInterval(0);
	}
}

