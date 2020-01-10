#pragma once
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

class Shader {
private:
	unsigned int m_RenderID;
	std::string m_VertexSource;
	std::string m_FragmentSource;
public:
	Shader(const std::string& vertexShader, const std::string& fragmentShader);
	~Shader();
	void CreateShader();
	unsigned int CompileShader(int type);
	void Bind() const;
	void Unbind() const;
};