#include "Configuration.h"

Define_Module(Configuration);

//#define EV ev << "Configuration : " ==> EV is now part of <omnetpp.h>

void Configuration::initialize(int stage)
{
	if (stage == 0)
	{
		EV << "Stage 0\n";

		searchRadius = 50;
	}
	else if (stage == 3)
	{
		//Select random node to be the sink.

		//Select random node to be the source.
		EV << "Stage 3\n";
		int numberOfNodes = getParentModule()->par("numNodes");
		int sinkNodeNumber = 4;//intrand(numberOfNodes);

		int sourceNodeNumber = -1;

		do
		{
			sourceNodeNumber = 1;//intrand(numberOfNodes);
		}
		while (sinkNodeNumber == sourceNodeNumber);

		//Set sink coordinates on all nodes.

		NodeInformation *sinkNodeInformationPtr = dynamic_cast<NodeInformation*>(getParentModule()->getSubmodule("node",sinkNodeNumber)->getSubmodule("nodeInfo"));

		if (sinkNodeInformationPtr != NULL)
		{
			BaseUtility *hostUtilityPtr = sinkNodeInformationPtr->getHostUtilityPtr();

			if (hostUtilityPtr != NULL)
			{
				sinkCoordinates = hostUtilityPtr->getPos();
				EV << "sink random node : " << sinkNodeNumber << "\n";
				EV << "Coord : x " << sinkCoordinates.getX() << " y " << sinkCoordinates.getY() << "z " << sinkCoordinates.getZ() << "\n";
			}

			sinkAddress = sinkNodeInformationPtr->getNetworkAddress();

			EV << "Sink address: " << sinkAddress << "\n";
		}

		NodeInformation *sourceNodeInformationPtr = dynamic_cast<NodeInformation*>(getParentModule()->getSubmodule("node",sourceNodeNumber)->getSubmodule("nodeInfo"));

		if (sourceNodeInformationPtr != NULL)
		{
			BaseUtility *hostUtilityPtr = sourceNodeInformationPtr->getHostUtilityPtr();

			if (hostUtilityPtr != NULL)
			{
				sourceCoordinates = hostUtilityPtr->getPos();
				EV << "Source random node : " << sourceNodeNumber << "\n";
				EV << "Coord : x " << sourceCoordinates.getX() << " y " << sourceCoordinates.getY() << "z " << sourceCoordinates.getZ() << "\n";
			}

			sourceAddress = sourceNodeInformationPtr->getNetworkAddress();

			EV << "Source address: " << sourceAddress << "\n";
		}
	}

}

int Configuration::getSinkAddress()
{
	return sinkAddress;
}

Coord Configuration::getSinkCoordinates()
{
	return sinkCoordinates;
}

int Configuration::getSourceAddress()
{
	return sourceAddress;
}

Coord Configuration::getSourceCoordinates()
{
	return sourceCoordinates;
}
