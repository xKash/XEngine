#include "AudioHandler.h"

std::unique_ptr<AudioHandler> AudioHandler::audioHandlerInstance = nullptr;
std::map<std::string, Material> AudioHandler::materials = std::map<std::string, Material>();

AudioHandler::AudioHandler() {

}

AudioHandler::~AudioHandler() {
	if (materials.size() != 0) {
		materials.clear();
	}
}

AudioHandler * AudioHandler::GetInstance() {
	if (audioHandlerInstance.get() == nullptr) {
		audioHandlerInstance.reset(new AudioHandler);
	}
	return audioHandlerInstance.get();
}

void AudioHandler::AddMaterial(const std::string & name_, Material mat_) {
	materials.insert(std::pair<std::string, Material>(name_, mat_));
}

const Material AudioHandler::GetMaterial(const std::string & name_) {
	if (materials.find(name_) != materials.end()) {
		return materials[name_];
	}
	return Material();
}