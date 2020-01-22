#pragma once
#include "Waypoint.h"
#include "Vector3.h"
#include <vector>
using namespace std;

class CWaypointManager
{
public:
	// Constructor
	CWaypointManager();
	// Destructor
	virtual ~CWaypointManager();

	// Init
	void Init(void);
	// Destroy the instance
	void Destroy(void);

	// Add waypoint
	int AddWaypoint(Vector3 position);
	// Add the position of a waypoint by searching for its m_iID
	int AddWaypoint(const int m_iID, Vector3 position);
	// Remove waypoint based on its m_iID
	bool RemoveWaypoint(const int m_iID);

	// Get next ID when adding a waypoint
	int GetNextIDToAdd(void);
	// Get Current ID
	int GetCurrentID(void);
	// Get Next WayPoint ID
	int GetNextWayPointID(void);

	// HasReachedWayPoint
	bool HasReachedWayPoint(Vector3 aPosition);
	// Get a Waypoint based on its ID
	CWaypoint* GetWaypoint(const int m_iID);
	// Get nearest waypoint amongst related Waypoints
	// This method is used when your NPC has deviated from the WayPoints 
	// and it needs to find the nearest WayPoint to go to
	CWaypoint* GetNearestWaypoint(Vector3 aPosition);
	// Get next waypoint
	CWaypoint* GetNextWaypoint(void);
	// Get next waypoint position
	Vector3 GetNextWaypointPosition(void);
	// Get the number of related Waypoints
	int GetNumberOfWaypoints(void) const;

	// PrintSelf
	void PrintSelf(void);

protected:
	// The current Waypoint's ID
	int m_iCurrentID;
	// Distance tolerance for checking proximity to a WayPoint
	float m_fDistanceTolerance;

	vector<CWaypoint*> listOfWaypoints;

	// Remove related waypoint
	void RemoveRelatedWaypoint(const int m_iID);
};