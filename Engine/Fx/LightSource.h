#ifndef LIGHTSOURCE_H
#define LIGHTSOURCE_H

#include <glm/glm.hpp>

class LightSource
{
public:
	LightSource(glm::vec3 postition_, float ambient_, float diffuse_, glm::vec3 lightColour_);
	~LightSource(); 
	glm::vec3 GetPosition() const;
	float GetAmbient() const;
	float GetDiffuse() const;
	glm::vec3 GetLightColour() const;

	void SetPosition(glm::vec3 position_);
	void SetAmbient(float ambient_);
	void Setdiffuse(float diffuse_);
	void SetLightColour(glm::vec3 lightColour_);

private:
	glm::vec3 position;
	glm::vec2 lightStrengths;
	glm::vec3 lightColour;
	float ambient;
	float diffuse;
};
#endif // !LIGHTSOURCE_H



