#pragma once

#include "Scene.h"
#include "Mtx44.h"
#include "Mesh.h"
#include "MatrixStack.h"
#include "../FPSCamera.h"
#include "ButtonEntity.h"
#include "../SpriteEntity.h"

class SceneManager;
class TextEntity;
//class TextEntity;
class CHighscoreState : public Scene
{
public:
	CHighscoreState();
	~CHighscoreState();

	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Exit();

private:
	FPSCamera camera;
	SpriteEntity* IntroStateBackground;
	TextEntity* tObj[3];
	SpriteEntity *mouseCursor;
	Vector3 mousePos;
	CButtonEntity *exit;
};
