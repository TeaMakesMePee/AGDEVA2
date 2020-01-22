#include "SceneNode.h"
#include "../EntityManager.h"
#include <algorithm>

#include "SceneGraph.h"
#include "GraphicsManager.h"
#include "../GenericEntity.h"
#include "MeshBuilder.h"
#include "RenderHelper.h"

CSceneNode::CSceneNode(void)
	: ID(-1)
	, theEntity(NULL)
	, theParent(NULL)
{
}

CSceneNode::~CSceneNode()
{
}

// Release all memory for this node and its children
void CSceneNode::Destroy(void)
{
	// Destroy the children first
	std::vector<CSceneNode*>::iterator it;
	for (it = theChildren.begin(); it != theChildren.end(); ++it)
	{
		(*it)->Destroy();
		delete *it;
		theChildren.erase(it);
	}

	// Reset the pointers for this node
	theEntity = NULL;
	theParent = NULL;
}

// Set the ID for this node
void CSceneNode::SetID(const int ID)
{
	this->ID = ID;
}

// Get the ID for this node
int CSceneNode::GetID(void) const
{
	return ID;
}

// Set the entity for this node
bool CSceneNode::SetEntity(EntityBase* theEntity)
{
	if (theEntity)
	{
		this->theEntity = theEntity;
		return true;
	}
	return false;
}
// Get the ID for this node
EntityBase* CSceneNode::GetEntity(void) const
{
	return theEntity;
}

// Set a parent to this node
void CSceneNode::SetParent(CSceneNode* theParent)
{
	this->theParent = theParent;
	this->theEntity->SetParent(theParent->GetEntity());
}

// Get parent of this node
CSceneNode* CSceneNode::GetParent(void) const
{
	return theParent;
}

// Add a child to this node
CSceneNode* CSceneNode::AddChild(EntityBase* theEntity)
{
	if (theEntity)
	{
		// Create a new Scene Node
		CSceneNode* aNewNode = new CSceneNode();
		// Set the entity to this new scene node
		aNewNode->SetEntity(theEntity);
		// Store the pointer to the parent
		aNewNode->SetParent(this);
		// Assign an ID to this node
		aNewNode->SetID(CSceneGraph::GetInstance()->GenerateID());
		// Add to vector list
		this->theChildren.push_back(aNewNode);
		if (this->theEntity)
			this->theEntity->SetChildren(aNewNode->GetEntity());
		// Return this new scene node
		return aNewNode;
	}

	cout << "CSceneNode::AddChild: Unable to add to this scene node, " << this->GetID() << endl;
	return NULL;
}

void CSceneNode::debugBalls()
{
	static const float BALL_SCALE = 0.05f;

	if (theEntity)
	{
		MS& modelStack = GraphicsManager::GetInstance()->GetModelStack();
		Mesh* mesh = MeshBuilder::GetInstance()->GetMesh("sphere");

		Vector3 pos, max, min;
		GenericEntity* e = dynamic_cast<GenericEntity*>(theEntity);
		e->GetAABB(max, min);
		pos = e->GetPosition();

		//if (!theUpdateTransformation)
		//{
		//	pos.x = GetTransform().a[0] * GetTransform().a[12] + GetTransform().a[4] * GetTransform().a[12] + GetTransform().a[8] * GetTransform().a[12];
		//	pos.y = GetTransform().a[1] * GetTransform().a[13] + GetTransform().a[5] * GetTransform().a[13] + GetTransform().a[9] * GetTransform().a[13];
		//	pos.z = GetTransform().a[2] * GetTransform().a[14] + GetTransform().a[6] * GetTransform().a[14] + GetTransform().a[10] * GetTransform().a[14];
		//	cout << "Dont Follow: " << pos << endl;
		//}

		modelStack.PushMatrix();
		modelStack.Translate(pos.x + max.x, pos.y + max.y, pos.z + max.z);
		modelStack.Scale(BALL_SCALE, BALL_SCALE, BALL_SCALE);
		RenderHelper::RenderMesh(mesh);
		modelStack.PopMatrix();

		modelStack.PushMatrix();
		modelStack.Translate(pos.x + min.x, pos.y + max.y, pos.z + max.z);
		modelStack.Scale(BALL_SCALE, BALL_SCALE, BALL_SCALE);
		RenderHelper::RenderMesh(mesh);
		modelStack.PopMatrix();

		modelStack.PushMatrix();
		modelStack.Translate(pos.x + max.x, pos.y + min.y, pos.z + max.z);
		modelStack.Scale(BALL_SCALE, BALL_SCALE, BALL_SCALE);
		RenderHelper::RenderMesh(mesh);
		modelStack.PopMatrix();

		modelStack.PushMatrix();
		modelStack.Translate(pos.x + max.x, pos.y + max.y, pos.z + min.z);
		modelStack.Scale(BALL_SCALE, BALL_SCALE, BALL_SCALE);
		RenderHelper::RenderMesh(mesh);
		modelStack.PopMatrix();

		modelStack.PushMatrix();
		modelStack.Translate(pos.x + min.x, pos.y + min.y, pos.z + min.z);
		modelStack.Scale(BALL_SCALE, BALL_SCALE, BALL_SCALE);
		RenderHelper::RenderMesh(mesh);
		modelStack.PopMatrix();

		modelStack.PushMatrix();
		modelStack.Translate(pos.x + max.x, pos.y + min.y, pos.z + min.z);
		modelStack.Scale(BALL_SCALE, BALL_SCALE, BALL_SCALE);
		RenderHelper::RenderMesh(mesh);
		modelStack.PopMatrix();

		modelStack.PushMatrix();
		modelStack.Translate(pos.x + min.x, pos.y + max.y, pos.z + min.z);
		modelStack.Scale(BALL_SCALE, BALL_SCALE, BALL_SCALE);
		RenderHelper::RenderMesh(mesh);
		modelStack.PopMatrix();

		modelStack.PushMatrix();
		modelStack.Translate(pos.x + min.x, pos.y + min.y, pos.z + max.z);
		modelStack.Scale(BALL_SCALE, BALL_SCALE, BALL_SCALE);
		RenderHelper::RenderMesh(mesh);
		modelStack.PopMatrix();
	}
}

// Delete a child from this node using the pointer to the entity
bool CSceneNode::DeleteChild(EntityBase* theEntity)
{
	// if this node contains theEntity, then we proceed to delete all its children
	if (this->theEntity == theEntity)
	{
		// If this node has children, then we proceed to delete them.
		if (theChildren.size() != 0)
		{
			// Iterate through all the children and delete all of their children and grand children etc
			vector <CSceneNode*>::iterator it = theChildren.begin();
			while (it != theChildren.end())
			{
				if ((*it)->DeleteAllChildren())
				{
					cout << "CSceneNode::DeleteChild: Deleted child nodes for theEntity." << endl;
				}
				(*it)->GetEntity()->SetIsDone(true);
				delete *it;
				it = theChildren.erase(it);
			}
		}
		return true;	// return true to say that this Node contains theEntity
	}
	else
	{
		// Search the children for this particular theEntity
		if (theChildren.size() != 0)
		{
			std::vector<CSceneNode*>::iterator it;
			for (it = theChildren.begin(); it != theChildren.end(); ++it)
			{
				// Check if this child is the one containing theEntity
				if ((*it)->DeleteChild(theEntity))
				{
					// If DeleteChild method call above DID remove theEntity
					// Then we should proceed to removed this child from our vector of children
					(*it)->GetEntity()->SetIsDone(true);
					delete *it;
					theChildren.erase(it);
					break;	// Stop deleting since we have already found and deleted theEntity
				}
			}
		}
	}

	return false;
}

// Delete a child from this node using its ID
bool CSceneNode::DeleteChild(const int ID)
{
	// if this node contains theEntity, then we proceed to delete all its children
	if (this->ID == ID)
	{
		// If this node has children, then we proceed to delete them.
		if (theChildren.size() != 0)
		{
			// Iterate through all the children and delete all of their children and grand children etc
			vector <CSceneNode*>::iterator it = theChildren.begin();
			while (it != theChildren.end())
			{
				if ((*it)->DeleteAllChildren())
				{
					cout << "CSceneNode::DeleteChild: Deleted child nodes for ID=" << ID << endl;
				}
				(*it)->GetEntity()->SetIsDone(true);
				delete *it;
				it = theChildren.erase(it);
			}
		}
		return true;	// return true to say that this Node contains theEntity
	}
	else
	{
		// Search the children for this particular theEntity
		if (theChildren.size() != 0)
		{
			std::vector<CSceneNode*>::iterator it;
			for (it = theChildren.begin(); it != theChildren.end(); ++it)
			{
				// Check if this child is the one containing theEntity
				if ((*it)->DeleteChild(theEntity))
				{
					// If DeleteChild method call above DID remove theEntity
					// Then we should proceed to removed this child from our vector of children
					(*it)->GetEntity()->SetIsDone(true);
					delete *it;
					theChildren.erase(it);
					break;	// Stop deleting since we have already found and deleted theEntity
				}
			}
		}
	}

	return false;
}
// Delete all children from this node using its ID
bool CSceneNode::DeleteAllChildren(void)
{
	bool bResult = false;

	vector <CSceneNode*>::iterator it = theChildren.begin();
	while (it != theChildren.end())
	{
		if ((*it)->DeleteAllChildren())
		{
			cout << "CSceneNode::DeleteChild: Delete child nodes." << endl;
		}
		(*it)->GetEntity()->SetIsDone(true);
		delete *it;
		it = theChildren.erase(it);
		bResult = true;
	}
	return bResult;
}
// Detach a child from this node using the pointer to the node
CSceneNode* CSceneNode::DetachChild(EntityBase* theEntity)
{
	if (theChildren.size() != 0)
	{
		vector <CSceneNode*>::iterator it = theChildren.begin();
		while (it != theChildren.end())
		{
			if ((*it)->GetEntity() == theEntity)
			{
				CSceneNode* theNode = (*it)->DetachChild(theEntity);
				if (theNode)
				{
					// Remove this node from the children
					theChildren.erase(it);
					return theNode;
				}
			}
			it++;
		}
	}
	return NULL;
}
// Detach a child from this node using its ID
CSceneNode* CSceneNode::DetachChild(const int ID)
{
	//// if it is inside this node, then return this node
	if (this->ID == ID)
		return this;

	if (theChildren.size() != 0)
	{
		vector <CSceneNode*>::iterator it = theChildren.begin();
		while (it != theChildren.end())
		{
			if ((*it)->GetID() == ID)
			{
				CSceneNode* theNode = (*it)->DetachChild(ID);
				if (theNode)
				{
					// Remove this node from the children
					theChildren.erase(it);
					return theNode;
				}
			}
			it++;
		}
	}
	return NULL;
}
// Get the entity inside this Scene Graph
CSceneNode* CSceneNode::GetEntity(EntityBase* theEntity)
{
	// if it is inside this node, then return this node
	if (this->theEntity == theEntity)
		return this;

	if (theChildren.size() != 0)
	{
		std::vector<CSceneNode*>::iterator it;
		for (it = theChildren.begin(); it != theChildren.end(); ++it)
		{
			CSceneNode* theNode = (*it)->GetEntity(theEntity);
			if (theNode)
			{
				return theNode;
			}
		}
	}
	return NULL;
}
// Get a child from this node using its ID
CSceneNode* CSceneNode::GetEntity(const int ID)
{
	// if it is inside this node, then return this node
	if (this->ID == ID)
		return this;

	// Check the children
	if (theChildren.size() != 0)
	{
		std::vector<CSceneNode*>::iterator it;
		for (it = theChildren.begin(); it != theChildren.end(); ++it)
		{
			CSceneNode* theNode = (*it)->GetEntity(ID);
			if (theNode)
			{
				return theNode;
			}
		}
	}
	return NULL;
}
// Return the number of children in this group
int CSceneNode::GetNumOfChild(void)
{
	// Start with this node's children
	int NumOfChild = theChildren.size();

	// Ask the children to feedback how many children they have
	std::vector<CSceneNode*>::iterator it;
	for (it = theChildren.begin(); it != theChildren.end(); ++it)
	{
		NumOfChild += (*it)->GetNumOfChild();
	}

	return NumOfChild;
}

// Update the Scene Graph
void CSceneNode::Update(const float dt)
{
	if (theUpdateTransformation)
	{
		ApplyTransform(GetUpdateTransform());
	}
	if (theEntity)
	{
		// Update this Scene Node
		theEntity->Update(dt);
	}

	// Count the number of children in this node
	int NumOfChild = theChildren.size();

	// Update the children
	std::vector<CSceneNode*>::iterator it;
	for (it = theChildren.begin(); it != theChildren.end(); ++it)
	{
		(*it)->Update(dt);
	}

	if (!theUpdateTransformation && theEntity && theEntity->HasCollider())
	{
		Vector3 pos;
		pos.x = GetTransform().a[0] * GetTransform().a[12] + GetTransform().a[4] * GetTransform().a[12] + GetTransform().a[8] * GetTransform().a[12];
		pos.y = GetTransform().a[1] * GetTransform().a[13] + GetTransform().a[5] * GetTransform().a[13] + GetTransform().a[9] * GetTransform().a[13];
		pos.z = GetTransform().a[2] * GetTransform().a[14] + GetTransform().a[6] * GetTransform().a[14] + GetTransform().a[10] * GetTransform().a[14];

		theEntity->SetPosition(pos);
	}
}

// Render the Scene Graph
void CSceneNode::Render(void)
{
	MS& modelStack = GraphicsManager::GetInstance()->GetModelStack();
	modelStack.PushMatrix();

		if (theEntity)
		{
			modelStack.Translate(	theEntity->GetPosition().x,
									theEntity->GetPosition().y,
									theEntity->GetPosition().z);
			if (theUpdateTransformation)
				modelStack.MultMatrix(GetTransform());

			// Render the entity
			theEntity->Render();
		}

		// Render the children
		std::vector<CSceneNode*>::iterator it;
		for (it = theChildren.begin(); it != theChildren.end(); ++it)
		{
			(*it)->Render();
		}

	modelStack.PopMatrix();
	//debugBalls();
}

void CSceneNode::ReCalc_AABB(void)
{
	if (!theEntity)
	{
		//cout << "ReCalc_AABB: theRoot start" << endl;
		// If this Scene Node is the root, then just iterate through all the children
		vector <CSceneNode*>::iterator it = theChildren.begin();
		while (it != theChildren.end())
		{
			(*it)->ReCalc_AABB();
			it++;
		}
		//cout << "ReCalc_AABB: theRoot end" << endl;
	}
	else
	{
		//cout << "\tReCalc_AABB: first tier scene node START" << endl;
		Vector3 theEntityPosition, theMaxAABB, theMinAABB;

		// Get the AABB of the entity in this Scene Node
		GenericEntity* theGenericEntity = dynamic_cast<GenericEntity*>(theEntity);
		theGenericEntity->GetAABB(theMaxAABB, theMinAABB);
		theEntityPosition = theGenericEntity->GetPosition();
		//cout << "\t\tBEFORE" << theEntityPosition + theMaxAABB << ", " << theEntityPosition + theMinAABB << endl;

		// Compare the children's AABB against this
		//Vector3 theChildPosition, theChildMaxAABB, theChildMinAABB;
		vector <CSceneNode*>::iterator it = theChildren.begin();
		while (it != theChildren.end())
		{
			// Get the AABB for this child
			(*it)->ReCalc_AABB(theEntityPosition, theMaxAABB, theMinAABB);

			// Go to the next child
			it++;
		}

		// Update the entity's AABB to include the children's AABB
		theGenericEntity->SetAABB(theMaxAABB, theMinAABB);
		//cout << "\t\tAFTER" << theEntityPosition + theMaxAABB << ", " << theEntityPosition + theMinAABB << endl;
		//cout << "\tReCalc_AABB: first tier scene node END" << endl;
	}
}

void CSceneNode::ReCalc_AABB(Vector3 theParentPosition, Vector3 & MaxAABB, Vector3 & MinAABB)
{
	// If this Scene Node has an entity
	// This should not be an issue as there should not be any root node at this point
	if (theEntity)
	{
		Vector3 theEntityPosition, theMaxAABB, theMinAABB;

		// Get the AABB of the entity in this Scene Node
		GenericEntity* theGenericEntity = dynamic_cast<GenericEntity*>(theEntity);
		theGenericEntity->GetAABB(theMaxAABB, theMinAABB);
		Vector3 theOffsetFromParent;
		GetTranslate(theOffsetFromParent.x, theOffsetFromParent.y, theOffsetFromParent.z);
		theEntityPosition = theParentPosition + theOffsetFromParent;// theGenericEntity->GetPosition();

		// Check if the entity's AABB is larger than the parent
		// If yes, then set the entity's AABB to the parent'sAABB
		if (theEntityPosition.x + theMaxAABB.x > theParentPosition.x + MaxAABB.x)
			MaxAABB.x = (theEntityPosition + theMaxAABB).x - theParentPosition.x;
		if (theEntityPosition.y + theMaxAABB.y > theParentPosition.y + MaxAABB.y)
			MaxAABB.y = (theEntityPosition + theMaxAABB).y - theParentPosition.y;
		if (theEntityPosition.z + theMaxAABB.z > theParentPosition.z + MaxAABB.z)
			MaxAABB.z = (theEntityPosition + theMaxAABB).z - theParentPosition.z;
		if (theEntityPosition.x + theMinAABB.x < theParentPosition.x + MinAABB.x)
			MinAABB.x = (theEntityPosition + theMinAABB).x - theParentPosition.x;
		if (theEntityPosition.y + theMinAABB.y < theParentPosition.y + MinAABB.y)
			MinAABB.y = (theEntityPosition + theMinAABB).x - theParentPosition.y;
		if (theEntityPosition.z + theMinAABB.z < theParentPosition.z + MinAABB.z)
			MinAABB.z = (theEntityPosition + theMinAABB).z - theParentPosition.z;

		// Check the children of this Scene Node
		//Vector3 theChildPosition, theChildMaxAABB, theChildMinAABB;
		vector <CSceneNode*>::iterator it = theChildren.begin();
		while (it != theChildren.end())
		{
			// Get the AABB for this child
			(*it)->ReCalc_AABB(theEntityPosition, theMaxAABB, theMinAABB);

			// Go to the next child
			it++;
		}

		// Check if the entity's AABB is larger than the parent
		// If yes, then set the entity's AABB to the parent'sAABB
		if (theEntityPosition.x + theMaxAABB.x > theParentPosition.x + MaxAABB.x)
			MaxAABB.x = (theEntityPosition + theMaxAABB).x - theParentPosition.x;
		if (theEntityPosition.y + theMaxAABB.y > theParentPosition.y + MaxAABB.y)
			MaxAABB.y = (theEntityPosition + theMaxAABB).y - theParentPosition.y;
		if (theEntityPosition.z + theMaxAABB.z > theParentPosition.z + MaxAABB.z)
			MaxAABB.z = (theEntityPosition + theMaxAABB).z - theParentPosition.z;
		if (theEntityPosition.x + theMinAABB.x < theParentPosition.x + MinAABB.x)
			MinAABB.x = (theEntityPosition + theMinAABB).x - theParentPosition.x;
		if (theEntityPosition.y + theMinAABB.y < theParentPosition.y + MinAABB.y)
			MinAABB.y = (theEntityPosition + theMinAABB).y - theParentPosition.y;
		if (theEntityPosition.z + theMinAABB.z < theParentPosition.z + MinAABB.z)
			MinAABB.z = (theEntityPosition + theMinAABB).z - theParentPosition.z;

		// Update the entity's AABB to include the children's AABB
		theGenericEntity->SetAABB(theMaxAABB, theMinAABB);
	}
}

// PrintSelf for debug purposes
void CSceneNode::PrintSelf(const int numTabs)
{
	if (numTabs == 0)
	{
		cout << "============================" << endl << "Start of theRoot::PrintSelf()" << endl;
		GetTransform().PrintSelf();
		cout << "CSceneNode::PrintSelf: ID=" << ID << "/Children=" << theChildren.size() << endl;
		cout << "Printing out the children:" << endl;
		vector <CSceneNode*>::iterator it = theChildren.begin();
		while (it != theChildren.end())
		{
			(*it)->PrintSelf((numTabs + 1));
			it++;
		}
		cout << "End of theRoot::PrintSelf()" << endl << "============================" << endl;
	}
	else
	{
		for (int i = 0; i < numTabs; i++)
			cout << "\t";
		cout << "CSceneNode::PrintSelf: ID=" << ID << "/theEntity=" << theEntity << 
				"/Children=" << theChildren.size() << endl;
		for (int i = 0; i < numTabs; i++)
			cout << "\t";
		cout << "Printing out the children:" << endl;
		vector <CSceneNode*>::iterator it = theChildren.begin();
		while (it != theChildren.end())
		{
			(*it)->PrintSelf((numTabs + 1));
			it++;
		}
	}
}