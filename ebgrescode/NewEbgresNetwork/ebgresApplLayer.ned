package newebgresnetwork;

import org.mixim.modules.application.TestApplication;
import org.mixim.base.modules.IBaseApplLayer;

simple ebgresApplLayer extends TestApplication like IBaseApplLayer
{
    parameters:
        @class(ebgresApplLayer);
    	int headerLength @unit("bit"); // length of the application message header (in bits)
    	int burstSize; // size of the burst
}