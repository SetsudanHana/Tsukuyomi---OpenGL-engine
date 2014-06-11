#include "stdafx.h"

#include "EventCatcher.h"

EventCatcher::EventCatcher()
{
	m_input = nullptr;
}

EventCatcher::EventCatcher(const EventCatcher&)
{

}

EventCatcher::~EventCatcher()
{

}

bool EventCatcher::catchEvents()
{
	if (m_input == nullptr)
	{
		Logger::getInstance()->write("Input instance is not set");
		return false;
	}

	while(SDL_PollEvent(&m_event) != 0)
	{
		if(m_event.type == SDL_QUIT)
		{
			return true;
		}
		else if( m_event.type == SDL_KEYDOWN )
		{
			m_input->pushDown(m_event.key.keysym.scancode);
		}
		else if( m_event.type == SDL_KEYUP )
		{
			m_input->pullUp(m_event.key.keysym.scancode);
		}
	}
	return false;
}

void EventCatcher::setInput(Input* input)
{
	if(input != nullptr)
		m_input = input;
	else
		Logger::getInstance()->write("Trying to add NULL as a Input instance");
}