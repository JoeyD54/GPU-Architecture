//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef ANIM_H
#define ANIM_H

#include "AnimTimer.h"
#include "MathEngine.h"
#include "Clip.h"
#include "SSBO.h"
#include "DLink.h"

namespace Azul
{
	class Anim : public DLink
	{
	public:

		enum Name
		{
			MOUSE_WALK,
			MOUSE_RUN,
			MOUSE_JUMP,
			MOUSE_SHUFFLE,
			MOUSE_GANGNAM,
			MOUSE_HAPPY_WALK,
			MOUSE_HIP_HOP,
			MOUSE_NORTH_SOUL,
			MOUSE_RUMBA,
			CHICKEN_WALK,
			CHICKEN_RUN,
			CHICKEN_SHOT_UP,
			CHICKEN_SIDE_STEP_R,
			EMPTY
		};

		Anim();
		Anim(const Anim &) = delete;
		Anim &operator = (const Anim &) = delete;
		~Anim();

		void Animate(AnimTime tCurr);
		void Animate(AnimTime tCurr, Mixer *pMixer);
		void Set(Anim::Name _name, Clip* pClip);

		AnimTime FindMaxTime();

		SSBO &GetResultSBO();
		int GetNumBones();

		virtual bool Compare(DLink* pTarget) override;
		virtual void Dump() override;
		virtual void Wash() override;

	private:
		

	public:
		Anim::Name		animName;
		Clip            *poClip;
		int              numBones;
		Bone            *poBoneResult;
		SSBO             sboResult;

	};

}
#endif

// --- End of File ---