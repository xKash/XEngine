#include "EngineClass.h"

std::unique_ptr<EngineClass> EngineClass::engineInstance = nullptr;

EngineClass::EngineClass() : window(nullptr), isRunning(false), fps(60), gameInterface(nullptr)
{
}

EngineClass::~EngineClass() {
}

bool EngineClass::Init(std::string name_, int width, int height_) {
	Debug::DebugInit();
	Debug::SetSeverity(MessageType::TYPE_INFO);

	window = new Window();
	if (!window->Init("GAME301 Engine", 800, 600)) {
		Debug::FatalError("Failed to initialize window object", __FILE__, __LINE__);
		return isRunning = false;
	}

	SDL_WarpMouseInWindow(window->GetWindow(), window->GetWidth() / 2, window->GetHeight() / 2);
	MouseEventListener::RegisterEngineObject(this);
	InputEventListener::RegisterEngineObject(this);


	ShaderHandler::GetInstance()->CreateProgram("colourShader", "Engine/Shaders/ColourVertexShader.glsl", "Engine/Shaders/ColourFragmentVertex.glsl");
	ShaderHandler::GetInstance()->CreateProgram("baseShader", "Engine/Shaders/VertexShader.glsl", "Engine/Shaders/FragmentShader.glsl");
	ShaderHandler::GetInstance()->CreateProgram("QuadShader", "Engine/Shaders/QuadVertexShader.glsl", "Engine/Shaders/QuadFragmentShader.glsl");

	if (gameInterface) {
		if (!gameInterface->Init()) {
			Debug::FatalError("Failed to initialize game interface", __FILE__, __LINE__);
		}
	}

	timer.Start();

	Debug::Info("Everthing initialize fine in engine", "EngineClass.cpp", __LINE__);
	
	return isRunning = true;
}

void EngineClass::Run() {
	while (isRunning) {
		EventListener::Update();
		timer.Update();
		Update(timer.GetDeltaTime());
		Render();
		SDL_Delay(timer.GetSleepTime(fps));
	}
	if (!isRunning) {
		ShutDown();
	}
}

bool EngineClass::GetIsRunning() {
	return isRunning;
}

void EngineClass::SetGameInterface(GameInterface * gameInterface_) {
	gameInterface = gameInterface_;
}

EngineClass * EngineClass::GetInstance() {
	if (engineInstance.get() == nullptr) {
		engineInstance.reset(new EngineClass);
	}
	return engineInstance.get();
}

glm::vec2 EngineClass::GetScreenSize() const {
	return glm::vec2(window->GetWidth(), window->GetHeight());
}

void EngineClass::NotifyOfButtonPressed(SDL_Keycode buttonType_) {
	keyReleased = 0;
	keyPressed = buttonType_;
}

void EngineClass::NotifyOfButtonReleased(SDL_Keycode buttonType_) {
	keyPressed = 0;
	keyReleased = buttonType_;
}

void EngineClass::NotifyOfMousePressed(int x_, int y_, int buttonType_) {
}

void EngineClass::NotifyOfMouseReleased(int x_, int y_, int buttonType_) {
	CollisionHandler::GetInstance()->Update(glm::vec2(x_, y_), buttonType_);
}
void EngineClass::NotifyOfMouseMove(int x_, int y_) {
}

void EngineClass::NotifyOfMouseScroll(int y_) {
	Camera::GetInstance()->ProcessMouseZoom(y_);
}

glm::vec2 EngineClass::GetMouse() {
	return glm::vec2(MouseEventListener::GetMousePosition());
}

glm::vec2 EngineClass::GetPreviousMouse() {
	return glm::vec2(MouseEventListener::GetPreviousMousePosition());
}

SDL_Keycode EngineClass::IsKeyPressed() {
	return (keyPressed);
}

SDL_Keycode EngineClass::IskeyReleased() {
	return (keyReleased);
}

void EngineClass::ExitGame() {
	isRunning = false;
}

void EngineClass::Update(const float deltaTime_) {
	if (gameInterface) {
		gameInterface->Update(deltaTime_);
	}
}

void EngineClass::Render() {
	glClearColor(255.0f, 255.0f, 255.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	if (gameInterface) {
		gameInterface->Render();
	}

	// Swap buffers back to front
	SDL_GL_SwapWindow(window->GetWindow());
}

void EngineClass::ShutDown() {
	delete window;	// calls the distroctor
	window = nullptr;
	delete gameInterface;
	gameInterface = nullptr;
	Mix_Quit();
	SDL_Quit();
}
