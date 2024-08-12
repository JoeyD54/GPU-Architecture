//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "Anim.h"
#include "Clip.h"

#include "ShaderMan.h"
#include "GameObjectMan.h"
#include "MeshNodeMan.h"

#include "MathEngine.h"
#include "MathApp.h"
#include "Mixer.h"

#include "GameObjectAnimSkin.h"
#include "GameObjectBasic.h"
#include "GraphicsObject_SkinTexture.h"
#include "GraphicsObject_Null.h"


namespace Azul
{
	extern GameObject *pPivotGameObject;

	Anim::Anim()
		: poClip(nullptr),
		numBones(0),
		poBoneResult(nullptr),
		sboResult()
	{
		animName = Anim::Name::EMPTY;
		//Doing this in set instead now.
		this->numBones = 0;
		this->poBoneResult = nullptr;
		// Transfer the sbo to GPU
		this->sboResult.Set(0, 0, nullptr);
	}

	Anim::~Anim()
	{
		delete[] this->poBoneResult;
		delete   this->poClip;
	}

	SSBO &Anim::GetResultSBO()
	{
		return this->sboResult;
	}

	int Anim::GetNumBones()
	{
		return this->numBones;
	}

	AnimTime Anim::FindMaxTime()
	{
		assert(poClip);
		return this->poClip->GetTotalTime();
	}

	void Anim::Animate(AnimTime tCurr)
	{
		this->poClip->AnimateBones(tCurr, this->poBoneResult);
	}

	void Anim::Animate(AnimTime tCurr, Mixer *pMixer)
	{
		assert(pMixer);
		this->poClip->AnimateBones(tCurr, pMixer);
	}

	void Anim::Set(Anim::Name _name, Clip* pClip)
	{
		this->animName = _name;
		this->poClip = pClip;

		assert(this->poClip);

		this->numBones = this->poClip->GetNumBones();

		this->poBoneResult = new Bone[(unsigned int)poClip->GetNumBones()]();
		assert(this->poBoneResult);

		// Transfer the sbo to GPU
		this->sboResult.Set((unsigned int)poClip->GetNumBones(), sizeof(Bone), this->poBoneResult);

	}


	bool Anim::Compare(DLink* pTarget)
	{
		// This is used in ManBase.Find() 
		assert(pTarget != nullptr);

		Anim* pDataB = (Anim*)pTarget;

		bool status = false;

		if (this->animName == pDataB->animName)
		{
			status = true;
		}

		return status;
	}

	void Anim::Dump()
	{
		Trace::out("      Anim(%p)\n", this);

		// Data:
		//Trace::out("      Name: %s \n", StringMe(this->name));
		//Trace::out("         x: %d \n", this->x);

		DLink::Dump();
	}

	void Anim::Wash()
	{
		this->animName = Anim::Name::EMPTY;
		this->poClip = nullptr;
	}

}

//--- End of File ----