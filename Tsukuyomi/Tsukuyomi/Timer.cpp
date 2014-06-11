#include "stdafx.h"

#include "Timer.h"

Timer::Timer()
{
	m_started = false;
}

Timer::Timer(const Timer&)
{

}

Timer::~Timer()
{

}

void Timer::start(std::chrono::milliseconds& time)
{
	m_started = true;
	m_clock = std::chrono::system_clock::now();
	m_time = time;
}

bool Timer::check()
{
	std::chrono::microseconds tmp = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now()-m_clock);
	if(tmp >= m_time)
	{
		m_started = false;
		return true;
	}
	return false;

}

std::chrono::microseconds Timer::getTime()
{
	return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now()-m_clock);
}

bool Timer::isStarted()
{
	return m_started;
}