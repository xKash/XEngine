#ifndef QUADMODEL_H
#define QUADMODEL_H

#include "Model.h"

class QuadModel : public Model {

public:
	QuadModel(const std::string & matPath_, GLuint shaderProgram_);
	~QuadModel();

	friend Model;

private:
	void LoadQuadMesh();
};
#endif // !QUADMODEL_H

