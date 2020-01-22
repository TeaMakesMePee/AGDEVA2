#include "WaypointManager.h"
#include <iostream>
using namespace std;

// Constructor
CWaypointManager::CWaypointManager()
	: m_iCurrentID(-1)
	, m_fDistanceTolerance(16.0f)	// We set the tolerance to 4.0 units squared == 16.0 units
{
	// Initialise this class
	Init();
}

// Destructor
CWaypointManager::~CWaypointManager()
{
	// Destroy this class
	Destroy();
}

// Init
void CWaypointManager::Init(void)
{
	// Set the m_iCurrentID to zero. 
	m_iCurrentID = 0;
	// Clear the listOfWaypoints
	listOfWaypoints.clear();
}

// Destroy the Singleton instance
void CWaypointManager::Destroy(void)
{
	// If listOfWaypoints is not empty, then proceed to delete
	if (listOfWaypoints.size() != 0)
	{
		// Iterate through all the Waypoints
		// Destroy the children first
		vector<CWaypoint*>::iterator it;
		for (it = listOfWaypoints.begin(); it != listOfWaypoints.end(); ++it)
		{
			// Delete an entry
			delete *it;
		}
	}
	// We delete the waypoints here
	listOfWaypoints.clear();
}

// Add waypoint
int CWaypointManager::AddWaypoint(Vector3 position)
{
	// Create a new CWayPoint
	CWaypoint* aNewWaypoint = new CWaypoint();
	// Get the next ID
	int m_iNextID = GetNextIDToAdd();
	// Assign to the new WayPoint
	aNewWaypoint->SetID(m_iNextID);
	// Set its position
	aNewWaypoint->SetPosition(position);
	// Push it into the listOfWaypoints
	listOfWaypoints.push_back(aNewWaypoint);
	// Return the m_iNextID
	return m_iNextID;
}

// Add a new waypoint to the list by searching for its ID, and it is related to an existing WayPoint
int CWaypointManager::AddWaypoint(const int m_iID, Vector3 position)
{
	// If Waypoints is not empty, then we proceed to search.
	if (listOfWaypoints.size() != 0)
	{
		// Loop through the listOfWaypoints
		for (unsigned i = 0; i < listOfWaypoints.size(); ++i)
		{
			CWaypoint* aWayPoint = listOfWaypoints[i];

			if (aWayPoint->GetID() == m_iID)
			{
				// Get the next ID
				int m_iNextID = GetNextIDToAdd();
				// Create a new WayPoint
				CWaypoint* aNewWaypoint = new CWaypoint();
				// Set the m_iNextID as the ID for the new waypoint
				aNewWaypoint->SetID(m_iNextID);
				// Set the position of the new waypoint
				aNewWaypoint->SetPosition(position);
				// Add it to listOfWaypoints
				listOfWaypoints.push_back(aNewWaypoint);

				// Add the current Waypoint as a related waypoint to the new Waypoint
				aNewWaypoint->AddRelatedWaypoint(aWayPoint);
				// Add this new Waypoint as a related waypoint to the current Waypoint
				aWayPoint->AddRelatedWaypoint(aNewWaypoint);

				return m_iNextID;
			}
		}
	}
	return -1;
}

// Remove waypoint based on its m_iNextID
bool CWaypointManager::RemoveWaypoint(const int m_iID)
{
	// Declare a boolean flag called result and its default value is false
	bool result = false;

	// If Waypoints is not empty, then we proceed to search.
	if (listOfWaypoints.size() != 0)
	{
		// Iterate through all the Waypoints
		std::vector<CWaypoint*>::iterator it = listOfWaypoints.begin();
		while (it != listOfWaypoints.end())
		{
			// If the WayPoint's ID matches the requested m_iNextID
			if ((*it)->GetID() == m_iID)
			{
				// Remove all references to this Waypoint from other Waypoints
				RemoveRelatedWaypoint(m_iID);

				// Remove this Waypoint from the WaypointManager
				delete *it;
				// Erase the waypoint from listOfWaypoints
				it = listOfWaypoints.erase(it);
				// Set the boolean result to true as this is successful
				result = true;
				break;
			}

			// Increase the iterator is we have not reach the end of listOfWaypoints
			if (it != listOfWaypoints.end())
				it++;
		}
	}
	return result;
}

// Remove related waypoint
void CWaypointManager::RemoveRelatedWaypoint(const int m_iID)
{
	// Iterate through all the Waypoints
	std::vector<CWaypoint*>::iterator it = listOfWaypoints.begin();
	while (it != listOfWaypoints.end())
	{
		(*it)->RemoveRelatedWaypoint(m_iID);
		it++;
	}
}

// Get next ID when adding a waypoint
int CWaypointManager::GetNextIDToAdd(void)
{
	// The next ID is the size of listOfWaypoints
	return GetNumberOfWaypoints();
}

// Get Current ID
int CWaypointManager::GetCurrentID(void)
{
	return m_iCurrentID;
}

// Get Next WayPoint ID
int CWaypointManager::GetNextWayPointID(void)
{
	// If we have reach the end of the listOfWaypoints, then we reset to 0
	m_iCurrentID++;
	if (m_iCurrentID >= listOfWaypoints.size())
		m_iCurrentID = 0;

	return m_iCurrentID;
}

// HasReachedWayPoint
bool CWaypointManager::HasReachedWayPoint(Vector3 aPosition)
{
	// Check if there is at least 1 WayPoint
	if (listOfWaypoints.size() > 0)
	{
		// Get the position of current WayPoint
		Vector3 currentWaypointPosition = listOfWaypoints[m_iCurrentID]->GetPosition();

		// Calculate the x- and z- component distance
		float xDistance = aPosition.x - currentWaypointPosition.x;
		float zDistance = aPosition.z - currentWaypointPosition.z;
		// Calculate the distance squared value. We avoid square root as it is expensive
		float distanceSquared = (float)(xDistance*xDistance + zDistance*zDistance);
		// if the distance between aPosition and the current WayPoint is within m_fDistanceTolerance value
		if (distanceSquared < m_fDistanceTolerance)
		{
			// then return true
			return true;
		}
	}
	// Return false is aPosition is not near the current WayPoint
	return false;
}

// Get a Waypoint based on its ID
CWaypoint* CWaypointManager::GetWaypoint(const int m_iID)
{
	// If Waypoints is not empty, then we proceed to search.
	if (listOfWaypoints.size() != 0)
	{
		// Iterate through all the Waypoints
		std::vector<CWaypoint*>::iterator it = listOfWaypoints.begin();
		while (it != listOfWaypoints.end())
		{
			if ((*it)->GetID() == m_iID)
			{
				// Assign m_iID to the current ID
				m_iCurrentID = m_iID;
				return (CWaypoint*)(*it);
			}
			it++;
		}
	}
	return NULL;
}

// Get nearest waypoint amongst related Waypoints
// This method is used when your NPC has deviated from the WayPoints 
// and it needs to find the nearest WayPoint to go to
CWaypoint* CWaypointManager::GetNearestWaypoint(Vector3 aPosition)
{
	CWaypoint* theNearestWaypoint = NULL;
	float m_fDistance = numeric_limits<float>::max();

	// If Waypoints has related Waypoints, then we proceed to search.
	if (listOfWaypoints.size() != 0)
	{
		// Iterate through all the Waypoints to find the nearest WayPoint
		std::vector<CWaypoint*>::iterator it = listOfWaypoints.begin();
		while (it != listOfWaypoints.end())
		{
			Vector3 aRelatedWaypoint = (*it)->GetPosition();

			float xDistance = aPosition.x - aRelatedWaypoint.x;
			float zDistance = aPosition.z - aRelatedWaypoint.z;
			float distanceSquared = (float)(xDistance*xDistance + zDistance*zDistance);
			if (m_fDistance > distanceSquared)
			{
				// Update the m_fDistance to this lower distance
				m_fDistance = distanceSquared;
				// Set this WayPoint as the nearest WayPoint
				theNearestWaypoint = (CWaypoint*)(*it);
			}
			it++;
		}
	}
	if (theNearestWaypoint)
	{
		// Update the current ID
		m_iCurrentID = theNearestWaypoint->GetID();
	}
	else
	{
		// Set to a value which is impossible to achieve, so that the program will crash.
		m_iCurrentID = -1;
	}

	return theNearestWaypoint;
}

// Get next waypoint
CWaypoint* CWaypointManager::GetNextWaypoint(void)
{
	// If Waypoints is not empty, then we proceed to search.
	if (listOfWaypoints.size() != 0)
	{
		m_iCurrentID = GetNextWayPointID();

		return (CWaypoint*)listOfWaypoints[m_iCurrentID];
	}

	return NULL;
}

// Get next waypoint position
Vector3 CWaypointManager::GetNextWaypointPosition(void)
{
	CWaypoint* cWayPoint = GetNextWaypoint();
	if (cWayPoint)
		return cWayPoint->GetPosition();
	else
		// Return the origin is there is no WayPoint available
		return Vector3(0.0f, 0.0f, 0.0f);
}

// Get the number of related Waypoints
int CWaypointManager::GetNumberOfWaypoints(void) const
{
	return (int)listOfWaypoints.size();
}

// PrintSelf
void CWaypointManager::PrintSelf(void)
{
	cout << "================================================================================" << endl;
	cout << "CWaypointManager::PrintSelf" << endl;
	// If Waypoints has related Waypoints, then we proceed to search.
	if (listOfWaypoints.size() != 0)
	{
		// Iterate through all the Waypoints
		vector<CWaypoint*>::iterator it = listOfWaypoints.begin();
		while (it != listOfWaypoints.end())
		{
			(*it)->PrintSelf();
			it++;
		}
	}
	cout << "================================================================================" << endl;
}
