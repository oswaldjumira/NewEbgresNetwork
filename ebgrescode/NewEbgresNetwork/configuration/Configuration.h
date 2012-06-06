#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include "BaseUtility.h"
#include "BaseMobility.h"
#include "NewEbgresNetwLayer.h"
#include "NodeInformation.h"
#include "Coord.h"

#define DATA_MESSAGE_SIZE_BYTES 1024

/*
 * Class Prototypes
 */
class NodeInformation;

class Configuration : public cSimpleModule
{
	protected:
		int sourceAddress;
		Coord sourceCoordinates;

		int sinkAddress;
		Coord sinkCoordinates;

		int searchRadius;

	public:
		virtual void initialize(int);

		virtual int numInitStages() const {
			return 4;
		}

		virtual int getSinkAddress();

		virtual Coord getSinkCoordinates();

		virtual int getSourceAddress();

		virtual Coord getSourceCoordinates();

		virtual int getSearchRadius()
		{
			return searchRadius;
		}
};

#endif
