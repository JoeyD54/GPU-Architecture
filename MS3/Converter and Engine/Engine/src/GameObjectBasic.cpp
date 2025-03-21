//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "Game.h"
#include "MathEngine.h"
#include "GameObjectBasic.h"
#include "GraphicsObject.h"
#include "Mesh.h"
#include "Anim.h"

namespace Azul
{
	GameObjectBasic::GameObjectBasic(GraphicsObject *pGraphicsObject)
		: GameObjectRigid(pGraphicsObject)
	{
		assert(pGraphicsObject);
		this->poTrans = new Vec3(0.0f, 0.0f, 0.0f);
		this->poScale = new Vec3(1.0f, 1.0f, 1.0f);
		this->poQuat = new Quat(0.0f, 0.0f, 0.0f, 1.0f);

		assert(this->poTrans);
		assert(this->poScale);
		assert(this->poQuat);

		this->delta_x = 0.0f;
		this->delta_y = 0.0f;
		this->delta_z = 0.0f;

		this->cur_rot_x = 0.0f;
		this->cur_rot_y = 0.0f;
		this->cur_rot_z = 0.0f;
	}

	GameObjectBasic::~GameObjectBasic()
	{
		delete this->poTrans;
		delete this->poScale;
		delete this->poQuat;
	}

	void GameObjectBasic::privUpdate(AnimTime currentTime)
	{
		AZUL_UNUSED_VAR(currentTime);

		Mat4 T(Mat4::Trans::XYZ, *this->poTrans);
		Mat4 S(Mat4::Scale::XYZ, *this->poScale);
		Quat   Q(*this->poQuat);

		cur_rot_x += delta_x;
		cur_rot_y += delta_y;
		cur_rot_z += delta_z;

		Mat4 Rx(Mat4::Rot1::X, cur_rot_x);
		Mat4 Ry(Mat4::Rot1::Y, cur_rot_y);
		Mat4 Rz(Mat4::Rot1::Z, cur_rot_z);

		//Mat4 R(Mat4::Rot1::Y, cur_rot_y);
		// world matrix
		*this->poWorld = S * Rx * Ry * Rz * Q  * T;
	}

	void GameObjectBasic::Update(AnimTime currentTime)
	{
		// Goal: update the world matrix
		this->privUpdate(currentTime);

		// update the bounding volume based on world matrix
		this->baseUpdateBoundingSphere();

		this->poGraphicsObject->SetWorld(*this->poWorld);
	}

	void GameObjectBasic::SetQuat(float qx, float qy, float qz, float qw)
	{
		this->poQuat->set(qx, qy, qz, qw);
	}

	void GameObjectBasic::SetScale(float sx, float sy, float sz)
	{
		this->poScale->set(sx, sy, sz);
	}

	void GameObjectBasic::SetTrans(float x, float y, float z)
	{
		this->poTrans->set(x, y, z);
	}

	void GameObjectBasic::SetScale(Vec3 &r)
	{
		*this->poScale = r;
	}

	void GameObjectBasic::SetQuat(Quat &r)
	{
		*this->poQuat = r;
	}

	void GameObjectBasic::SetTrans(Vec3 &r)
	{
		*this->poTrans = r;
	}

}

// --- End of File ---
