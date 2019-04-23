#ifndef ENGINECLASS_H
#define ENGINECLASS_H

#include "Window.h"
#include "Timer.h"
#include "GameInterface.h"
#include <SDL_Mixer.h>
#include "../Rendering/3D/GameObject.h"
#include "../Graphics/ShaderHandler.h"
#include "../Camera/Camera.h"
#include "../Graphics/TextureHandler.h"
#include "../Events/EventListener.h"
#include "../Events/TextInput.h"
#include "../Rendering/SceneGraph.h"
#include "../Rendering/3D/Player.h"
#include <memory>

class EngineClass {
public:
	// Make it impossible to instantiate this class outside of the engine
	EngineClass(const EngineClass&) = delete;
	EngineClass(EngineClass&&) = delete;
	EngineClass& operator=(const EngineClass&) = delete;
	EngineClass& operator=(EngineClass&&) = delete;

	EngineClass();
	~EngineClass();

	bool Init(std::string name_, int width, int height_);
	void Run();
	bool GetIsRunning();
	void SetGameInterface(GameInterface* gameInterface_);
	static EngineClass* GetInstance();
	
	glm::vec2 GetScreenSize() const;

	void NotifyOfButtonPressed(SDL_Keycode buttonType_);
	void NotifyOfButtonReleased(SDL_Keycode buttonType_);
	void NotifyOfMousePressed(int x_, int y_, int buttonType_);
	void NotifyOfMouseReleased(int x_, int y_, int buttonType_);
	void NotifyOfMouseMove(int x_, int y_);
	void NotifyOfMouseScroll(int y_);

	glm::vec2 GetMouse();
	glm::vec2 GetPreviousMouse();

	SDL_Keycode IsKeyPressed();
	SDL_Keycode IskeyReleased();

	void ExitGame();

private:
	void Update(const float deltaTime_);
	void Render();
	void ShutDown();

	static std::unique_ptr<EngineClass> engineInstance;
	friend std::default_delete<EngineClass>;

	Window* window;
	Timer timer;
	GameInterface* gameInterface;
	bool isRunning;
	unsigned int fps;

	SDL_Keycode keyPressed;
	SDL_Keycode keyReleased;
};
#endif // !ENGINECLASS_H



