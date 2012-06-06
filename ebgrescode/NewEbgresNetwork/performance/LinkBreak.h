/* -*- mode:c++ -*- ********************************************************
 * file:        LinkBreak.h
 *
 * author:      Daniël Kotze
 *
 * copyright:   (C) 2009 Stellenbosch University, DSP Laboratory
 *
 *              This program is free software; you can redistribute it 
 *              and/or modify it under the terms of the GNU General Public 
 *              License as published by the Free Software Foundation; either
 *              version 2 of the License, or (at your option) any later 
 *              version.
 *              For further information see file COPYING 
 *              in the top level directory
 ***************************************************************************
 * part of:     Cluster Head Gateway Routing Protocol
 * description: - This is the application layer of the Cluster Head Gateway Routing Protocol
 ***************************************************************************/


#ifndef LINK_BREAK_LAYER_H
#define LINK_BREAK_LAYER_H

class LinkBreak
{
	protected:
		int sourceAddress;
		int destinationAddress;
		
	public:
		LinkBreak()
		{
			setSourceAddress(-1);
			setDestinationAddress(-1);
		}
		
		int getSourceAddress()
		{
			return sourceAddress;
		}
		
		void setSourceAddress(int sAddress)
		{
			sourceAddress = sAddress;
		}
		
		int getDestinationAddress()
		{
			return destinationAddress;
		}
		
		void setDestinationAddress(int dAddress)
		{
			destinationAddress = dAddress;
		}
};

#endif
 
