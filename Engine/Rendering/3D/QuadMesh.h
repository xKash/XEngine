#ifndef QUADMESH_H
#define QUADMESH_H

#include "Mesh.h"

class QuadMesh : public Mesh {
public:
	QuadMesh(SubMesh subMesh_, GLuint shaderProgram_);
	~QuadMesh();

	friend Mesh;

	void GenerateBuffers() override;
	void Render(std::vector<glm::mat4> instances_, Camera* camera_) override;

private:
};
#endif // !QUADMESH_H
