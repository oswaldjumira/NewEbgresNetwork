/***************************************************************************
 * file:        SystemController.h
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
 * part of:     Cluster Head Gateway Routing Protocol Simulation
 * description: - The performance module provides a mechanism to publish performance data of the protocol
 *
 ***************************************************************************
 * changelog:   $Revision: 382 $
 *              last modified:   $Date: 2006-07-31 16:10:24 +0200 (Mo, 31 Jul 2006) $
 *              by:              $Author: koepke $
 ***************************************************************************/

#ifndef SYSTEM_CONTROLLER_H
#define SYSTEM_CONTROLLER_H

#include<stdio.h>
#include<string.h>
#include<cstdlib>

class SystemController
{
	protected:
		char baseDirectory[255];
		
	public:
		SystemController()
		{
		}
		
		char *getBaseDirectory()
		{
			return baseDirectory;
		}
		
		void setBaseDirectory(char bDirectory[])
		{
			strcpy(baseDirectory, bDirectory);
		}
		
		void createDirectory(char directory[])
		{
			char command[255];
			strcpy(command, "mkdir ");
			strcat(command, baseDirectory);
			strcat(command, directory);
			system(command);
		}
};

#endif
