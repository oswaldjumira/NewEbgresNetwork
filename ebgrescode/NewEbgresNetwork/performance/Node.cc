/***************************************************************************
 * file:        Node.cc
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
 * description: - The node object is used by the performance module to access important data structures of nodes themselves, for instance their routing tables etc.
 *
 ***************************************************************************
 * changelog:   $Revision: 382 $
 *              last modified:   $Date: 2006-07-31 16:10:24 +0200 (Mo, 31 Jul 2006) $
 *              by:              $Author: koepke $
 ***************************************************************************/

#include "Node.h"

std::ostream &operator<<(std::ostream& stream, Node &nodeObject)
{
	stream << "Node Information : " << endl;
	stream << "Network Address : " << nodeObject.getAddress() << endl;
	stream << "Mac Address : " << nodeObject.getMacAddress() << endl;
	stream << "Block Mac Address : " << *(nodeObject.getBlockMacAddressPtr()) << endl;
	if (nodeObject.getIsClusterHead()) 
	{
		stream << "Node is a Cluster Head" << endl;
		stream << "Cluster Head Time : " << nodeObject.getClusterHeadTime() << endl;
	}
	stream << "Messages created : " << nodeObject.getMessagesCreated() << endl;
	stream << "Messages passed on : " << nodeObject.getMessagesPassedOn() << endl;
	stream << "Messages arrived at destination : " << nodeObject.getMessagesArrivedDestination() << endl;
	stream << "Messages dropped : " << nodeObject.getMessagesDropped() << endl;
	stream << "Messages sent that arrived successfully : " << nodeObject.getMessagesSentSuccess() << endl;
	return stream;
}  // define ostream << for Node object
