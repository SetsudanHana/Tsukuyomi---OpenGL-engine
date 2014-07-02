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
	bool createWindow(const unsigned& = 800,const unsigned& = 600);

	unsigned getHeight();
	unsigned getWidth();

private:
	SDL_Window* m_window;
	unsigned m_width;
	unsigned m_height;
};