#include "stdafx.h"

#include "Shader.h"

Shader::Shader()
{

}

Shader::Shader(unsigned programme)
{
	ShaderDeleter::instance()->add( programme );
	m_programme = programme;
}

Shader::Shader(const Shader& other)
{
	m_programme = other.m_programme;
}

Shader::~Shader()
{

}

void Shader::setProgramme(unsigned programme)
{
	m_programme = programme;
}

unsigned Shader::getProgramme()
{
	return m_programme;
}

void Shader::setSampler(const UINT& sampler, const std::string& name)
{
	glActiveTexture(GL_TEXTURE0 + sampler);
	GLint tmp = glGetUniformLocation(m_programme, name.c_str());
	if(tmp == -1)
	{
		std::string output = "Attaching Sampler that doesnt exist, " + name;
		Logger::getInstance()->write(output);
	}
	glUniform1i(tmp, sampler);
}

void Shader::setField(const float& val, const std::string& name)
{
	GLint tmp = glGetUniformLocation(m_programme, name.c_str());
	if(tmp == -1)
	{
		std::string output = "Attaching Field that doesnt exist, " + name;
		Logger::getInstance()->write(output);
	}
	glUniform1f(tmp, val);
}

void Shader::setVector2(const glm::vec2& vec, const std::string& name)
{
	GLint tmp = glGetUniformLocation(m_programme, name.c_str());
	if(tmp == -1)
	{
		std::string output = "Attaching vec2 that doesnt exist, " + name;
		Logger::getInstance()->write(output);
	}
	glUniform2fv(tmp, 1, glm::value_ptr(vec));
}

void Shader::setVector3(const glm::vec3& vec, const std::string& name)
{
	GLint tmp = glGetUniformLocation(m_programme, name.c_str());
	if(tmp == -1)
	{
		std::string output = "Attaching vec3 that doesnt exist, " + name;
		Logger::getInstance()->write(output);
	}
	glUniform3fv(tmp, 1, glm::value_ptr(vec));
}

void Shader::setVector4(const glm::vec4& vec, const std::string& name)
{
	GLint tmp = glGetUniformLocation(m_programme, name.c_str());
	if(tmp == -1)
	{
		std::string output = "Attaching vec4 that doesnt exist, " + name;
		Logger::getInstance()->write(output);
	}
	glUniform4fv(tmp, 1, glm::value_ptr(vec));
}

void Shader::setMatrix2(const glm::mat2& mat, const std::string& name)
{
	GLint tmp = glGetUniformLocation(m_programme, name.c_str());
	if(tmp == -1)
	{
		std::string output = "Attaching mat2 that doesnt exist, " + name;
		Logger::getInstance()->write(output);
	}
	glUniformMatrix2fv(tmp, 1, GL_FALSE, glm::value_ptr(mat));
}

void Shader::setMatrix3(const glm::mat3& mat, const std::string& name)
{
	GLint tmp = glGetUniformLocation(m_programme, name.c_str());
	if(tmp == -1)
	{
		std::string output = "Attaching mat3 that doesnt exist, " + name;
		Logger::getInstance()->write(output);
	}
	glUniformMatrix3fv(tmp, 1, GL_FALSE, glm::value_ptr(mat));
}

void Shader::setMatrix4(const glm::mat4& mat, const std::string& name)
{
	GLint tmp = glGetUniformLocation(m_programme, name.c_str());
	if(tmp == -1)
	{
		std::string output = "Attaching mat4 that doesnt exist, " + name;
		Logger::getInstance()->write(output);
	}
	glUniformMatrix4fv(tmp, 1, GL_FALSE, glm::value_ptr(mat));
}