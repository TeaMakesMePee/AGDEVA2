#include "Enemy3D.h"
#include "../EntityManager.h"
#include "GraphicsManager.h"
#include "RenderHelper.h"
#include "MeshBuilder.h"
#include "../Performance/Performance.h"

CEnemy3D::CEnemy3D(Mesh* _modelMesh)
	: GenericEntity(NULL)
	, destinationPosition(NULL)
	, m_pTerrain(NULL)
	, m_fElapsedTimeBeforeUpdate(0.0f)
{
	this->modelMesh = _modelMesh;

	//Init wapoint manager
	cWaypointManager.Init();
}


CEnemy3D::~CEnemy3D()
{
	//destry waypoint manager
	cWaypointManager.Destroy();
}

void CEnemy3D::Init(void)
{
	destinationPosition.Set(5.0f, 0.0f, 500.0f);

	// Set speed
	m_dSpeed = 1.0;

	//init cwaypointmanager
	cWaypointManager.Init();

	//add in some test waypoints
	int m_iWayPointID = cWaypointManager.AddWaypoint(Vector3(position.x, position.y, position.z));
	m_iWayPointID = cWaypointManager.AddWaypoint(m_iWayPointID, Vector3(position.x + 50.f, position.y, position.z));
	m_iWayPointID = cWaypointManager.AddWaypoint(m_iWayPointID, Vector3(position.x, position.y, position.z + 50.f));

	cWaypointManager.PrintSelf();
}

// Reset this player instance to default
void CEnemy3D::Reset(void)
{
	// Set the current values to default values
	/*
	position = defaultPosition;
	target = defaultTarget;
	up = defaultUp;
	*/
}

/*
// Set position
void CEnemy3D::SetPos(const Vector3& pos)
{
	position = pos;
}

// Set target
void CEnemy3D::SetTarget(const Vector3& target)
{
	this->target = target;
}
// Set Up
void CEnemy3D::SetUp(const Vector3& up)
{
	this->up = up;
}
*/

// Set the boundary for the player info
void CEnemy3D::SetBoundary(Vector3 max, Vector3 min)
{
	/*
	maxBoundary = max;
	minBoundary = min;
	*/
}
// Set the terrain for the player info
void CEnemy3D::SetTerrain(GroundEntity* m_pTerrain)
{
	if (m_pTerrain != NULL)
	{
		this->m_pTerrain = m_pTerrain;

		SetBoundary(this->m_pTerrain->GetMaxBoundary(), this->m_pTerrain->GetMinBoundary());
	}
}

// Set the speed of this Enemy's movement
void CEnemy3D::SetSpeed(const double m_dSpeed)
{
	this->m_dSpeed = m_dSpeed;
}
// Set the acceleration of this Enemy's movement
void CEnemy3D::SetAcceleration(const double m_dAcceleration)
{
	this->m_dAcceleration = m_dAcceleration;
}

/*
// Get position
Vector3 CEnemy3D::GetPos(void) const
{
	return position;
}

// Get target
Vector3 CEnemy3D::GetTarget(void) const
{
	return target;
}
// Get Up
Vector3 CEnemy3D::GetUp(void) const
{
	return up;
}
*/

// Get the terrain for the player info
GroundEntity* CEnemy3D::GetTerrain(void)
{
	return m_pTerrain;
}

// Get the speed of this Enemy's movement
double CEnemy3D::GetSpeed(void) const
{
	return m_dSpeed;
}
// Get the acceleration of this Enemy's movement
double CEnemy3D::GetAcceleration(void) const
{
	return m_dAcceleration;
}

// Update
void CEnemy3D::Update(double dt)
{
	Vector3 movementDirection = (destinationPosition - position).Normalized();
	position += movementDirection * (float)m_dSpeed * (float)dt;

	// Constrain the position
	Constrain();

	// This is RealTime Loop control
	// Update the target once every 5 seconds. 
	// Doing more of these calculations will not affect the outcome.
	m_fElapsedTimeBeforeUpdate += (float)dt;
	if (m_fElapsedTimeBeforeUpdate > 5.0f)
	{
		// Run A.I. algorithms here

		// Reset the timer
		m_fElapsedTimeBeforeUpdate = 0.0f;
	}
}

// Constrain the position within the borders
void CEnemy3D::Constrain(void)
{
	// Constrain player within the boundary
	//if (position.x > m_pTerrain->GetMaxBoundary().x - 20.0f)
	//{
	//	position.x = m_pTerrain->GetMaxBoundary().x - 20.0f;
	//}
	//if (position.z > m_pTerrain->GetMaxBoundary().z - 20.0f)
	//{
	//	position.z = m_pTerrain->GetMaxBoundary().z - 20.0f;
	//	destinationPosition.z = position.z * -1;
	//}
	//if (position.x < m_pTerrain->GetMinBoundary().x + 20.0f)
	//{
	//	position.x = m_pTerrain->GetMinBoundary().x + 20.0f;
	//}
	//if (position.z < m_pTerrain->GetMinBoundary().z + 20.0f)
	//{
	//	position.z = m_pTerrain->GetMinBoundary().z + 20.0f;
	//	destinationPosition.z = position.z * -1;
	//}

	if (cWaypointManager.HasReachedWayPoint(position))
		destinationPosition = cWaypointManager.GetNextWaypointPosition();

	// if the y position is not equal to terrain height at that position, 
	// then update y position to the terrain height
	if (position.y != m_pTerrain->GetTerrainHeight(position))
		position.y = m_pTerrain->GetTerrainHeight(position);
}

// Render
void CEnemy3D::Render(void)
{
	/*
	MS& modelStack = GraphicsManager::GetInstance()->GetModelStack();
	modelStack.PushMatrix();
	modelStack.Translate(position.x, position.y, position.z);
	modelStack.Scale(scale.x, scale.y, scale.z);
	*/
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

CEnemy3D* Create::Enemy3D(const std::string& _meshName,
	const Vector3& _position,
	const Vector3& _scale,
	const bool bAddToEntityManager)
{
	Mesh* modelMesh = MeshBuilder::GetInstance()->GetMesh(_meshName);
	if (modelMesh == nullptr)
		return nullptr;

	CEnemy3D* result = new CEnemy3D(modelMesh);
	result->SetPosition(_position);
	result->SetScale(_scale);
	result->SetCollider(false);
	EntityManager::GetInstance()->entityCount++;

	if (bAddToEntityManager)
		EntityManager::GetInstance()->AddEntity(result);
	return result;
}