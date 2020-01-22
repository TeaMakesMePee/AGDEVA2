#include "ButtonEntity.h"
#include "MeshBuilder.h"
#include "../EntityManager.h"
#include "GraphicsManager.h"
#include "RenderHelper.h"
#include "MouseController.h"
#include "../Application.h"
#include "KeyboardController.h"
#include "MouseController.h"
#include "SceneManager.h"

#include <iostream>
using namespace std;

// Constructor
CButtonEntity::CButtonEntity(void)
{
	Init();
}

// Destructor
CButtonEntity::~CButtonEntity(void)
{
}

// Initialise this class instance
void CButtonEntity::Init(void)
{
	bMouseEntered = false;
	bClickedOn = false;
	bMouseReleased = true;
	bMousePressed = false;
}

// Destroy this class instance
void CButtonEntity::Destroy(void)
{
}

// When the mouse enters the entity's region...
void CButtonEntity::OnMouseEnter()
{
	std::cout << "Enter" << std::endl;
	cColour = cEnterColour;
}

// When the mouse leaves the entity's region...
void CButtonEntity::OnMouseLeave()
{
	std::cout << "Leave" << std::endl;
	cColour = cLeaveColour;
}

// When the mouse button was pressed...
void CButtonEntity::OnMousePressed(void)
{
	std::cout << "Pressed" << std::endl;
	bMouseReleased = false;
	bMousePressed = true;
}

// When the mouse button was released...
void CButtonEntity::OnMouseReleased(void)
{
	std::cout << "Released" << std::endl;
	bMouseReleased = true;
	bMousePressed = false;
}

// Check if a position is within the button's region
bool CButtonEntity::IsWithinButtonRegion(	const float entity1_posX, const float entity1_posY,
											const float entity1_Width, const float entity1_Height,
											const float entity2_posX, const float entity2_posY,
											const float entity2_Width, const float entity2_Height)
{
	if ( (entity1_posX - (entity1_Width*0.5f) < entity2_posX - (entity2_Width*0.5f) + entity2_Width)
		&& (entity1_posX - (entity1_Width*0.5f) + entity1_Width > entity2_posX - (entity2_Width*0.5f)) )
	{
		if ( (entity1_posY - (entity1_Height*0.5f) < entity2_posY - (entity2_Height*0.5f) + entity2_Height)
			&& (entity1_posY - (entity1_Height*0.5f) + entity1_Height > entity2_posY - (entity2_Height*0.5f)) )
			return true;
	}
	return false;
}

// Check if the button was clicked on
bool CButtonEntity::IsClickedOn(void) const
{
	return bClickedOn;
}

// Default update for this entity
void CButtonEntity::Update(const double _dt)
{
	// Reset these flags
	bMouseReleased = true;
	bMousePressed = false;

	// Get the mouse position
	Vector3 mousePos;
	mousePos.SetZero();
	MouseController::GetInstance()->GetMousePosition(mousePos.x, mousePos.y);
	mousePos.x -= Application::GetInstance().GetWindowWidth()*0.5f;

	mousePos.y = Application::GetInstance().GetWindowHeight() - mousePos.y;
	mousePos.y -= Application::GetInstance().GetWindowHeight()*0.5f;

	// Check if the mouse position is within this ButtonEntity
	if (IsWithinButtonRegion(position.x, position.y,
		GetBackgroundScale().x, GetBackgroundScale().y,
		mousePos.x, mousePos.y,
		1, 1))
	{
		// if the mouse enters the ButtonEntity for the first time...
		if (bMouseEntered == false)
		{
			OnMouseEnter();
			bMouseEntered = true;
		}

		// if the mouse button was clicked when the mouse was inside the ButtonEntity...
		if (bClickedOn == false && MouseController::GetInstance()->IsButtonDown(MouseController::GetInstance()->LMB))
		{
			OnMousePressed();
			bClickedOn = true;
		}
		// if the mouse button was released when the mouse was inside the ButtonEntity...
		else if (bClickedOn == true && !MouseController::GetInstance()->IsButtonDown(MouseController::GetInstance()->LMB))
		{
			OnMouseReleased();
			bClickedOn = false;
		}
	}
	else
	{
		// If the mouse is not inside the ButtonEntity...
		if (bMouseEntered == true)
		{
			OnMouseLeave();
			bMouseEntered = false;
		}
		bClickedOn = false;
	}
}

// Render this entity in 3D
void CButtonEntity::Render(void)
{
}

// Render this entity in 2D
void CButtonEntity::RenderUI(void)
{
	// Render the button background
	MS& modelStack = GraphicsManager::GetInstance()->GetModelStack();
	modelStack.PushMatrix();
		modelStack.Translate(v3Position.x, v3Position.y, v3Position.z - 0.1);
		modelStack.Scale(v3BackgroundScale.x, v3BackgroundScale.y, v3BackgroundScale.z);
		RenderHelper::RenderMesh(mButtonMesh);
	modelStack.PopMatrix();

	// Render the text within the button
	modelStack.PushMatrix();
		modelStack.Translate(v3Position.x - (sText.length() + 0.5f)*0.5f * v3TextScale.x, v3Position.y, v3Position.z);
		modelStack.Scale(v3TextScale.x, v3TextScale.y, v3TextScale.z);
		RenderHelper::RenderText(mTextMesh, sText, cColour);
	modelStack.PopMatrix();
}

// Create a Button2DObject
CButtonEntity* Create::Button2DObject(	const std::string& _sTextMeshName,
										const std::string& _sButtonMeshName,
										const Vector3& _v3Position,
										const std::string& _sText,
										const Vector3& _v3TextScale,
										const Vector3& _v3BackgroundScale,
										const Color& _cEnterColour,
										const Color& _cLeaveColour,
										const bool& _addToLibrary)
{
	Mesh* textMesh = MeshBuilder::GetInstance()->GetMesh(_sTextMeshName);
	Mesh* buttonMesh = MeshBuilder::GetInstance()->GetMesh(_sButtonMeshName);
	if (textMesh == nullptr || buttonMesh == nullptr)
	{
		cout << "Unable to create a CButtonEntity" << endl;
		return nullptr;
	}

	CButtonEntity* result = new CButtonEntity();
	result->SetTextMesh(textMesh);
	result->SetButtonBGMesh(buttonMesh);
	result->SetText(_sText);
	result->SetEnterColour(_cEnterColour);
	result->SetLeaveColour(_cLeaveColour);
	result->SetColour(_cLeaveColour);
	result->SetPosition(_v3Position);
	result->SetTextScale(_v3TextScale);
	result->SetBackgroundScale(_v3BackgroundScale);
	if (_addToLibrary)
		EntityManager::GetInstance()->AddEntity(result);
	return result;
}