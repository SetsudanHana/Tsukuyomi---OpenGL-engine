#pragma once

#include "stdafx.h"

#include "ShaderDeleter.h"

class Shader
{
public:
	Shader();
	Shader(unsigned);
	Shader(const Shader&);
	~Shader();

	void setProgramme(unsigned);
	unsigned getProgramme();
	
	void useProgram();

	void setField(const float&, const std::string&);
	void setSampler(const UINT&, const std::string&);
	void setVector2(const glm::vec2&, const std::string&);
	void setVector3(const glm::vec3&, const std::string&);
	void setVector4(const glm::vec4&, const std::string&);
	void setMatrix2(const glm::mat2&, const std::string&);
	void setMatrix3(const glm::mat3&, const std::string&);
	void setMatrix4(const glm::mat4&, const std::string&);

private:
	unsigned int m_programme;
};