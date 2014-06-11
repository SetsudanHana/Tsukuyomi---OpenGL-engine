#include "stdafx.h"

#include "IndexBufferObject.h"

IndexBufferObject::IndexBufferObject()
{

}

IndexBufferObject::IndexBufferObject(const unsigned& size,unsigned short* indices)
{
	m_type = IndexBufferType::UNSIGNED_SHORT;
	m_size = size;
	glGenBuffers(1, &m_ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size * sizeof(unsigned short), indices, GL_STATIC_DRAW);
	BufferDeleter::instance()->add(m_ibo);

	std::stringstream out;
	out << "IndexBufferObject created! Id: " << m_ibo;
	Logger::getInstance()->write(out.str());

}

IndexBufferObject::IndexBufferObject(const unsigned& size,unsigned* indices)
{
	m_type = IndexBufferType::UNSIGNED_INT;
	m_size = size;
	glGenBuffers(1, &m_ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size * sizeof(unsigned), indices, GL_STATIC_DRAW);
	BufferDeleter::instance()->add(m_ibo);

	std::stringstream out;
	out << "IndexBufferObject created! Id: " << m_ibo;
	Logger::getInstance()->write(out.str());
}

IndexBufferObject::IndexBufferObject(const IndexBufferObject& other)
{
	m_size = other.m_size;
	m_ibo = other.m_ibo;
	m_type = other.m_type;
}

IndexBufferObject::~IndexBufferObject()
{

}

unsigned IndexBufferObject::getIBO()
{
	return m_ibo;
}

unsigned IndexBufferObject::getSize()
{
	return m_size;
}

IndexBufferType IndexBufferObject::getType()
{
	return m_type;
}
