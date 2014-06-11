#include "stdafx.h"

#include "Command.h"

Command::Command()
{

}

Command::Command(const Command& other)
{
	m_function = other.m_function;
}

Command::~Command()
{

}

void Command::execute()
{
	if(m_function != nullptr)
	{
		m_function();
	}
}

void Command::setFunction(std::function<void(void)> function)
{
	m_function = function;
}