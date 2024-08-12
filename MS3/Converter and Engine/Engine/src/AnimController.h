//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef ANIM_CONTROLLER_H
#define ANIM_CONTROLLER_H

#include "TimerController.h"
#include "GameObjectAnim.h"
#include "Anim.h"
#include "Mixer.h"

namespace Azul
{
	class AnimController
	{
	public:
		AnimController(AnimTime delta, Anim *pAnim);
		AnimController(const AnimController &) = delete;
		AnimController &operator = (const AnimController &) = delete;
		~AnimController();

		void Update();
		void Update(Mixer *pMixer);

		Anim *GetAnim();
		void SetAnim(Anim* _pAnim);
		//void SwitchAnim(Anim* _pAnim, )

	private:
		Anim *poAnim;
		TimerController *poTimerController;

	};
}

#endif

// --- End of File ---
