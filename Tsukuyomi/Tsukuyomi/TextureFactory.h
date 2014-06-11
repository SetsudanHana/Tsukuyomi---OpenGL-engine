#pragma once

#include "stdafx.h"

#include "ResourceManager.h"
#include "Texture.h"

class TextureFactory
{
public:

	TextureFactory();
	TextureFactory(const TextureFactory&);
	~TextureFactory();
	
	Texture createTexture(const std::string&);

};