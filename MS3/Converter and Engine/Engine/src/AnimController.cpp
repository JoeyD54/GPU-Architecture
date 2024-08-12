//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "AnimController.h"
#include "Anim.h"
#include "Mixer.h"

namespace Azul
{
	AnimController::AnimController(AnimTime delta, Anim *pAnim)
		: poAnim(pAnim),
		poTimerController(nullptr)
	{
		assert(this->poAnim);

		// TimerController
		AnimTime maxTime = poAnim->FindMaxTime();
		AnimTime minTime = AnimTime(AnimTime::Duration::ZERO);
		this->poTimerController = new TimerController(delta, minTime, maxTime);
		assert(this->poTimerController);
	}

	AnimController::~AnimController()
	{
		delete poAnim;
		delete poTimerController;
	}

	void AnimController::Update()
	{
		// advance time
		this->poTimerController->Update();

		// interpolate all bones
		this->poAnim->Animate(this->poTimerController->GetCurrTime());
	}

	void AnimController::Update(Mixer *pMixer)
	{
		// advance time
		this->poTimerController->Update();

		// interpolate all bones
		assert(pMixer);
		this->poAnim->Animate(this->poTimerController->GetCurrTime(), pMixer);
	}


	Anim *AnimController::GetAnim()
	{
		assert(this->poAnim);

		return this->poAnim;
	}
	void AnimController::SetAnim(Anim* _pAnim)
	{		
		this->poAnim = _pAnim;
		AnimTime maxTime = _pAnim->FindMaxTime();
		this->poTimerController->SetMaxTime(maxTime);
		this->poTimerController->SetCurrTime(AnimTime(AnimTime::Duration::ZERO));
	}
}

// --- End of File ---
