#pragma once

#include "EntityBase.h"
#include "Vector3.h"
#include "Vertex.h"
#include <string>

class Mesh;

class CButtonEntity : public EntityBase
{
public:
	// Constructor
	CButtonEntity(void);
	// Destructor
	virtual ~CButtonEntity(void);

	// Initialise this class instance
	virtual void Init(void);
	// Destroy this class instance
	virtual void Destroy(void);

	// When the mouse enters the entity's region...
	virtual void OnMouseEnter(void);
	// When the mouse leaves the entity's region...
	virtual void OnMouseLeave(void);
	// When the mouse button was released...
	virtual void OnMouseReleased(void);
	// When the mouse button was pressed...
	virtual void OnMousePressed(void);

	// Check if a position is within the button's region
	virtual bool IsWithinButtonRegion(	const float entity1_posX, const float entity1_posY, 
										const float entity1_Width, const float entity1_Height, 
										const float entity2_posX, const float entity2_posY, 
										const float entity2_Width, const float entity2_Height);
	// Check if the button was clicked on
	virtual bool IsClickedOn(void) const;

	// Default update for this entity
	virtual void Update(const double _dt);
	// Render this entity in 3D
	virtual void Render(void);
	// Render this entity in 2D
	virtual void RenderUI(void);

	////////////////////////////////////////////////////////////
	// Methods to customise this button entity
	////////////////////////////////////////////////////////////
	inline void SetPosition(const Vector3& _value) { v3Position = _value; };
	inline Vector3 GetPosition(void) const { return v3Position; };

	inline void SetTextScale(const Vector3& _value){ v3TextScale = _value; };
	inline Vector3 GetTextScale(void) const { return v3TextScale; };

	inline void SetBackgroundScale(const Vector3& _value) { v3BackgroundScale = _value; }
	inline Vector3 GetBackgroundScale(void) const { return v3BackgroundScale; };

	inline void SetTextMesh(Mesh* _mesh) { mTextMesh = _mesh; }
	inline Mesh* GetTextMesh(void) const { return mTextMesh; };
	inline void SetButtonBGMesh(Mesh *_mesh) { mButtonMesh = _mesh; }
	inline Mesh* GetButtonBGMesh(void) const { return mButtonMesh; };

	inline void SetText(const std::string& _text){ sText = _text; };
	inline std::string GetText(void) const { return sText; };

	inline void SetEnterColour(const Color& _colour){ cEnterColour = _colour; };
	inline Color GetEnterColour(void) const { return cEnterColour; };
	inline void SetLeaveColour(const Color& _colour) { cLeaveColour = _colour; };
	inline Color GetLeaveColor(void) const { return cLeaveColour; };
	inline void SetColour(const Color& _colour) { cColour = _colour; };
	inline Color GetColour(void) const { return cColour; };

protected:
	Vector3 v3Position;
	Vector3 v3TextScale;
	Vector3 v3BackgroundScale;
	Vector3 v3ButtonBGScale;
	Mesh* mTextMesh;
	Mesh* mButtonMesh;
	std::string sText;
	Color cEnterColour;
	Color cLeaveColour;
	Color cColour;

	bool bClickedOn;
	bool bMouseEntered;
	bool bMouseReleased;
	bool bMousePressed;
};

namespace Create
{
	CButtonEntity* Button2DObject(	const std::string& _sTextMeshName,
									const std::string& _sButtonMeshName, 
									const Vector3& _v3Position, 
									const std::string& _sText, 
									const Vector3& _v3TextScale, 
									const Vector3& _v3BackgroundScale, 
									const Color& _cEnterColour, 
									const Color& _cLeaveColour,
									const bool& _addToLibrary);
};
