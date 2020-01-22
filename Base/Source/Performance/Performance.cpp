#include "Performance.h"

CPerformance::~CPerformance()
{
}

void CPerformance::SetFaceCount(int count)
{
	this->faceCount = count;
}

int CPerformance::GetFaceCount(void)
{
	return faceCount;
}

void CPerformance::SetCollisionCheckCount(int count)
{
	this->collisionCheckCount = count;
}

int CPerformance::GetCollisionCheckCount(void)
{
	return collisionCheckCount;
}

bool CPerformance::IsSpatialPartition(void)
{
	return usingSpatialPartitioning;
}

void CPerformance::SetIsSpatialPartition(bool x)
{
	this->usingSpatialPartitioning = x;
}

bool CPerformance::IsSceneGraph(void)
{
	return usingSceneGraph;
}

void CPerformance::SetIsSceneGraph(bool x)
{
	this->usingSceneGraph = x;
}

bool CPerformance::IsOrthoView(void)
{
	return orthoView;
}

void CPerformance::SetIsOrthoView(bool x)
{
	this->orthoView = x;
}

bool CPerformance::IsFrustumView(void)
{
	return frustumCull;
}

void CPerformance::SetIsFrustumView(bool x)
{
	this->frustumCull = x;
}

bool CPerformance::IsHighLODMode(void)
{
	return HighLODMode;
}

void CPerformance::SetIsHighLODMode(bool x)
{
	this->HighLODMode = x;
}

bool CPerformance::IsLowLODMode(void)
{
	return LowLODMode;
}

void CPerformance::SetIsLowLODMode(bool x)
{
	this->LowLODMode = x;
}

bool CPerformance::IsViewTest(void)
{
	return viewTest;
}

void CPerformance::SetIsViewTest(bool x)
{
	this->viewTest = x;
}

CPerformance::CPerformance(void) :
	faceCount(0),
	collisionCheckCount(0),
	usingSceneGraph(false),
	usingSpatialPartitioning(false),
	orthoView(false),
	frustumCull(false),
	HighLODMode(false),
	LowLODMode(false),
	viewTest(true)
{
}
