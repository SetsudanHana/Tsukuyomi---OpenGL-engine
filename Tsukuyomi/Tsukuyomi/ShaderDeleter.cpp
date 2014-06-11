#include "stdafx.h"

#include "ShaderDeleter.h"

ShaderDeleter::ShaderDeleter()
{

}

ShaderDeleter::ShaderDeleter(const ShaderDeleter&)
{

}

ShaderDeleter::~ShaderDeleter()
{

}

void ShaderDeleter::add(const UINT& id)
{
	m_element.push_back(id);
}

void ShaderDeleter::release()
{
	for(auto i : m_element)
	{
		glDeleteProgram( i );
		std::stringstream out;
		out << "Program id: " << i << " released";
		Logger::getInstance()->write( out.str() );
	}
}