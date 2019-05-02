#include "Game.h"

Game::Game() {

}

Game::~Game() {
	
}

bool Game::Init() {
	
	isPressedPause = false;

	Camera::GetInstance()->AddLightSource(new LightSource(glm::vec3(0.0f, 0.0f, 100.0f), 0.1f, 0.5f, glm::vec3(1.0f, 1.0f, 1.0f)));
	
	CollisionHandler::GetInstance()->Initialize(100.0f);

	
	Model* fox1 = new Model("Resources/Models/fox.obj", "Resources/Materials/fox.mtl", ShaderHandler::GetInstance()->GetShader("baseShader"));
	SceneGraph::GetInstance()->AddModel(fox1);
	
	SceneGraph::GetInstance()->AddGameObject(new GameObject(fox1, glm::vec3(3.0f, 0.0, 0.0f)), "fox");
	SceneGraph::GetInstance()->GetGameObject("fox")->SetScale(glm::vec3(0.05f));

	SceneGraph::GetInstance()->AddGameObject(new Player(fox1, glm::vec3(0.0f, 0.0f, 0.0f), SceneGraph::GetInstance()->GetGameObject("fox")),  "player");
	Camera::GetInstance()->BindPlayer(SceneGraph::GetInstance()->GetGameObject("player"));
	SceneGraph::GetInstance()->GetGameObject("player")->SetScale(glm::vec3(0.05f));

	Model* quad = new QuadModel("Resources/Materials/Quad.mtl", ShaderHandler::GetInstance()->GetShader("QuadShader"));
	SceneGraph::GetInstance()->AddModel(quad);
	SceneGraph::GetInstance()->AddGameObject(new GameObject(quad), "quad");
	SceneGraph::GetInstance()->GetGameObject("quad")->SetPosition(glm::vec3(0.0f, 0.0f, 0.0f));
	SceneGraph::GetInstance()->GetGameObject("quad")->SetScale(glm::vec3(100.0f));
	SceneGraph::GetInstance()->GetGameObject("quad")->SetAngle(90.0f);
	SceneGraph::GetInstance()->GetGameObject("quad")->SetRotation(glm::vec3(1.0f, 0.0f, 0.0f));

	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);

	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
		std::cout << "Error: " << Mix_GetError() << std::endl;

	Mix_Music* bgm = Mix_LoadMUS("Resources/SoundsPlay/ChillingMusic.wav");
	Mix_Chunk* soundEffect = Mix_LoadWAV("Resources/SoundsPlay/walking.wav");

	Mix_PlayMusic(bgm, -1);
	Mix_VolumeMusic(20);	

	/*SDL_Event ev;
	if (ev.type == SDL_QUIT)
		SDL_Quit();
	else if (ev.type == SDL_KEYDOWN) {
		while (SDL_PollEvent(&ev) != 0) {
			switch (ev.key.keysym.sym) {
			case SDLK_p:
				if (!Mix_PlayingMusic())
					Mix_PlayMusic(bgm, -1);
				else if (Mix_PausedMusic())
					Mix_ResumeMusic();
				else
					Mix_PausedMusic();
				std::cout << "pressed p" << std::endl;
				break;
			case SDLK_o:
				Mix_HaltMusic();
				std::cout << "pressed o" << std::endl;
				break;
			case SDLK_w | SDLK_a | SDLK_s | SDLK_d:
				Mix_PlayChannel(1, soundEffect, 1);
				Mix_HaltChannel(1);
				std::cout << "pressed w a s d" << std::endl;
				break;
			}
		}
	}*/
	
	return true;
}

void Game::Update(const float deltaTime_) {
	//std::cout << "Game update deltaTime: " << deltaTime_ << std::endl;
	SceneGraph::GetInstance()->Update(deltaTime_);
	Camera::GetInstance()->Update(deltaTime_);
	if (EngineClass::GetInstance()->IsKeyPressed() == SDLK_p) {
		isPressedPause = true;
	}
	if (isPressedPause && EngineClass::GetInstance()->IskeyReleased() == SDLK_p){
		isPressedPause = false;
		if (Mix_PausedMusic()) {
			Mix_ResumeMusic();
		}
		else {
			Mix_PauseMusic();
		}
	}



}

void Game::Render() {
	SceneGraph::GetInstance()->Render(Camera::GetInstance());
}
