//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "MathEngine.h"
#include "GameObject2D.h"
#include "GraphicsObject.h"

namespace Azul
{
	GameObject2D::GameObject2D(GraphicsObject_Sprite *pGraphicsObject)
		: GameObject(pGraphicsObject)
	{
		assert(pGraphicsObject != 0);

		this->angle = 0.0f;
		this->posX = pGraphicsObject->origPosX;
		this->posY = pGraphicsObject->origPosY;
		this->scaleX = 1.0f;
		this->scaleY = 1.0f;
	}

	GameObject2D::~GameObject2D()
	{
	}


	void GameObject2D::Update(AnimTime currentTime)
	{
		AZUL_UNUSED_VAR(currentTime);

		// Goal: update the world matrix
		Mat4 Scale(Mat4::Scale::XYZ, this->scaleX, this->scaleY, 1.0f);
		Mat4 Rot(Mat4::Rot1::Z, this->angle);
		Mat4 Trans(Mat4::Trans::XYZ, this->posX, this->posY, 0.0f);

		*this->poWorld = Scale * Rot * Trans;

		// push to graphics object
		this->poGraphicsObject->SetWorld(*this->poWorld);
	}

}

//--- End of File ---
