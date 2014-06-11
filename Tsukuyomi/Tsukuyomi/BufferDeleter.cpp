#include "stdafx.h"

#include "BufferDeleter.h"

BufferDeleter::BufferDeleter()
{

}

BufferDeleter::BufferDeleter(const BufferDeleter&)
{

}

BufferDeleter::~BufferDeleter()
{

}

void BufferDeleter::add(const unsigned& index, const bool& isArray /* = false */)
{
	if( isArray )
		m_arrays.push_back(index);
	else
		m_buffers.push_back(index);
}

void BufferDeleter::release()
{
	for(auto i : m_arrays)
	{
		glDeleteVertexArrays(1, &i);
		std::stringstream out;
		out << "VertexArray released! Id: " << i;
		Logger::getInstance()->write(out.str());
	}
	for(auto i : m_buffers)
	{
		glDeleteBuffers(1, &i);
		std::stringstream out;
		out << "VertexBuffer/IndexBuffer released! Id: " << i;
		Logger::getInstance()->write(out.str());
	}
}