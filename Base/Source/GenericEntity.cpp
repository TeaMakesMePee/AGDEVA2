#include "GenericEntity.h"
#include "MeshBuilder.h"
#include "EntityManager.h"
#include "GraphicsManager.h"
#include "RenderHelper.h"
#include "Performance/Performance.h"

GenericEntity::GenericEntity(Mesh* _modelMesh)
	: modelMesh(_modelMesh)
{
}

GenericEntity::~GenericEntity()
{
}

void GenericEntity::Update(double _dt)
{
	// Does nothing here, can inherit & override or create your own version of this class :D
}

void GenericEntity::Render()
{
	//MS& modelStack = GraphicsManager::GetInstance()->GetModelStack();
	//modelStack.PushMatrix();
	//modelStack.Translate(position.x, position.y, position.z);
	//modelStack.Scale(scale.x, scale.y, scale.z);

	if (GetLODStatus())
	{
		if (theDetailLevel != NO_DETAILS)
		{
			if (CPerformance::GetInstance()->IsHighLODMode())
				theDetailLevel = HIGH_DETAILS;
			else if (CPerformance::GetInstance()->IsLowLODMode())
				theDetailLevel = LOW_DETAILS;
			RenderHelper::RenderMesh(GetLODMesh());
		}
	}
	else
		RenderHelper::RenderMesh(modelMesh);
	//modelStack.PopMatrix();
}

// Set the maxAABB and minAABB
void GenericEntity::SetAABB(Vector3 maxAABB, Vector3 minAABB)
{
	this->maxAABB = maxAABB;
	this->minAABB = minAABB;
}

void GenericEntity::GetAABB(Vector3 & maxAABB, Vector3 & minAABB)
{
	maxAABB = this->maxAABB;
	minAABB = this->minAABB;
}

GenericEntity* Create::Entity(	const std::string& _meshName, 
								const Vector3& _position,
								const Vector3& _scale,
								const bool bAddToEntityManager)
{
	Mesh* modelMesh = MeshBuilder::GetInstance()->GetMesh(_meshName);
	if (modelMesh == nullptr)
		return nullptr;

	GenericEntity* result = new GenericEntity(modelMesh);
	result->SetPosition(_position);
	result->SetScale(_scale);
	result->SetCollider(false);
	//EntityManager::GetInstance()->entityCount++;

	// Add to Entity Manager if bAddToEntityManager==true
	if (bAddToEntityManager)
		EntityManager::GetInstance()->AddEntity(result);
	return result;
}
