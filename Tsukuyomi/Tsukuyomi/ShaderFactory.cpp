#include "stdafx.h"

#include "ShaderFactory.h"

ShaderFactory::ShaderFactory()
{

}

ShaderFactory::ShaderFactory(const ShaderFactory&)
{

}

ShaderFactory::~ShaderFactory()
{

}

Shader ShaderFactory::createShader(const std::string& name)
{
	std::string vs_container = ResourceManager::instance()->loadTextFile(SHADER_PATH + name + ".vs");

	if(vs_container == "")
	{
		Logger::getInstance()->write("VertexShader " + name + ": failed to read file");
		return 0;
	}

	std::string fs_container = ResourceManager::instance()->loadTextFile(SHADER_PATH + name + ".fs");

	if(fs_container == "")
	{
		Logger::getInstance()->write("FragmentShader " + name + ": failed to read file");
		return 0;
	}

	const char* vertex_shader = vs_container.c_str();
	const char* fragment_shader = fs_container.c_str();

	GLint lenVS = vs_container.length();
	GLint lenFS = fs_container.length();

	unsigned int vs = glCreateShader (GL_VERTEX_SHADER);
	unsigned int fs = glCreateShader (GL_FRAGMENT_SHADER);
	glShaderSource (vs, 1, &vertex_shader, &lenVS);
	glCompileShader (vs);
	glShaderSource (fs, 1, &fragment_shader, &lenFS);
	glCompileShader (fs);

	bool result = true;

	result = checkShaderErrors(vs);

	if(!result)
	{
		Logger::getInstance()->write("VertexShader " + name + " compiled with errors");
		return 0;
	}

	result = checkShaderErrors(fs);

	if(!result)
	{
		Logger::getInstance()->write("FragmentShader " + name + " compiled with errors");
		return 0;
	}

	unsigned int shader_programme = glCreateProgram();
	glAttachShader (shader_programme, fs);
	glAttachShader (shader_programme, vs);
	glLinkProgram (shader_programme);

	std::stringstream out;
	out << "Created Shader id: " << shader_programme;
	Logger::getInstance()->write( out.str() );

	return Shader(shader_programme);

}

bool ShaderFactory::checkShaderErrors(const unsigned& shaderID)
{
	GLint blen = 0;
	GLsizei slen = 0;

	glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &blen);

	if (blen > 1)
	{
		GLchar* compiler_log = (GLchar*)malloc(blen);

		glGetInfoLogARB(shaderID, blen, &slen, compiler_log);
		std::string out = std::string("\ncompiler_log:\n") + compiler_log;
		Logger::getInstance()->write(out);
		free(compiler_log);
		return false;
	}
	return true;
}