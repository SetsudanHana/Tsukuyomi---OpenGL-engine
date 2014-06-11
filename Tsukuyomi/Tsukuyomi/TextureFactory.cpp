#include "stdafx.h"

#include "TextureFactory.h"

TextureFactory::TextureFactory()
{

}

TextureFactory::TextureFactory(const TextureFactory&)
{

}

TextureFactory::~TextureFactory()
{

}

Texture TextureFactory::createTexture(const std::string& name)
{
	UINT tmp = ResourceManager::instance()->loadTexture(TEXTURE_PATH + name);

	if(tmp == UINT_MAX)
	{
		std::stringstream out;
		out << "Texture " << name << " failed to create";
		Logger::getInstance()->write(out.str());
		return 0;
	}
	else
	{
		std::stringstream out;
		out << "TextureObject id: " << tmp << " created";
		Logger::getInstance()->write(out.str());
		return Texture(tmp);
	}

}