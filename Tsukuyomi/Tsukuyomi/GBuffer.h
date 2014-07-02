#pragma once

#include "stdafx.h"

#include "Logger.h"

class GBuffer
{
public:

	enum GBUFFER_TEXUTRE_TYPE
	{
		GBUFFER_TEXTURE_TYPE_POSITION,
		GBUFFER_TEXTURE_TYPE_DIFFUSE,
		GBUFFER_TEXTURE_TYPE_NORMAL,
		GBUFFER_TEXTURE_TYPE_TEXCOORD,
		GBUFFER_NUM_TEXTURES
	};

	GBuffer();
	GBuffer(const GBuffer&);
	~GBuffer();

	bool Init(const unsigned&, const unsigned&);

	void BindForWriting();
	void BindForReading();
	void SetReadBuffer(const GBUFFER_TEXUTRE_TYPE&);

private:

	unsigned m_fbo;
	unsigned m_textures[GBUFFER_NUM_TEXTURES];
	unsigned m_depthTexture;

};

