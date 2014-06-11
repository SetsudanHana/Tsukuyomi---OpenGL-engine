#include "stdafx.h"

#include "Texture.h"

Texture::Texture()
{

}

Texture::Texture(const UINT& id)
{
	TextureDeleter::instance()->add(id);
	m_id = id;

}

Texture::Texture(const Texture& other)
{
	m_id = other.m_id;
}

Texture::~Texture()
{

}

UINT Texture::getTextureId()
{
	return m_id;
}