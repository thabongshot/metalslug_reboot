#ifndef _TIMER_H_
#define _TIMER_H_

class Timer {
private:
	int m_startTicks, m_pausedTicks;
	bool b_started, b_paused;

public:
	Timer();
	Timer(const Timer &other);
	~Timer();

	int GetElapsedTime();

	int GetDeltaTime();

	int GetPausedTime();

	void Start();

	void Stop();

	void Pause();

	void Resume();

	void Update();
};

#endif