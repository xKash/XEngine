#include "CollisionHandler.h"
#include "../Core/EngineClass.h"

std::unique_ptr<CollisionHandler> CollisionHandler::collisionInstance = nullptr;
//std::vector<GameObject*> CollisionHandler::colliders = std::vector<GameObject*>();
std::vector<GameObject*> CollisionHandler::previousCollisions = std::vector<GameObject*>();


CollisionHandler::CollisionHandler() {

}


CollisionHandler::~CollisionHandler() {

	//if (colliders.size() > 0) {
	//	for (auto go : colliders) {
	//		go = nullptr;
	//	}
	//	colliders.clear();
	//	colliders.shrink_to_fit();
	//}

	if (previousCollisions.size() > 0) {
		for (auto go : previousCollisions) {
			go = nullptr;
		}
		previousCollisions.clear();
		previousCollisions.shrink_to_fit();
	}
}

CollisionHandler * CollisionHandler::GetInstance() {

	if (collisionInstance.get() == nullptr) {
		collisionInstance.reset(new CollisionHandler);
	}
	return collisionInstance.get();
}

void CollisionHandler::Initialize(float worldSize_) {

	previousCollisions.clear();
	previousCollisions.shrink_to_fit();

	scenePartition = new OctSpatialPartition(worldSize_);
}

void CollisionHandler::AddObject(GameObject * obj_) {
	//colliders.push_back(obj_);
	scenePartition->AddObject(obj_);
}

void CollisionHandler::Update(glm::vec2 mousePosition_, int buttonType_) {

	// To do:
	// Remove object from de scene graph
	// Remove object from model
	// Remove object from cell

	Ray ray = CollisionDetection::ScreenToWorldRay(mousePosition_, EngineClass::GetInstance()->GetScreenSize());
	
	GameObject* goHit = nullptr;

	goHit = scenePartition->GetCollision(ray);

	//// Check which object has collided with the ray	
	//float distance = FLT_MAX;
	//for (auto go : colliders) {

	//	if (CollisionDetection::RayOBBIntersection(&ray, &go->GetBoundingBox())) {
	//		if (distance > ray.intersectionDistance) {
	//			distance = ray.intersectionDistance;
	//			goHit = go;
	//		}
	//	}
	//}

	// Update game object hit
	if (goHit != nullptr) {
		goHit->SetHit(true, buttonType_);
	}

	// Check previous collisions and set not hit and clean the previous collisions vector
	if (previousCollisions.size() > 0) {

		for (auto go : previousCollisions) {
			if( ( go != goHit && goHit != nullptr) || goHit == nullptr) {
				go->SetHit(false, buttonType_);
				go = nullptr;
			}
		}
	}
	previousCollisions.clear();
	previousCollisions.shrink_to_fit();

	// Update previous collision	
	if (goHit != nullptr) {
		previousCollisions.push_back(goHit);
	}
}
