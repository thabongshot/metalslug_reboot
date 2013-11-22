#ifndef _MAINCOMPONENT_H_
#define _MAINCOMPONENT_H_

enum MSGTYPE
{
	MSG_QUIT
};

class MainComponent
{
private:
	static bool closeRequested;

public:
	MainComponent(int *argc, char **argv);

	void init(int *argc, char** argv);

	void initDevIL();

	void initCallbacks();

	void run();

	void update();

	void render();

	void cleanUp();

	static void postMsg(MSGTYPE msg);
};

#endif