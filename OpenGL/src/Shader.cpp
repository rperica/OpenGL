#include "Shader.h"
#include "glad/glad.h"

Shader::Shader(const std::string& vertexShaderPath, const std::string &fragmentShaderPath){
	
	std::ifstream vertexFile(vertexShaderPath);
	std::ifstream fragmentFile(fragmentShaderPath);

	std::stringstream vertexStream;
	std::stringstream fragmentStream;

	std::string readVertex;
	std::string readFragment;

	while (std::getline(vertexFile,readVertex))
	{
		vertexStream << readVertex << "\n";
	}

	while (std::getline(fragmentFile, readFragment))
	{
		fragmentStream << readFragment << "\n";
	}
	
	m_VertexSource = vertexStream.str();
	m_FragmentSource = fragmentStream.str();

	CreateShader();
}

Shader::~Shader()
{
	glDeleteProgram(m_RenderID);
}

void Shader::CreateShader() 
{

	unsigned int vertexShader = CompileShader(GL_VERTEX_SHADER);
	unsigned int fragmentShader = CompileShader(GL_FRAGMENT_SHADER);

	m_RenderID = glCreateProgram();
	glAttachShader(m_RenderID, vertexShader);
	glAttachShader(m_RenderID, fragmentShader);
	glLinkProgram(m_RenderID);
	glValidateProgram(m_RenderID);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

unsigned int Shader::CompileShader(int type) 
{
	unsigned int id = glCreateShader(type);
	std::string name;

	switch (type) {
		case GL_VERTEX_SHADER:
		{
			const char* vertexSource = m_VertexSource.c_str();
			glShaderSource(id, 1, &vertexSource, nullptr);
			name = "VERTEX";
			break;
		}
		case GL_FRAGMENT_SHADER:
		{
			const char* fragmentSource = m_FragmentSource.c_str();
			glShaderSource(id, 1, &fragmentSource, nullptr);
			name = "FRAGMENT";
			break;
		}
	}
	
	int success;
	char infolog[512];

	glGetShaderiv(id, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(id, 512, nullptr, infolog);
		std::cerr << "SHADER ERROR: " << name << " -----------  " << infolog << std::endl;
	}

	return id;
}

void Shader::Bind() const
{
	glUseProgram(m_RenderID);
}

void Shader::Unbind() const
{
	glUseProgram(0);
}