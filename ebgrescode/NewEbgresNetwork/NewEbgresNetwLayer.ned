package newebgresnetwork;

import org.mixim.base.modules.BaseNetwLayer;
import org.mixim.base.modules.IBaseNetwLayer;

// Base module for every network layer module
simple NewEbgresNetwLayer extends BaseNetwLayer like IBaseNetwLayer
{
    parameters:
        @class(NewEbgresNetwLayer);
        
        //bool debug; // debug switch
        //bool stats; // stats switch
        //double headerLength @unit(bit); // length of the network packet header (in bits)
}
