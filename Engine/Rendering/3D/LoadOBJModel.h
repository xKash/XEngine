#ifndef LOADOBJMODEL_H
#define LOADOBJMODEL_H

#include "Mesh.h"
#include "../../Graphics/TextureHandler.h"
#include "../../Fx/MaterialLoader.h"
#include "../../../Engine/Math/BoundingBox.h"
#include "../../Fx/MaterialLoader.h"
#include <sstream>

class LoadOBJModel
{
public:
	LoadOBJModel();
	~LoadOBJModel();
	void LoadModel(const std::string& fileName_);
	void LoadModel(const std::string& fileName_, const std::string& matName_);

	std::vector<Vertex> GetVerts();
	std::vector<GLuint> GetIndices();
	std::vector<SubMesh> GetMeshes();

	BoundingBox GetBoundingBox();

private:
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec3> normals;
	std::vector<glm::vec2> texturesCoords;

	std::vector<GLuint> indices;
	std::vector<GLuint> normalIndices;
	std::vector<GLuint> textureIndices;

	std::vector<Vertex> meshVertices;
	std::vector<SubMesh> meshes;

	void PostProcessing();
	void LoadMaterial(const std::string& fileName_);
	void LoadMaterialLibrary(const std::string& matName_);

	Material currentMaterial;
	BoundingBox boundingBox;
};
#endif // !LOADOBJMODEL_H


