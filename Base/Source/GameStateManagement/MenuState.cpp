#include <iostream>
using namespace std;

#include "MenuState.h"
#include "GL\glew.h"
#include "../Application.h"
#include "LoadTGA.h"
#include "GraphicsManager.h"
#include "MeshBuilder.h"
#include "../TextEntity.h"
#include "RenderHelper.h"
#include "../SpriteEntity.h"
#include "../EntityManager.h"

#include "KeyboardController.h"
#include "SceneManager.h"
#include "MouseController.h"
#include "LuaManager.h"

CMenuState::CMenuState()
{

}
CMenuState::~CMenuState()
{

}

void CMenuState::Init()
{
	// Create and attach the camera to the scene
	camera.Init(Vector3(0, 0, 10), Vector3(0, 0, 0), Vector3(0, 1, 0));
	GraphicsManager::GetInstance()->AttachCamera(&camera);
	
	background = CLuaManager::GetInstance()->get<string>("GameScreen.screens.menu");

	Edittables *bg = new Edittables("GameScreen.screens.menu", "string");
	bg->stringvar = &background;
	CLuaManager::GetInstance()->edittableList.push_back(bg);

	// Load all the meshes
	MeshBuilder::GetInstance()->GenerateQuad("MENUSTATE_BKGROUND", Color(1, 1, 1), 1.f);
	MeshBuilder::GetInstance()->GetMesh("MENUSTATE_BKGROUND")->textureID = LoadTGA(background.c_str());
	MenuStateBackground = Create::Sprite2DObject("MENUSTATE_BKGROUND", 
												 Vector3(0.0f, 0.0f, 0.0f), 
												 Vector3(800.0f, 600.0f, 0.0f), true);

	MeshBuilder::GetInstance()->GenerateText("text", 16, 16);
	MeshBuilder::GetInstance()->GetMesh("text")->textureID = LoadTGA("Image//calibri.tga");
	MeshBuilder::GetInstance()->GetMesh("text")->material.kAmbient.Set(1, 0, 0);
	MeshBuilder::GetInstance()->GenerateQuad("menuButton", Color(0, 0, 0), 1.f);
	MeshBuilder::GetInstance()->GetMesh("menuButton")->textureID = LoadTGA("Image//menuButtonBG.tga");

	//Vector3 playButtonPos = CLuaManager::GetInstance()->get<Vector3>("GameScreen.button.menuPlay");
	//Vector3 hsButtonPos = CLuaManager::GetInstance()->get<Vector3>("GameScreen.button.menuHs");
	//Vector3 exitButtonPos = CLuaManager::GetInstance()->get<Vector3>("GameScreen.button.menuExit");

	Vector3 playButtonPos = Vector3(0.0, 100.0, 2.0);
	Vector3 hsButtonPos = Vector3(0.0, 0.0, 2.0);
	Vector3 exitButtonPos = Vector3(0.0, -100.0, 2.0);

	Color playEnterColor = Color(1, 1, 1);
	Color playLeaveColor = Color(0, 0, 0);

	Vector3 playButtonTextScale = Vector3(30.0f, 30.0f, 1.0f);
	Vector3 playButtonBGScale = Vector3(200.0f, 60.0f, 1.0f);

	//Color playEnterColor = Color(CLuaManager::GetInstance()->get<float>("GameScreen.button.enterColor.x"),
	//	CLuaManager::GetInstance()->get<float>("GameScreen.button.enterColor.y"),
	//	CLuaManager::GetInstance()->get<float>("GameScreen.button.enterColor.z"));

	//Color playLeaveColor = Color(CLuaManager::GetInstance()->get<float>("GameScreen.button.leaveColor.x"),
	//	CLuaManager::GetInstance()->get<float>("GameScreen.button.leaveColor.y"),
	//	CLuaManager::GetInstance()->get<float>("GameScreen.button.leaveColor.z"));

	playButton = Create::Button2DObject("text", 
										"menuButton", 
										playButtonPos, 
										"PLAY", 
										playButtonTextScale, 
										playButtonBGScale, 
										playEnterColor, 
										playLeaveColor,
										true);

	exitButton = Create::Button2DObject("text",
										"menuButton",
										exitButtonPos,
										"EXIT",
										playButtonTextScale,
										playButtonBGScale,
										playEnterColor,
										playLeaveColor,
										true);

	hsButton = Create::Button2DObject("text",
									  "menuButton",
									  hsButtonPos,
									  "SCORE",
									  playButtonTextScale,
									  playButtonBGScale,
									  playEnterColor,
									  playLeaveColor,
									  true);

	MeshBuilder::GetInstance()->GenerateQuad("cursor", Color(1, 1, 1), 1.f);
	MeshBuilder::GetInstance()->GetMesh("cursor")->textureID = LoadTGA("Image//cursor.tga");
	mouseCursor = Create::Sprite2DObject("cursor", Vector3(0, 0, 0), Vector3(25, 40, 1), true);
	MouseController::GetInstance()->SetKeepMouseCentered(false);

	cout << "CMenuState loaded\n" << endl;
}

void CMenuState::Update(double dt)
{
	if (CLuaManager::GetInstance()->updateNeeded)
	{
		MeshBuilder::GetInstance()->GetMesh("MENUSTATE_BKGROUND")->textureID = LoadTGA(background.c_str());
	}
	// Update the mouse position
	MouseController::GetInstance()->GetMousePosition(mousePos.x, mousePos.y);
	mousePos.x -= Application::GetInstance().GetWindowWidth()*0.5f;
	// Flip the mouse coordinate
	mousePos.y = Application::GetInstance().GetWindowHeight() - mousePos.y;
	mousePos.y -= Application::GetInstance().GetWindowHeight()*0.5f;

	mouseCursor->SetPosition(Vector3(mousePos.x, mousePos.y, 5));

	// Update the playButton
	playButton->Update(dt);
	hsButton->Update(dt);
	exitButton->Update(dt);

	// Check if the playButton was clicked
	if (playButton->IsClickedOn())
	{
		cout << "Loading GameState..." << endl;
		SceneManager::GetInstance()->SetActiveScene("GameState");
		Application::update = false;
	}
	if (exitButton->IsClickedOn())
	{
		cout << "Exitting Programme" << endl;
		Application::run = false;
	}
	if (hsButton->IsClickedOn())
	{
		cout << "Loading highscores" << endl;
		SceneManager::GetInstance()->SetActiveScene("HighScore");
	}
}

// Render this state
void CMenuState::Render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	GraphicsManager::GetInstance()->UpdateLightUniforms();

	// Setup 3D pipeline then render 3D
	GraphicsManager::GetInstance()->SetPerspectiveProjection(45.0f, 4.0f / 3.0f, 0.1f, 10000.0f);
	GraphicsManager::GetInstance()->AttachCamera(&camera);

	// PreRenderMesh
	RenderHelper::PreRenderMesh();
		EntityManager::GetInstance()->Render();
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
	// PostRenderText
	RenderHelper::PostRenderText();

	// Disable blend mode
	glDisable(GL_BLEND);
}

void CMenuState::Exit()
{
	// Remove the entity from EntityManager
	EntityManager::GetInstance()->RemoveEntity(MenuStateBackground);
	EntityManager::GetInstance()->RemoveEntity(playButton);
	EntityManager::GetInstance()->RemoveEntity(exitButton);
	EntityManager::GetInstance()->RemoveEntity(hsButton);
	EntityManager::GetInstance()->RemoveEntity(mouseCursor);

	// Remove the meshes which are specific to CMenuState
	MeshBuilder::GetInstance()->RemoveMesh("MENUSTATE_BKGROUND");

	// Detach camera from other entities
	GraphicsManager::GetInstance()->DetachCamera();
}