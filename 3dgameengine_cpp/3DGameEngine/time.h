#ifndef _TIME_H_
#define _TIME_H_

#define SECOND 1000.0

class Time
{
private:
	static double delta;

public:
	static double getTime();

	static double getDelta();

	static void setDelta(double _delta);
};

#endif