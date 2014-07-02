#include "stdafx.h"

#include "Window.h"

Window::Window()
{
	m_window = 0;
	m_height = 0;
	m_width = 0;
}

Window::Window(const Window& wnd)
{
	m_window = wnd.m_window;
}

Window::~Window()
{
	Logger::getInstance()->write("SDLwindow deleted");
	SDL_Quit();
}

SDL_Window* Window::getWindow()
{
	return m_window;
}

bool Window::createWindow(const unsigned& width,const unsigned& height)
{
	m_height = height;
	m_width = width;

	m_window = SDL_CreateWindow("Tsukuyomi", m_width/2, m_height/2, m_width, m_height, SDL_WINDOW_OPENGL);

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

unsigned Window::getHeight()
{
	return m_height;
}

unsigned Window::getWidth()
{
	return m_width;
}