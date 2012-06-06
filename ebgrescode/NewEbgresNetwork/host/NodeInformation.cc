#include "NodeInformation.h"

Define_Module(NodeInformation);

void NodeInformation::initialize(int stage)
{
	if (stage == 0)
	{
		simpleBatteryPtr = dynamic_cast<SimpleBattery*>(getParentModule()->getSubmodule("battery"));
		hostUtilityPtr = dynamic_cast<BaseUtility*>(getParentModule()->getSubmodule("utility"));

		sinkHost = false;

		dataMessageId = 0;
	}
	else if (stage == 1)
	{

	}
	else if (stage == 2)
	{
		/*
		 * Getting network address.
		 */
		NewEbgresNetwLayer *newEbgresNetwLayerPtr = dynamic_cast<NewEbgresNetwLayer*>(getParentModule()->getSubmodule("net"));
		setNetworkAddress(newEbgresNetwLayerPtr->getNetwAddr());
	}
	else if (stage == 4)
	{
		/*
		 * Getting the sink node coordinates and address.
		 */

		Configuration *configurationPtr = dynamic_cast<Configuration*>(getParentModule()->getParentModule()->getSubmodule("configuration"));
		sinkAddress = configurationPtr->getSinkAddress();
		sinkCoordinates = configurationPtr->getSinkCoordinates();
		sourceAddress = configurationPtr->getSourceAddress();
	}
}

Coord NodeInformation::getHostCoordinates()
{
	return hostUtilityPtr->getPos();
}

void NodeInformation::setHostCoordinates(Coord hCoordinates)
{
	hostCoordinates = hCoordinates;
}

Coord NodeInformation::getSinkCoordinates()
{
	return sinkCoordinates;
}

void NodeInformation::setSinkCoordinates(Coord sCoordinates)
{
	sinkCoordinates = sCoordinates;
}

int NodeInformation::getSinkAddress()
{
	return sinkAddress;
}

void NodeInformation::setSinkAddress(int sAddress)
{
	sinkAddress = sAddress;
}

int NodeInformation::getSourceAddress()
{
	return sourceAddress;
}

void NodeInformation::setSourceAddress(int sAddress)
{
	sourceAddress = sAddress;
}

bool NodeInformation::isSourceNode()
{
	return (sourceAddress == networkAddress);
}


double NodeInformation::getResidualEnergy()
{
	return simpleBatteryPtr->estimateResidualAbs();
}

void NodeInformation::setResidualEnergy(double rEnergy)
{
	residualEnergy = rEnergy;
}

bool NodeInformation::isSinkHost()
{
	return sinkHost;
}


void NodeInformation::setSinkHost(bool sHost)
{
	sinkHost = sHost;
}

long NodeInformation::getDataMessageId() const
{
    return dataMessageId;
}

void NodeInformation::setDataMessageId(long  dataMessageId)
{
    this->dataMessageId = dataMessageId;
}

void NodeInformation::increaseDataMessageId()
{
	dataMessageId++;
}

int NodeInformation::getNetworkAddress()
{
	return networkAddress;
}

void NodeInformation::setNetworkAddress(int nAddress)
{
	networkAddress = nAddress;
}
