#pragma once

#include "stdafx.h"

#include "TextureDeleter.h"
#include "Logger.h"

class TextureDeleter
{
public:

	~TextureDeleter();

	static TextureDeleter* instance()
	{
		static TextureDeleter instance;
		return &instance;
	}

	void add(const UINT&);
	void release();

private:

	TextureDeleter();
	TextureDeleter(const TextureDeleter&);

private:

	std::vector<UINT> m_elements;
};