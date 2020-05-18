#include "Texture.h" 
#include "Renderer.h"
#include "stb_image/stb_image.h"

Texture::Texture(const std::string& path)
	:m_RenderID(0),m_FilePath(path),m_Width(0),m_Height(0),m_BPP(0),m_LocalBuffer(nullptr)
{
	stbi_set_flip_vertically_on_load(true);
	m_LocalBuffer = stbi_load(path.c_str(), &m_Width, &m_Height, &m_BPP, 0);

	GLCall(glGenTextures(1, &m_RenderID));
	GLCall(glBindTexture(GL_TEXTURE_2D, m_RenderID));

	GLenum format;
	if (m_BPP == 1)
		format = GL_RED;
	else if (m_BPP == 3)
		format = GL_RGB;
	else if (m_BPP == 4)
		format = GL_RGBA;

	GLCall(glTexImage2D(GL_TEXTURE_2D, 0, format, m_Width, m_Height, 0, format, GL_UNSIGNED_BYTE, m_LocalBuffer));
	GLCall(glGenerateMipmap(GL_TEXTURE_2D));

	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));

	if (m_LocalBuffer)
	{
		stbi_image_free(m_LocalBuffer);
	}
}

Texture::Texture()
{
	glGenTextures(1, &m_RenderID);
	glBindTexture(GL_TEXTURE_2D,m_RenderID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 800, 600, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_RenderID, 0);
}


Texture::Texture(const int& width, const int& height)
{
	glGenTextures(1, &m_RenderID);
	glBindTexture(GL_TEXTURE_2D, m_RenderID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, m_RenderID, 0);
	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);
}

Texture::Texture(const std::vector<std::string>& faces)
{
	glGenTextures(1, &m_RenderID);
	glBindTexture(GL_TEXTURE_CUBE_MAP, m_RenderID);

	for (unsigned int i = 0; i < faces.size(); i++)
	{
		m_LocalBuffer = stbi_load(faces[i].c_str(), &m_Width, &m_Height, &m_BPP, 0);

		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, m_Width, m_Height, 0, GL_RGB, GL_UNSIGNED_BYTE, m_LocalBuffer);

		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

		if (m_LocalBuffer)
		{
			stbi_image_free(m_LocalBuffer);
		}
	}
}

Texture::~Texture()
{
	GLCall(glDeleteTextures(1, &m_RenderID));
}

void Texture::Bind(unsigned int slot /*= 0*/) const
{
	GLCall(glActiveTexture(GL_TEXTURE0 + slot));
	GLCall(glBindTexture(GL_TEXTURE_2D, m_RenderID));
}

void Texture::UnBind() const
{
	GLCall(glBindTexture(GL_TEXTURE_2D, 0));
}

void Texture::BindCubeMap() const
{
	GLCall(glActiveTexture(GL_TEXTURE0));
	GLCall(glBindTexture(GL_TEXTURE_CUBE_MAP, m_RenderID));
}