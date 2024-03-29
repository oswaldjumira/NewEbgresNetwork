package newebgresnetwork;

import newebgresnetwork.host.NodeInformation;

import org.mixim.modules.nic.Nic80211Battery;

import org.mixim.base.modules.*;

import org.mixim.modules.power.battery.SimpleBattery;

import org.mixim.modules.power.battery.BatteryStats;

import newebgresnetwork.network_interface_card.EbgresNic;

module BaseNode
{
    parameters:
        string applType; //type of the application layer
        string netwType; //type of the network layer
        string mobType; //type of the mobility module
        @display("bgb=,,white,,");
    gates:
        input radioIn; // gate for sendDirect
    submodules:
        utility: BaseUtility {
            parameters:
                @display("p=130,38;b=24,24,rect,black;i=block/blackboard");
        }
        arp: BaseArp {
            parameters:
                @display("p=130,101;b=24,24,rect,blue;i=block/process");
        }
        mobility: <mobType> like IBaseMobility {
            parameters:
                @display("p=130,166;i=block/cogwheel");
        }
        appl: <applType> like IBaseApplLayer {
            parameters:
                @display("p=59,38;i=app");
        }
        net: <netwType> like IBaseNetwLayer {
            parameters:
                @display("p=60,101;i=block/layer");
        }
        nic: EbgresNic {
            parameters:
                @display("p=60,166;i=block/ifcard");
        }
        nodeInfo: NodeInformation {
        }
        batteryStats: BatteryStats {
            @display("p=239,206;i=block/circle");
        }
        battery: SimpleBattery {
            @display("p=171,206;i=block/control");
        }
    connections:
        nic.upperGateOut --> net.lowerGateIn;
        nic.upperGateIn <-- net.lowerGateOut;
        nic.upperControlOut --> { @display("ls=red;m=m,70,0,70,0"); } --> net.lowerControlIn;
        nic.upperControlIn <-- { @display("ls=red;m=m,70,0,70,0"); } <-- net.lowerControlOut;

        net.upperGateOut --> appl.lowerGateIn;
        net.upperGateIn <-- appl.lowerGateOut;
        net.upperControlOut --> { @display("ls=red;m=m,70,0,70,0"); } --> appl.lowerControlIn;
        net.upperControlIn <-- { @display("ls=red;m=m,70,0,70,0"); } <-- appl.lowerControlOut;

        radioIn --> nic.radioIn;

}
