#include "SoundManager.h"

SoundManager* SoundManager::sInstance = NULL;

SoundManager* SoundManager::Instance() {

	if (sInstance == NULL) {
		sInstance = new SoundManager();
	}
	return sInstance;
}

void SoundManager::Release() {

	delete sInstance;
	sInstance = NULL;
}

SoundManager::SoundManager() {

	mAudioMgr = AudioManager::Instance();

	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096) < 0) {

		printf("Mixer Initialization Error: %s\n", Mix_GetError());
	}
}

SoundManager::~SoundManager() {
	
	mAudioMgr = NULL;
	Mix_Quit();
}

void SoundManager::PlayMusic(std::string filename_, int loops_) {

	Mix_PlayMusic(mAudioMgr->GetMusic(filename_), loops_);
}

void SoundManager::PauseMusic() {

	if (Mix_PlayingMusic() != 0) {
		Mix_PauseMusic();
	}
}

void SoundManager::ResumeMusic() {

	if (Mix_PausedMusic() != 0) {
		Mix_ResumeMusic();
	}
}

void SoundManager::PlaySFX(std::string filename_, int loops_, int channel_) {
	
	Mix_PlayChannel(channel_, mAudioMgr->GetSFX(filename_), loops_);
}