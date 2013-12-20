/*
#define _CRT_SECURE_NO_WARNINGS

//   Test program for TinyXML.


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

//printf("[img]:%s\n", node->FirstChild("img_resources")->FirstChild("img")->ToElement()->GetText());
//printf("[imgsrc]:%s\n", node->FirstChild("img_resources")->FirstChild("img")->ToElement()->Attribute("src"));
//printf("[sprites]:%s\n", node->FirstChild("img_resources")->FirstChild("img")->ToElement()->Attribute("sprites"));


void ParseImageResources(MapData* parsedData, TiXmlNode* parent)
{
    TiXmlNode* node = parent->FirstChild("img_resources")->FirstChild("img");
    
    while (node != NULL) {
        ImageResource* nImg = new ImageResource();
        TiXmlElement* element = node->ToElement();
        
        strcpy(nImg->imgname, element->GetText());
        strcpy(nImg->imgsrc, element->Attribute("src"));
        
        nImg->width = atoi(element->Attribute("width"));
        nImg->height = atoi(element->Attribute("height"));
        nImg->sprites = atoi(element->Attribute("sprites"));
        
        printf("%s %s %d %d %d\n", nImg->imgname, nImg->imgsrc, nImg->width, nImg->height, nImg->sprites);
        
        parsedData->mImageResourceList.push_back(nImg);
        
        node = node->NextSibling();
    }
    
    printf("saved vector size: %lu\n", parsedData->mImageResourceList.size());
}

void ParseBackgroundFarResources(MapData* parsedData, TiXmlNode* parent)
{
    TiXmlNode* node = parent->FirstChild("background_far_resources")->FirstChild("background_far");
    
    while (node != NULL) {
        BackgroundFar* nBgf = new BackgroundFar();
        TiXmlElement* element = node->ToElement();
        
        strcpy(nBgf->imgname, element->GetText());
        nBgf->pos_x = atoi(element->Attribute("pos_x"));
        nBgf->pos_y = atoi(element->Attribute("pos_y"));
        nBgf->speed = atof(element->Attribute("speed"));
        
        printf("%s %d %d %f\n", nBgf->imgname, nBgf->pos_x, nBgf->pos_y, nBgf->speed);
        parsedData->mBackgroundFarList.push_back(nBgf);
        
        node = node->NextSibling();
    }
    
    printf("saved vector size: %lu\n", parsedData->mImageResourceList.size());
}

void ParseBackgroundNearResources(MapData* parsedData, TiXmlNode* parent)
{
    TiXmlNode* node = parent->FirstChild("background_near_resources")->FirstChild("background_near");
    
    while (node != NULL) {
        BackgroundNear* nBgn = new BackgroundNear();
        TiXmlElement* element = node->ToElement();
        
        strcpy(nBgn->imgname, element->GetText());
        nBgn->pos_x = atoi(element->Attribute("pos_x"));
        nBgn->pos_y = atoi(element->Attribute("pos_y"));
        
        printf("%s %d %d\n", nBgn->imgname, nBgn->pos_x, nBgn->pos_y);
        parsedData->mBackgroundNearList.push_back(nBgn);
        
        node = node->NextSibling();
    }
    
    printf("saved vector size: %lu\n", parsedData->mImageResourceList.size());
}

void ParseGroundObjectResources(MapData* parsedData, TiXmlNode* parent)
{
    TiXmlNode* node = parent->FirstChild("objectground_resources")->FirstChild("background_near");
    
    while (node != NULL) {
        GroundObject* nGro = new GroundObject();
        TiXmlElement* element = node->ToElement();
        
        strcpy(nGro->imgname, element->GetText());
        nGro->pos_x = atoi(element->Attribute("pos_x"));
        nGro->pos_y = atoi(element->Attribute("pos_y"));
        
        printf("%s %d %d\n", nGro->imgname, nGro->pos_x, nGro->pos_y);
        parsedData->mGroundObjectList.push_back(nGro);
        
        node = node->NextSibling();
    }
    
    printf("saved vector size: %lu\n", parsedData->mImageResourceList.size());
}

void ParseForegroundObjectResources(MapData* parsedData, TiXmlNode* parent)
{
    TiXmlNode* node = parent->FirstChild("background_far_resources")->FirstChild("background_far");
    
    while (node != NULL) {
        Foreground* nFgf = new Foreground();
        TiXmlElement* element = node->ToElement();
        
        strcpy(nFgf->imgname, element->GetText());
        nFgf->pos_x = atoi(element->Attribute("pos_x"));
        nFgf->pos_y = atoi(element->Attribute("pos_y"));
        nFgf->speed = atof(element->Attribute("speed"));
        
        printf("%s %d %d %f\n", nFgf->imgname, nFgf->pos_x, nFgf->pos_y, nFgf->speed);
        parsedData->mForegroundList.push_back(nFgf);
        
        node = node->NextSibling();
    }
    
    printf("saved vector size: %lu\n", parsedData->mImageResourceList.size());
}

void ParseMapData(const char* xmlpath, MapData* parsedData)
{
    TiXmlDocument doc(xmlpath);
    
    bool loadOkay = doc.LoadFile();
    if (loadOkay) {
        printf("\n%s:\n", xmlpath);
        TiXmlNode* node = doc.FirstChild("map");
        
        if (node != NULL) {
            ParseImageResources(parsedData, node);
            ParseBackgroundFarResources(parsedData, node);
            ParseBackgroundNearResources(parsedData, node);
            ParseForegroundObjectResources(parsedData, node);
            
        } else {
            fprintf(stderr, "first child of this document returned null\n");
        }
        
    } else {
        fprintf(stderr, "filaed to load %s\n", xmlpath);
    }
}

int main(int argc, char** argv)
{
    if (argc < 2) {
        fprintf(stderr, "./xmltest filename");
        return 0;
    }
    
    MapData* mdata = new MapData();
    ParseMapData(argv[1], mdata);
    
    return 0;
}
*/