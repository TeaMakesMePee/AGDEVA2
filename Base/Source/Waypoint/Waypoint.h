#pragma once

#include "Vector3.h"
#include <vector>
using namespace std;

class CWaypoint
{
public:
	// Constructor
	CWaypoint();
	// Destructor
	virtual ~CWaypoint();

	// Init this class instance
	void Init(void);
	// Destroy this class instance
	void Destroy(void);

	// Set position
	void SetPosition(Vector3 position);
	// Get position
	Vector3 GetPosition(void) const;

	// Set ID
	void SetID(const int m_iID);
	// Get position
	int GetID(void) const;

	// Add related waypoint
	void AddRelatedWaypoint(CWaypoint* relatedWaypoint);
	// Remove related waypoint
	bool RemoveRelatedWaypoint(const int m_iID);
	// Get nearest waypoint amongst related Waypoints
	CWaypoint* GetNearestWaypoint(void);
	// Get the number of related Waypoints
	int GetNumberOfWaypoints(void) const;

	// PrintSelf
	void PrintSelf(void);

protected:
	// Position of this WayPoint
	Vector3 position;

	// The ID of this WayPoint
	int m_iID;

	// Vector of related WayPoints
	vector<CWaypoint*> relatedWaypoints;
};