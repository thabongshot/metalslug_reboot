#include <tchar.h>
#include <vector>

using namespace std;

class ObjectBase {
public:
	TCHAR* imgsrc;
	int pos_x;
	int pos_y;
	int width;
	int height;
};

class BackgroundFar : ObjectBase {
public:
	bool animation;
	// attribs ...
};


class BackgroundNear : ObjectBase {
public:	
	bool animation;
	// attribs ...
};


class MapObject : ObjectBase {
public:
	int damage;
	// attribs ...
};


class Foreground : ObjectBase {
public:
	// attribs ...
};


class MapDataCollection {
public:
	vector<BackgroundFar> vBackGroundFar;
	vector<BackgroundNear> vBackgroundNear;
	vector<MapObject> vMapObject;
	vector<Foreground> vForeground;
};
