#include <iostream>
using namespace std;

#include "highscorestate.h"
#include "GL\glew.h"
#include "../Application.h"
#include "LoadTGA.h"
#include "GraphicsManager.h"
#include "MeshBuilder.h"
#include "../TextEntity.h"
#include "RenderHelper.h"
#include "../SpriteEntity.h"
#include "MouseController.h"
#include "../EntityManager.h"

#include "KeyboardController.h"
#include "SceneManager.h"
#include "LuaManager.h"

CHighscoreState::CHighscoreState()
{

}
CHighscoreState::~CHighscoreState()
{

}

void CHighscoreState::Init()
{
	// Create and attach the camera to the scene
	camera.Init(Vector3(0, 0, 10), Vector3(0, 0, 0), Vector3(0, 1, 0));
	GraphicsManager::GetInstance()->AttachCamera(&camera);

	// Load all the meshes
	MeshBuilder::GetInstance()->GenerateQuad("INTROSTATE_BKGROUND", Color(1, 1, 1), 1.f);
	MeshBuilder::GetInstance()->GetMesh("INTROSTATE_BKGROUND")->textureID = LoadTGA(CLuaManager::GetInstance()->get<string>("GameScreen.screens.highscore").c_str());
	IntroStateBackground = Create::Sprite2DObject("INTROSTATE_BKGROUND", 
													Vector3(0.0f, 0.0f, 0.0f), 
													Vector3(800.0f, 600.0f, 0.0f), true);

	float halfWindowWidth = Application::GetInstance().GetWindowWidth() / 2.0f;
	float halfWindowHeight = Application::GetInstance().GetWindowHeight() / 2.0f;
	float fontSize = 25.0f;
	float halfFontSize = fontSize / 2.0f;
	for (int i = 0; i < 3; ++i)
	{
		tObj[i] = Create::Text2DObject("text", Vector3(-180, 150 - i * 40, 3.0f), "", Vector3(fontSize, fontSize, fontSize), Color(1.0f, 0.0f, 0.0f));
	}

	string x = "1: " + std::to_string(CLuaManager::GetInstance()->get<int>("Highscore.scores.first"));
	tObj[0]->SetText(x);

	x = "3: " + std::to_string(CLuaManager::GetInstance()->get<int>("Highscore.scores.third"));
	tObj[2]->SetText(x);

	x = "2: " + std::to_string(CLuaManager::GetInstance()->get<int>("Highscore.scores.second"));
	tObj[1]->SetText(x);

	Vector3 exitButtonPos = Vector3(0.0, -250.0, 2.0);
	Vector3 playButtonTextScale = Vector3(30.0f, 30.0f, 1.0f);
	Vector3 playButtonBGScale = Vector3(200.0f, 60.0f, 1.0f);

	Color playEnterColor = Color(1, 1, 1);

	Color playLeaveColor = Color(0, 0, 0);

	MeshBuilder::GetInstance()->GenerateQuad("menuButton", Color(0, 0, 0), 1.f);
	MeshBuilder::GetInstance()->GetMesh("menuButton")->textureID = LoadTGA("Image//menuButtonBG.tga");

	exit = Create::Button2DObject("text",
		"menuButton",
		exitButtonPos,
		"EXIT",
		playButtonTextScale,
		playButtonBGScale,
		playEnterColor,
		playLeaveColor,
		true);

	MeshBuilder::GetInstance()->GenerateQuad("cursor", Color(1, 1, 1), 1.f);
	MeshBuilder::GetInstance()->GetMesh("cursor")->textureID = LoadTGA("Image//cursor.tga");
	mouseCursor = Create::Sprite2DObject("cursor", Vector3(0, 0, 0), Vector3(25, 40, 1), true);
	MouseController::GetInstance()->SetKeepMouseCentered(false);

	cout << "CIntroState loaded\n" << endl;
}

void CHighscoreState::Update(double dt)
{
	// Update the mouse position
	MouseController::GetInstance()->GetMousePosition(mousePos.x, mousePos.y);
	mousePos.x -= Application::GetInstance().GetWindowWidth()*0.5f;
	// Flip the mouse coordinate
	mousePos.y = Application::GetInstance().GetWindowHeight() - mousePos.y;
	mousePos.y -= Application::GetInstance().GetWindowHeight()*0.5f;

	mouseCursor->SetPosition(Vector3(mousePos.x, mousePos.y, 5));

	//string x = "1: " + std::to_string(CLuaManager::GetInstance()->get<int>("Highscore.scores.first"));
	//tObj[0]->SetText(x);

	//x = "3: " + std::to_string(CLuaManager::GetInstance()->get<int>("Highscore.scores.third"));
	//tObj[2]->SetText(x);

	//x = "2: " + std::to_string(CLuaManager::GetInstance()->get<int>("Highscore.scores.second"));
	//tObj[1]->SetText(x);

	exit->Update(dt);

	// Check if the playButton was clicked
	if (exit->IsClickedOn())
	{
		cout << "Loading Menu..." << endl;
		SceneManager::GetInstance()->SetActiveScene("MenuState");
	}
}

void CHighscoreState::Render()
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

void CHighscoreState::Exit()
{
	// Remove the entity from EntityManager
	EntityManager::GetInstance()->RemoveEntity(IntroStateBackground);
	EntityManager::GetInstance()->RemoveEntity(exit);
	EntityManager::GetInstance()->RemoveEntity(mouseCursor);
	// Remove the meshes which are specific to CIntroState
	MeshBuilder::GetInstance()->RemoveMesh("INTROSTATE_BKGROUND");

	// Detach camera from other entities
	GraphicsManager::GetInstance()->DetachCamera();
}