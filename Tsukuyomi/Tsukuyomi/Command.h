#pragma once

#include "stdafx.h"

class Command
{
public:
	Command();
	Command(const Command&);
	~Command();

	void setFunction(std::function<void(void)>);
	void execute();

private:
	std::function<void(void)> m_function;
};