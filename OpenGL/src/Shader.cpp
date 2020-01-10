#include "Shader.h"
#include "glad/glad.h"

Shader::Shader(const std::string& vertexShaderPath, const std::string &fragmentShaderPath){
	
	std::ifstream vertexFile;
	std::ifstream fragmentFile;

	std::stringstream vertexStream;
	std::stringstream fragmentStream;

	std::string readVertex;
	std::string readFragment;

	vertexFile.open(vertexShaderPath);
	fragmentFile.open(fragmentShaderPath);

	if (!vertexFile)
	{
		std::cerr << "ERROR WITH VERTEX FILE " << std::endl;
	}

	if(!fragmentFile)
	{
		std::cerr << "ERROR WITH FRAGMENT FILE " << std::endl;
	}
	while (std::getline(vertexFile,readVertex))
	{
		if (!std::string::npos)
		{
			vertexStream << readVertex << "\n";
		}
	}

	while (std::getline(fragmentFile, readFragment))
	{
		if (!std::string::npos)
		{
			fragmentStream << readFragment << "\n";
		}
	}
	
	vertexFile.close();
	fragmentFile.close();

	m_VertexSource = vertexStream.str();
	m_FragmentSource = fragmentStream.str();
}

void Shader::CreateShader()
{
	const char* vertexSource = m_VertexSource.c_str();
	const char* fragmentSource = m_FragmentSource.c_str();

	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexSource, nullptr);
	glCompileShader(vertexShader);

	int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentSource, nullptr);
	glCompileShader(fragmentShader);

	unsigned int program = glCreateProgram();
	glAttachShader(program, vertexShader);
	glAttachShader(program, fragmentShader);
	glLinkProgram(program);
	glValidateProgram(program);
	glUseProgram(program);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}
