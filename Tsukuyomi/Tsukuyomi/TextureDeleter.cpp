#include "stdafx.h"

#include "TextureDeleter.h"

TextureDeleter::TextureDeleter()
{

}

TextureDeleter::TextureDeleter(const TextureDeleter&)
{

}

TextureDeleter::~TextureDeleter()
{

}

void TextureDeleter::add(const UINT& id)
{
	m_elements.push_back(id);
}

void TextureDeleter::release()
{
	for(auto i : m_elements)
	{
		glDeleteTextures(1, &i);
		std::stringstream out;
		out << "Texture id " << i << " released";
		Logger::getInstance()->write(out.str());
	}
}