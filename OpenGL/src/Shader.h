#pragma once
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

#include "glm/glm.hpp"

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

	void SetUniform4x4(const std::string& name,const glm::mat4& value) const;
	void SetUniformVec3(const std::string& name, float x, float y, float z) const;
	void SetUniformVec3(const std::string& name, const glm::vec3& value) const;
	void SetUniformFloat(const std::string& name, const float& value) const;
	void SetUniformInt(const std::string& name, const int& value) const;

	inline const unsigned int GetID() const { return m_RenderID; }
};