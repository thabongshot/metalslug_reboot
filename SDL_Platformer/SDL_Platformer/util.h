#ifndef UTIL_H
#define UTIL_H

#define _CRT_SECURE_NO_WARNINGS

/*
   Test program for TinyXML.
*/


#ifdef TIXML_USE_STL
	#include <iostream>
	#include <sstream>
	using namespace std;
#else
	#include <stdio.h>
#endif

#if defined( WIN32 ) && defined( TUNE )
	#include <crtdbg.h>
	_CrtMemState startMemState;
	_CrtMemState endMemState;
#endif

#include "tinyxml.h"
#include "objectdata.h"

void ParseImageResources(MapData* parsedData, TiXmlNode* parent);

void ParseBackgroundFarResources(MapData* parsedData, TiXmlNode* parent);

void ParseBackgroundNearResources(MapData* parsedData, TiXmlNode* parent);

void ParseGroundObjectResources(MapData* parsedData, TiXmlNode* parent);

void ParseForegroundObjectResources(MapData* parsedData, TiXmlNode* parent);

void ParseMapData(const char* xmlpath, MapData* parsedData);

#endif