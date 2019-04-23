#ifndef OCTSPATIALPARTITION_H
#define OCTSPATIALPARTITION_H

#include "../Rendering/3D/GameObject.h"
#include "../Math/Ray.h"

class OctNode {
private:
	friend class OctSpatialPartition;
	BoundingBox* octBounds;
	OctNode* parent;
	OctNode* children[8];
	std::vector<GameObject*> objectList;
	float size;
	static int childNum;
public:
	enum OctChildren {
		OCT_TLF, // Top Left Front
		OCT_BLF, // Bottom Left Front
		OCT_BRF, // Bottom Right Front
		OCT_TRF, // Top Right Front
		OCT_TLR, // Top Left Rear
		OCT_BLR, // Bottom Left Rear
		OCT_BRR, // Bottom Right Rear
		OCT_TRR  // Top Right Rear
	};

	OctNode(glm::vec3 position_, float size_, OctNode* parent_);
	~OctNode();
	void Octify(int depth_);
	OctNode* GetParent();
	OctNode* GetChild(OctChildren type_);
	void AddCollisionObject(GameObject* obj_);
	int GetObjectCount() const;
	bool IsLeaf() const;
	BoundingBox* GetBoundingBox() const;
	int GetChildCount() const;
};

class OctSpatialPartition {
private:
	OctNode* root;
	std::vector<OctNode*> rayIntersectionList;
	void AddObjectToCell(OctNode* cell_, GameObject* obj_, bool& found_);
	void PrepareCollisionQuery(OctNode* cell_, Ray ray_);
public:
	OctSpatialPartition(float worldSize_);
	~OctSpatialPartition();
	void AddObject(GameObject* obj_);
	GameObject* GetCollision(Ray ray_);
};
#endif // !OCTSPATIALPARTITION_H


