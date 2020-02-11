#include "Pistol.h"
#include "LuaManager.h"


CPistol::CPistol()
{
}


CPistol::~CPistol()
{
}

// Initialise this instance to default values
void CPistol::Init(void)
{
	// Call the parent's Init method
	CWeaponInfo::Init();

	// The number of ammunition in a magazine for this weapon
	//magRounds = 8;
	//// The maximum number of ammunition for this magazine for this weapon
	//maxMagRounds = 8;
	//// The current total number of rounds currently carried by this player
	//totalRounds = 40;
	//// The max total number of rounds currently carried by this player
	//maxTotalRounds = 40;

	//// The time between shots
	//timeBetweenShots = 0.3333;
	// The elapsed time (between shots)
	magRounds = CLuaManager::GetInstance()->get<int>("Pistol.magRounds");
	// The maximum number of ammunition for this magazine for this weapon
	//maxMagRounds = 1;
	maxMagRounds = CLuaManager::GetInstance()->get<int>("Pistol.maxMagRounds");

	// The current total number of rounds currently carried by this player
	//totalRounds = 8;
	totalRounds = CLuaManager::GetInstance()->get<int>("Pistol.totalRounds");

	// The max total number of rounds currently carried by this player
	//maxTotalRounds = 8;
	maxTotalRounds = CLuaManager::GetInstance()->get<int>("Pistol.maxTotalRounds");

	// The time between shots
	timeBetweenShots = CLuaManager::GetInstance()->get<float>("Pistol.timeBetweenShots");
	elapsedTime = 0.0;
	// Boolean flag to indicate if weapon can fire now
	bFire = true;
}
