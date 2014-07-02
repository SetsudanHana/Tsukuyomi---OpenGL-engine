#include "stdafx.h"

#include "GBuffer.h"

GBuffer::GBuffer()
{

}

GBuffer::GBuffer(const GBuffer&)
{

}

GBuffer::~GBuffer()
{
	std::stringstream out;
	out << "GBuffer deleted, id: " << m_fbo;
	Logger::getInstance()->write(out.str());
	glDeleteFramebuffers(1, &m_fbo);
}

bool GBuffer::Init(const unsigned& windowWidth, const unsigned& windowHeight)
{

	glGenFramebuffers(1, &m_fbo);
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_fbo);

	Logger::getInstance()->write("GBuffer generated, id: " + m_fbo);

	glGenTextures(GBUFFER_NUM_TEXTURES, m_textures);
	glGenTextures(1, &m_depthTexture);

	Logger::getInstance()->write("Textures for GBuffer generated");

	for (unsigned int i = 0 ; i < GBUFFER_NUM_TEXTURES ; i++) {
		glBindTexture(GL_TEXTURE_2D, m_textures[i]);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB32F, windowWidth, windowHeight, 0, GL_RGB, GL_FLOAT, NULL);
		glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, GL_TEXTURE_2D, m_textures[i], 0);
	}

	glBindTexture(GL_TEXTURE_2D, m_depthTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32F, windowWidth, windowHeight, 0, GL_DEPTH_COMPONENT, GL_FLOAT,
		NULL);
	glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, m_depthTexture, 0);

	GLenum DrawBuffers[] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2, GL_COLOR_ATTACHMENT3 };
	glDrawBuffers(GBUFFER_NUM_TEXTURES, DrawBuffers);

	GLenum Status = glCheckFramebufferStatus(GL_FRAMEBUFFER);

	if (Status != GL_FRAMEBUFFER_COMPLETE) {
		Logger::getInstance()->write("GBuffer building error, id: " + Status);
		return false;
	}

	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);

	return true;
}

void GBuffer::BindForReading()
{
	glBindFramebuffer(GL_READ_FRAMEBUFFER, m_fbo);
}

void GBuffer::BindForWriting()
{
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_fbo);
}

void GBuffer::SetReadBuffer(const GBUFFER_TEXUTRE_TYPE& type)
{
	glReadBuffer(GL_COLOR_ATTACHMENT0 + type);
}

