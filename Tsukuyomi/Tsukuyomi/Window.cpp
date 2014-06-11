#include "stdafx.h"

#include "Window.h"

Window::Window()
{
	m_window = 0;
}

Window::Window(const Window& wnd)
{
	m_window = wnd.m_window;
}

Window::~Window()
{
	SDL_Quit();
}

SDL_Window* Window::getWindow()
{
	return m_window;
}

bool Window::createWindow()
{
	m_window = SDL_CreateWindow("Tsukuyomi", 200, 200, 800, 600, SDL_WINDOW_OPENGL);

	if(!m_window)
	{
		std::string error(SDL_GetError());
		Logger::getInstance()->write("SDL2 window creating error: " + error);
		return false;
	}
	else
	{
		Logger::getInstance()->write("SDL2 window created");
	}

	return true;
}