#include "QuadModel.h"

QuadModel::QuadModel(const std::string & matPath_, GLuint shaderProgram_) : Model(matPath_, shaderProgram_) {
	LoadQuadMesh();
}

QuadModel::~QuadModel() {
}

void QuadModel::LoadQuadMesh() {

	std::vector<glm::vec2> position;
	SubMesh subMesh;

	position.push_back(glm::vec2(-1.0f, 1.0f));
	position.push_back(glm::vec2(-1.0f, -1.0f));
	position.push_back(glm::vec2(1.0f, 1.0f));
	position.push_back(glm::vec2(1.0f, -1.0f));

	subMesh.quadPosition = position;
	subMesh.material = MaterialHandler::GetInstance()->GetMaterial("quad"); //The name is inside mtl file

	AddGuiSubMesh(subMesh);
}
