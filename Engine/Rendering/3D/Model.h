#ifndef MODEL_H
#define MODEL_H

#include "Mesh.h"
#include "QuadMesh.h"
#include "../../Camera/Camera.h"
#include <glm/gtc/matrix_transform.hpp>
#include "LoadOBJModel.h"
#include <string>

class Model {
public:
	Model(const std::string& objPath_, const std::string& matPath_, GLuint shaderProgram_);
	Model(const std::string& matPath_, GLuint shaderProgram_);
	~Model();

	void Render(Camera* camera_);
	void AddMesh(Mesh* mesh_);
	void AddGuiSubMesh(SubMesh subMesh_);
	GLuint CreateInstance(glm::vec3 position_, float angle_, glm::vec3 rotation_, glm::vec3 scale_);
	void UpdateInstance(GLuint index_, glm::vec3 position_, float angle_, glm::vec3 rotation_, glm::vec3 scale_);
	glm::mat4 GetTransform(GLuint index_) const;
	BoundingBox GetBoundingBox();
	GLuint GetShader();
private:
	std::vector<Mesh*> subMeshes;
	std::vector<glm::mat4> modelInstances;
	GLuint shaderProgram;
	LoadOBJModel* obj;
	BoundingBox boundingBox;

	glm::mat4 GetTransform(glm::vec3 position_, float angle_, glm::vec3 rotation_, glm::vec3 scale_);
	void LoadModel();
};
#endif // !MODEL_H