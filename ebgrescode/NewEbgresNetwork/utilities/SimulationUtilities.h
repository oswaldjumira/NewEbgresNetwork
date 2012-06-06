

#ifndef SIMULATION_UTILITIES_H
#define SIMULATION_UTILITIES_H

#include<omnetpp.h>

class SimulationUtilities
{
	public:
		static std::vector<cModule> getModulesByType()
		{
			cSimulation* simulationPtr = cSimulation.getActiveSimulation();
			simulationPtr->getModuleByPath("")
		}
};

#endif
