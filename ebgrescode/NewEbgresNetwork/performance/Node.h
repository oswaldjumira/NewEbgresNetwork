/***************************************************************************
 * file:        Node.h
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
 ***************************************************************************/

#ifndef NODE_H
#define NODE_H

#include "omnetpp.h"
#include <sstream>
#include "Router.h"
#include "RoutingInformation.h"
#include "NetworkLayerInformation.h"
#include "NodeData.h"
#include "Queue.h"
#include <Coord.h>

#include <list>
#include <vector>

class Node : public cObject
{
	protected:
		//Simulation Parameters
	    int					id;
		int					nodeIndex;
		
		int					macAddress;
		int					address;
		int 				messagesCreated;
		int					messagesPassedOn;
		int					messagesArrivedDestination;
		int					messagesDropped;

		int					messagesSentSuccess;
		int					messagesSentLost;

		bool				isClusterHead;

		double				clusterHeadTime;

		int					nodeHops[10];

		int					nodesReachable[30];
		char				numberOfNodesReachable;

		double				connectivity;

		bool				printClusterTableSet;
		bool				printNetworkNodeTable;
		bool				printNeighbourTable;
		
		//Block Parameters
		int *blockMacAddressPtr;
        long *shortRetriesPtr;
        long *longRetriesPtr;

        /*
         * Routing information like tables etc.
         */
        RoutingInformation *routingInformationPtr;

        /*
         * NetworklayerInformation like the network address etc.
         */
        NetworkLayerInformation *networkLayerInformationPtr;

        NodeData *nodeDataPtr;

        /*
         * Abstracting the router.
         */
        Router *routerPtr;

        Coord coordinate;

	protected:
		void initialize()
		{
			setNodeIndex(0);
			
			setMacAddress(-1);
			address = -1;
			id = -1;

			messagesCreated = 0;
			messagesPassedOn = 0;
			messagesArrivedDestination = 0;
			messagesDropped = 0;

			messagesSentSuccess = 0;
			messagesSentLost = 0;

			isClusterHead = false;
			clusterHeadTime = 0;

			setRoutingInformationPtr(NULL);
			setNetworkLayerInformationPtr(NULL);

			setPrintClusterTableSet(false);
			setPrintNetworkNodeTable(false);
			setPrintNeighbourTable(false);

			setConnectivity(0);
            
            shortRetriesPtr = NULL;
            longRetriesPtr = NULL;
            blockMacAddressPtr = NULL;
		};

		void initializeNodeHops()
		{
			for (int i=0; i<10; i++)
			{
				nodeHops[i] = 0;
			}
		};

	protected:
		void initializeNodesReachableArray()
		{
			numberOfNodesReachable = 0;
			for (int i=0; i<30; i++)
			{
				nodesReachable[i] = 0;
			}
		};

	public:
		Node()
		{
			Item();
			initialize();
			initializeNodesReachableArray();
		};

		Node(int addr)
		{
			address = addr;
			initialize();
			initializeNodesReachableArray();
		};

		//Operator overloading

		int 	getAddress()
		{
			return address;
		};

		void 	setAddress(int addr)
		{
			address = addr;
		};

		virtual void copyItem(Item *original)
		{
			//printf("Copying original data\n");
			setAddress(((Node*)(original))->getAddress());
			//printf("Address of %d obtained\n",getAddress());
		};

		void increaseMessagesCreated()
		{
			messagesCreated++;
		}

		int getMessagesCreated()
		{
			return messagesCreated;
		}

		void increaseMessagesPassedOn()
		{
			messagesPassedOn++;
		}

		int getMessagesPassedOn()
		{
			return messagesPassedOn;
		}

		void increaseMessagesArrivedDestination()
		{
			messagesArrivedDestination++;
		}

		int getMessagesArrivedDestination()
		{
			return messagesArrivedDestination;
		}

		void increaseMessagesDropped()
		{
			messagesDropped++;
		}

		int getMessagesDropped()
		{
			return messagesDropped;
		}

		void increaseMessagesSentSuccess()
		{
			messagesSentSuccess++;
		}

		int getMessagesSentSuccess()
		{
			return messagesSentSuccess;
		}

		void increaseMessagesSentLost()
		{
			messagesSentSuccess++;
		}

		int getMessagesSentLost()
		{
			return messagesSentSuccess;
		}

		void setIsClusterHead(bool isCHead)
		{
			isClusterHead = isCHead;
		};

		bool getIsClusterHead()
		{
			return isClusterHead;
		};

		void setClusterHeadTime(double cHeadTime)
		{
			clusterHeadTime = cHeadTime;
		};

		double getClusterHeadTime()
		{
			return clusterHeadTime;
		};
		
		RoutingInformation *getRoutingInformationPtr()
		{
			return routingInformationPtr;
		}

		void setRoutingInformationPtr(RoutingInformation *rInformationPtr)
		{
			routingInformationPtr = rInformationPtr;
		}

		void setRouterPtr(Router *rtrPtr)
		{
			routerPtr = rtrPtr;
		};

		Router *getRouterPtr()
		{
			return routerPtr;
		};
		
		NetworkLayerInformation *getNetworkLayerInformationPtr()
		{
			return networkLayerInformationPtr;
		}

		void setNetworkLayerInformationPtr(NetworkLayerInformation *nLayerInformationPtr)
		{
			networkLayerInformationPtr = nLayerInformationPtr;
		}
		
		NodeData *getNodeDataPtr()
		{
			return nodeDataPtr;
		}
		
		void setNodeDataPtr(NodeData *nDataPtr)
		{
			nodeDataPtr = nDataPtr;
		}

		int *getNodeHopsArray()
		{
			return nodeHops;
		}

		void addNodeToNodesReachableArray(int nodeAddress)
		{
			//search if node is in list if list is larger than 0
			bool found = false;
			if (numberOfNodesReachable>0)
			{
				for (int i=0; i<numberOfNodesReachable; i++)
				{
					if (nodeAddress == nodesReachable[i])
					{
						found = true;
						break;
					}
				}
			}

			if ((found == false) && (numberOfNodesReachable<30))
			{
				nodesReachable[numberOfNodesReachable] = nodeAddress;
				numberOfNodesReachable++;
			}
		}

		int determineNextHop(int destAddr)
		{
			int hops = -1;
			int nextHop = -1;
			return nextHop;
		}

		void setCoordinate(Coord coord)
		{
			coordinate = coord;
		}

		Coord getCoordinate()
		{
			return coordinate;
		}

		void setConnectivity(double cnt)
		{
			connectivity = cnt;
		}

		double getConnectivity()
		{
			return connectivity;
		};

		void setPrintClusterTableSet(bool pClusterTableSet)
		{
			printClusterTableSet = pClusterTableSet;
		};

		bool getPrintClusterTableSet()
		{
			return printClusterTableSet;
		};

		void setPrintNetworkNodeTable(bool pNetworkNodeTable)
		{
			printNetworkNodeTable = pNetworkNodeTable;
		};

		bool getPrintNetworkNodeTable()
		{
			return printNetworkNodeTable;
		};

		void setPrintNeighbourTable(bool pNeighbourTable)
		{
			printNeighbourTable = pNeighbourTable;
		}

		bool getPrintNeighbourTable()
		{
			return printNeighbourTable;
		}

		int getNodeIndex()
		{
			return nodeIndex;
		}
		
		void setNodeIndex(int nIndex)
		{
			nodeIndex = nIndex;
		}
		
		int getMacAddress()
		{
			return macAddress;
		}
		
		void setMacAddress(int mAddress)
		{
			macAddress = mAddress;
		}
		
		int *getBlockMacAddressPtr()
		{
			return blockMacAddressPtr;
		}
		
		void setBlockMacAddressPtr(int *bMacAddressPtr)
		{
			blockMacAddressPtr = bMacAddressPtr;
		}
        
        long *getShortRetriesPtr()
        {
            return shortRetriesPtr;
        }
        
        void setShortRetriesPtr(long *sRetriesPtr)
        {
            shortRetriesPtr = sRetriesPtr;
        }
        
        long *getLongRetriesPtr()
        {
            return longRetriesPtr;
        }
        
        void setLongRetriesPtr(long *lRetriesPtr)
        {
            longRetriesPtr = lRetriesPtr;
        }

		friend std::ostream &operator<<(std::ostream& stream, Node &nodeObject);
};

class NodeList
{
	protected:
		cLongHistogram clusterHeadConnectionStats;
		std::vector<Node*> nodePtrList;
		
	public:
		NodeList(){};

		Node *getNodePtr(int index)
		{
			return nodePtrList[index];
		};

		std::vector<Node*> getNodePtrList()
		{
			return nodePtrList;
		};

		Node* getItem(int index)
		{
			return nodePtrList[index];
		}

		double calculateNodeConnectivity(int nodeNum)
		{
			printf("In calculateNodeConnectivity of node %d \n", nodeNum);
			int totalNumberOfNodes = nodePtrList.size();

			double connectivity = 0;

			Node *node = getNodePtr(nodeNum);
			Router *routerPtr = node->getRouterPtr();
			printf("After assigning pointers\n");
			for (int i = 0; i<totalNumberOfNodes; i++)
			{
				printf("In for loop inspecting node %d\n",i);
				if ((routerPtr->determineNextHop(getNodePtr(i)->getAddress()) != -1) || (i == nodeNum)) connectivity = ( ( (double) 1 )/ ( (double) totalNumberOfNodes ) ) + connectivity;
			}
			printf("After for Loop\n");
			return connectivity;
		};

		void calculateAndSetNodeConnectivity(int nodeNum)
		{
			getNodePtr(nodeNum)->setConnectivity(calculateNodeConnectivity(nodeNum));
		};

		void calculateAndSetConnectivityForAllNodes()
		{
			printf("In calculate and set connectivity\n");
			for (int i=0; i<nodePtrList.size(); i++)
			{
				getNodePtr(i)->setConnectivity((calculateNodeConnectivity(i)));
			}
		};

		int calculateNumberOfConnections()
		{
			int numberOfNodes = nodePtrList.size();
			//Number of Connections 1 + 2 + 3 + ... + n = ((n)*(n+1))/2

			int numberOfConnections = (numberOfNodes*(numberOfNodes-1))/2;

			return numberOfConnections;
		}

		double calculateNetworkConnectivity()
		{
			double connectivity = 0;
			
			calculateAndSetConnectivityForAllNodes();
			
			for (int i=0; i<nodePtrList.size(); i++)
			{
				connectivity = getNodePtr(i)->getConnectivity() + connectivity;
			}

			connectivity = connectivity/( (double) nodePtrList.size());
			return connectivity;
		};

		int determineTotalFullBufferPacketsDropped()
		{
			int messagesDropped = 0;
			for (int i=0; i<nodePtrList.size(); i++) messagesDropped += getNodePtr(i)->getNodeDataPtr()->getMessagesDroppedFullBuffer();
			return messagesDropped;
		}
        
        int findNode(int nodeAddress)
        {
            for (int i=0; i<nodePtrList.size(); i++)
            {
                if (nodeAddress == getNodePtr(i)->getAddress()) return i;
            }
            return -1;
        }

        int getListSize()
        {
        	return nodePtrList.size();
        }
};

#endif
