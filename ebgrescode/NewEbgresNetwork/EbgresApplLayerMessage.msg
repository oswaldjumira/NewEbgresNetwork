cplusplus {{
#include <ApplPkt_m.h>
}}


class ApplPkt;

//class PayLoad
//{
//	char	content[1024];
//}


class DataApplMessage
{
    char	content[1024];
}

message EbgresApplMessage extends ApplPkt
{
    DataApplMessage dataApplMessage[1];
}
