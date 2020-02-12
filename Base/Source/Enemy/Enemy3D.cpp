#include "Enemy3D.h"
#include "../EntityManager.h"
#include "GraphicsManager.h"
#include "RenderHelper.h"
#include "MeshBuilder.h"
#include "../Performance/Performance.h"
#include "../Lua//LuaManager.h"

int CEnemy3D::count = 0;

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

void CEnemy3D::Init(CPlayerInfo* player, float health)
{
	this->player = player;
	this->health = health;
	destinationPosition.Set(0.f, 0.0f, 10.0f);

	// Set speed
	m_dSpeed = 1.0;

	//init cwaypointmanager
	cWaypointManager.Init();

	Vector3 aWayPoint_A(0.0f, 0.0f, 0.0f);
	Vector3 aWayPoint_B(0.0f, 0.0f, 0.0f);
	Vector3 aWayPoint_C(0.0f, 0.0f, 0.0f);
	Vector3 aWayPoint_D(0.0f, 0.0f, 0.0f);

	try
	{
		aWayPoint_A = CLuaManager::GetInstance()->get<Vector3>("WayPoints.Enemy_1.A");
		if ((aWayPoint_A.x == 0.0f) && (aWayPoint_A.y == 0.0f) && (aWayPoint_A.x == 0.0f))
			throw "error102";
		aWayPoint_B = CLuaManager::GetInstance()->get<Vector3>("WayPoints.Enemy_1.B");
		aWayPoint_C = CLuaManager::GetInstance()->get<Vector3>("WayPoints.Enemy_1.C");
		aWayPoint_D = CLuaManager::GetInstance()->get<Vector3>("WayPoints.Enemy_1.D");
	}
	catch (exception& e)
	{
		cout << e.what() << '\n';
	}
	catch (const char* sErrorMessage)
	{
		CLuaManager::GetInstance()->error(sErrorMessage);
	}

	// Apply offsets to the Enemy3D's position
	aWayPoint_A.x = position.x + aWayPoint_A.x;
	aWayPoint_A.z = position.z + aWayPoint_A.z;
	aWayPoint_B.x = position.x + aWayPoint_B.x;
	aWayPoint_B.z = position.z + aWayPoint_B.z;
	aWayPoint_C.x = position.x + aWayPoint_C.x;
	aWayPoint_C.z = position.z + aWayPoint_C.z;
	aWayPoint_D.x = position.x + aWayPoint_D.x;
	aWayPoint_D.z = position.z + aWayPoint_D.z;

	destinationPosition = aWayPoint_A;

	int m_iWayPointID = cWaypointManager.AddWaypoint(aWayPoint_A);
	m_iWayPointID = cWaypointManager.AddWaypoint(m_iWayPointID, aWayPoint_B);
	m_iWayPointID = cWaypointManager.AddWaypoint(m_iWayPointID, aWayPoint_C);
	m_iWayPointID = cWaypointManager.AddWaypoint(m_iWayPointID, aWayPoint_D);

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
	//Edittables *spd = new Edittables("EnemyInfo.speed", "float");
	//spd->floatvar = &this->m_dSpeed;
	//CLuaManager::GetInstance()->edittableList.push_back(spd);
	this->m_dSpeed = CLuaManager::GetInstance()->get<float>("EnemyInfo.speed");
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
	string state = CLuaManager::GetInstance()->AIDecision("AIDecision",
		player->GetPos(),
		position, health);

	if (state == "chase")
	{
		std::cout << "Chasing" << std::endl;
		Vector3 movementDirection = (player->GetPos() - position).Normalized();
		position += movementDirection * (float)m_dSpeed * (float)dt;
	}
	else if (state == "waypoint")
	{
		std::cout << "Waypoint" << std::endl;
		Vector3 movementDirection = (destinationPosition - position).Normalized();
		position += movementDirection * (float)m_dSpeed * (float)dt;
		position.y = 0.f;
	}
	else if (state == "heal")
	{
		std::cout << "Heal: " << health << std::endl;
		this->health += 10 * dt;
		Vector3 movementDirection = (player->GetPos() - position).Normalized();
		position += -movementDirection * (float)m_dSpeed * (float)dt;
	}

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

	
	MS& modelStack = GraphicsManager::GetInstance()->GetModelStack();
	modelStack.PushMatrix();
	modelStack.Translate(position.x, position.y, position.z);
	modelStack.Scale(scale.x, scale.y, scale.z);
	modelStack.PopMatrix();
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