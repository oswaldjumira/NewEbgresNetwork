/*
 * Class to abstract the node's routing.
 */

#ifndef ROUTER_H
#define ROUTER_H

class Router : public cObject
{
	public:
		virtual int determineNextHop(int nodeAddress);
};

#endif
