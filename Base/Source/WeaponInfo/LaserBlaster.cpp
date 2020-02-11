#include "LaserBlaster.h"
#include "../Projectile/Laser.h"
#include "MeshBuilder.h"
#include "../EntityManager.h"
#include "LuaManager.h"

CLaserBlaster::CLaserBlaster()
{
}


CLaserBlaster::~CLaserBlaster()
{
}

// Initialise this instance to default values
void CLaserBlaster::Init(void)
{
	// Call the parent's Init method
	CWeaponInfo::Init();

	//// The number of ammunition in a magazine for this weapon
	//magRounds = 5;
	//// The maximum number of ammunition for this magazine for this weapon
	//maxMagRounds = 5;
	//// The current total number of rounds currently carried by this player
	//totalRounds = 10;
	//// The max total number of rounds currently carried by this player
	//maxTotalRounds = 10;

	//// The time between shots
	//timeBetweenShots = 0.1667;
	magRounds = CLuaManager::GetInstance()->get<int>("Laser.magRounds");
	// The maximum number of ammunition for this magazine for this weapon
	//maxMagRounds = 1;
	maxMagRounds = CLuaManager::GetInstance()->get<int>("Laser.maxMagRounds");

	// The current total number of rounds currently carried by this player
	//totalRounds = 8;
	totalRounds = CLuaManager::GetInstance()->get<int>("Laser.totalRounds");

	// The max total number of rounds currently carried by this player
	//maxTotalRounds = 8;
	maxTotalRounds = CLuaManager::GetInstance()->get<int>("Laser.maxTotalRounds");

	// The time between shots
	timeBetweenShots = CLuaManager::GetInstance()->get<float>("Laser.timeBetweenShots");
	// The elapsed time (between shots)
	elapsedTime = 0.0;
	// Boolean flag to indicate if weapon can fire now
	bFire = true;
}

// Discharge this weapon
void CLaserBlaster::Discharge(Vector3 position, Vector3 target, CPlayerInfo* _source)
{
	if (bFire)
	{
		// If there is still ammo in the magazine, then fire
		if (magRounds > 0)
		{
			Vector3 _direction = (target - position).Normalized();
			// Create a laser with a laser mesh. The length is 10.0f, mesh is also set at 10.0f
			CLaser* aLaser = Create::Laser("laser",
				position,
				_direction,
				0.1f,		// Length of laser
				30.0f,		// Life of laser
				3.0f,		// Speed of laser
				_source);
			aLaser->SetIsLaser(true);
			aLaser->SetCollider(true);
			aLaser->SetAABB(Vector3(0.5f, 0.5f, 0.5f), Vector3(-0.5f, -0.5f, -0.5f));
			bFire = false;
			magRounds--;
		}
	}
}
