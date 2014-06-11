#include "stdafx.h"

#include "VertexArrayObject.h"

VertexArrayObject::VertexArrayObject()
{
	m_vao = 0;
	glGenVertexArrays (1, &m_vao);
	BufferDeleter::instance()->add(m_vao, true);

	std::stringstream out;
	out << "VertexArray created! Id: " << m_vao;
	Logger::getInstance()->write(out.str());
}

VertexArrayObject::VertexArrayObject(const VertexArrayObject& other)
{
	m_vao = other.m_vao;
}

VertexArrayObject::~VertexArrayObject()
{
	
}

unsigned VertexArrayObject::getVAO()
{
	return m_vao;
}

void VertexArrayObject::bindVBO(VertexBufferObject& vbo, const VertexBufferType& type)
{
	glBindVertexArray (m_vao);
	glBindBuffer (GL_ARRAY_BUFFER, vbo.getVBO());

	switch( type )
	{
	case TEXTURE_COORDS:
	case POSITION_2:
		glVertexAttribPointer (type, 2, GL_FLOAT, GL_FALSE, 0, NULL);
		break;
	case POSITION_3:
	case NORMALS:
		glVertexAttribPointer (type, 3, GL_FLOAT, GL_FALSE, 0, NULL);
		break;
	}
	
	std::stringstream out;
	out << "VertexBuffer id: " << vbo.getVBO() << " binded to VertexArray id: " << m_vao;
	Logger::getInstance()->write(out.str());

	enableVBO(type);
}

void VertexArrayObject::enableVBO(const VertexBufferType& type)
{
	glBindVertexArray (m_vao);
	glEnableVertexAttribArray(type);

	std::stringstream out;
	out << "VertexBufferType: " << type << " enabled in VertexArray id: " << m_vao;
	Logger::getInstance()->write(out.str());
}

void VertexArrayObject::disableVBO(const VertexBufferType& type)
{
	glBindVertexArray (m_vao);
	glDisableVertexAttribArray(type);

	std::stringstream out;
	out << "VertexBufferType: " << type << " enabled in VertexArray id: " << m_vao;
	Logger::getInstance()->write(out.str());
}