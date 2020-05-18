#include "RenderBuffer.h"

//extern const unsigned int SCR_WIDTH;
//extern const unsigned int SCR_HEIGHT;

RenderBuffer::RenderBuffer()
{
	glGenRenderbuffers(1, &m_RendererID);
	glBindRenderbuffer(GL_RENDERBUFFER, m_RendererID);
	glRenderbufferStorage(GL_RENDERBUFFER,GL_DEPTH24_STENCIL8,800, 600);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT,GL_RENDERBUFFER,m_RendererID);
}

RenderBuffer::~RenderBuffer()
{
	glDeleteRenderbuffers(1, &m_RendererID);
}

void RenderBuffer::Bind()
{
	glBindRenderbuffer(GL_RENDERBUFFER, m_RendererID);
}

void RenderBuffer::UnBind()
{
	glBindRenderbuffer(GL_RENDERBUFFER,0);
}
