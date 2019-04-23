#ifndef INPUTEVENTLISTENER_H
#define INPUTEVENTLISTENER_H

#include <SDL.h>
#include<glm/glm.hpp>

using namespace std;

class EngineClass;

class InputEventListener {

public:
	// Make impossible do instantiate this class outside of the egine
	InputEventListener() = delete;
	~InputEventListener();
	InputEventListener(const InputEventListener&) = delete;
	InputEventListener(InputEventListener&&) = delete;
	InputEventListener& operator=(const InputEventListener&) = delete;
	InputEventListener& operator=(InputEventListener&&) = delete;

	static void RegisterEngineObject(EngineClass* engine_);
	static void Update(SDL_Event e);
	static void NotifyOfButtonPressed(SDL_Keycode buttonType_);
	static void NotifyOfButtonReleased(SDL_Keycode buttonType_);
	//static void TextInput(SDL_Event e, SDL_Keycode buttonType_, string text_);

private:
	static EngineClass* engineInstance;
};
#endif // !InputEventListener_H


