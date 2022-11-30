#pragma once

#include "VertexBuffer.h"

class VertexBufferLayout;

class VertexArray{
private:
	unsigned int id;

public:
	VertexArray();

	~VertexArray();

	void addBuffer(const VertexBuffer &vBuffer, const VertexBufferLayout &layout);

	void Bind() const;
	void unBind() const;
};