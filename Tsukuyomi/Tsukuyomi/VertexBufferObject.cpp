#include "stdafx.h"

#include "VertexBufferObject.h"

VertexBufferObject::VertexBufferObject()
{

}

VertexBufferObject::VertexBufferObject(const unsigned& size, float points[], const VertexBufferType& type)
{
	m_size = size;
	m_type = type;
	glGenBuffers (1, &m_vbo);
	glBindBuffer (GL_ARRAY_BUFFER, m_vbo);

	switch( type )
	{
	case TEXTURE_COORDS:
	case POSITION_2:
		glBufferData (GL_ARRAY_BUFFER, 2 * size * sizeof (float), points, GL_STATIC_DRAW);
		break;
	case POSITION_3:
	case NORMALS:
		glBufferData (GL_ARRAY_BUFFER, 3 * size * sizeof (float), points, GL_STATIC_DRAW);
		break;
	}

	BufferDeleter::instance()->add(m_vbo);

	std::stringstream out;
	out << "VertexBuffer created! Id: " << m_vbo;
	Logger::getInstance()->write(out.str());
}

VertexBufferObject::VertexBufferObject(const VertexBufferObject& other)
{
	m_vbo = other.m_vbo;
	m_type = other.m_type;
	m_size = other.m_size;
}

VertexBufferObject::~VertexBufferObject()
{

}

unsigned VertexBufferObject::getVBO()
{
	return m_vbo;
}

VertexBufferType VertexBufferObject::getType()
{
	return m_type;
}

unsigned VertexBufferObject::getSize()
{
	return m_size;
}