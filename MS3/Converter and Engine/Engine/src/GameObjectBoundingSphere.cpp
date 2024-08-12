//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "GameObjectBoundingSphere.h"
#include "GameObject.h"
#include "CameraMan.h"
#include "GraphicsObject_WireframeConstantColor.h"


namespace Azul
{
	GameObjectBoundingSphere::GameObjectBoundingSphere(GraphicsObject *pGraphicsObject)
		: GameObjectRigid(pGraphicsObject)
	{
		this->pRefGameObj = nullptr;
		this->poScale = new Vec3();
		this->poTrans = new Vec3();

		assert(pGraphicsObject);
		assert(this->poScale);
		assert(this->poTrans);
	}

	GameObjectBoundingSphere::~GameObjectBoundingSphere()
	{
		delete this->poScale;
		delete this->poTrans;
	}

	void GameObjectBoundingSphere::SetBoundingSphereReference(GameObject *pGameObj)
	{
		this->pRefGameObj = pGameObj;
	}

	void GameObjectBoundingSphere::privUpdate(AnimTime currentTime)
	{
		AZUL_UNUSED_VAR(currentTime);

		// Goal: update the world matrix

		Mat4 Scale(Mat4::Scale::XYZ, *this->poScale);
		Mat4 TransA(Mat4::Trans::XYZ, *this->poTrans);

		// world matrix
		*this->poWorld = Scale * TransA;

		// Flip the color based on camera_0
		Camera3D *pCam = (Camera3D *)CameraMan::Find3D(Camera::Name::CAMERA_0);
		assert(pCam);
		assert(pCam->getType() == Camera::Type::PERSPECTIVE_3D);

		Sphere *pCurrSphere = this->poGraphicsObject->poCurrSphere;

		// Architecture issue... this doesn't feel good.
		GraphicsObject_WireframeConstantColor *pGObj = (GraphicsObject_WireframeConstantColor *)this->poGraphicsObject;
		if(pCam->CullTest(*pCurrSphere) == Camera::CullResult::CULL_OUTSIDE)
		{
			pGObj->poWireColor->set(1.0f, 0.0f, 0.0f, 1.0f);
		}
		else
		{
			pGObj->poWireColor->set(0.0f, 1.0f, 0.0f, 1.0f);
		}


	}

	void GameObjectBoundingSphere::privUpdateBoundingSphereReference(AnimTime currentTime)
	{
		// incase the reference object wasn't updated first
		// update it now.

		this->pRefGameObj->Update(currentTime);

		// set the center and scale of bound box based on ref game object's world coord
		Sphere *pRefCurrSphere = this->pRefGameObj->GetGraphicsObject()->poCurrSphere;
		this->poScale->set(pRefCurrSphere->rad, pRefCurrSphere->rad, pRefCurrSphere->rad);
		this->poTrans->set(pRefCurrSphere->cntr);

		Sphere *pCurrSphere = this->GetGraphicsObject()->poCurrSphere;
		*pCurrSphere = *pRefCurrSphere;
	}

	void GameObjectBoundingSphere::Update(AnimTime currentTime)
	{
		// Set Translation & Scale from reference
		this->privUpdateBoundingSphereReference(currentTime);

		// Goal: update the world matrix
		this->privUpdate(currentTime);

		// push to graphics object
		this->poGraphicsObject->SetWorld(*this->poWorld);
	}

}

// --- End of File ---

