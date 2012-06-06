// Filename: EbgresPhysicalLayer.cc
// Date: 06/11/2011
// Author: Oswald and Daniel

#include "EbgresPhysicalLayer.h"

//#define EV ev << "EbgresPhysicalLayer : " ==> EV is now part of <omnetpp.h>

Define_Module(EbgresPhysicalLayer);

void EbgresPhysicalLayer::initialize(int stage) {
	PhyLayerBattery::initialize(stage);
}

void EbgresPhysicalLayer::setRadioCurrent(int rs)
{
	double residualBefore = battery->estimateResidualAbs();
	EV << " Energy " << battery->estimateResidualAbs() << "\n";
	PhyLayerBattery::setRadioCurrent(rs);
	double residualAfter = battery->estimateResidualAbs();
	EV << " Energy " << battery->estimateResidualAbs() << "\n";
	double difference = residualBefore - residualAfter;
	EV << "Energy difference " << difference << "\n";
}
