#pragma once

#include "vector"

#include "Renderer.h"

struct Vertex
{
	glm::vec3 Position;
	glm::vec3 normal;
	glm::vec2 textureCordinates;
	glm::vec3 tangent;
	glm::vec3 bitangent;
};

struct Textures
{
	unsigned int id;
	std::string type;
	std::string path;
};

class Mesh
{
public:
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<Textures> textures;
	unsigned int VAO;

	Mesh(const std::vector<Vertex>& vertices,const std::vector<unsigned int>& indices,const std::vector<Textures>& textures);
	void Draw(const Shader& shader);
private:
	unsigned int VBO,IBO;
	void setupMesh();
};