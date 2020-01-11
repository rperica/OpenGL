#pragma once
#include "glad/glad.h"

#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"

class Renderer
{
public:
	void Clear();
	void Draw(const VertexArray& va,const IndexBuffer& ib,const Shader& shader);
};