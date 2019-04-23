#ifndef CAMERA_H
#define CAMERA_H

#include "../Fx/LightSource.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glew.h>
#include <memory>
#include <vector>

class Camera {
public:
	// Make impossible do instantiate this class
	Camera(const Camera&) = delete;
	Camera(Camera&&) = delete;
	Camera& operator=(const Camera&) = delete;
	Camera& operator=(Camera&&) = delete;

	static Camera* GetInstance();

	void SetPosition(glm::vec3 position_);
	void SetRotation(GLfloat yaw_, GLfloat pitch_);
	glm::mat4 GetView() const;
	glm::mat4 GetPerspective() const;
	glm::mat4 GetOrthographic() const;
	glm::vec3 GetPosition() const;

	glm::vec2 GetClippingPlanes() const;

	void AddLightSource(LightSource* light_);
	std::vector<LightSource*> GetLightSources() const;

	void ProcessMouseZoom(int y_);

	void Update(const float deltaTime_);
	void BindPlayer(class GameObject* player_);

private:
	Camera();
	~Camera();

	static std::unique_ptr<Camera> cameraInstance;
	friend std::default_delete<Camera>;
	
	void UpdateView();
	void CalculateZoom();
	float CalculateHorizontalDistance();
	float CalculateVerticalDistance();
	void CalculatePosition(float horizontalD, float verticalD);

	glm::mat4 view;

	glm::vec3 position;
	glm::mat4 perspective;
	glm::mat4 orthographic;
	GLfloat fieldOfView;
	GLfloat yaw;
	GLfloat pitch;
	GLfloat nearPlane;
	GLfloat farPlane;
	glm::vec3 forwardVector;
	glm::vec3 upVector;
	glm::vec3 rightVector;
	glm::vec3 worldUp;

	std::vector<LightSource*> lights;

	GameObject* player;

	float distancePlayer;
	float angleAroundPlayer;
	float mouseX;
	float prevMouseX;
	float mouseY;
	float prevMouseY;
	int zoom;
	int buttonType;
};
#endif // !CAMERA_H



