#ifndef ENTITY_BASE_H
#define ENTITY_BASE_H

#include "Vector3.h"
#include <vector>

class EntityBase
{
public:
	EntityBase();
	virtual ~EntityBase();

	virtual void Update(double _dt);
	virtual void Render();
	virtual void RenderUI();

	inline void SetPosition(const Vector3& _value){ position = _value; };
	inline Vector3 GetPosition(){ return position; };

	inline void SetVirtualPosition(const Vector3& _value) { virtualPosition = _value; };
	inline Vector3 GetVirtualPosition() { return virtualPosition; };

	inline void SetScale(const Vector3& _value){ scale = _value; };
	inline Vector3 GetScale(){ return scale; };

	bool IsDone();
	void SetIsDone(const bool _value);

	// Check if this entity has a collider class parent
	virtual bool HasCollider(void) const;
	// Set the flag to indicate if this entity has a collider class parent
	virtual void SetCollider(const bool _value);

	virtual void SetIsLaser(const bool bLaser);
	virtual bool GetIsLaser(void) const;

	//To give entities the information of their parent and child entities
	virtual void SetParent(EntityBase* parent);
	virtual EntityBase* GetParent(void);

	virtual void SetChildren(EntityBase* child);
	virtual std::vector<EntityBase*> GetChildren();

protected:
	Vector3 position;
	Vector3 virtualPosition;
	Vector3 scale;

	bool isDone;
	bool m_bCollider;
	bool bLaser;

	EntityBase* theParent;
	std::vector<EntityBase*> theChildren;
};

#endif // ENTITY_BASE_H