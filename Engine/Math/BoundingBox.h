#ifndef BoundingBox_H
#define BoundingBox_H

#include <glm/glm.hpp>
#include <glm/gtx/matrix_decompose.hpp>
#include <glm/gtx/string_cast.hpp>

struct  BoundingBox {

public:
	glm::vec3 minVert;
	glm::vec3 maxVert;
	glm::mat4 transform;

	inline BoundingBox() {
		minVert = glm::vec3(0.0f);
		maxVert = glm::vec3(0.0f);
		transform = glm::mat4(0.0f);
	}

	inline BoundingBox(glm::vec3 minVert_, glm::vec3 maxVert_, glm::mat4 transform_) {
		minVert = minVert_;
		maxVert = maxVert_;
		transform = transform_;
	}

	inline bool Intersects(BoundingBox* box_) {

		glm::vec3 minCorner = GetTransformPoint(minVert, transform);
		glm::vec3 maxCorner = GetTransformPoint(maxVert, transform);
		glm::vec3 other_minCorner = GetTransformPoint(box_->minVert, box_->transform);
		glm::vec3 other_maxCorner = GetTransformPoint(box_->maxVert, box_->transform);

		// AABB collision detection
		//Check if maxCorner is greater than other_minCornern and minCorner is less other_maxCorner
		return(maxCorner.x > other_minCorner.x && minCorner.x < other_maxCorner.x &&
			maxCorner.y > other_minCorner.y && minCorner.y < other_maxCorner.y &&
			maxCorner.z > other_minCorner.z && minCorner.z < other_maxCorner.z);

		return false;
	}

private:

	inline glm::vec3 GetTransformPoint(glm::vec3 point_, glm::mat4 transform_) {

		glm::vec3 scale;
		glm::quat rotation;
		glm::vec3 translation;
		glm::vec3 skew;
		glm::vec4 perspective;

		glm::decompose(transform_, scale, rotation, translation, skew, perspective);

		return point_ + translation;
	}
};
#endif // !BoundingBox_H

