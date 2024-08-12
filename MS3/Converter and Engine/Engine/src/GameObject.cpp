//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include <math.h>
#include "MathEngine.h"
#include "GameObject.h"
#include "Game.h"
#include "GraphicsObject.h"
#include "Mesh.h"

namespace Azul
{

	GameObject::GameObject(GraphicsObject *pGraphicsObject)
		: poGraphicsObject(pGraphicsObject),
	          mDrawEnable(true)
	{
		this->poWorld = new Mat4(Mat4::Special::Identity);
		assert(poWorld);

		assert(pGraphicsObject);
	}

	GameObject::~GameObject()
	{
		delete this->poWorld;
		delete this->poGraphicsObject;

	}
	void GameObject::baseUpdateBoundingSphere()
	{
		// Get the ref Sphere
		Sphere *pRefSphere = poGraphicsObject->GetMesh()->poRefSphere;
		assert(pRefSphere);
		// Get the curr Sphere
		Sphere *pCurrSphere = poGraphicsObject->poCurrSphere;
		assert(pCurrSphere);
		// Update... cntr process through the world
		// Assuming a uniform scaling
		Vec3 A = pRefSphere->cntr;
		Vec3 radius(1.0f, 0.0f, 0.0f);
		Vec3 B = A + radius;
		Vec3 A_out;
		A_out = A * (*this->poWorld);
		Vec3 B_out;
		B_out = B * (*this->poWorld);
		pCurrSphere->rad = (B_out - A_out).len() * pRefSphere->rad;
		pCurrSphere->cntr = A_out;
	}

	Mat4 *GameObject::GetWorld()
	{
		return this->poWorld;
	}

	GraphicsObject *GameObject::GetGraphicsObject()
	{
		return this->poGraphicsObject;
	}

	void GameObject::SetWorld(Mat4 *pWorld)
	{
		assert(pWorld);
		*this->poWorld = *pWorld;
	}

	void GameObject::DrawEnable()
	{
		this->mDrawEnable = true;
	}

	void GameObject::DrawDisable()
	{
		this->mDrawEnable = false;
	}

	void GameObject::Draw()
	{
		GraphicsObject *pGraphicsObj = this->GetGraphicsObject();
		assert(pGraphicsObj);

		if(this->mDrawEnable)
		{
			pGraphicsObj->Render();
		}
	}

}

// --- End of File ---
