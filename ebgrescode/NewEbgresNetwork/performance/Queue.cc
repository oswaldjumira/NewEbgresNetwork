/* -*- mode:c++ -*- ********************************************************
 * file:        Queue.cc
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
 * description: - The queue object provides a basic message queue where messages can wait for a transmission chance.
                    If the queue is full packets are dropped.
 ***************************************************************************/

#include "Queue.h"

std::ostream &operator<<(std::ostream& stream, QueueSetList &queueSetList)
{
	stream << "Queue Set List : " << endl;
	int numberOfQueueSets = queueSetList.getNumberOfQueueSets();
	for (int i=0; i<numberOfQueueSets; i++) stream << queueSetList.getQueueSetViaIndex(i);
	return stream;
}

std::ostream &operator<<(std::ostream& stream, QueueSet &queueSet)
{
	stream << "Queue Set Cluster Address : " << queueSet.getClusterAddress() << endl;
	stream << "Personal Queue : " << endl;
	stream << queueSet.getPersonalQueue();
	stream << "Cluster Queue : " << endl;
	stream << queueSet.getClusterQueue();
	return stream;
}

std::ostream &operator<<(std::ostream& stream, Queue &queue)
{
	stream << "Mean Arrival Time : " << queue.getMeanArrivalTime() << endl;
    stream << "Number of Arrivals : " << queue.getNumberOfArrivals() << endl;
	stream << "Mean Service Time : " << queue.getMeanServiceTime() << endl;
    stream << "Number of Customers Serviced : " << queue.getNumberOfCustomersServiced() << endl;
	return stream;
}

void Queue::recordService(double serviceTime)
{
	if (numberOfCustomersServiced == 0) previousServiceTime = serviceTime;
	else
	{
		double currentServiceTime = serviceTime;
		meanServiceTime = ( meanServiceTime*( ((double) numberOfCustomersServiced)-1 )+( currentServiceTime-previousServiceTime ) ) / ((double) numberOfCustomersServiced);
		previousServiceTime = currentServiceTime;
	}
	numberOfCustomersServiced++;
}

void Queue::reset()
{
	messagesInQueue = 0;
	meanWaitingTime = 0;

	numberOfArrivals = 0;
	meanArrivalTime = 0;
	previousArrivalTime = 0;

	numberOfCustomersServiced = 0;
	meanServiceTime = 0;
	previousServiceTime = 0;
}

void QueueSet::resetQueues()
{
	personalQueue.reset();
	clusterQueue.reset();
}

bool QueueSetList::createQueueSet(int cAddress)
{
	//Test if the the maximum number of QueueSets has been reached
	if ((getNumberOfQueueSets()<MAX_NUMBER_OF_QUEUE_SETS) && (findQueueSet(cAddress) == -1))
	{
		queueSet[numberOfQueueSets].setClusterAddress(cAddress);
		queueSet[numberOfQueueSets].resetQueues();
		numberOfQueueSets++;
		return true;
	}
	else return false;
}

int QueueSetList::findQueueSet(int cAddress)
{
	for (int i=0; i<getNumberOfQueueSets(); i++)
		if (cAddress == queueSet[i].getClusterAddress()) return i;
	return -1;
}

void QueueSetList::removeQueueSet(int cAddress)
{
	int index = findQueueSet(cAddress);

	for (int i=index; i<getNumberOfQueueSets()-1; i++) queueSet[i] = queueSet[i+1];

	setNumberOfQueueSets(getNumberOfQueueSets()-1);
}
