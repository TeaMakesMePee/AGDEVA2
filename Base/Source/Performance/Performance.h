#pragma once

#include "SingletonTemplate.h"

class CPerformance : public Singleton<CPerformance>
{
	friend Singleton<CPerformance>;
public:
	// Destructor
	virtual ~CPerformance();

	void SetFaceCount(int count);
	int GetFaceCount(void);

	void SetCollisionCheckCount(int count);
	int GetCollisionCheckCount(void);

	bool IsSpatialPartition(void);
	void SetIsSpatialPartition(bool x);

	bool IsSceneGraph(void);
	void SetIsSceneGraph(bool x);

	bool IsOrthoView(void);
	void SetIsOrthoView(bool x);

	bool IsFrustumView(void);
	void SetIsFrustumView(bool x);
	
	bool IsHighLODMode(void);
	void SetIsHighLODMode(bool x);

	bool IsLowLODMode(void);
	void SetIsLowLODMode(bool x);

	bool IsViewTest(void);
	void SetIsViewTest(bool x);

private:
	// Constructor
	CPerformance(void);
	int faceCount;
	int collisionCheckCount;

	bool usingSpatialPartitioning;
	bool usingSceneGraph;

	bool orthoView;

	bool frustumCull;

	bool HighLODMode;
	bool LowLODMode;

	bool viewTest;
};
