/***************************************************************************
 * file:        ItemVector.cc
 *
 * author:      Daniël Kotze
 *
Copyright (c) 2011 Stellenbosch University, DSP Laboratory
    This program is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the 
    Free Software Foundation; either version 2 of the License, or (at your option) any later version.
    This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or 
    FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.
    You should have received a copy of the GNU General Public License along with this program; if not, write to the Free Software Foundation, Inc., 59 Temple 
    Place, Suite 330, Boston, MA 02111-1307 USA

Contact Details:
E-mail: daniel.kotze@gmail.com
 ***************************************************************************
 * part of:     Cluster Head Gateway Routing Protocol Simulation
 * description: The item vector object contains item object references.
 ***************************************************************************/

#ifndef ITEM_VECTOR_H
#define ITEM_VECTOR_H

#include<iostream>
#include<Item.h>
#include<vector>

class ItemVector
{
	protected:
		std::vector<Item*> itemVec;
		
	public:
		ItemVector(){}
		~ItemVector(){}
		
		void addItem(Item item);
		
		Item& getItem(int index);
		
		int getSize();
		
		void removeItem(int index);
		
		void printItemVectorId();
};

#endif
