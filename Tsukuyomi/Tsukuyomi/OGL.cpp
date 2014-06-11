#include "stdafx.h"

#include "OGL.h"

OGL::OGL()
{

}

OGL::OGL(const OGL& ogl)
{

}

OGL::~OGL()
{
	glDisable(GL_DEPTH_TEST);
	SDL_GL_DeleteContext(m_glContext);
}

SDL_GLContext OGL::getGLContext()
{
	return m_glContext;
}

bool OGL::init(Window* wnd)
{
	if( wnd->getWindow() == nullptr )
	{
		Logger::getInstance()->write( "SDL2 window is not initialized" );
		return false;
	}

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
	SDL_GL_SetAttribute(SDL_GL_FRAMEBUFFER_SRGB_CAPABLE, 1);

	m_glContext = SDL_GL_CreateContext( wnd->getWindow() );

	if( m_glContext == nullptr )
	{
		Logger::getInstance()->write("Creating openGL context error");
		return false;
	}

	const unsigned char *version = glGetString(GL_VERSION);
	if (version == NULL) 
	{
		Logger::getInstance()->write("Getting OGL version error");
		return false;
	}

	Logger::getInstance()->write((char*) version);

	SDL_GL_MakeCurrent(wnd->getWindow(), m_glContext);

	glewExperimental = true;

	GLenum err = glewInit();

	if( GLEW_OK != err )
	{
		Logger::getInstance()->write( (char*) glewGetErrorString(err) );
		return false;
	}
	Logger::getInstance()->write( (char*) glewGetString(GLEW_VERSION) );

	glEnable(GL_DEPTH_TEST);

	glDepthFunc(GL_LESS);

	return true;
}

void OGL::enableDebug()
{
	if (glDebugMessageCallbackARB != NULL) {
		glDebugMessageCallbackARB(&OGL::ErrorCallback, NULL);
		glEnable(GL_DEBUG_OUTPUT);
	}
}