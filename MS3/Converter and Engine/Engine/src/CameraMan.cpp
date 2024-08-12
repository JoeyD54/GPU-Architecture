//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "Camera.h"
#include "CameraNode.h"
#include "CameraMan.h"
#include "Camera2D.h"
#include "Camera3D.h"

namespace Azul
{
	CameraMan::CameraMan()
	{
		this->poActive = nullptr;

		// w1(1) - Camera Type
		//this->currCamera = nullptr;

		this->pCamOrthographic = nullptr;
		this->pCamPerspective = nullptr;
	}

	CameraMan *CameraMan::privGetInstance()
	{
		// This is where its actually stored (BSS section)
		static CameraMan cameraMan;
		return &cameraMan;
	}

	void CameraMan::Create()
	{
		// Get the instance to the manager
		CameraMan *pCameraMan;
		pCameraMan = CameraMan::privGetInstance();
		assert(pCameraMan);
	}

	void CameraMan::Destroy()
	{
		// Get the instance to the manager
		CameraMan *pCameraMan = CameraMan::privGetInstance();
		assert(pCameraMan);

		CameraLink *pTmp = pCameraMan->poActive;
		while (pTmp != nullptr)
		{
			CameraLink *pDeleteMe = pTmp;
			pTmp = pTmp->next;
			delete pDeleteMe;
		}

	}

	void CameraMan::Add(Camera::Name name, Camera *pCamera)
	{
		// Get the instance to the manager
		CameraMan *pCameraMan = CameraMan::privGetInstance();
		assert(pCameraMan);

		// Create a TextureNode
		CameraNode *pNode = new CameraNode();
		assert(pNode);

		// initialize it
		assert(pCamera);
		pCamera->setName(name);
		pNode->set(pCamera);

		// Now add it to the manager
		pCameraMan->privAddToFront(pNode, pCameraMan->poActive);
	}


	Camera2D *CameraMan::Find2D(Camera::Name _name)
	{
		// Get the instance to the manager
		CameraMan *pCameraMan = CameraMan::privGetInstance();
		assert(pCameraMan);

		CameraNode *pNode = (CameraNode *)pCameraMan->poActive;
		while (pNode != nullptr)
		{
			if (pNode->poCamera->getName() == _name)
			{
				// found it
				break;
			}

			pNode = (CameraNode *)pNode->next;
		}
		assert(pNode);

		Camera2D *pTmp = (Camera2D *)pNode->poCamera;
		assert(pTmp->getType() == Camera::Type::ORTHOGRAPHIC_2D);

		return pTmp;
	}

	Camera3D *CameraMan::Find3D(Camera::Name _name)
	{
		// Get the instance to the manager
		CameraMan *pCameraMan = CameraMan::privGetInstance();
		assert(pCameraMan);

		CameraNode *pNode = (CameraNode *)pCameraMan->poActive;
		while(pNode != nullptr)
		{
			if(pNode->poCamera->getName() == _name)
			{
				// found it
				break;
			}

			pNode = (CameraNode *)pNode->next;
		}
		assert(pNode);

		Camera3D *pTmp = (Camera3D *)pNode->poCamera;
		assert(pTmp->getType() == Camera::Type::PERSPECTIVE_3D);

		return pTmp;
	}

	void CameraMan::SetCurrent2D(const Camera::Name name)
	{
		CameraMan *pCamMan = CameraMan::privGetInstance();
		assert(pCamMan);

		Camera2D *pCam = CameraMan::Find2D(name);
		assert(pCam);
		assert(pCam->getType() == Camera::Type::ORTHOGRAPHIC_2D);

		pCamMan->pCamOrthographic = (Camera2D *)pCam;
	}

	void CameraMan::SetCurrent3D(const Camera::Name name)
	{
		CameraMan *pCamMan = CameraMan::privGetInstance();
		assert(pCamMan);

		Camera *pCam = CameraMan::Find3D(name);
		assert(pCam);
		assert(pCam->getType() == Camera::Type::PERSPECTIVE_3D);

		pCamMan->pCamPerspective = (Camera3D *)pCam;
	}

	Camera2D *CameraMan::GetCurrent2D()
	{
		Camera2D *pCam = CameraMan::privGetInstance()->pCamOrthographic;
		assert(pCam);
		assert(pCam->getType() == Camera::Type::ORTHOGRAPHIC_2D);

		return pCam;
	}

	Camera3D *CameraMan::GetCurrent3D()
	{
		Camera3D *pCam = CameraMan::privGetInstance()->pCamPerspective;
		assert(pCam);
		assert(pCam->getType() == Camera::Type::PERSPECTIVE_3D);

		return pCam;
	}

	void CameraMan::privAddToFront(CameraLink *node, CameraLink *&head)
	{
		assert(node != nullptr);

		if (head == nullptr)
		{
			head = node;
			node->next = nullptr;
			node->prev = nullptr;
		}
		else
		{
			node->next = head;
			head->prev = node;
			head = node;
		}
	}

	void CameraMan::privRemove(CameraLink *pNode, CameraLink *&poHead)
	{
		assert(pNode);

		if (pNode->prev != nullptr)
		{	// middle or last node
			pNode->prev->next = pNode->next;
		}
		else
		{  // first
			poHead = (CameraLink *)pNode->next;
		}

		if (pNode->next != nullptr)
		{	// middle node
			pNode->next->prev = pNode->prev;
		}
	}

}

// --- End of File ---
