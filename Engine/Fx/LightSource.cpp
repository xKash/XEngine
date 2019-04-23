#include "LightSource.h"


LightSource::LightSource(glm::vec3 postition_, float ambient_, float diffuse_, glm::vec3 lightColour_) {
	SetPosition(postition_);
	SetAmbient(ambient_);
	Setdiffuse(diffuse_);
	SetLightColour(lightColour_);
}

LightSource::~LightSource() {}
glm::vec3 LightSource::GetPosition() const {
	return position;
}
float LightSource::GetAmbient() const {
	return ambient;
}
float LightSource::GetDiffuse() const {
	return diffuse;
}
glm::vec3 LightSource::GetLightColour() const {
	return lightColour;
}

void LightSource::SetPosition(glm::vec3 position_) {
	position = position_;
}

void LightSource::SetAmbient(float ambient_) {
	ambient = ambient_;
}
void LightSource::Setdiffuse(float diffuse_) {
	diffuse = diffuse_;
}
void LightSource::SetLightColour(glm::vec3 lightColour_) {
	lightColour = lightColour_;
}
