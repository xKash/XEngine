#ifndef PLAYER_H
#define PLAYER_H

#include "GameObject.h"
#include <SDL_mixer.h>

class Player : public GameObject {
public:
	Player(Model * model_, glm::vec3 position_, GameObject* fox_);

	~Player();

	friend GameObject;

	void Update(const float deltaTime_) override;

private:
	float speed;
	float speedRotation;
	float speedDefault;
	float speedRotationDefault;
	Mix_Chunk* soundEffect;
	Mix_Chunk* soundEffect2;
	GameObject* fox;

	SDL_Event SDLEvent;
};
#endif // !PLAYER_H

