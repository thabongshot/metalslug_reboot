#ifndef OBJECT_DATA_H
#define OBJECT_DATA_H

#include <cstring>
#include <vector>

using namespace std;

class ImageResource {
public:
    char imgname[64];
    char imgsrc[512];
    int width;
    int height;
    int sprites;
};

class ObjectBase {
public:
    char imgname[64];
    int pos_x;
    int pos_y;
};

class BackgroundFar : public ObjectBase {
public:
    float speed;
    // attribs ...
};

class BackgroundNear : public ObjectBase {
public:
    int cover;
    // attribs ...
};

class GroundObject : public ObjectBase {
public:
    // attribs ...
};

class Foreground : public ObjectBase {
public:
    // attribs ...
    float speed;
};

class MapData {
    public:
    vector<ImageResource*> mImageResourceList;
    vector<BackgroundFar*> mBackgroundFarList;
    vector<BackgroundNear*> mBackgroundNearList;
    vector<GroundObject*> mGroundObjectList;
    vector<Foreground*> mForegroundList;
};

#endif