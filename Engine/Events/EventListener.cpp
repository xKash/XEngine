#include "EventListener.h"
#include "../Core/EngineClass.h"

void EventListener::Update() {
	
	SDL_Event SDLEvent;
	while (SDL_PollEvent(&SDLEvent)) {
		switch (SDLEvent.type) {
		case SDL_QUIT:
			EngineClass::GetInstance()->ExitGame();
			break;
		case SDL_KEYDOWN:
			InputEventListener::Update(SDLEvent);
			break;
		case SDL_KEYUP:
			InputEventListener::Update(SDLEvent);
			break;
		case SDL_MOUSEBUTTONDOWN:
		case SDL_MOUSEBUTTONUP:
		case SDL_MOUSEMOTION:
		case SDL_MOUSEWHEEL:
			MouseEventListener::Update(SDLEvent);
			break;
		default:
			break;
		}
	}
}
