#pragma once

#include "stdafx.h"

#include "Input.h"
#include "Logger.h"

class EventCatcher
{
public:

	EventCatcher();
	EventCatcher(const EventCatcher&);
	~EventCatcher();

	bool catchEvents();

	void setInput(Input* input);

private:

	Input* m_input;
	SDL_Event m_event;
};