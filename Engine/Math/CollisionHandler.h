#ifndef COLLISIONHANDLER_H
#define COLLISIONHANDLER_H

#include "CollisionDetection.h"
#include "../Rendering/3D/GameObject.h"
#include "../Core/OctSpatialPartition.h"
#include "Ray.h"

class CollisionHandler {
public:

	// Make impossible do instantiate this class outside of the egine
	CollisionHandler(const CollisionHandler&) = delete;
	CollisionHandler(CollisionHandler&&) = delete;
	CollisionHandler& operator=(const CollisionHandler&) = delete;
	CollisionHandler& operator=(CollisionHandler&&) = delete;

	static CollisionHandler* GetInstance();
	void Initialize(float worldSize_);
	void AddObject(GameObject* obj_);
	void Update(glm::vec2 mousePosition_, int buttonType_);

private:
	CollisionHandler();
	~CollisionHandler();

	static std::unique_ptr<CollisionHandler> collisionInstance;
	friend std::default_delete<CollisionHandler>;

	//static std::vector<GameObject*> colliders;
	static std::vector<GameObject*> previousCollisions;

	OctSpatialPartition* scenePartition;
};
#endif // !COLLISIONHANDLER_H


