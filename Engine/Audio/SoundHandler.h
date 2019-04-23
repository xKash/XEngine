#ifndef SOUNDHANDLER_H
#define SOUNDHANDLER_H

#include <memory>
#include <string>
#include <map>
#include <SDL.h>
#include <SDL_mixer.h>
#include <glew.h>
#include "AudioHandler.h"
#include "../Core/Debug.h"

struct Sound {
	GLuint soundID = 0;
	int volume = 0;
};

class SoundHandler
{
public:
	static SoundHandler* GetInstance();																																																			

	// Make impossible do instantiate this class
	SoundHandler(const SoundHandler&) = delete;
	SoundHandler(SoundHandler&&) = delete;
	SoundHandler& operator=(const SoundHandler&) = delete;
	SoundHandler& operator=(SoundHandler&&) = delete;

	void CreateSound(const std::string& soundName_, const std::string & soundFileName_);
	static GLuint GetSound(const std::string& soundName_);
	static const Sound* GetSoundData(const std::string& soundName_);
	void PlaySound(std::string soundName_, int loops);
private:
	SoundHandler();
	~SoundHandler();

	static std::unique_ptr<SoundHandler> soundHandlerInstance;
	static SoundHandler* sInstance;
	AudioHandler* audioManager;
	friend std::default_delete<SoundHandler>;

	static std::map<std::string, Sound*> sounds;
};

#endif // !SOUNDHANDLER_H