#include "MouseEventListener.h"
#include "../Core/EngineClass.h"


EngineClass* MouseEventListener::engineInstance = nullptr;
int MouseEventListener::mouseX = 0;
int MouseEventListener::mouseY = 0;
int MouseEventListener::prevMouseX = 0;
int MouseEventListener::prevMouseY = 0;
bool MouseEventListener::firstUpdate = true;

MouseEventListener::~MouseEventListener() {
	engineInstance = nullptr;
}

void MouseEventListener::RegisterEngineObject(EngineClass * engine_) {
	engineInstance = engine_;
}

void MouseEventListener::Update(SDL_Event e) {
	switch (e.type)	{
	case SDL_MOUSEBUTTONDOWN:
		UpdateMousePosition();
		NotifyOfMousePressed(e.button.button);
		break;
	case SDL_MOUSEBUTTONUP:
		UpdateMousePosition();
		NotifyOfMouseReleased(e.button.button);
		break;
	case SDL_MOUSEMOTION:
		UpdateMousePosition();
		NotifyOfMouseMove();
		break;
	case SDL_MOUSEWHEEL:
		NotifyOfMouseScroll(e.wheel.y);
		break;
	}
}

void MouseEventListener::NotifyOfMousePressed(int buttonType_) {
	if (engineInstance) {
		engineInstance->NotifyOfMousePressed(mouseX, mouseY, buttonType_);
	}
}

void MouseEventListener::NotifyOfMouseReleased(int buttonType_) {
	if (engineInstance) {
		engineInstance->NotifyOfMouseReleased(mouseX, mouseY, buttonType_);
	}
}

void MouseEventListener::NotifyOfMouseMove() {
	if (engineInstance) {
		engineInstance->NotifyOfMouseMove(mouseX, mouseY);
	}
}

void MouseEventListener::NotifyOfMouseScroll(int y_) {
	if (engineInstance) {
		engineInstance->NotifyOfMouseScroll(y_);
	}
}

glm::vec2 MouseEventListener::GetPreviousMousePosition()
{
	return glm::vec2(prevMouseX, prevMouseY);
}

glm::vec2 MouseEventListener::GetMousePosition()
{
	return glm::vec2(mouseX, mouseY);
}

glm::vec2 MouseEventListener::GetMouseOffSet()
{
	return glm::vec2(mouseX - prevMouseX, prevMouseY - mouseY);
}

void MouseEventListener::UpdateMousePosition() {
	int tmpX, tmpY;
	SDL_GetMouseState(&tmpX, &tmpY);
	tmpY = (int) engineInstance->GetScreenSize().y - tmpY;
	if (firstUpdate) {
		prevMouseX = mouseX - tmpX;
		prevMouseY = mouseY - tmpY;
		firstUpdate = false;
	}
	else if (tmpX != mouseX && tmpY != mouseY) {
		prevMouseX = mouseX;
		prevMouseY = mouseY;
		mouseX = tmpX;
		mouseY = tmpY;
	}
}
