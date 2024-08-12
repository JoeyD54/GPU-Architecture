//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "Game.h"
#include "MathEngine.h"
#include "GameObjectAnimSkin.h"
#include "GraphicsObject.h"
#include "Mesh.h"
#include "Anim.h"
#include "AnimController.h"
#include "SSBO.h"
#include "ShaderMan.h"
#include "WorldCompute.h"
#include "Mixer.h"

namespace Azul
{
	GameObjectAnimSkin::GameObjectAnimSkin(GraphicsObject *_pGraphicsObject)
		: GameObjectAnim(_pGraphicsObject)
	{
		assert(_pGraphicsObject);

		this->poTrans = new Vec3(0.0f, 0.0f, 0.0f);
		this->poScale = new Vec3(1.0f, 1.0f, 1.0f);
		this->poQuat = new Quat(0.0f, 0.0f, 0.0f, 1.0f);

		assert(this->poTrans);
		assert(this->poScale);
		assert(this->poQuat);

		this->pAnimController = nullptr;
		this->pMixer = nullptr;
		this->pWorldCompute = nullptr;

		this->delta_x = 0.0f;
		this->delta_y = 0.0f;
		this->delta_z = 0.0f;

		this->cur_rot_x = 0.0f;
		this->cur_rot_y = 0.0f;
		this->cur_rot_z = 0.0f;
	}

	GameObjectAnimSkin::~GameObjectAnimSkin()
	{
		delete this->poTrans;
		delete this->poScale;
		delete this->poQuat;
	}

	void GameObjectAnimSkin::privUpdateWorld(AnimTime currentTime)
	{
		AZUL_UNUSED_VAR(currentTime);

		Quat Qy(Quat::Rot1::Y, MATH_PI2);
		Quat Qx(Quat::Rot1::X, MATH_PI2);
		Quat Qy2(Quat::Rot1::Y, MATH_PI);

		Quat Q = Qy2 * Qx * Qy;

		Mat4 T(Mat4::Trans::XYZ, *this->poTrans);
		Mat4 S(Mat4::Scale::XYZ, *this->poScale);

		cur_rot_x += delta_x;
		cur_rot_y += delta_y;
		cur_rot_z += delta_z;

		Mat4 Rx(Mat4::Rot1::X, cur_rot_x);
		Mat4 Ry(Mat4::Rot1::Y, cur_rot_y);
		Mat4 Rz(Mat4::Rot1::Z, cur_rot_z);

		// world matrix
		*this->poWorld = S * Rx * Ry * Rz * Q * T;
	}


	void GameObjectAnimSkin::Update(AnimTime currentTime)
	{
		AZUL_UNUSED_VAR(currentTime);

		this->privUpdateWorld(currentTime);

		this->poGraphicsObject->SetWorld(*this->poWorld);

		this->privComputeShaders();

	}

	void GameObjectAnimSkin::SetAnimController(AnimController* _pAnimcontroller)
	{
		this->pAnimController = _pAnimcontroller;
	}

	void GameObjectAnimSkin::SetMixer(Mixer* _pMixer)
	{
		this->pMixer = _pMixer;
	}

	void GameObjectAnimSkin::SetWorldCompute(WorldCompute* _pWorldCompute)
	{
		this->pWorldCompute = _pWorldCompute;
	}


	void GameObjectAnimSkin::privComputeShaders()
	{
		ShaderObject *pComputeShader = nullptr;
		//ShaderObject *pMouseComputeShader = nullptr;
		unsigned int count = 0;

		// ---------------------------
		// MIXER 1
		// ---------------------------
		pComputeShader = ShaderMan::Find(ShaderObject::Name::COMPUTE_MIXER);

		pComputeShader->SetActive();

		this->pMixer->KeyA.Bind(0);
		this->pMixer->KeyB.Bind(1);
		this->pMixer->Result.Bind(2);

		glUniform1f(pComputeShader->GetLocation("ts"), this->pMixer->tS);
		glUniform1i(pComputeShader->GetLocation("boneCount"), this->pMixer->numBones);

		// Dispatch
		count = (unsigned int)ceil((float)this->pMixer->numBones / 10.0f);
		pComputeShader->Dispatch(count, 1, 1);

		// Block Waiting for stages to complete
		glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT);

		// ---------------------------
		// World Matrix
		// ---------------------------

		// Lock and load the shader...
		pComputeShader = ShaderMan::Find(ShaderObject::Name::COMPUTE_WORLD);

		pComputeShader->SetActive();

		this->pWorldCompute->LocalBone.Bind(0);
		this->pWorldCompute->Hierarchy.Bind(1);
		this->pWorldCompute->WorldMat.Bind(2);
		this->pWorldCompute->InvBind.Bind(3);

		glUniform1i(pComputeShader->GetLocation("hierarchyDepth"), this->pWorldCompute->hierarchyDepth);
		glUniform1i(pComputeShader->GetLocation("boneCount"), this->pWorldCompute->boneCount);

		// Dispatch
		count = (unsigned int)ceil((float)this->pWorldCompute->boneCount / 10.0f);
		pComputeShader->Dispatch(count, 1, 1);

		// Block Waiting for stages to complete
		glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT);
	}

	void GameObjectAnimSkin::SetQuat(float qx, float qy, float qz, float qw)
	{
		this->poQuat->set(qx, qy, qz, qw);
	}

	void GameObjectAnimSkin::SetScale(float sx, float sy, float sz)
	{
		this->poScale->set(sx, sy, sz);
	}

	void GameObjectAnimSkin::SetTrans(float x, float y, float z)
	{
		this->poTrans->set(x, y, z);
	}

	void GameObjectAnimSkin::SetScale(Vec3 &r)
	{
		*this->poScale = r;
	}

	void GameObjectAnimSkin::SetQuat(Quat &r)
	{
		*this->poQuat = r;
	}

	void GameObjectAnimSkin::SetTrans(Vec3 &r)
	{
		*this->poTrans = r;
	}
}

// --- End of File ---
