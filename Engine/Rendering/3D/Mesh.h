#ifndef MESH_H
#define MESH_H

#include <glew.h>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "../../Graphics/ShaderHandler.h"
#include "../../Camera/Camera.h"
#include "../../Graphics/MaterialHandler.h"

struct Vertex {
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 texCoords;
};

struct SubMesh {
	std::vector<Vertex> vertexList;
	std::vector<GLuint> meshIndice;
	std::vector<glm::vec2> quadPosition;
	Material material;
};

class Mesh {
public:
	Mesh(SubMesh subMesh_, GLuint shaderProgram_);
	~Mesh();

	virtual void GenerateBuffers();
	virtual void Render(std::vector<glm::mat4> instances_, Camera* camera_);

protected:
	GLuint VAO, VBO;
	SubMesh subMesh;
	GLuint shaderProgram;

	GLuint modelLoc;
	GLuint viewLoc;
	GLuint projLoc;

	GLuint viewPositionLoc;

	GLuint lightPosLoc;
	GLuint lightAmbientLoc;
	GLuint lightDiffuseLoc;
	GLuint lightColourLoc;

	GLuint diffuseMapLoc;
	GLuint shininessLoc;
	GLuint transparencyLoc;
	GLuint ambientLoc;
	GLuint diffuseLoc;
	GLuint specularLoc;
};
#endif // !MESH_H