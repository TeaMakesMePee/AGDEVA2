#include "SpatialPartition.h"
#include "stdio.h"
#include "Collider\Collider.h"
#include "GraphicsManager.h"
#include "RenderHelper.h"
#include "../FrustumCulling/FrustumCulling.h"
#include "../Performance/Performance.h"

template <typename T> vector<T> concat(vector<T> &a, vector<T> &b) {
	vector<T> ret = vector<T>();
	copy(a.begin(), a.end(), back_inserter(ret));
	copy(b.begin(), b.end(), back_inserter(ret));
	return ret;
}

/********************************************************************************
 Constructor
 ********************************************************************************/
bool CSpatialPartition::IsVisible(Vector3 theCameraPosition,
	Vector3 theCameraDirection,
	const int xIndex, const int zIndex)
{
	float xGridCentre = (xGridSize * xIndex + (xGridSize >> 1) - (xSize >> 1));
	float zGridCentre = (zGridSize * zIndex + (zGridSize >> 1) - (zSize >> 1));

	if (theCameraPosition.x >= xGridCentre - (xGridSize >> 1) && theCameraPosition.x <= xGridCentre + (xGridSize >> 1))
		if (theCameraPosition.z >= zGridCentre - (zGridSize >> 1) && theCameraPosition.z <= zGridCentre + (zGridSize >> 1))
			return true;

	Vector3 offSetToGrid(xGridCentre - theCameraPosition.x, 0.f, zGridCentre - theCameraPosition.z);
	offSetToGrid.Normalize();
	if (theCameraDirection.Dot(offSetToGrid) < 0)
	{
		return false;
	}

	return true;
}

Vector3 CSpatialPartition::GetCentreByIndex(int xIndex, int yIndex)
{
	float xGridCentre = (xGridSize * xIndex + (xGridSize >> 1) - (xSize >> 1));
	float zGridCentre = (zGridSize * yIndex + (zGridSize >> 1) - (zSize >> 1));
	return Vector3(xGridCentre * 0.5f, 0, zGridCentre * 0.5f);
}

CSpatialPartition::CSpatialPartition(void)
	: theGrid(NULL)
	, xSize(0)
	, zSize(0)
	, xGridSize(0)
	, zGridSize(0)
	, xNumOfGrid(0)
	, zNumOfGrid(0)
	, yOffset(0.0f)
	, theCamera(NULL)
{
}

/********************************************************************************
 Destructor
 ********************************************************************************/
CSpatialPartition::~CSpatialPartition(void)
{
	theCamera = NULL;
}

/********************************************************************************
Initialise the spatial partition
********************************************************************************/
void CSpatialPartition::Destroy()
{
	if (theGrid)
	{
		delete[] theGrid;
	}
	Singleton<CSpatialPartition>::Destroy();
}

/********************************************************************************
 Initialise the spatial partition
 ********************************************************************************/
bool CSpatialPartition::Init(	const int xGridSize, const int zGridSize, 
								const int xNumOfGrid, const int zNumOfGrid, 
								const float yOffset)
{
	if ((xGridSize>0) && (zGridSize>0)
		&& (xNumOfGrid>0) && (zNumOfGrid>0))
	{
		this->xNumOfGrid = xNumOfGrid;
		this->zNumOfGrid = zNumOfGrid;
		this->xGridSize = xGridSize;
		this->zGridSize = zGridSize;
		this->xSize = xGridSize * xNumOfGrid;
		this->zSize = zGridSize * zNumOfGrid;
		this->yOffset = yOffset;

		// Create an array of grids
		theGrid = new CGrid[ xNumOfGrid*zNumOfGrid ];

		// Initialise the array of grids
		for (int i=0; i<xNumOfGrid; i++)
		{
			for (int j=0; j<zNumOfGrid; j++)
			{
				theGrid[i*zNumOfGrid + j].Init(i, j, xGridSize, zGridSize, (float)(xSize >> 1), (float)(zSize >> 1));
				float xGridCentre = (xGridSize * i + (xGridSize >> 1) - (xSize >> 1));
				float zGridCentre = (zGridSize * j + (zGridSize >> 1) - (zSize >> 1));
				theGrid[i*zNumOfGrid + j].SetCentre(Vector3(xGridCentre * 0.5f, 0, zGridCentre * 0.5f));
			}
		}

		// Assign a Mesh to each Grid if available.
		//ApplyMesh();

		// Create a migration list vector
		MigrationList.clear();

		return true;
	}
	return false;
}

/********************************************************************************
 Set Mesh's Render Mode
 ********************************************************************************/
void CSpatialPartition::SetMeshRenderMode(CGrid::SMeshRenderMode meshRenderMode)
{
	this->meshRenderMode = meshRenderMode;

	// Initialise the array of grids
	for (int i = 0; i<xNumOfGrid; i++)
	{
		for (int j = 0; j<zNumOfGrid; j++)
		{
			theGrid[i*zNumOfGrid + j].SetMeshRenderMode(meshRenderMode);
		}
	}
}

/********************************************************************************
 Get Mesh's Render Mode
 ********************************************************************************/
CGrid::SMeshRenderMode CSpatialPartition::GetMeshRenderMode(void) const
{
	if (xNumOfGrid*zNumOfGrid > 0)
		return theGrid[0].GetMeshRenderMode();
	else
		return CGrid::FILL;
}

/********************************************************************************
 Set a particular grid's Mesh
 ********************************************************************************/
void CSpatialPartition::SetMesh(const std::string& _meshName, const std::string& _meshName2, const std::string& _meshName3)
{
	//this->_meshName = _meshName;
	if (_meshName.size() != 0)
	{
		for (int i = 0; i < xNumOfGrid; i++)
		{
			for (int j = 0; j < zNumOfGrid; j++)
			{
				theGrid[i*zNumOfGrid + j].SetMesh(_meshName, _meshName2, _meshName3);
			}
		}
	}
	// Assign a Mesh to each Grid if available.
	//ApplyMesh();
}

/********************************************************************************
  ApplyMesh
 ********************************************************************************/
void CSpatialPartition::ApplyMesh(void)
{
	//if (_meshName.size() != 0)
	//{
	//	for (int i = 0; i<xNumOfGrid; i++)
	//	{
	//		for (int j = 0; j<zNumOfGrid; j++)
	//		{
	//			theGrid[i*zNumOfGrid + j].SetMesh(_meshName);
	//		}
	//	}
	//}
}

/********************************************************************************
Update the spatial partition
********************************************************************************/
void CSpatialPartition::Update(void)
{
	//cout << "Rendering these grids:" << endl;
	int details = 0;
	int nodetails = 0;
	for (int i = 0; i < xNumOfGrid; i++)
	{
		for (int j = 0; j < zNumOfGrid; j++)
		{
			// Update the grid
			theGrid[i*zNumOfGrid + j].Update(&MigrationList);

			if (CPerformance::GetInstance()->IsViewTest())
			{	
				if (IsVisible(theCamera->GetCameraPos(), theCamera->GetCameraTarget() - theCamera->GetCameraPos(), i, j))
				{
					// Calculate LOD for this CGrid
					float distance = CalculateDistanceSquare(&(theCamera->GetCameraPos()), i, j);
					if (distance < LevelOfDetails_Distances[0])
					{
						theGrid[i*zNumOfGrid + j].SetDetailLevel(CLevelOfDetails::HIGH_DETAILS);
					}
					else if (distance < LevelOfDetails_Distances[1])
					{
						theGrid[i*zNumOfGrid + j].SetDetailLevel(CLevelOfDetails::MID_DETAILS);
					}
					else
					{
						theGrid[i*zNumOfGrid + j].SetDetailLevel(CLevelOfDetails::LOW_DETAILS);
					}
					details++;
				}
				else
				{
					theGrid[i * zNumOfGrid + j].SetDetailLevel(CLevelOfDetails::NO_DETAILS);
					nodetails++;
				}

				float gridXPos = (float)(xGridSize* i + (xGridSize >> 1) - (xSize >> 1));
				float gridZPos = (float)(zGridSize* j + (zGridSize >> 1) - (zSize >> 1));
				Vector3 gridPos(gridXPos, 0.f, gridZPos);

				if (CPerformance::GetInstance()->IsFrustumView())
				{
					if (!CFrustumCulling::GetInstance()->isBoxInFrustum(gridPos, xGridSize, zGridSize))
					{
						theGrid[i * zNumOfGrid + j].SetDetailLevel(CLevelOfDetails::NO_DETAILS);
					}
				}
			}
			else
			{
				float distance = CalculateDistanceSquare(&(theCamera->GetCameraPos()), i, j);
				if (distance < LevelOfDetails_Distances[0])
				{
					theGrid[i*zNumOfGrid + j].SetDetailLevel(CLevelOfDetails::HIGH_DETAILS);
				}
				else if (distance < LevelOfDetails_Distances[1])
				{
					theGrid[i*zNumOfGrid + j].SetDetailLevel(CLevelOfDetails::MID_DETAILS);
				}
				else
				{
					theGrid[i*zNumOfGrid + j].SetDetailLevel(CLevelOfDetails::LOW_DETAILS);
				}
			}
		}
		//cout << endl;
	}
	//cout << "Viewing " << details << " amount of grids." << endl;
	//cout << "Not Viewing " << nodetails << " amount of grids." << endl;

	// If there are objects due for migration, then process them
	if (MigrationList.empty() == false)
	{
		// Check each object to see if they are no longer in this grid
		for (int i = 0; i < (int)MigrationList.size(); ++i)
		{
			Add(MigrationList[i]);
		}

		MigrationList.clear();
	}
}

/********************************************************************************
Render the spatial partition
********************************************************************************/
void CSpatialPartition::Render(Vector3 theCameraPosition, Vector3 theCameraTarget, Vector3 theCameraUp)
{
	CFrustumCulling::GetInstance()->Update(theCameraPosition, theCameraTarget, theCameraUp);

	// Render the Spatial Partitions
	MS& modelStack = GraphicsManager::GetInstance()->GetModelStack();

	modelStack.PushMatrix();
	modelStack.Translate(0.0f, yOffset, 0.0f);

	for (int i = 0; i < xNumOfGrid; i++)
	{
		for (int j = 0; j < zNumOfGrid; j++)
		{
			// Set up the variables for the grid coordinates
			float gridXPos = (float)(xGridSize* i + (xGridSize >> 1) - (xSize >> 1));
			float gridZPos = (float)(zGridSize* j + (zGridSize >> 1) - (zSize >> 1));
			Vector3 gridPos(gridXPos, 0.f, gridZPos);

			// Do Frustum Culling. We only render the grid if it is in the Frustum
			//if (CFrustumCulling::GetInstance()->isBoxInFrustum(gridPos, xGridSize, zGridSize))		// || EnableVisibilityCheck)
			//{
			modelStack.PushMatrix();
			modelStack.Translate((float)(xGridSize*i - (xSize >> 1) + (xGridSize >> 1)), 0.0f, (float)(zGridSize*j - (zSize >> 1) + (zGridSize >> 1)));
			modelStack.PushMatrix();
			modelStack.Scale((float)xGridSize, 1.0f, (float)zGridSize);
			modelStack.Rotate(-90, 1, 0, 0);
			theGrid[i*zNumOfGrid + j].Render();
			modelStack.PopMatrix();
			modelStack.PopMatrix();
			//}
		}
	}

	modelStack.PopMatrix();
}

/********************************************************************************
 Get xSize of the entire spatial partition
********************************************************************************/
int CSpatialPartition::GetxSize(void) const
{
	return xSize;
}
/********************************************************************************
 Get zSize of the entire spatial partition
********************************************************************************/
int CSpatialPartition::GetzSize(void) const
{
	return zSize;
}
/********************************************************************************
 Get xSize
********************************************************************************/
int CSpatialPartition::GetxGridSize(void) const
{
	return xGridSize;
}
/********************************************************************************
 Get zNumOfGrid
********************************************************************************/
int CSpatialPartition::GetzGridSize(void) const
{
	return zGridSize;
}
/********************************************************************************
Get xNumOfGrid
********************************************************************************/
int CSpatialPartition::GetxNumOfGrid(void) const
{
	return xNumOfGrid;
}
/********************************************************************************
Get zNumOfGrid
********************************************************************************/
int CSpatialPartition::GetzNumOfGrid(void) const
{
	return zNumOfGrid;
}

/********************************************************************************
 Get a particular grid
 ********************************************************************************/
CGrid CSpatialPartition::GetGrid(const int xIndex, const int yIndex) const
{
	return theGrid[ xIndex*zNumOfGrid + yIndex ];
}

CGrid CSpatialPartition::GetGrid(const int index) const
{
	return theGrid[index];
}

CGrid * CSpatialPartition::GetGrid()
{
	return this->theGrid;
}

/********************************************************************************
 Get vector of objects from this Spatial Partition
 ********************************************************************************/
vector<EntityBase*> CSpatialPartition::GetObjects(Vector3 position, const float radius)
{
	// Get the indices of the object's position
	int xIndex = (((int)position.x - (-xSize >> 1)) / (xSize / xNumOfGrid));
	int zIndex = (((int)position.z - (-zSize >> 1)) / (zSize / zNumOfGrid));

	if (((xIndex < 0) || (zIndex < 0)) || ((xIndex >= xNumOfGrid) || (zIndex >= zNumOfGrid)))
	{
		vector<EntityBase*> ListOfObjects;
		return ListOfObjects;
	}

	return theGrid[xIndex*zNumOfGrid + zIndex].GetListOfObject(position, radius);
}

/********************************************************************************
 Add a new object model
 ********************************************************************************/
void CSpatialPartition::Add(EntityBase* theObject)
{
	// Get the indices of the object's position
	int xIndex = (((int)theObject->GetPosition().x - (-xSize >> 1)) / (xSize / xNumOfGrid));
	int zIndex = (((int)theObject->GetPosition().z - (-zSize >> 1)) / (zSize / zNumOfGrid));

	//int xIndex = (theObject->GetPosition().x - (xGridSize >> 1) + (xSize >> 1)) / xGridSize;
	//int zIndex = (theObject->GetPosition().z - (zGridSize >> 1) + (zSize >> 1)) / zGridSize;
	// Add them to each grid
	if (((xIndex >= 0) && (xIndex<xNumOfGrid)) && ((zIndex >= 0) && (zIndex<zNumOfGrid)))
	{

		theGrid[xIndex*zNumOfGrid + zIndex].Add(theObject);
	}
}

// Remove but not delete object from this grid
void CSpatialPartition::Remove(EntityBase* theObject)
{
	
	// Get the indices of the object's position
	int posX = theObject->GetPosition().x;
	int posY = theObject->GetPosition().z;
	if (theObject->GetParent())
	{
		posX += theObject->GetParent()->GetPosition().x;
		posY += theObject->GetParent()->GetPosition().z;
	}
	else
	{
		std::vector<EntityBase*> chldrn = theObject->GetChildren();
		for (auto c : chldrn)
		{
			int posX = c->GetPosition().x + theObject->GetPosition().x;
			int posY = c->GetPosition().z + theObject->GetPosition().z;
			int xIndex = (((int)posX - (-xSize >> 1)) / (xSize / xNumOfGrid));
			int zIndex = (((int)posY - (-zSize >> 1)) / (zSize / zNumOfGrid));
			if (((xIndex >= 0) && (xIndex < xNumOfGrid)) && ((zIndex >= 0) && (zIndex < zNumOfGrid)))
			{
				theGrid[xIndex*zNumOfGrid + zIndex].Remove(c);
			}
		}
	}

	int xIndex = (((int)posX - (-xSize >> 1)) / (xSize / xNumOfGrid));
	int zIndex = (((int)posY - (-zSize >> 1)) / (zSize / zNumOfGrid));

	// Add them to each grid
	if (((xIndex >= 0) && (xIndex<xNumOfGrid)) && ((zIndex >= 0) && (zIndex<zNumOfGrid)))
	{
		theGrid[xIndex*zNumOfGrid + zIndex].Remove(theObject);
	}
	
}

/********************************************************************************
 Calculate the squared distance from camera to a grid's centrepoint
 ********************************************************************************/
float CSpatialPartition::CalculateDistanceSquare(Vector3* theCameraPosition, const int xIndex, const int zIndex)
{
	float xDistance = (xGridSize*xIndex - (xSize >> 1) + (xGridSize >> 1))
		- theCameraPosition->x;
	float yDistance = (zGridSize*zIndex - (zSize >> 1) + (zGridSize >> 1))
		- theCameraPosition->z;

	return (float)(xDistance*xDistance + yDistance * yDistance);
}

void CSpatialPartition::SetCamera(FPSCamera * _cameraPtr)
{
	theCamera = _cameraPtr;
}

void CSpatialPartition::RemoveCamera(void)
{
	theCamera = nullptr;
}

void CSpatialPartition::SetLevelOfDetails(const float distance_High2Mid, const float distance_Mid2Low)
{
	LevelOfDetails_Distances[0] = distance_High2Mid;
	LevelOfDetails_Distances[1] = distance_Mid2Low;
}


/********************************************************************************
 PrintSelf
 ********************************************************************************/
void CSpatialPartition::PrintSelf() const
{
	cout << "******* Start of CSpatialPartition::PrintSelf() **********************************" << endl;
	cout << "xSize\t:\t" << xSize << "\tzSize\t:\t" << zSize << endl;
	cout << "xNumOfGrid\t:\t" << xNumOfGrid << "\tzNumOfGrid\t:\t" << zNumOfGrid << endl;
	if (theGrid)
	{
		cout << "theGrid : OK" << endl;
		cout << "Printing out theGrid below: " << endl;
		for (int i=0; i<xNumOfGrid; i++)
		{
			for (int j=0; j<zNumOfGrid; j++)
			{
				theGrid[ i*zNumOfGrid + j ].PrintSelf();
			}
		}
	}
	else
		cout << "theGrid : NULL" << endl;
	cout << "******* End of CSpatialPartition::PrintSelf() **********************************" << endl;
}
