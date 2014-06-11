#pragma once

#include "stdafx.h"

#include "Logger.h"

class BufferDeleter
{
public:

	~BufferDeleter();

	static BufferDeleter* instance()
	{
		static BufferDeleter instance;
		return &instance;
	}

	void add(const unsigned&, const bool& = false);
	void release();

private:
	BufferDeleter();
	BufferDeleter(const BufferDeleter&);

private:

	std::vector<unsigned> m_buffers;
	std::vector<unsigned> m_arrays;
};