#ifndef _WINDOW_H_
#define _WINDOW_H_

class Window
{
private:
	Window();

public:
	static void createWindow(int width, int height, const char *title);
};

#endif