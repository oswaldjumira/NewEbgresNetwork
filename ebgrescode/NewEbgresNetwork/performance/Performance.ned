package newebgresnetwork.performance;

import org.mixim.base.modules.BaseModule;

simple Performance
{
    parameters:
        @class(Performance);
	bool debug; // debug switch
	string simulationOutputDirectory; //Specifies the output directory of the current simulation
	string runOutputDirectory; //Specifies the output directory of the current simulation run
	bool printNetworkHopsPercentage; //Print the percentage nodes are reachable after a certain amount of hops
	bool pMessagesSentReceived; //Print the messages sent and the messages received
	bool pMessagesStartEndTime; //Print the message start and end time
	bool pBitRateDemandedHandled; //Print the bitrate demanded and handled
	bool simulationTimeConnectivity; //Calculate the simulation time connectivity at discrete points throughout the simulation.
	
	//File Write Parameters
	bool writeCommunicationLinkToFile; //Write Communication Link Information to file
	
	//Recording Parameters
	bool recordCommunicationLink; //Record Communication Link Information
	
	//Simulation Parameters
	int runNumber; //Run number of simulation
	
	//XML Parameters
	xml xmlParameters; //XML parameters file
}
