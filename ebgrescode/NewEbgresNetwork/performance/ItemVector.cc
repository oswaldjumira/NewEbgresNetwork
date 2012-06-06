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

#include "ItemVector.h"

void ItemVector::addItem(Item item)
{
	Item *itemPtr = new Item(item);
	itemVec.push_back(itemPtr);
}

void ItemVector::printItemVectorId()
{
	for (int i=0; i<itemVec.size(); i++) std::cout << "Item vector element " << i << " id : " << (*itemVec[i]).getId() << "\n";
}

Item& ItemVector::getItem(int index)
{
	return *(itemVec[index]);
}

int ItemVector::getSize()
{
	return itemVec.size();
}

void ItemVector::removeItem(int index)
{
	//Free memory first
	delete itemVec[index];
	std::vector<Item*>::iterator iter = itemVec.begin();
	iter = iter+index;
	itemVec.erase(iter);
}
