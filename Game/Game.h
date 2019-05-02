#ifndef GAME_H
#define GAME_H

#include <SDL_mixer.h>
#include <SDL.h>
#include "../Engine/Core/EngineClass.h"
#include <glm/gtx/string_cast.hpp>

class Game : public GameInterface {
public:
	Game();
	virtual ~Game();
	bool Init();
	void Update(const float deltaTime_);
	void Render();
private:
	bool isPressedPause;
};
#endif // !GAME_H


