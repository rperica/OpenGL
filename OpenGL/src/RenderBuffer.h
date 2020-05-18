#pragma once

#include "Renderer.h"

class RenderBuffer
{
private:
	unsigned int m_RendererID;
public:
	RenderBuffer();
	~RenderBuffer();

	void Bind();
	void UnBind();
};