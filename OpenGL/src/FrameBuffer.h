#pragma once
#include "Renderer.h"

#include "Texture.h"
#include "RenderBuffer.h"

class FrameBuffer
{
private:
	unsigned int m_RenderID;
public:
	FrameBuffer();
	~FrameBuffer();

	void Bind();
	void UnBind();

	void Status();
};