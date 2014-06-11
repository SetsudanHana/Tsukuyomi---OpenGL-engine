#pragma once

#include "stdafx.h"
#include "Window.h"

class OGL
{
public:
	OGL();
	OGL(const OGL&);
	~OGL();

	bool init(Window*);
	SDL_GLContext getGLContext();
	void enableDebug();

private:

	static void APIENTRY ErrorCallback(GLenum _source, GLenum _type, GLuint _id, GLenum _severity, GLsizei _length, const char* _message, void* _userParam)
	{
		Logger::getInstance()->write(_message);
	}

private:
	SDL_GLContext m_glContext;
};