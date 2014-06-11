#pragma once

#include "stdafx.h"

#include "TextureDeleter.h"

class Texture
{
public:

	Texture();
	Texture(const UINT&);
	Texture(const Texture&);
	~Texture();

	UINT getTextureId();

private:

	UINT m_id;
};