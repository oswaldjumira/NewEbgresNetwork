// Filename: EbgresNic.ned
// Date: 06/11/2011
// Author: Oswald and Daniel

package newebgresnetwork.network_interface_card;

import org.mixim.modules.nic.Nic80211Battery;
import org.mixim.modules.nic.INic;

import org.mixim.modules.mac.Mac80211;
import org.mixim.modules.phy.PhyLayerBattery;

import newebgresnetwork.physical_layer.EbgresPhysicalLayer;

module EbgresNic like INic
{
    parameters:
        string connectionManagerName = default("");   //name of the ConnectionManager module
        double sleepCurrent @unit(mA);
        double rxCurrent @unit(mA);
        double decodingCurrentDelta @unit(mA);
        double txCurrent @unit(mA);
        double setupRxCurrent @unit(mA);
        double setupTxCurrent @unit(mA);
        double rxTxCurrent @unit(mA);
        double txRxCurrent @unit(mA);

        @display("i=block/ifcard");
    gates:
        input upperGateIn; // to upper layers
        output upperGateOut; // from upper layers
        output upperControlOut; // control information 
        input upperControlIn; // control information 
        input radioIn; // radioIn gate for sendDirect

    submodules:
        mac: Mac80211 {
            parameters:
                @display("p=96,87;i=block/layer");
        }
        phy: EbgresPhysicalLayer {
            parameters:
                headerLength = 192bit;
                @display("p=106,157;i=block/process_s");
        }

    connections:
        radioIn --> phy.radioIn;
        phy.upperGateIn <-- { @display("m=m,25,0,25,0"); } <-- mac.lowerGateOut;
        phy.upperGateOut --> { @display("m=m,73,0,50,50"); } --> mac.lowerGateIn;
        phy.upperControlOut --> mac.lowerControlIn;
        phy.upperControlIn <-- mac.lowerControlOut;

        mac.upperGateOut --> upperGateOut;
        mac.upperControlOut --> upperControlOut;
        mac.upperGateIn <-- upperGateIn;
        mac.upperControlIn <-- upperControlIn;
}