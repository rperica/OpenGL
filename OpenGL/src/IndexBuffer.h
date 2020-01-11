#pragma once

class IndexBuffer
{
private:
	unsigned int m_RenderID;
	unsigned int m_Count;
public:
	IndexBuffer(const unsigned int* data,unsigned int count);
	~IndexBuffer();

	void Bind() const;
	void UnBind() const;

	inline unsigned int GetCount() const { return m_RenderID; }
};