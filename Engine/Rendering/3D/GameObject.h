#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "Model.h"
#include "QuadModel.h"

class GameObject
{
public:
	GameObject(Model* model_);
	GameObject(Model* model_, glm::vec3 position_);
	~GameObject();
		
	void SetPosition(glm::vec3 position_);
	void SetRotation(glm::vec3 rotation_);
	void SetScale(glm::vec3 scale_);
	void SetAngle(float angle_);
	void SetTag(std::string tag_);
	void SetHit(bool hit_, int buttonType);

	glm::vec3 GetPosition();
	glm::vec3 GetRotation();
	glm::vec3 GetScale();
	std::string GetTag();
	float GetAngle();

	virtual void Update(const float deltaTime_);

	BoundingBox GetBoundingBox() const;

protected:
	Model* model;
	GLuint modelInstance;

	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;
	float angle;

	std::string tag;

	BoundingBox boundingBox;

	bool hit;
};
#endif // !GAMEOBJECT_H


