#include "InputEventListenter.h"
#include "../Core/EngineClass.h"

EngineClass* InputEventListener::engineInstance = nullptr;

InputEventListener::~InputEventListener() {
	engineInstance = nullptr;
}

void InputEventListener::RegisterEngineObject(EngineClass * engine_) {
	engineInstance = engine_;
}

void InputEventListener::Update(SDL_Event e) {

	switch (e.type) {
	case SDL_KEYDOWN:
		if(e.key.repeat == 0)
			NotifyOfButtonPressed(e.key.keysym.sym);
		break;
	case SDL_KEYUP:
		NotifyOfButtonReleased(e.key.keysym.sym);
		break;
	}
}

void InputEventListener::NotifyOfButtonPressed(SDL_Keycode buttonType_) {
	if (engineInstance) {
		engineInstance->NotifyOfButtonPressed(buttonType_);
	}
}

void InputEventListener::NotifyOfButtonReleased(SDL_Keycode buttonType_) {
	if (engineInstance) {
		engineInstance->NotifyOfButtonReleased(buttonType_);
	}
}

//void InputEventListener::TextInput(SDL_Event e, SDL_Keycode buttonType_, string text_) {
//	bool isRunning = true;
//	SDL_StartTextInput();
//
//	while (isRunning) {
//		while (SDL_PollEvent(&e) != 0) {
//			// Getting the quit and keyboard events
//			if (e.type == SDL_QUIT) {
//				isRunning = false;
//			}
//			else if (e.type == SDL_TEXTINPUT || e.type == SDL_KEYDOWN) {
//				system("cls");
//				if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_BACKSPACE && text_.length() > 0) {
//					text_ = text_.substr(0, text_.length() - 1);
//				}
//				else if (e.type == SDL_TEXTINPUT) {
//					text_ += e.text.text;
//				}
//				std::cout << text_ << std::endl;
//			}
//		}
//	}
//		
//}
