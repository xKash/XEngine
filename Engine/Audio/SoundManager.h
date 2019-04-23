#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H

#include "AudioManager.h"


class SoundManager
{
private:

	static SoundManager* sInstance;

	AudioManager* mAudioMgr;

public:
	
	static SoundManager* Instance();
	static void Release();

	void PlayMusic(std::string filename_, int loops = -1);
	void PauseMusic();
	void ResumeMusic();

	void PlaySFX(std::string filename_, int loops = 0, int channel = 0);

private:

	SoundManager();
	~SoundManager();
};

#endif // !SOUNDMANAGER_H