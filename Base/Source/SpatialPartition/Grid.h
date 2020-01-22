#pragma once

#include "EntityBase.h"
#include "Vector3.h"
#include "Mesh.h"
#include <vector>
using namespace std;

#include "../LevelOfDetails/LevelOfDetails.h"

//Include GLEW
#include <GL/glew.h>

class CGrid
{
public:
	enum SMeshRenderMode
	{
		WIRE,
		FILL,
		NUM_MODE
	};

	// Constructor
	CGrid(void);
	// Destructor
	~CGrid(void);

	// Init
	void Init(	const int xIndex, const int zIndex, 
				const int xGridSize, const int zGridSize,
				const float xOffset = 0, const float zOffset = 0);

	// Set a particular grid's Mesh
	void SetMesh(const std::string& _meshName, const std::string& _meshName2, const std::string& _meshName3);
	// Set Mesh's Render Mode
	void SetMeshRenderMode(CGrid::SMeshRenderMode meshRenderMode);
	// Get Mesh's Render Mode
	CGrid::SMeshRenderMode GetMeshRenderMode(void) const;

	// Update the grid
	void Update(vector<EntityBase*>* migrationList);
	// Render the grid
	void Render(void);
	// RenderObjects
	void RenderObjects(const int RESOLUTION);

	// Add a new object to this grid
	void Add(EntityBase* theObject);
	// Remove but not delete all objects from this grid
	void Remove(void);
	// Remove but not delete an object from this grid
	bool Remove(EntityBase* theObject);

	// Check if an object is in this grid
	bool IsHere(EntityBase* theObject) const;

	// Get list of objects in this grid
	vector<EntityBase*> GetListOfObject(Vector3 position, const float radius = 0.0f);

	void SetDetailLevel(const CLevelOfDetails::DETAIL_LEVEL theDetailLevel);
	// PrintSelf
	void PrintSelf(void);

	bool GetOccupied(void);
	void SetOccupied(bool x);

	Vector3 GetCentre(void);
	void SetCentre(Vector3 pos);

protected:
	// We use a Vector3 to store the indices of this Grid within the Spatial Partition array.
	Vector3 index;
	// We use a Vector3 to store the size of this Grid within the Spatial Partition array.
	Vector3 size;
	// We use a Vector3 to store the x- and z-offset of this Grid.
	Vector3 offset;
	// We use a Vector3 to store the x- and z-offset of this Grid.
	Vector3 min, max;

	// The mesh to represent the grid
	Mesh *theMesh1, *theMesh2, *theMesh3;
	// Define the mesh render mode
	SMeshRenderMode meshRenderMode;

	// List of objects in this grid
	vector<EntityBase*> ListOfObjects;

	CLevelOfDetails::DETAIL_LEVEL theDetailLevel;

	bool occupied;
	Vector3 centre;
};
