#ifndef PLAYER_H
#define PLAYER_H

#include "GameObject.h"
#include "../../Audio/SoundManager.h"

class Player : public GameObject {
public:
	Player(Model * model_, glm::vec3 position_);
	~Player();

	friend GameObject;

	void Update(const float deltaTime_) override;

private:
	float speed;
	float speedRotation;
	float speedDefault;
	float speedRotationDefault;

	SoundManager* mSoundMgr;

	SDL_Event SDLEvent;
};
#endif // !PLAYER_H

