#pragma once

#include "Mesh.h"

#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"

#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
#include <string>

unsigned int TextureFromFile(const char* path, const std::string& directory, bool gamma=false);

class Model
{
public:
	Model(std::string const& path,bool gamma=false);
	void Draw(const Shader& shader);
private:
	std::vector<Textures> textures_loaded;
	std::vector<Mesh> meshes;
	std::string directory;
	bool gammaCorrection;

	void LoadModel(std::string const& path);
	void ProcessNode(aiNode* node, const aiScene* scene);
	Mesh ProcessMesh(aiMesh* mesh, const aiScene* scene);
	std::vector<Textures> LoadMaterialTexture(aiMaterial* mat, aiTextureType type, std::string typeName);
};