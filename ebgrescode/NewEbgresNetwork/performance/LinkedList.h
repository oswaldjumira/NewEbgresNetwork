/***************************************************************************
 * file:        LinkedList.h
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
 * description: This class implements the linked list datastructure. (I coded this before realizing that one can use the C++ STL)
 ***************************************************************************/

#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include "Item.h"

class ItemEntry
{
	protected:
		ItemEntry *nextPtr;
		Item *entry;

	public:
		ItemEntry()
		{
			nextPtr = NULL;
			entry = NULL;
		};

		ItemEntry(ItemEntry *nPtr)
		{
			entry = NULL;
			nextPtr = nPtr;
		};

		~ItemEntry()
		{
			if (entry != NULL) delete entry;
		}

		ItemEntry *getNextPtr()
		{
			return nextPtr;
		};

		void setNextPtr(ItemEntry *nPtr)
		{
			nextPtr = nPtr;
		};

		void setEntry(Item *item)
		{
			printf("Setting Entry\n");
			entry = item;
		};

		Item *getEntry()
		{
			return entry;
		};
};

class LinkedList
{
	protected:
		ItemEntry *startPtr, *currentPtr;
		int			listSize;
		long		idNum;

		void increaseListSize()
		{
			listSize++;
		};

		void decreaseListSize()
		{
			listSize--;
		};

	public:
		LinkedList()
		{
			startPtr = NULL;
			currentPtr = NULL;
			listSize = 0;
			idNum = 0;
		};

		~LinkedList()
		{
			if (startPtr == NULL)
			{
				ItemEntry *tempPtr;
				tempPtr = startPtr;
				startPtr = startPtr->getNextPtr();
			}
		};

		int addItem(Item *newItem)
		{
			//printf("Adding item\n");
			if (startPtr == NULL)
			{
				startPtr = new ItemEntry();
				startPtr->setEntry(newItem);
				currentPtr = startPtr;
			}
			else
			{
				currentPtr = startPtr;
				while (currentPtr->getNextPtr() != NULL) currentPtr = currentPtr->getNextPtr();
				currentPtr->setNextPtr(new ItemEntry());
				currentPtr = currentPtr->getNextPtr();
				currentPtr->setEntry(newItem);
			}
			increaseListSize();
			printf("Items in list now is %d\n",listSize);
			currentPtr->getEntry()->setId(idNum);
			printf("Id num now %d\n",idNum);
			return idNum++;
		};

		Item *getItem(int index)
		{
			if (listSize>0)
			{
				int count = 0;
				currentPtr = startPtr;
				while (count<index)
				{
					currentPtr = currentPtr->getNextPtr();
					count++;
				}
				return (currentPtr->getEntry());
			}
			else
			{
				Item *blank;
				blank = NULL;
				return blank;
			}
		};

		Item *getItemId(int itemId)
		{
			if (listSize>0)
			{
				bool found = false;
				currentPtr = startPtr;
				while (currentPtr != NULL)
				{
					if (currentPtr->getEntry()->getId() == itemId) 
					{
						found = true;
						break;
					}
					currentPtr = currentPtr->getNextPtr();
				}
				if (found) return (currentPtr->getEntry());
			}
			return (NULL);
		};

		void removeItemId(int itemId)
		{
			if (listSize>0)
			{
				bool found = false;
				ItemEntry *previousPtr = NULL;
				currentPtr = startPtr;
				while (currentPtr != NULL)
				{
					if (currentPtr->getEntry()->getId() == itemId) 
					{
						found = true;
						break;
					}
					previousPtr = currentPtr;
					currentPtr = currentPtr->getNextPtr();
				}
				if (found) 
				{
					if (currentPtr == startPtr)
					{
						if (startPtr->getNextPtr() == NULL) startPtr = NULL;
						else startPtr = currentPtr->getNextPtr();
					}
					else
					{
						previousPtr->setNextPtr(currentPtr->getNextPtr());
					}
					listSize--;
					printf("List size decreased now %d\n",listSize);
					delete currentPtr;
				}
			}
		};
		
		int printList()
		{
			currentPtr = startPtr;
			int count = 0;
			while (currentPtr != NULL)
			{
				printf("Entry %d value : %d\n", count, currentPtr->getEntry()->getId());
				currentPtr = currentPtr->getNextPtr();
				count++;
			}
			return count;
		}
		
		

		int getListSize()
		{
			return listSize;
		};
};

#endif
