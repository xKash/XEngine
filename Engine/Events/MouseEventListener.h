#ifndef MOUSELISTENER_H
#define MOUSELISTENER_H

#include <SDL.h>
#include<glm/glm.hpp>

class EngineClass;

class MouseEventListener {
public:
	// Make impossible do instantiate this class outside of the egine
	MouseEventListener() = delete;
	~MouseEventListener();
	MouseEventListener(const MouseEventListener&) = delete;
	MouseEventListener(MouseEventListener&&) = delete;
	MouseEventListener& operator=(const MouseEventListener&) = delete;
	MouseEventListener& operator=(MouseEventListener&&) = delete;

	static void RegisterEngineObject(EngineClass* engine_);
	static void Update(SDL_Event e);
	static void NotifyOfMousePressed(int buttonType_);
	static void NotifyOfMouseReleased(int buttonType_);
	static void NotifyOfMouseMove();
	static void NotifyOfMouseScroll(int y_);
	static glm::vec2 GetPreviousMousePosition();
	static glm::vec2 GetMousePosition();
	static glm::vec2 GetMouseOffSet();
private:
	static EngineClass* engineInstance;
	static int mouseX, mouseY, prevMouseX, prevMouseY;
	static bool firstUpdate;
	static void UpdateMousePosition();
};
#endif // !MOUSELISTENER_H



