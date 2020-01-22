#ifndef ENTITY_MANAGER_H
#define ENTITY_MANAGER_H

#include "SingletonTemplate.h"
#include <list>
#include "Vector3.h"

class EntityBase;

class EntityManager : public Singleton<EntityManager>
{
	friend Singleton<EntityManager>;
public:
	enum ENTITY_TYPE
	{
		FIXED = 0,
		PROJECTILE,
		NUM_ENTITY_TYPE,
	};

	void Update(double _dt);
	void Render();
	void RenderUI();

	void AddEntity(EntityBase* _newEntity, ENTITY_TYPE sEntityType = FIXED);
	bool RemoveEntity(EntityBase* _existingEntity);
	void Destroy(void);
	int entityCount = 0;

private:
	EntityManager();
	virtual ~EntityManager();

	// Check for overlap
	bool CheckOverlap(Vector3 thisMinAABB, Vector3 thisMaxAABB, Vector3 thatMinAABB, Vector3 thatMaxAABB);
	// Check if this entity's bounding sphere collided with that entity's bounding sphere 
	bool CheckSphereCollision(EntityBase *ThisEntity, EntityBase *ThatEntity);
	// Check if this entity collided with another entity, but both must have collider
	bool CheckAABBCollision(EntityBase *ThisEntity, EntityBase *ThatEntity);
	// Check if any Collider is colliding with another Collider
	bool CheckForCollision(void);

	bool GetIntersection(const float fDist1, const float fDst2, Vector3 P1, Vector3 P2, Vector3 &Hit);
	bool CheckLineSegmentPlane(Vector3 line_start, Vector3 line_end, Vector3 minAABB, Vector3 maxAABB, Vector3 &Hit);

	bool InBox(Vector3 Hit, Vector3 B1, Vector3 B2, const int Axis);

	std::list<EntityBase*> entityList;
	//int entityCount = 0;
	std::list<EntityBase*> projectileList;
};

#endif // ENTITY_MANAGER_H