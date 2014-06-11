#pragma once

#include "stdafx.h"

#include "Logger.h"

class ShaderDeleter
{
public:

	~ShaderDeleter();

	static ShaderDeleter* instance()
	{
		static ShaderDeleter instance;
		return &instance;
	}

	void add(const UINT&);
	void release();

private:

	ShaderDeleter();
	ShaderDeleter(const ShaderDeleter&);

private:

	std::vector<UINT> m_element;

};