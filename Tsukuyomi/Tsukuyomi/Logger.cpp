#include "stdafx.h"

#include "Logger.h"

Logger::Logger()
{
	file = std::ofstream("logfile.txt", std::ofstream::out);
}

Logger::Logger(const Logger&)
{

}

Logger::~Logger()
{
	file.close();
}

void Logger::write(const std::string& message)
{
	auto now = std::chrono::system_clock::now();
	auto t = std::chrono::system_clock::to_time_t(now);
	char data[30];
	ctime_s(data, 30, &t);
	std::string out(data);
	file << out.substr(0, out.size()-1) << " - " << message << std::endl;
	return;
}