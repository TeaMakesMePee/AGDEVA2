#include "SceneText.h"
#include "GL\glew.h"

#include "shader.hpp"
#include "MeshBuilder.h"
#include "Application.h"
#include "Utility.h"
#include "LoadTGA.h"
#include <sstream>
#include "KeyboardController.h"
#include "MouseController.h"
#include "SceneManager.h"
#include "GraphicsManager.h"
#include "ShaderProgram.h"
#include "EntityManager.h"
#include "RenderHelper.h"

#include "GenericEntity.h"
#include "GroundEntity.h"
#include "TextEntity.h"
#include "SpriteEntity.h"
#include "Light.h"
#include "SkyBox/SkyBoxEntity.h"
#include "Minimap\Minimap.h"

#include "SceneGraph\SceneGraph.h"
#include "SceneGraph/UpdateTransformation.h"
#include "SpatialPartition/SpatialPartition.h"
#include "FrustumCulling/FrustumCulling.h"
#include "Performance/Performance.h"

#include "Lua/LuaManager.h"

#include <iostream>
using namespace std;

//SceneText* SceneText::sInstance = new SceneText(SceneManager::GetInstance());

SceneText::SceneText()
	: theMinimap(NULL)
	, theCameraEffects(NULL)
	, theMouse(NULL)
	, theKeyboard(NULL)
{
}

//SceneText::SceneText(SceneManager* _sceneMgr)
//	: theMinimap(NULL)
//	, theCameraEffects(NULL)
//	, theMouse(NULL)
//	, theKeyboard(NULL)
//{
//	_sceneMgr->AddScene("Start", this);
//}

void SceneText::CreateEntities(void)
{
	//
	//GenericEntity* NPCTorse = Create::Entity("cube", Vector3(0.f, 0.f, 0.f), Vector3(1.f, 1.f, 1.f), false);
	//NPCTorse->SetCollider(true);
	//NPCTorse->SetAABB(Vector3(0.45f, 0.45f, 0.45f), Vector3(-0.45f, -0.45f, -0.45f));

	//CSceneNode* NPCSceneNode = CSceneGraph::GetInstance()->AddNode(NPCTorse);
	//NPCSceneNode->SetTranslate(Vector3(0.f, 1.f, -10.f));
	//CUpdateTransformation* aRotateMtx = new CUpdateTransformation();
	//aRotateMtx->ApplyUpdate(1.f, 0, 1, 0);
	//aRotateMtx->SetSteps(-60, 60);
	//NPCSceneNode->SetUpdateTransformation(aRotateMtx);

	//CSpatialPartition::GetInstance()->Add(NPCTorse);

	//GenericEntity* NPCPart = Create::Entity("sphere", Vector3(0.f, 0.f, 0.f), Vector3(1.f, 1.f, 1.f), false);
	//NPCPart->SetCollider(true);
	//NPCPart->SetAABB(Vector3(0.45f, 0.45f, 0.45f), Vector3(-0.45f, -0.45f, -0.45f));

	//CSceneNode* childNode = NPCSceneNode->AddChild(NPCPart);
	//childNode->SetTranslate(Vector3(0.f, 1.f, 0.f));

	//NPCPart = Create::Entity("cube", Vector3(0.f, 0.f, 0.f), Vector3(1.f, 1.f, 1.f), false);
	//NPCPart->SetCollider(true);
	//NPCPart->SetAABB(Vector3(0.45f, 0.45f, 0.45f), Vector3(-0.45f, -0.45f, -0.45f));
	//childNode = NPCSceneNode->AddChild(NPCPart);
	//childNode->SetTranslate(Vector3(-0.6f, -1.f, 0.f));
	//CSpatialPartition::GetInstance()->Add(NPCPart);

	//NPCPart = Create::Entity("cube", Vector3(0.f, 0.f, 0.f), Vector3(1.f, 1.f, 1.f), false);
	//NPCPart->SetCollider(true);
	//NPCPart->SetAABB(Vector3(0.45f, 0.45f, 0.45f), Vector3(-0.45f, -0.45f, -0.45f));
	//childNode = NPCSceneNode->AddChild(NPCPart);
	//childNode->SetTranslate(Vector3(0.6f, -1.f, 0.f));
	//CSpatialPartition::GetInstance()->Add(NPCPart);

	//NPCPart = Create::Entity("cube", Vector3(0.f, 0.f, 0.f), Vector3(1.f, 1.f, 1.f), false);
	//NPCPart->SetCollider(true);
	//NPCPart->SetAABB(Vector3(0.45f, 0.45f, 0.45f), Vector3(-0.45f, -0.45f, -0.45f));
	//childNode = NPCSceneNode->AddChild(NPCPart);
	//childNode->SetTranslate(Vector3(-1.2f, 0.f, 0.f));
	//CSpatialPartition::GetInstance()->Add(NPCPart);

	//NPCPart = Create::Entity("cube", Vector3(0.f, 0.f, 0.f), Vector3(1.f, 1.f, 1.f), false);
	//NPCPart->SetCollider(true);
	//NPCPart->SetAABB(Vector3(0.45f, 0.45f, 0.45f), Vector3(-0.45f, -0.45f, -0.45f));
	//childNode = NPCSceneNode->AddChild(NPCPart);
	//childNode->SetTranslate(Vector3(1.2f, 0.f, 0.f));
	//aRotateMtx = new CUpdateTransformation();
	//aRotateMtx->ApplyUpdate(1.f, 0, 1, 0);
	//aRotateMtx->SetSteps(-60, 60);
	//childNode->SetUpdateTransformation(aRotateMtx);
	//CSpatialPartition::GetInstance()->Add(NPCPart);




	CSceneNode* NPCSceneNode;
	CSceneNode* childNode;
	CUpdateTransformation* aRotateMtx;
	//anEnemy3D = Create::Enemy3D("cube", Vector3(10.f, 0.0f, 0.0f), Vector3(1.f, 1.f, 1.f), false);
	//anEnemy3D->InitLOD("sphere2", "sphere", "cube");
	//anEnemy3D->Init();
	//anEnemy3D->SetSpeed(0.1);
	//anEnemy3D->SetCollider(true);
	//anEnemy3D->SetAABB(Vector3(0.5, 0.5, 0.5), Vector3(-0.5, -0.5, -0.5));

	//anEnemy3D->SetTerrain(groundEntity);
	//CSpatialPartition::GetInstance()->Add(anEnemy3D);

	//NPCSceneNode = CSceneGraph::GetInstance()->AddNode(anEnemy3D);
	//NPCSceneNode->SetTranslate(Vector3(0.f, 0.f, 0.f));
	//aRotateMtx = new CUpdateTransformation();
	//aRotateMtx->ApplyUpdate(1.f, 0, 1, 0);
	//aRotateMtx->SetSteps(-60, 60);
	//NPCSceneNode->SetUpdateTransformation(aRotateMtx);

	//NPCPart = Create::Entity("sphere", Vector3(0.f, 0.f, 0.f), Vector3(1.f, 1.f, 1.f), false);
	//NPCPart->SetCollider(true);
	//NPCPart->SetAABB(Vector3(0.45f, 0.45f, 0.45f), Vector3(-0.45f, -0.45f, -0.45f));
	//childNode = NPCSceneNode->AddChild(NPCPart);
	//childNode->SetTranslate(Vector3(0.f, 1.f, 0.f));
	//aRotateMtx = new CUpdateTransformation();
	//aRotateMtx->ApplyUpdate(1.f, 1, 0, 0);
	//aRotateMtx->SetSteps(-60, 60);
	//childNode->SetUpdateTransformation(aRotateMtx);
	//CSpatialPartition::GetInstance()->Add(NPCPart);

	//CSceneGraph::GetInstance()->ReCalc_AABB();

	std::vector<bool> occupied;
	occupied.resize(100, false);

	//GenericEntity* BuildingTest;
	//for (int x = 4; x < 6; ++x)
	//{
	//	for (int y = 4; y < 6; ++y)
	//	{
	//		Vector3 pos = CSpatialPartition::GetInstance()->GetCentreByIndex(x, y) * 2.f;
	//		BuildingTest = Create::Entity("Building_Low", pos, Vector3(1.f, 1.f, 1.f), false);
	//		occupied[x * 10 + y] = true; 
	//		BuildingTest->InitLOD("Building_High", "Building_Mid", "Building_Low");
	//		BuildingTest->SetCollider(false);
	//		BuildingTest->SetAABB(Vector3(0.45f, 0.45f, 0.45f), Vector3(-0.45f, -0.45f, -0.45f));
	//		CSpatialPartition::GetInstance()->Add(BuildingTest);
	//		NPCSceneNode = CSceneGraph::GetInstance()->AddNode(BuildingTest);
	//		NPCSceneNode->SetTranslate(Vector3(0.0f, 0.0f, 0.0f));
	//	}
	//}

	//for (int x = 0; x < 10; ++x)
	//{
	//	for (int z = 0; z < 10; ++z)
	//	{
	//		if (!occupied[x * 10 + z])
	//		{
	//			int count = 0;
	//			if (x + 1 <= 9)
	//				if (occupied[(x + 1) * 10 + z])
	//					count++;
	//			if (x - 1 >= 0)
	//				if (occupied[(x - 1) * 10 + z])
	//					count++;
	//			if (z + 1 <= 9)
	//				if (occupied[x * 10 + z + 1])
	//					count++;
	//			if (z - 1 >= 0)
	//				if (occupied[x * 10 + z - 1])
	//					count++;

	//			if (count > 0)
	//				continue;

	//			int rand = Math::RandIntMinMax(0, 1);
	//			Vector3 pos = CSpatialPartition::GetInstance()->GetCentreByIndex(x, z) * 2.f;

	//			if (rand)
	//			{
	//				BuildingTest = Create::Entity("Building_Low", pos, Vector3(1.f, 1.f, 1.f), false);
	//				occupied[x * 10 + z] = true;
	//				BuildingTest->InitLOD("Building_High", "Building_Mid", "Building_Low");
	//				BuildingTest->SetCollider(false);
	//				BuildingTest->SetAABB(Vector3(0.45f, 0.45f, 0.45f), Vector3(-0.45f, -0.45f, -0.45f));
	//				CSpatialPartition::GetInstance()->Add(BuildingTest);
	//				NPCSceneNode = CSceneGraph::GetInstance()->AddNode(BuildingTest);
	//				NPCSceneNode->SetTranslate(Vector3(0.0f, 0.0f, 0.0f));
	//			}
	//		}
	//	}
	//}

	//CEnemy3D* anEnemy3D;
	//GenericEntity* enemyPart;
	//srand(NULL);
	//for (int x = 0; x < 10; ++x)
	//{
	//	for (int z = 0; z < 10; ++z)
	//	{
	//		if (!occupied[x * 10 + z])
	//		{
	//			int rand = Math::RandIntMinMax(0, 1);
	//			if (rand)
	//			{
	//				occupied[x * 10 + z] = true;
	//				//Vector3 pos(50, 0, 50);
	//				Vector3 pos = CSpatialPartition::GetInstance()->GetCentreByIndex(x, z) * 2.f;
	//				anEnemy3D = Create::Enemy3D("cube2", pos, Vector3(2.5f, 2.5f, 2.5f), false);
	//				anEnemy3D->InitLOD("sphere2", "sphere", "cube2");
	//				anEnemy3D->Init();
	//				//anEnemy3D->SetPos(Vector3(0, 0, 0));
	//				anEnemy3D->SetSpeed(0.0f);
	//				anEnemy3D->SetCollider(true);
	//				anEnemy3D->SetAABB(Vector3(0.5f * 2.5f, 0.5f * 2.5f, 0.5f * 2.5f), Vector3(-0.5f * 2.5f, -0.5f * 2.5f, -0.5f * 2.5f));

	//				anEnemy3D->SetTerrain(groundEntity);

	//				NPCSceneNode = CSceneGraph::GetInstance()->AddNode(anEnemy3D);
	//				aRotateMtx = new CUpdateTransformation();
	//				NPCSceneNode->SetUpdateTransformation(aRotateMtx);

	//				// Add the entity into the Spatial Partition
	//				CSpatialPartition::GetInstance()->Add(anEnemy3D);

	//				enemyPart = Create::Entity("sphere3", pos + Vector3(2.f, 0.f, 0.f), Vector3(1.f, 1.f, 1.f), false);
	//				enemyPart->InitLOD("sphere3", "sphere4", "cube");
	//				enemyPart->SetCollider(true);
	//				enemyPart->SetAABB(Vector3(0.45f, 0.45f, 0.45f), Vector3(-0.45f, -0.45f, -0.45f));
	//				childNode = NPCSceneNode->AddChild(enemyPart);
	//				childNode->SetTranslate(Vector3(4.f, 0.f, 0.f));
	//				CSpatialPartition::GetInstance()->Add(enemyPart);

	//				enemyPart = Create::Entity("sphere3", pos + Vector3(-2.f, 0.f, 0.f), Vector3(1.f, 1.f, 1.f), false);
	//				enemyPart->InitLOD("sphere3", "sphere4", "cube");
	//				enemyPart->SetCollider(true);
	//				enemyPart->SetAABB(Vector3(0.45f, 0.45f, 0.45f), Vector3(-0.45f, -0.45f, -0.45f));
	//				childNode = NPCSceneNode->AddChild(enemyPart);
	//				childNode->SetTranslate(Vector3(-4.f, 0.f, 0.f));
	//				CSpatialPartition::GetInstance()->Add(enemyPart);

	//				enemyPart = Create::Entity("sphere3", pos + Vector3(0.f, 0.f, 2.f), Vector3(1.f, 1.f, 1.f), false);
	//				enemyPart->InitLOD("sphere3", "sphere4", "cube");
	//				enemyPart->SetCollider(true);
	//				enemyPart->SetAABB(Vector3(0.45f, 0.45f, 0.45f), Vector3(-0.45f, -0.45f, -0.45f));
	//				childNode = NPCSceneNode->AddChild(enemyPart);
	//				childNode->SetTranslate(Vector3(0.f, 0.f, 4.f));
	//				CSpatialPartition::GetInstance()->Add(enemyPart);

	//				enemyPart = Create::Entity("sphere3", pos + Vector3(0.f, 0.f, -2.f), Vector3(1.f, 1.f, 1.f), false);
	//				enemyPart->InitLOD("sphere3", "sphere4", "cube");
	//				enemyPart->SetCollider(true);
	//				enemyPart->SetAABB(Vector3(0.45f, 0.45f, 0.45f), Vector3(-0.45f, -0.45f, -0.45f));
	//				childNode = NPCSceneNode->AddChild(enemyPart);
	//				childNode->SetTranslate(Vector3(0.f, 0.f, -4.f));
	//				CSpatialPartition::GetInstance()->Add(enemyPart);
	//			}
	//		}
	//	}
	//}

	CEnemy3D* anEnemy3D;
	anEnemy3D = Create::Enemy3D("cube2", CLuaManager::GetInstance()->get<Vector3>("EnemyPos.enemy1"), Vector3(2.5f, 2.5f, 2.5f), false);
	//anEnemy3D = Create::Enemy3D("cube2", Vector3(50, 0, 50), Vector3(2.5f, 2.5f, 2.5f), false);
	anEnemy3D->InitLOD("sphere2", "sphere", "cube2");
	anEnemy3D->Init(playerInfo);
	anEnemy3D->SetSpeed(20.0f);
	anEnemy3D->SetCollider(true);
	anEnemy3D->SetAABB(Vector3(0.5f * 2.5f, 0.5f * 2.5f, 0.5f * 2.5f), Vector3(-0.5f * 2.5f, -0.5f * 2.5f, -0.5f * 2.5f));
	anEnemy3D->SetTerrain(groundEntity);
	NPCSceneNode = CSceneGraph::GetInstance()->AddNode(anEnemy3D);
	aRotateMtx = new CUpdateTransformation();
	NPCSceneNode->SetUpdateTransformation(aRotateMtx);
	CSpatialPartition::GetInstance()->Add(anEnemy3D);
	CEnemy3D::count++;

	anEnemy3D = Create::Enemy3D("cube2", CLuaManager::GetInstance()->get<Vector3>("EnemyPos.enemy2"), Vector3(2.5f, 2.5f, 2.5f), false);
	//anEnemy3D = Create::Enemy3D("cube2", Vector3(-50, 0, -50), Vector3(2.5f, 2.5f, 2.5f), false);
	anEnemy3D->InitLOD("sphere2", "sphere", "cube2");
	anEnemy3D->Init(playerInfo);
	anEnemy3D->SetSpeed(20.0f);
	anEnemy3D->SetCollider(true);
	anEnemy3D->SetAABB(Vector3(0.5f * 2.5f, 0.5f * 2.5f, 0.5f * 2.5f), Vector3(-0.5f * 2.5f, -0.5f * 2.5f, -0.5f * 2.5f));
	anEnemy3D->SetTerrain(groundEntity);
	NPCSceneNode = CSceneGraph::GetInstance()->AddNode(anEnemy3D);
	aRotateMtx = new CUpdateTransformation();
	NPCSceneNode->SetUpdateTransformation(aRotateMtx);
	CSpatialPartition::GetInstance()->Add(anEnemy3D);
	CEnemy3D::count++;

	anEnemy3D = Create::Enemy3D("cube2", CLuaManager::GetInstance()->get<Vector3>("EnemyPos.enemy3"), Vector3(2.5f, 2.5f, 2.5f), false);
	//anEnemy3D = Create::Enemy3D("cube2", Vector3(-50, 0, 50), Vector3(2.5f, 2.5f, 2.5f), false);
	anEnemy3D->InitLOD("sphere2", "sphere", "cube2");
	anEnemy3D->Init(playerInfo);
	anEnemy3D->SetSpeed(20.0f);
	anEnemy3D->SetCollider(true);
	anEnemy3D->SetAABB(Vector3(0.5f * 2.5f, 0.5f * 2.5f, 0.5f * 2.5f), Vector3(-0.5f * 2.5f, -0.5f * 2.5f, -0.5f * 2.5f));
	anEnemy3D->SetTerrain(groundEntity);
	NPCSceneNode = CSceneGraph::GetInstance()->AddNode(anEnemy3D);
	aRotateMtx = new CUpdateTransformation();
	NPCSceneNode->SetUpdateTransformation(aRotateMtx);
	CSpatialPartition::GetInstance()->Add(anEnemy3D);
	CEnemy3D::count++;

	anEnemy3D = Create::Enemy3D("cube2", CLuaManager::GetInstance()->get<Vector3>("EnemyPos.enemy4"), Vector3(2.5f, 2.5f, 2.5f), false);
	//anEnemy3D = Create::Enemy3D("cube2", Vector3(50, 0, -50), Vector3(2.5f, 2.5f, 2.5f), false);
	anEnemy3D->InitLOD("sphere2", "sphere", "cube2");
	anEnemy3D->Init(playerInfo);
	anEnemy3D->SetSpeed(20.0f);
	anEnemy3D->SetCollider(true);
	anEnemy3D->SetAABB(Vector3(0.5f * 2.5f, 0.5f * 2.5f, 0.5f * 2.5f), Vector3(-0.5f * 2.5f, -0.5f * 2.5f, -0.5f * 2.5f));
	anEnemy3D->SetTerrain(groundEntity);
	NPCSceneNode = CSceneGraph::GetInstance()->AddNode(anEnemy3D);
	aRotateMtx = new CUpdateTransformation();
	NPCSceneNode->SetUpdateTransformation(aRotateMtx);
	CSpatialPartition::GetInstance()->Add(anEnemy3D);
	CEnemy3D::count++;
}

SceneText::~SceneText()
{
	if (theCameraEffects)
	{
		delete theCameraEffects;
		theCameraEffects = NULL;
	}
	if (theMinimap)
	{
		delete theMinimap;
		theMinimap = NULL;
	}
	if (theMouse)
	{
		delete theMouse;
		theMouse = NULL;
	}
	if (theKeyboard)
	{
		delete theKeyboard;
		theKeyboard = NULL;
	}
	// Delete the scene graph
	CSceneGraph::GetInstance()->Destroy();
	// Delete the Spatial Partition
	CSpatialPartition::GetInstance()->Destroy();
	// Delete the EntityManager
	EntityManager::GetInstance()->Destroy();
}

void SceneText::Init()
{
	//currProg = GraphicsManager::GetInstance()->LoadShader("default", "Shader//comg.vertexshader", "Shader//comg.fragmentshader");
	//
	//// Tell the shader program to store these uniform locations
	//currProg->AddUniform("MVP");
	//currProg->AddUniform("MV");
	//currProg->AddUniform("MV_inverse_transpose");
	//currProg->AddUniform("material.kAmbient");
	//currProg->AddUniform("material.kDiffuse");
	//currProg->AddUniform("material.kSpecular");
	//currProg->AddUniform("material.kShininess");
	//currProg->AddUniform("lightEnabled");
	//currProg->AddUniform("numLights");
	//currProg->AddUniform("lights[0].type");
	//currProg->AddUniform("lights[0].position_cameraspace");
	//currProg->AddUniform("lights[0].color");
	//currProg->AddUniform("lights[0].power");
	//currProg->AddUniform("lights[0].kC");
	//currProg->AddUniform("lights[0].kL");
	//currProg->AddUniform("lights[0].kQ");
	//currProg->AddUniform("lights[0].spotDirection");
	//currProg->AddUniform("lights[0].cosCutoff");
	//currProg->AddUniform("lights[0].cosInner");
	//currProg->AddUniform("lights[0].exponent");
	//currProg->AddUniform("lights[1].type");
	//currProg->AddUniform("lights[1].position_cameraspace");
	//currProg->AddUniform("lights[1].color");
	//currProg->AddUniform("lights[1].power");
	//currProg->AddUniform("lights[1].kC");
	//currProg->AddUniform("lights[1].kL");
	//currProg->AddUniform("lights[1].kQ");
	//currProg->AddUniform("lights[1].spotDirection");
	//currProg->AddUniform("lights[1].cosCutoff");
	//currProg->AddUniform("lights[1].cosInner");
	//currProg->AddUniform("lights[1].exponent");
	//currProg->AddUniform("colorTextureEnabled");
	//currProg->AddUniform("colorTexture");
	//currProg->AddUniform("textEnabled");
	//currProg->AddUniform("textColor");
	//
	//// Tell the graphics manager to use the shader we just loaded
	//GraphicsManager::GetInstance()->SetActiveShader("default");
	elapsedTime = 0.0;

	lights[0] = new Light();
	GraphicsManager::GetInstance()->AddLight("lights[0]", lights[0]);
	lights[0]->type = Light::LIGHT_DIRECTIONAL;
	lights[0]->position.Set(0, 5, 0);
	lights[0]->color.Set(1, 0, 0);
	lights[0]->power = 10;
	lights[0]->kC = 1.f;
	lights[0]->kL = 0.01f;
	lights[0]->kQ = 0.001f;
	lights[0]->cosCutoff = cos(Math::DegreeToRadian(45));
	lights[0]->cosInner = cos(Math::DegreeToRadian(30));
	lights[0]->exponent = 3.f;
	lights[0]->spotDirection.Set(0.f, 1.f, 0.f);
	lights[0]->name = "lights[0]";

	lights[1] = new Light();
	GraphicsManager::GetInstance()->AddLight("lights[1]", lights[1]);
	lights[1]->type = Light::LIGHT_DIRECTIONAL;
	lights[1]->position.Set(1, 1, 0);
	lights[1]->color.Set(1, 1, 0.5f);
	lights[1]->power = 0.4f;
	lights[1]->name = "lights[1]";

	//currProg->UpdateInt("numLights", 1);
	//currProg->UpdateInt("textEnabled", 0);
	
	// Create the playerinfo instance, which manages all information about the player
	playerInfo = CPlayerInfo::GetInstance();
	playerInfo->Init();

	// Create and attach the camera to the scene
	//camera.Init(Vector3(0, 0, 10), Vector3(0, 0, 0), Vector3(0, 1, 0));
	camera.Init(playerInfo->GetPos(), playerInfo->GetTarget(), playerInfo->GetUp());
	playerInfo->AttachCamera(&camera);
	GraphicsManager::GetInstance()->AttachCamera(&camera);

	// Load all the meshes
	MeshBuilder::GetInstance()->GenerateAxes("reference");
	MeshBuilder::GetInstance()->GenerateCrossHair("crosshair");
	MeshBuilder::GetInstance()->GenerateQuad("quad", Color(1, 1, 1), 1.f);
	MeshBuilder::GetInstance()->GetMesh("quad")->textureID = LoadTGA("Image//calibri.tga");
	MeshBuilder::GetInstance()->GenerateText("text", 16, 16);
	MeshBuilder::GetInstance()->GetMesh("text")->textureID = LoadTGA("Image//calibri.tga");
	MeshBuilder::GetInstance()->GetMesh("text")->material.kAmbient.Set(1, 0, 0);
	//MeshBuilder::GetInstance()->GenerateOBJ("Chair", "OBJ//chair.obj");
	//MeshBuilder::GetInstance()->GetMesh("Chair")->textureID = LoadTGA("Image//chair.tga");

	//Building meshes
	MeshBuilder::GetInstance()->GenerateOBJ("Building_Low", "OBJ//Building_Low.obj");
	MeshBuilder::GetInstance()->GetMesh("Building_Low")->textureID = LoadTGA("Image//wall.tga");
	MeshBuilder::GetInstance()->GenerateOBJ("Building_Mid", "OBJ//Building_Mid.obj");
	MeshBuilder::GetInstance()->GetMesh("Building_Mid")->textureID = LoadTGA("Image//wall.tga");
	MeshBuilder::GetInstance()->GenerateOBJ("Building_High", "OBJ//Building_High.obj");
	MeshBuilder::GetInstance()->GetMesh("Building_High")->textureID = LoadTGA("Image//wall.tga");

	MeshBuilder::GetInstance()->GenerateOBJ("Boxx", "OBJ//boxx.obj");
	MeshBuilder::GetInstance()->GetMesh("Boxx")->textureID = LoadTGA("Image//chair.tga");
	MeshBuilder::GetInstance()->GenerateRing("ring", Color(1, 0, 1), 36, 1, 0.5f);
	MeshBuilder::GetInstance()->GenerateSphere("lightball", Color(1, 1, 1), 18, 36, 1.f);
	MeshBuilder::GetInstance()->GenerateSphere("sphere", Color(1, 1, 0), 18, 36, 2.f);
	MeshBuilder::GetInstance()->GenerateSphere("sphere2", Color(0.5f, 0, 0.5f), 36, 72, 2.f);
	MeshBuilder::GetInstance()->GenerateSphere("sphere4", Color(0, 1, 1), 18, 36, 1.f);
	MeshBuilder::GetInstance()->GenerateSphere("sphere3", Color(0.f, 0, 1.f), 36, 72, 1.f);
	MeshBuilder::GetInstance()->GenerateCone("cone", Color(0.5f, 1, 0.3f), 36, 10.f, 10.f);
	MeshBuilder::GetInstance()->GenerateSphere("projectile", Color(0.5f, 0.5f, 0.5f), 18, 36, 0.5f);
	MeshBuilder::GetInstance()->GenerateCube("cube", Color(1.0f, 1.0f, 0.0f), 1.0f);
	MeshBuilder::GetInstance()->GenerateCube("cube2", Color(1.0f, 1.0f, 0.0f), 2.f);
	MeshBuilder::GetInstance()->GetMesh("cone")->material.kDiffuse.Set(0.99f, 0.99f, 0.99f);
	MeshBuilder::GetInstance()->GetMesh("cone")->material.kSpecular.Set(0.f, 0.f, 0.f);
	MeshBuilder::GetInstance()->GenerateQuad("GRASS_DARKGREEN", Color(1, 1, 1), 1.f);
	MeshBuilder::GetInstance()->GetMesh("GRASS_DARKGREEN")->textureID = LoadTGA("Image//grass_darkgreen.tga");
	MeshBuilder::GetInstance()->GenerateQuad("GEO_GRASS_LIGHTGREEN", Color(1, 1, 1), 1.f);
	MeshBuilder::GetInstance()->GetMesh("GEO_GRASS_LIGHTGREEN")->textureID = LoadTGA("Image//grass_lightgreen.tga");

	MeshBuilder::GetInstance()->GenerateQuad("SKYBOX_FRONT", Color(1, 1, 1), 1.f);
	MeshBuilder::GetInstance()->GenerateQuad("SKYBOX_BACK", Color(1, 1, 1), 1.f);
	MeshBuilder::GetInstance()->GenerateQuad("SKYBOX_LEFT", Color(1, 1, 1), 1.f);
	MeshBuilder::GetInstance()->GenerateQuad("SKYBOX_RIGHT", Color(1, 1, 1), 1.f);
	MeshBuilder::GetInstance()->GenerateQuad("SKYBOX_TOP", Color(1, 1, 1), 1.f);
	MeshBuilder::GetInstance()->GenerateQuad("SKYBOX_BOTTOM", Color(1, 1, 1), 1.f);
	MeshBuilder::GetInstance()->GetMesh("SKYBOX_FRONT")->textureID = LoadTGA("Image//SkyBox//skybox_front.tga");
	MeshBuilder::GetInstance()->GetMesh("SKYBOX_BACK")->textureID = LoadTGA("Image//SkyBox//skybox_back.tga");
	MeshBuilder::GetInstance()->GetMesh("SKYBOX_LEFT")->textureID = LoadTGA("Image//SkyBox//skybox_left.tga");
	MeshBuilder::GetInstance()->GetMesh("SKYBOX_RIGHT")->textureID = LoadTGA("Image//SkyBox//skybox_right.tga");
	MeshBuilder::GetInstance()->GetMesh("SKYBOX_TOP")->textureID = LoadTGA("Image//SkyBox//skybox_top.tga");
	MeshBuilder::GetInstance()->GetMesh("SKYBOX_BOTTOM")->textureID = LoadTGA("Image//SkyBox//skybox_bottom.tga");

	MeshBuilder::GetInstance()->GenerateQuad("GRIDMESH", Color(1, 0, 0), 1.f);
	MeshBuilder::GetInstance()->GenerateQuad("GRIDMESH2", Color(1, 1, 0), 1.f);
	MeshBuilder::GetInstance()->GenerateQuad("GRIDMESH3", Color(0, 1, 0), 1.f);

	MeshBuilder::GetInstance()->GenerateQuad("Crosshair", Color(1.0f, 0.0f, 1.0f), 1.0f);
	MeshBuilder::GetInstance()->GetMesh("Crosshair")->textureID = LoadTGA("Image//Crosshair.tga");

	MeshBuilder::GetInstance()->GenerateRay("laser", 10.f);

	CSpatialPartition::GetInstance()->Init(100, 100, 10, 10);
	CSpatialPartition::GetInstance()->SetMeshRenderMode(CGrid::FILL);
	CSpatialPartition::GetInstance()->SetMesh("GRIDMESH", "GRIDMESH2", "GRIDMESH3");
	CSpatialPartition::GetInstance()->SetCamera(&camera);
	CSpatialPartition::GetInstance()->SetLevelOfDetails(CLuaManager::GetInstance()->get<float>("LOD.Detail.HighMid"), CLuaManager::GetInstance()->get<float>("LOD.Detail.MidLow"));

	CFrustumCulling::GetInstance()->Init(45.f, 4.f / 3.f, 0.1f, 10000.f);

	// Create entities into the scene
	Create::Entity("reference", Vector3(0.0f, 0.0f, 0.0f)); // Reference
	//Create::Entity("lightball", Vector3(lights[0]->position.x, lights[0]->position.y, lights[0]->position.z)); // Lightball
	//GenericEntity* aCube = Create::Entity("cube", Vector3(-20.0f, 0.0f, -20.0f));
	Create::Entity("ring", Vector3(0.0f, 0.0f, 0.0f)); // Reference


	groundEntity = Create::Ground("GRASS_DARKGREEN", "GEO_GRASS_LIGHTGREEN");
//	Create::Text3DObject("text", Vector3(0.0f, 0.0f, 0.0f), "DM2210", Vector3(10.0f, 10.0f, 10.0f), Color(0, 1, 1));
	Create::Sprite2DObject("crosshair", Vector3(0.0f, 0.0f, 0.0f), Vector3(10.0f, 10.0f, 10.0f));

	SkyBoxEntity* theSkyBox = Create::SkyBox("SKYBOX_FRONT", "SKYBOX_BACK",
											 "SKYBOX_LEFT", "SKYBOX_RIGHT",
											 "SKYBOX_TOP", "SKYBOX_BOTTOM");

	// Customise the ground entity
	groundEntity->SetPosition(Vector3(0, -10, 0));
	groundEntity->SetScale(Vector3(100.0f, 100.0f, 100.0f));
	groundEntity->SetGrids(Vector3(10.0f, 1.0f, 10.0f));
	playerInfo->SetTerrain(groundEntity);

	// Create a CEnemy instance
	//anEnemy3D = Create::Enemy3D("cube", Vector3(0.0f, 0.0f, -20.0f));
	//anEnemy3D->Init(); 
	//anEnemy3D->SetCollider(true);
	//anEnemy3D->SetAABB( Vector3(0.5,0.5,0.5), Vector3(-0.5, -0.5, -0.5) );

	//anEnemy3D->SetTerrain(groundEntity);


	// Setup the 2D entities
	float halfWindowWidth = Application::GetInstance().GetWindowWidth() / 2.0f;
	float halfWindowHeight = Application::GetInstance().GetWindowHeight() / 2.0f;
	float fontSize = 25.0f;
	float halfFontSize = fontSize / 2.0f;
	for (int i = 0; i < 3; ++i)
	{
		textObj[i] = Create::Text2DObject("text", Vector3(-halfWindowWidth, -halfWindowHeight + fontSize*i + halfFontSize, 0.0f), "", Vector3(fontSize, fontSize, fontSize), Color(0.0f, 1.0f, 1.0f));
	}

	// Hardware Abstraction
	theKeyboard = new CKeyboard();
	theKeyboard->Create(playerInfo);

	// Activate the Blend Function
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Minimap
	theMinimap = Create::Minimap(false);
	theMinimap->SetBackground(MeshBuilder::GetInstance()->GenerateQuad("MINIMAP", Color(1, 1, 1), 1.f));
	theMinimap->GetBackground()->textureID = LoadTGA("Image//minimap_square.tga");
	theMinimap->SetBorder(MeshBuilder::GetInstance()->GenerateCircle("MINIMAPBORDER", Color(1, 1, 1), 1.05f));
	theMinimap->SetAvatar(MeshBuilder::GetInstance()->GenerateQuad("MINIMAPAVATAR", Color(1, 1, 0), 0.25f));
	theMinimap->GetAvatar()->textureID = LoadTGA("Image//Avatar.tga");
	theMinimap->SetStencil(MeshBuilder::GetInstance()->GenerateCircle("MINIMAP_STENCIL", Color(1, 1, 1), 1.0f));

	//// CameraEffects
	//theCameraEffects = Create::CameraEffects(false);
	//theCameraEffects->SetBloodScreen(MeshBuilder::GetInstance()->GenerateQuad("CAMERAEFFECTS_BLOODSCREEN", Color(1, 1, 1), 1.f));
	//theCameraEffects->GetBloodScreen()->textureID = LoadTGA("Image//CameraEffects_Blood.tga");
	//theCameraEffects->SetStatus_BloodScreen(false);

	theCameraEffects = Create::CameraEffects(false);
	theCameraEffects->SetBloodScreen(MeshBuilder::GetInstance()->GenerateQuad("Crosshair", Color(1, 1, 1), 1.f));
	theCameraEffects->GetBloodScreen()->textureID = LoadTGA("Image//Crosshair.tga");
	theCameraEffects->SetStatus_BloodScreen(true);

	// Hardware Abstraction
	theKeyboard = new CKeyboard();
	theKeyboard->Create(playerInfo);

	theMouse = new CMouse();
	theMouse->Create(playerInfo);
	CreateEntities();
}

void SceneText::Update(double dt)
{
	std::cout << "this: " << CEnemy3D::count << std::endl;
	if (CEnemy3D::count == 0)
	{
		if ((float)elapsedTime < CLuaManager::GetInstance()->get<float>("Highscore.scores.first"))
		{
			CLuaManager::GetInstance()->set<float>("Highscore.scores.first", (float)elapsedTime, false);
		}
		else if ((float)elapsedTime < CLuaManager::GetInstance()->get<float>("Highscore.scores.second"))
		{
			CLuaManager::GetInstance()->set<float>("Highscore.scores.second", (float)elapsedTime, false);
		}
		else if ((float)elapsedTime < CLuaManager::GetInstance()->get<float>("Highscore.scores.third"))
		{
			CLuaManager::GetInstance()->set<float>("Highscore.scores.third", (float)elapsedTime, false);
		}
		Application::run = false;
		//SceneManager::GetInstance()->SetActiveScene("HighScore");
	}
	else
	{
		elapsedTime += dt;
	}

	// Update our entities
	EntityManager::GetInstance()->Update(dt);
	//CSceneGraph::GetInstance()->ReCalc_AABB();

	// THIS WHOLE CHUNK TILL <THERE> CAN REMOVE INTO ENTITIES LOGIC! Or maybe into a scene function to keep the update clean
	if(KeyboardController::GetInstance()->IsKeyDown('1'))
		glEnable(GL_CULL_FACE);
	if(KeyboardController::GetInstance()->IsKeyDown('2'))
		glDisable(GL_CULL_FACE);
	if(KeyboardController::GetInstance()->IsKeyDown('3'))
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	if(KeyboardController::GetInstance()->IsKeyDown('4'))
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	
	if(KeyboardController::GetInstance()->IsKeyDown('5'))
	{
		lights[0]->type = Light::LIGHT_POINT;
	}
	else if(KeyboardController::GetInstance()->IsKeyDown('6'))
	{
		lights[0]->type = Light::LIGHT_DIRECTIONAL;
	}
	else if(KeyboardController::GetInstance()->IsKeyDown('7'))
	{
		lights[0]->type = Light::LIGHT_SPOT;
	}

	if (KeyboardController::GetInstance()->IsKeyReleased('V'))
	{
		if (CPerformance::GetInstance()->IsSpatialPartition())
			CPerformance::GetInstance()->SetIsSpatialPartition(false);
		else
			CPerformance::GetInstance()->SetIsSpatialPartition(true);
	}

	if (KeyboardController::GetInstance()->IsKeyReleased('B'))
	{
		if (CPerformance::GetInstance()->IsSceneGraph())
			CPerformance::GetInstance()->SetIsSceneGraph(false);
		else
			CPerformance::GetInstance()->SetIsSceneGraph(true);
	}

	if (KeyboardController::GetInstance()->IsKeyReleased('O'))
	{
		if (CPerformance::GetInstance()->IsOrthoView())
			CPerformance::GetInstance()->SetIsOrthoView(false);
		else
			CPerformance::GetInstance()->SetIsOrthoView(true);
	}

	if (KeyboardController::GetInstance()->IsKeyReleased('F'))
	{
		if (CPerformance::GetInstance()->IsFrustumView())
			CPerformance::GetInstance()->SetIsFrustumView(false);
		else
			CPerformance::GetInstance()->SetIsFrustumView(true);
	}

	if (KeyboardController::GetInstance()->IsKeyReleased('L'))
	{
		if (CPerformance::GetInstance()->IsLowLODMode())
			CPerformance::GetInstance()->SetIsLowLODMode(false);
		else
			CPerformance::GetInstance()->SetIsLowLODMode(true);
	}

	if (KeyboardController::GetInstance()->IsKeyReleased('H'))
	{
		if (CPerformance::GetInstance()->IsHighLODMode())
			CPerformance::GetInstance()->SetIsHighLODMode(false);
		else
			CPerformance::GetInstance()->SetIsHighLODMode(true);
	}

	if (KeyboardController::GetInstance()->IsKeyReleased('X'))
	{
		if (CPerformance::GetInstance()->IsViewTest())
			CPerformance::GetInstance()->SetIsViewTest(false);
		else
			CPerformance::GetInstance()->SetIsViewTest(true);
	}

	//if (KeyboardController::GetInstance()->IsKeyPressed(VK_SPACE))
	//{
	//	SceneManager::GetInstance()->SetActiveScene("MenuState");
	//}

	// if the left mouse button was released
	if (MouseController::GetInstance()->IsButtonReleased(MouseController::LMB))
	{
		cout << "Left Mouse Button was released!" << endl;
	}
	if (MouseController::GetInstance()->IsButtonReleased(MouseController::RMB))
	{
		cout << "Right Mouse Button was released!" << endl;
	}
	if (MouseController::GetInstance()->IsButtonReleased(MouseController::MMB))
	{
		cout << "Middle Mouse Button was released!" << endl;
	}
	if (MouseController::GetInstance()->GetMouseScrollStatus(MouseController::SCROLL_TYPE_XOFFSET) != 0.0)
	{
		cout << "Mouse Wheel has offset in X-axis of " << MouseController::GetInstance()->GetMouseScrollStatus(MouseController::SCROLL_TYPE_XOFFSET) << endl;
	}
	if (MouseController::GetInstance()->GetMouseScrollStatus(MouseController::SCROLL_TYPE_YOFFSET) != 0.0)
	{
		cout << "Mouse Wheel has offset in Y-axis of " << MouseController::GetInstance()->GetMouseScrollStatus(MouseController::SCROLL_TYPE_YOFFSET) << endl;
	}
	// <THERE>

	// Hardware Abstraction
	theKeyboard->Read((float)dt);
	theMouse->Read((float)dt);

	// Update the player position and other details based on keyboard and mouse inputs //redundant
	playerInfo->Update(dt);

	//camera.Update(dt); // Can put the camera into an entity rather than here (Then we don't have to write this)
	CSceneGraph::GetInstance()->Update((float)dt);
	// Update NPC
	//enemyInfo->Update(dt);

	CSpatialPartition::GetInstance()->Update();

	//redundant
	GraphicsManager::GetInstance()->UpdateLights(dt);

	// Update the 2 text object values. NOTE: Can do this in their own class but i'm lazy to do it now :P
	// Eg. FPSRenderEntity or inside RenderUI for LightEntity
	DisplayText.str("");
	DisplayText.clear();
	DisplayText << "Collision checks:" << CPerformance::GetInstance()->GetCollisionCheckCount();
	textObj[0]->SetText(DisplayText.str());

	DisplayText.precision(5);
	float fps = (float)(1.f / dt);
	DisplayText.str("");
	DisplayText.clear();
	DisplayText << "FPS: " << fps;
	textObj[2]->SetText(DisplayText.str());

	DisplayText.str("");
	DisplayText.clear();
	DisplayText << "Polygons:" << CPerformance::GetInstance()->GetFaceCount();
	textObj[1]->SetText(DisplayText.str());

	// Update camera effects //redundant
	theCameraEffects->Update((float)dt);
}

void SceneText::Render()
{
	CPerformance::GetInstance()->SetFaceCount(0);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	GraphicsManager::GetInstance()->UpdateLightUniforms();

	// Setup 3D pipeline then render 3D
	if (!CPerformance::GetInstance()->IsOrthoView())
	{
		GraphicsManager::GetInstance()->SetPerspectiveProjection(45.0f, 4.0f / 3.0f, 0.1f, 10000.0f);
		GraphicsManager::GetInstance()->AttachCamera(&camera);
	}
	else
	{
		FPSCamera* _cameraPtr = new FPSCamera();
		_cameraPtr->Init(Vector3(0.f, 1.f, 0.f), Vector3(0.f, 0.f, 0.f), Vector3(0.f, 0.f, 1.f));
		GraphicsManager::GetInstance()->SetOrthographicProjection(-500, 500, -500, 500, -2000, 2000);
		GraphicsManager::GetInstance()->AttachCamera(_cameraPtr);
	}

	// Setup 3D pipeline then render 3D
	//GraphicsManager::GetInstance()->SetPerspectiveProjection(45.0f, 4.0f / 3.0f, 0.1f, 10000.0f);
	//GraphicsManager::GetInstance()->AttachCamera(&camera);


	// PreRenderMesh
	RenderHelper::PreRenderMesh();
		EntityManager::GetInstance()->Render();
		CSceneGraph::GetInstance()->Render();
		CSpatialPartition::GetInstance()->Render(playerInfo->GetPos(), playerInfo->GetTarget(), playerInfo->GetUp());
	// PostRenderMesh
	RenderHelper::PostRenderMesh();

	// Enable blend mode
	glEnable(GL_BLEND);

		// Setup 2D pipeline then render 2D
		int halfWindowWidth = Application::GetInstance().GetWindowWidth() / 2;
		int halfWindowHeight = Application::GetInstance().GetWindowHeight() / 2;
		GraphicsManager::GetInstance()->SetOrthographicProjection(-halfWindowWidth, halfWindowWidth, -halfWindowHeight, halfWindowHeight, -10, 10);
		GraphicsManager::GetInstance()->DetachCamera();

		// PreRenderText
		RenderHelper::PreRenderText();

			EntityManager::GetInstance()->RenderUI();

			if (KeyboardController::GetInstance()->IsKeyDown('9'))
				theCameraEffects->SetStatus_BloodScreen(true);
			// Render Camera Effects
			theCameraEffects->RenderUI();

			// Render Minimap
			theMinimap->RenderUI();

		// PostRenderText
		RenderHelper::PostRenderText();

	// Disable blend mode
	glDisable(GL_BLEND);
}

void SceneText::Exit()
{
	// Detach camera from other entities
	GraphicsManager::GetInstance()->DetachCamera();
	playerInfo->DetachCamera();

	if (playerInfo->DropInstance() == false)
	{
#if _DEBUGMODE==1
		cout << "Unable to drop PlayerInfo class" << endl;
#endif
	}

	// Delete the lights
	delete lights[0];
	delete lights[1];
}
