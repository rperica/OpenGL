#pragma once
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

class Shader {
private:
	std::string m_VertexSource;
	std::string m_FragmentSource;
public:
	Shader(const std::string& vertexShader, const std::string& fragmentShader);
	void CreateShader();
	void CompileShader();
};