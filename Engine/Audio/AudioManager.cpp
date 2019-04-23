#include "AudioManager.h"


AudioManager::AudioManager() {

}


AudioManager::~AudioManager() { 

}

Mix_Music* AudioManager::GetMusic(std::string filename_) {

	std::string fullPath = SDL_GetBasePath();
	fullPath.append("Resources/SoundsPlay/" + filename_);

	if (mMusic[fullPath] == nullptr) {

		mMusic[fullPath] = Mix_LoadMUS(fullPath.c_str());
		if (mMusic[fullPath] == NULL) {

			printf("Music Loading Error: File-%s Error-%s", filename_.c_str(), Mix_GetError());
		}
	}
	return mMusic[fullPath];
}

Mix_Chunk* AudioManager::GetSFX(std::string filename_) {

	std::string fullPath = SDL_GetBasePath();
	fullPath.append("Resources/SoundsPlay/" + filename_);

	if (mSFX[fullPath] == nullptr) {

		mSFX[fullPath] = Mix_LoadWAV(fullPath.c_str());
		if (mSFX[fullPath] == NULL) {
			printf("SFX Loading Error: File-%s", filename_.c_str(), Mix_GetError());
		}
	}
	return mSFX[fullPath];
}