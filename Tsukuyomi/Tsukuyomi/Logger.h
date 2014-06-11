#pragma once

#include "stdafx.h"

class Logger
{
public:
	~Logger();

	static Logger* getInstance()
	{
		static Logger instance;
		return &instance;
	}

	void write(const std::string&);

private:
	Logger();
	Logger(const Logger&);
	std::ofstream file;
};