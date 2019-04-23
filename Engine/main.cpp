#include "Core/EngineClass.h"
#include "../Game/Game.h"

int main(int argc, char* args[]) {

	EngineClass::GetInstance()->SetGameInterface(new Game());
	EngineClass::GetInstance()->Init("GAME301 Engine", 800, 600);
	EngineClass::GetInstance()->Run();

	return 0;
}