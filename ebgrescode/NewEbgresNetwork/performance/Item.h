/***************************************************************************
 * file:        Item.h
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
 * description: The item object is a general object that can be added to a linked list. Derived classes can be used to store data.
 ***************************************************************************/

#ifndef ITEM_H
#define ITEM_H

class Item
{

	protected:
		int		id;
	public:
		Item(){};
		
		Item(int idIni)
		{
			setId(idIni);
		}
		
		Item(const Item &item)
		{
			id = item.id;
		}
		
		void setId(int identity);
		
		int getId();

		virtual void copyItem(Item *original){};
};

#endif
