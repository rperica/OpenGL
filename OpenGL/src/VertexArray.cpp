#include "VertexArray.h"
#include "glad/glad.h"

VertexArray::VertexArray()
{
	glGenVertexArrays(1, &m_RenderID);
	glBindVertexArray(m_RenderID);
}

VertexArray::~VertexArray()
{
	glDeleteVertexArrays(1, &m_RenderID);
}

void VertexArray::Bind() const
{
	glBindVertexArray(m_RenderID);
}

void VertexArray::UnBind() const
{
	glBindVertexArray(0);
}

void VertexArray::AddBuffer(const VertexBuffer& vb)
{
	Bind();
	vb.Bind();

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (void*)0);
	glEnableVertexAttribArray(0);
}