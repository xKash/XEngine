#include "Player.h"
#include "../../Core/EngineClass.h"

Player::Player(Model * model_, glm::vec3 position_, GameObject* fox_) : GameObject(model_, position_),
	speed(0.0f),
	speedRotation(0.0f),
	speedDefault(15.0f),
	speedRotationDefault(70.0)
{
	//mSoundMgr = SoundManager::Instance();
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);

	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
		std::cout << "Error: " << Mix_GetError() << std::endl;

	soundEffect = Mix_LoadWAV("Resources/SoundsPlay/walking.wav");
	soundEffect2 = Mix_LoadWAV("Resources/SoundsPlay/wolf.wav");
	Mix_PlayChannel(2, soundEffect2, 1000);
	Mix_VolumeChunk(soundEffect2, 0);



	fox = fox_;

}

Player::~Player() {
	//SoundManager::Release();	`
	//mSoundMgr = nullptr;
}

void Player::Update(const float deltaTime_) {

	
	float maxDistance = 125.0f;
	float distance = glm::length(position - fox->GetPosition());
	float volume = (100 - ((distance / maxDistance) * 100.0f));

	if (distance > maxDistance) {
		Mix_VolumeChunk(soundEffect2, 0);
	}
	else {
		Mix_VolumeChunk(soundEffect2, (int)(volume * 0.3));
	}
	
	SDL_Keycode keyP = EngineClass::GetInstance()->IsKeyPressed();
	SDL_Keycode keyR = EngineClass::GetInstance()->IskeyReleased();

	glm::vec3 newPosition = position;

	if (keyR == SDLK_w || keyR == SDLK_s || keyR == SDLK_UP || keyR == SDLK_DOWN) {
		speed = 0.0f;
		Mix_HaltChannel(1);
	}
	else if (keyP == SDLK_w || keyP == SDLK_UP) {
		speed = speedDefault;
		Mix_PlayChannel(1, soundEffect, 1);
	}
	else if (keyP == SDLK_s || keyP == SDLK_DOWN) {
		speed = -speedDefault;
		Mix_PlayChannel(1, soundEffect, 1);
	}

	if (keyR == SDLK_a || keyR == SDLK_d || keyR == SDLK_LEFT || keyR == SDLK_RIGHT) {
		speedRotation = 0.0f;
	}
	else if (keyP == SDLK_a || keyP == SDLK_LEFT) {
		speedRotation = speedRotationDefault;
	}
	else if (keyP == SDLK_d || keyP == SDLK_RIGHT) {
		speedRotation = -speedRotationDefault;
	}

	// Horizontal control
	if (speed != 0.0 || speedRotation != 0.0f) {

		float distance = speed * deltaTime_;

		// Rotate
		SetAngle(angle + (speedRotation * deltaTime_));

		float dx = distance * glm::sin(glm::radians(angle));
		float dz = distance * glm::cos(glm::radians(angle));

		newPosition.x += dx;
		newPosition.z += dz;
		SetPosition(newPosition);
	}
}
