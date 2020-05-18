#include "VertexArray.h"
#include "glad/glad.h"

#include "VertexBufferLayout.h"

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

void VertexArray::AddBuffer(const VertexBuffer& vb,const VertexBufferLayout& layout)
{
	Bind();
	vb.Bind();

	const auto& elements = layout.GetElements();
	unsigned int offset = 0;

	for (int i = 0; i < elements.size(); i++)
	{
		const auto& element = elements[i];
		glVertexAttribPointer(i, element.count, element.type, element.normalized,layout.GetStride(), (const void*)offset);
		glEnableVertexAttribArray(i);

		offset += element.count * element.GetSizeOfType(element.type);
	}
}
