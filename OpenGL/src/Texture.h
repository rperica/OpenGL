#pragma once
#include <string>
#include<vector>
#include "vendor/stb_image/stb_image.h"

class Texture
{
private:
	unsigned int m_RenderID;
	std::string m_FilePath;
	int m_Width, m_Height, m_BPP; 
	unsigned char* m_LocalBuffer;

public:
	Texture(const std::string& path);
	Texture();
	Texture(const int& width,const int& height);
	Texture(const std::vector<std::string>& faces);

	~Texture();

	void Bind(unsigned int slot=0) const;
	void UnBind() const;

	void BindCubeMap() const;
};