#pragma once

#include "stdafx.h"

class Timer
{
public:
	Timer();
	Timer(const Timer&);
	~Timer();

	void start(std::chrono::milliseconds&);
	std::chrono::microseconds getTime();
	bool check();
	bool isStarted();

private:
	std::chrono::time_point<std::chrono::system_clock> m_clock;
	std::chrono::microseconds m_time;
	bool m_started;
};