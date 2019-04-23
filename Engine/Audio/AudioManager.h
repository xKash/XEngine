#ifndef AUDIOMANAGER_H
#define AUDIOMANAGER_H

#include <SDL.h>	
#include <SDL_mixer.h>
#include <map>

class AudioManager
{
private:
	static AudioManager* sInstance;

	std::map<std::string, Mix_Music*> mMusic;
	std::map<std::string, Mix_Chunk*> mSFX;

public:

	static AudioManager* Instance();
	static void Release();

	Mix_Music* GetMusic(std::string filename_);
	Mix_Chunk* GetSFX(std::string filename_);

private:
	AudioManager();
	~AudioManager();
};

#endif // !AUDIOMANAGER_H