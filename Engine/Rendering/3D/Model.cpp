#include "Model.h"

Model::Model(const std::string& objPath_, const std::string& matPath_, GLuint shaderProgram_) :
	subMeshes(std::vector<Mesh*>()),
	modelInstances(std::vector<glm::mat4>())
{
	shaderProgram = shaderProgram_;

	obj = new LoadOBJModel();
	obj->LoadModel(objPath_, matPath_);
	this->LoadModel();
}

Model::Model(const std::string & matPath_, GLuint shaderProgram_) {

	shaderProgram = shaderProgram_;

	if (matPath_ != "") MaterialLoader::LoadMaterial(matPath_);
}

Model::~Model() {

	if (subMeshes.size() > 0) {
		for (auto m : subMeshes) {
			delete m;
			m = nullptr;
		}
		subMeshes.clear();
		subMeshes.shrink_to_fit();
	}

	modelInstances.clear();
	modelInstances.shrink_to_fit();
}

void Model::Render(Camera* camera_) {
	for (auto m : subMeshes) {
		m->Render(modelInstances, camera_);
	}
}

void Model::AddMesh(Mesh * mesh_) {
	subMeshes.push_back(mesh_);
}

void Model::AddGuiSubMesh(SubMesh subMesh_) {
	subMeshes.push_back(new QuadMesh(subMesh_, shaderProgram));
	subMeshes[subMeshes.size() - 1]->GenerateBuffers();
}

GLuint Model::CreateInstance(glm::vec3 position_, float angle_, glm::vec3 rotation_, glm::vec3 scale_) {

	modelInstances.push_back(GetTransform(position_, angle_, rotation_, scale_));

	return modelInstances.size() - 1;
}

void Model::UpdateInstance(GLuint index_, glm::vec3 position_, float angle_, glm::vec3 rotation_, glm::vec3 scale_) {
	modelInstances[index_] = GetTransform(position_, angle_, rotation_, scale_);
}

glm::mat4 Model::GetTransform(GLuint index_) const {
	return modelInstances[index_];
}

BoundingBox Model::GetBoundingBox()
{
	return boundingBox;
}

GLuint Model::GetShader() {
	return shaderProgram;
}

glm::mat4 Model::GetTransform(glm::vec3 position_, float angle_, glm::vec3 rotation_, glm::vec3 scale_) {

	glm::mat4 model;

	model = glm::translate(model, position_);
	model = glm::rotate(model, glm::radians(angle_), rotation_);
	model = glm::scale(model, scale_);

	return model;
}

void Model::LoadModel() {

	for (size_t i = 0; i < obj->GetMeshes().size(); ++i) {
		subMeshes.push_back(new Mesh(obj->GetMeshes()[i], shaderProgram));
		subMeshes[subMeshes.size() - 1]->GenerateBuffers();
	}

	boundingBox = obj->GetBoundingBox();

	delete obj;
	obj = nullptr;
}