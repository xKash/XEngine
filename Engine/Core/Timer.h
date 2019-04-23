#ifndef TIMER_H
#define TIMER_H

#include <SDL.h>

class Timer {
public:
	Timer();
	~Timer();

	// Make impossible do instantiate this class outside of the egine
	Timer(const Timer&) = delete;
	Timer(Timer&&) = delete;
	Timer& operator=(const Timer&) = delete;
	Timer& operator=(Timer&&) = delete;

	void Start();
	void Update();
	float GetDeltaTime() const;
	unsigned int GetSleepTime(const unsigned int fps_) const;
	float GetCurrentTicks() const;
private:
	unsigned int prevTicks;
	unsigned int currentTicks;
};
#endif // !TIMER_H

