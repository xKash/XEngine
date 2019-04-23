#include "QuadMesh.h"

QuadMesh::QuadMesh(SubMesh subMesh_, GLuint shaderProgram_) : Mesh(subMesh_, shaderProgram_) {
}

QuadMesh::~QuadMesh() {
}

void QuadMesh::GenerateBuffers() {

	// Create VAO buffer	
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	// Create VBO buffer
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	// Store data in a float buffer (vertices) VBO
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec2) * subMesh.quadPosition.size(), &subMesh.quadPosition[0], GL_STATIC_DRAW);

	// Position
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec2), (GLvoid*)0);

	// Unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);			// Disable the VBO
	glBindVertexArray(0);						// Disable the VAO

	modelLoc = glGetUniformLocation(shaderProgram, "model");
	viewLoc = glGetUniformLocation(shaderProgram, "view");
	projLoc = glGetUniformLocation(shaderProgram, "proj");

	diffuseMapLoc = glGetUniformLocation(shaderProgram, "diffuseMap");
}

void QuadMesh::Render(std::vector<glm::mat4> instances_, Camera * camera_) {

	//Material
	glUniform1i(diffuseMapLoc, 0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, subMesh.material.diffuseMap);

	// View and Projection
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(camera_->GetView()));
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(camera_->GetPerspective()));

	// Enable VAO
	glBindVertexArray(VAO);

	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(instances_[0]));
	glDrawArrays(GL_TRIANGLE_STRIP, 0, subMesh.quadPosition.size());
	
	glBindVertexArray(0);		// Disable the VAO
}
