#pragma once

#include "stdafx.h"

#include "BufferDeleter.h"

enum IndexBufferType
{
	UNSIGNED_INT,
	UNSIGNED_SHORT
};

class IndexBufferObject
{
public:
	IndexBufferObject();
	IndexBufferObject(const unsigned&,unsigned short*);
	IndexBufferObject(const unsigned&,unsigned*);
	IndexBufferObject(const IndexBufferObject&);
	~IndexBufferObject();

	unsigned getIBO();
	unsigned getSize();
	IndexBufferType getType();

private:

	unsigned m_ibo;
	unsigned m_size;
	IndexBufferType m_type;
};