#include "Player.h"
#include "../../Core/EngineClass.h"

Player::Player(Model * model_, glm::vec3 position_) : GameObject(model_, position_),
	speed(0.0f),
	speedRotation(0.0f),
	speedDefault(30.0f),
	speedRotationDefault(70.0)
{
	//mSoundMgr = SoundManager::Instance();

}

Player::~Player() {
	//SoundManager::Release();
	//mSoundMgr = nullptr;
}

void Player::Update(const float deltaTime_) {


	SDL_Keycode keyP = EngineClass::GetInstance()->IsKeyPressed();
	SDL_Keycode keyR = EngineClass::GetInstance()->IskeyReleased();

	glm::vec3 newPosition = position;

	if (keyR == SDLK_w || keyR == SDLK_s || keyR == SDLK_UP || keyR == SDLK_DOWN) {
		speed = 0.0f;
		//mSoundMgr->PlaySFX("walking.wav");
	}
	else if (keyP == SDLK_w || keyP == SDLK_UP) {
		speed = speedDefault;
		//mSoundMgr->PlaySFX("walking.wav");
	}
	else if (keyP == SDLK_s || keyP == SDLK_DOWN) {
		speed = -speedDefault;
		//mSoundMgr->PlaySFX("walking.wav");
	}

	if (keyR == SDLK_a || keyR == SDLK_d || keyR == SDLK_LEFT || keyR == SDLK_RIGHT) {
		speedRotation = 0.0f;
		//mSoundMgr->PlaySFX("walking.wav");
	}
	else if (keyP == SDLK_a || keyP == SDLK_LEFT) {
		speedRotation = speedRotationDefault;
		//mSoundMgr->PlaySFX("walking.wav");
	}
	else if (keyP == SDLK_d || keyP == SDLK_RIGHT) {
		speedRotation = -speedRotationDefault;
		//mSoundMgr->PlaySFX("walking.wav");
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
