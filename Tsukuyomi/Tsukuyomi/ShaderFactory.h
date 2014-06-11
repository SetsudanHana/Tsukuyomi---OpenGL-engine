#pragma once

#include "stdafx.h"

#include "ResourceManager.h"
#include "Shader.h"

class ShaderFactory
{
public:

	ShaderFactory();
	ShaderFactory(const ShaderFactory&);
	~ShaderFactory();

	Shader createShader(const std::string&);

private:

	bool checkShaderErrors(const unsigned&);

};