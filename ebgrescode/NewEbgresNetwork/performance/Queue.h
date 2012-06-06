/***************************************************************************
 * file:        Queue.h
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

#ifndef QUEUE_H
#define QUEUE_H

#include "Item.h"
#include "omnetpp.h"

class Queue : public Item
{
	protected:
		int 	messagesInQueue;
		double	meanWaitingTime;

		int		numberOfArrivals;
		double	meanArrivalTime;
		double	previousArrivalTime;

		int		numberOfCustomersServiced;
		double	meanServiceTime;
		double	previousServiceTime;

	public:
		Queue()
		{
			reset();
		}

		void setMessagesInQueue(int mInQueue)
		{
			messagesInQueue = mInQueue;
		}

		int getMessagesInQueue()
		{
			return messagesInQueue;
		}

		void recordArrival(double arrivalTime)
		{
			if (numberOfArrivals == 0) previousArrivalTime = arrivalTime;
			else
			{
				double currentArrivalTime = arrivalTime;
				meanArrivalTime = ( meanArrivalTime*( ((double) numberOfArrivals)-1 )+( currentArrivalTime-previousArrivalTime ) )/((double) numberOfArrivals);
				previousArrivalTime = currentArrivalTime;
			}
			numberOfArrivals++;
		}
		
		void reset();

		void recordService(double serviceTime);

		double getMeanArrivalTime() { return meanArrivalTime; }
		double getMeanServiceTime() { return meanServiceTime; }
        int getNumberOfArrivals() { return numberOfArrivals; }
        int getNumberOfCustomersServiced() { return numberOfCustomersServiced; }

	friend std::ostream &operator<<(std::ostream& stream, Queue &queue);
};

class QueueSet
{
	protected:
		int	clusterAddress;
		Queue personalQueue;
		Queue clusterQueue;
	public:
		QueueSet()
		{
			setClusterAddress(-1);
		};

		void setClusterAddress(int cAddress)
		{
			clusterAddress = cAddress;
		};

		int getClusterAddress()
		{
			return clusterAddress;
		};

		Queue &getPersonalQueue()
		{
			return personalQueue;
		};

		Queue &getClusterQueue()
		{
			return clusterQueue;
		}
		
		void resetQueues();

	friend std::ostream &operator<<(std::ostream& stream, QueueSet &queueSet);
};

#define MAX_NUMBER_OF_QUEUE_SETS 8

class QueueSetList
{
	protected:
		int			numberOfQueueSets;
		QueueSet 	queueSet[MAX_NUMBER_OF_QUEUE_SETS];

	public:
		QueueSetList()
		{
			setNumberOfQueueSets(0);
		};

		int getNumberOfQueueSets() { return numberOfQueueSets; }
		void setNumberOfQueueSets(int nOfQueueSets) { numberOfQueueSets = nOfQueueSets; }

		bool createQueueSet(int cAddress);

		void removeQueueSet(int cAddress);

		int findQueueSet(int cAddress);

		QueueSet &getQueueSet(int cAddress)
		{
			return queueSet[findQueueSet(cAddress)];
		};

		QueueSet &getQueueSetViaIndex(int index)
		{
			return queueSet[index];
		};

	friend std::ostream &operator<<(std::ostream& stream, QueueSetList &queueSetList);
};

#endif
