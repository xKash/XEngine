#ifndef AUDIOHANDLER_H
#define AUDIOHANDLER_H
#include <glew.h>
#include <glm/glm.hpp>
#include <memory>
#include <map>
#include <string>


struct Material {

	inline Material() : diffuseMap(0), shininess(0), transparency(0.0f), ambient(glm::vec3(1.0f)), diffuse(glm::vec3(1.0f)),
		specular(glm::vec3()) {};

	GLuint diffuseMap;		//newmtl

	float shininess;		// Ns
	float transparency;		// d

	glm::vec3 ambient;		// Ka
	glm::vec3 diffuse;		// Kd
	glm::vec3 specular;		// Ks
};

class AudioHandler {
public:

	// Make impossible do instantiate this class
	AudioHandler(const AudioHandler&) = delete;
	AudioHandler(AudioHandler&&) = delete;
	AudioHandler& operator=(const AudioHandler&) = delete;
	AudioHandler& operator=(AudioHandler&&) = delete;

	static AudioHandler* GetInstance();

	void AddMaterial(const std::string& name_, Material mat_);
	const Material GetMaterial(const std::string& name_);

private:
	AudioHandler();
	~AudioHandler();

	static std::unique_ptr<AudioHandler> audioHandlerInstance;
	friend std::default_delete<AudioHandler>;

	static std::map<std::string, Material> materials;
};

#endif // !AUDIOHANDLER_H
