#include "Camera.h"
#include "../Core/EngineClass.h"

std::unique_ptr<Camera> Camera::cameraInstance = nullptr;

const float maxZoom = 350.0f;
const float minZoom = 2.0f;

Camera::Camera() : position(glm::vec3()), perspective(glm::mat4()), orthographic(glm::mat4()), fieldOfView(0.0f), 
	yaw(0.0f), pitch(0.0f), forwardVector(glm::vec3()), upVector(glm::vec3()), rightVector(glm::vec3()), worldUp(glm::vec3()), lights(std::vector<LightSource*>())
{
	fieldOfView = 45.0f;
	forwardVector = glm::vec3(0.0f, 0.0f, -1.0f);
	upVector = glm::vec3(0.0f, 1.0f, 0.0f);
	worldUp = upVector;
	nearPlane = 2.0f;
	farPlane = 800.0f;

	pitch = 20.0f;
	distancePlayer = 10.0f;

	perspective = glm::perspective(glm::radians(fieldOfView), EngineClass::GetInstance()->GetScreenSize().x /
		EngineClass::GetInstance()->GetScreenSize().y, nearPlane, farPlane);

	orthographic = glm::ortho(0.0f, EngineClass::GetInstance()->GetScreenSize().x, 0.0f, 
				EngineClass::GetInstance()->GetScreenSize().y, -1.0f, 1.0f);
}


Camera::~Camera() {
	for (auto light : lights) {
		delete light;
		light = nullptr;
	}
	lights.clear();
	lights.shrink_to_fit();
}

Camera * Camera::GetInstance() {

	if (cameraInstance.get() == nullptr) {
		cameraInstance.reset(new Camera);
	}
	return cameraInstance.get();
}

void Camera::UpdateView() {

	// Create a entity matrix
	glm::mat4 newView = glm::mat4(1.0f);

	// Rotate the camera
	newView = glm::rotate(newView, glm::radians(pitch), glm::vec3(1.0f, 0.0f, 0.0f));
	newView = glm::rotate(newView, glm::radians(yaw), glm::vec3(0.0f, 1.0f, 0.0f));

	// Translate the camera
	newView = glm::translate(newView, -position);

	// Update view matrix
	view = newView;
}

void Camera::CalculateZoom() {

	float check = distancePlayer;

	if (zoom > 0) {
		check -= zoom;
		if (check > minZoom) distancePlayer -= zoom;
	}
	else if (zoom < 0) {
		check -= zoom;
		if (check < maxZoom) distancePlayer -= zoom;
	}

	zoom = 0;
}

float Camera::CalculateHorizontalDistance() {
	return distancePlayer * glm::cos(glm::radians(pitch));
}

float Camera::CalculateVerticalDistance() {
	return distancePlayer * glm::sin(glm::radians(pitch));
}

void Camera::CalculatePosition(float horizontalD, float verticalD) {

	if (player) {

		float theta = player->GetAngle() + angleAroundPlayer;

		float offsetX = horizontalD * glm::sin(glm::radians(theta));
		float offsetZ = horizontalD * glm::cos(glm::radians(theta));

		position.x = player->GetPosition().x - offsetX;
		position.z = player->GetPosition().z - offsetZ;
		position.y = player->GetPosition().y + verticalD + 2.0f;

		yaw = 180.0f - (player->GetAngle() + angleAroundPlayer);
		yaw = fmod(yaw, 360.0f);  // return to 0, when reaches 360
	}
	else {
		yaw = 180.0f - angleAroundPlayer;
	}
}

void Camera::Update(const float deltaTime_) {

	CalculateZoom();

	CalculatePosition(CalculateHorizontalDistance(), CalculateVerticalDistance());

	UpdateView();
}


void Camera::SetPosition(glm::vec3 position_) {
	position = position_;
	UpdateView();
}

void Camera::SetRotation(GLfloat yaw_, GLfloat pitch_) {
	yaw = yaw_;
	pitch = pitch_;
	UpdateView();
}

glm::mat4 Camera::GetView() const {
	return view;
}

glm::mat4 Camera::GetPerspective() const {
	return perspective;
}

glm::mat4 Camera::GetOrthographic() const {
	return orthographic;
}

glm::vec3 Camera::GetPosition() const {
	return position;
}

glm::vec2 Camera::GetClippingPlanes() const {
	return glm::vec2(nearPlane, farPlane);
}

void Camera::AddLightSource(LightSource * light_) {
	lights.push_back(light_);
}

std::vector<LightSource*> Camera::GetLightSources() const {
	return lights;
}

void Camera::ProcessMouseZoom(int y_) {

	zoom = y_ * 3;
}

void Camera::BindPlayer(GameObject * player_) {
	player = player_;
}
