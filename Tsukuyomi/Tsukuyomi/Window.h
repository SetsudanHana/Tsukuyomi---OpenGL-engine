#pragma once

#include "Logger.h"
#include "Input.h"

class Window
{
public:
	Window();
	Window(const Window&);
	~Window();

	SDL_Window* getWindow();
	bool createWindow();

private:
	SDL_Window* m_window;
};