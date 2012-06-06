/***************************************************************************
 * file:        NodeData.cc
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
 ***************************************************************************
 * changelog:   $Revision: 382 $
 *              last modified:   $Date: 2006-07-31 16:10:24 +0200 (Mo, 31 Jul 2006) $
 *              by:              $Author: koepke $
 ***************************************************************************/

#include"NodeData.h"

// define ostream << for Node object
std::ostream &operator<<(std::ostream& stream, NodeData &nodeDataObject)
{
	stream << "Bytes of Control Data Sent : " << nodeDataObject.getBytesControlData() << "\n";
	stream << "Bytes of Control Data Sent (without token messages) : " << nodeDataObject.getBytesControlDataWithoutToken() << "\n";
	stream << "Bytes of Hello Message Control Data Sent : " << nodeDataObject.getBytesHelloControlData() << "\n";
	stream << "Bytes of Cluster Table Message Control Data Sent : " << nodeDataObject.getBytesClusterTableMessageControlData() << "\n";
	stream << "Bytes of Token Message Control Data Sent : " << nodeDataObject.getBytesTokenControlData() << "\n";
	
	stream << "Token Packets Sent : " << nodeDataObject.getTokenPacketsSent() << "\n";
	stream << "Token Packet Time Outs : " << nodeDataObject.getTokenPacketTimeOuts() << "\n";
	
	stream << "Messages Dropped : " << nodeDataObject.getMessagesDropped() << "\n";
    stream << "Messages Dropped (Mac Error): " << nodeDataObject.getMessagesDroppedMacError() << "\n";
	stream << "Messages Dropped (Unable to Route): " << nodeDataObject.getMessagesDroppedUnableToRoute() << "\n";
	stream << "Messages Dropped (Full Buffer) : " << nodeDataObject.getMessagesDroppedFullBuffer() << "\n";
	stream << "Messages Dropped (No Cluster Transmission Handler) : " << nodeDataObject.getMessagesDroppedNoClusterTransmissionHandler() << "\n";
    
    stream << "Average Cluster Cycle Time : " << nodeDataObject.getAverageClusterCycleTime() << "\n";
    
    stream << "Cluster Cycle Time Samples : " << nodeDataObject.getClusterCycleTimeSamples() << "\n";
	return stream;
}
