#include "timer.h"

#include <SDL_timer.h>

Timer::Timer() {
	m_startTicks = 0;
	m_pausedTicks = 0;
	b_started = false;
	b_paused = false;
}

Timer::Timer(const Timer &other) {
	m_startTicks = other.m_startTicks;
	m_pausedTicks = other.m_pausedTicks;
	b_started = other.b_started;
	b_paused = other.b_paused;
}

Timer::~Timer() {

}

int Timer::GetElapsedTime() {
	return SDL_GetTicks();
}

int Timer::GetDeltaTime() {
	if(b_started && !b_paused) {
		int currTicks = SDL_GetTicks();

		int result = currTicks - m_startTicks;

		return result;
	}
	else
		return 0;
}

int Timer::GetPausedTime() {
	if(b_started && b_paused) {
		int currTicks = SDL_GetTicks();

		return currTicks - m_pausedTicks;
	}
	else
		return 0;
}

void Timer::Start() {
	b_started = true;
	b_paused = false;

	m_startTicks = SDL_GetTicks();
}

void Timer::Stop() {
	b_started = false;
}

void Timer::Pause() {
	if(b_started && !b_paused) {
		b_paused = true;
		m_pausedTicks = SDL_GetTicks();
	}
}

void Timer::Resume() {
	if(b_started && b_paused) {
		b_paused = false;
		m_startTicks = SDL_GetTicks();
	}
}

void Timer::Update() {
	m_startTicks = SDL_GetTicks();
}