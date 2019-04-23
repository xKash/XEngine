#include "SoundHandler.h"

std::unique_ptr<SoundHandler> SoundHandler::soundHandlerInstance = nullptr;
std::map<std::string, Sound*> SoundHandler::sounds = std::map<std::string, Sound*>();


SoundHandler::SoundHandler() {

}


SoundHandler::~SoundHandler() {

	if (sounds.size() > 0) {
		for (auto t : sounds) {
			glDeleteTextures(sizeof(GLuint), &t.second->soundID);
			delete t.second;
			t.second = nullptr;
		}
		sounds.clear();
	}
}

SoundHandler * SoundHandler::GetInstance() {

	if (soundHandlerInstance.get() == nullptr) {
		soundHandlerInstance.reset(new SoundHandler);
	}
	return soundHandlerInstance.get();
}

void SoundHandler::CreateSound(const std::string & soundName_, const std::string & soundFileName_) {

	audioManager = AudioHandler::GetInstance();

	try {
		Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096);
	}
	catch (const std::exception e) {
		Debug::Error("Sound" + soundName_ + " failed to load", __FILE__, __LINE__);
		return;
	}

}

GLuint SoundHandler::GetSound(const std::string & soundName_) {

	if (sounds.find(soundName_.c_str()) != sounds.end()) {
		return sounds[soundName_]->soundID;
	}

	return 0;
}

const Sound* SoundHandler::GetSoundData(const std::string & soundName_)
{
	if (sounds.find(soundName_.c_str()) != sounds.end()) {
		return sounds[soundName_];
	}

	return 0;
}

void SoundHandler::PlaySound(std::string soundName_, int loops_) {
	//Mix_PlayMusic(audioManager->GetInstance(soundName_), loops_);
}