#ifndef GAMEINTERFACE_H
#define GAMEINTERFACE_H

class GameInterface {
public:
	GameInterface() {};
	virtual ~GameInterface() {};

	virtual bool Init() = 0;
	virtual void Update(const float deltaTime_) = 0;
	virtual void Render() = 0;
};
#endif // !GAMEINTERFACE_H



