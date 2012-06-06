/***************************************************************************
 * file:        GraphFileCreator.h
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

#ifndef GRAPH_FILE_CREATOR_H
#define GRAPH_FILE_CREATOR_H

#include<stdio.h>

#include <iostream>
#include <sstream>
#include <fstream>
#include <cstring>

#include<string.h>
#include<cstdlib>

#include "Node.h"

#define MAX_PATH_LENGTH 255

class FileCreator
{
	protected:
		std::ofstream 	outputFileStream;
		char			filePath[MAX_PATH_LENGTH];

	public:
		FileCreator(){};

		bool openFile()
		{
			outputFileStream.open(filePath);
			return outputFileStream;
		}

		bool openFileAppend()
		{
			outputFileStream.open(filePath, std::ios::out|std::ios::app);
			return outputFileStream;
		}

		bool setFilePath(const char fPath[])
		{
			if ( strlen(fPath) > MAX_PATH_LENGTH ) return false;
			else strcpy(filePath, fPath);

			return true;
		}
		

		bool closeFile()
		{
			outputFileStream.close();
			return true;
		}
		
		void flushIt()
		{
			outputFileStream.flush();
		}
		
};

class GraphFileCreator : public FileCreator
{
	protected:
		NodeList *nodeListPtr;

	public:
		GraphFileCreator()
		{
			nodeListPtr = NULL;
		};

		void setNodeListPtr(NodeList *nListPtr)
		{
			nodeListPtr = nListPtr;
		};

		NodeList *getNodeListPtr()
		{
			return nodeListPtr;
		};
        
		std::string generateForwarderNodeString(bool forwarderNode)
		{
			std::ostringstream message;
			if (forwarderNode) message << "style=filled";
			return message.str();
		}
        
		bool compileGraphFile()
		{
			char command[255];
			char pictureOutputFile[255];
			
			strcpy(command,"neato -Tps ");
			strcat(command, filePath);
			strcat(command," -o ");
			
			strcpy(pictureOutputFile,filePath);
			char *fExtention = strstr(pictureOutputFile,".dot");
			
			if (fExtention == NULL) return false;
			else
			{
				strcpy(fExtention, ".eps");
				strcat(command, pictureOutputFile);
				system(command);
			}
			return true;
		}
};

#endif
