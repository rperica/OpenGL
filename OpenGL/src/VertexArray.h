#pragma once
#include "VertexBuffer.h"

class VertexArray {
private:
	unsigned int m_RenderID;
public:
	VertexArray();
	~VertexArray();

	void Bind() const;
	void UnBind() const;

	void AddBuffer(const VertexBuffer& vb);
};