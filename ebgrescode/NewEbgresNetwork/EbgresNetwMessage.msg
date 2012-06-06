cplusplus {{
#include <NetwPkt_m.h>

#include <Coord.h>
}}


class NetwPkt;

class noncobject Coord;


class SelectMessage
{
    int selectNodeAddress;
    Coord selectNodePos;
}

class DataMessage
{
    Coord destinationPos;
    Coord sourcePos;
    
    Coord idealPos;
    double residualEnergySender;
}

class AckMessage
{
    int intermediateNodeAddress;
    Coord intermediatePos;
    double residualEnergySender;
    
}

class AnalysisData
{
    int routeNodes[];
}

packet EbgresNetwMessage extends NetwPkt
{
    //SrcAddr is the initial source of a packet. (Inherited from NetwPkt)
    //DestAddr is the final destination of a packet.
    
    // Type 0 message : is a dataMessage.
    // Type 1 message : is a ackMessage.
    // Type 2 message : is a selectMessage.
    
    int type;
    int nextHopAddr; //Address of next hop
    int receivedFromAddr; //Address of node that sent packet.
    
    int dataMessageId; //Identification number of data exchange
    SelectMessage selectMessage[1];
    DataMessage dataMessage[1];
    AckMessage AckMessage[1];
    
    AnalysisData analysisData[1];
}
