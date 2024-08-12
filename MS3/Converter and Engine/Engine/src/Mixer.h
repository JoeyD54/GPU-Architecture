//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef MIXER_H
#define MIXER_H

#include "AnimTimer.h"
#include "Bone.h"
#include "SSBO.h"

namespace Azul
{

	class Anim;

	class Mixer
	{
	public:
		Mixer(Anim *pAnim);

		Mixer() = delete;
		Mixer(const Mixer &) = delete;
		Mixer &operator = (const Mixer &) = delete;
		~Mixer() = default;


		static void Blend(	Bone *pResult,
							const Bone *pA,
							const Bone *pB,
							const float tS,
							const int numBones);
	public:
		SSBO   KeyA;
		SSBO   KeyB;
		float  tS;
		SSBO   Result;
		int    numBones;
	};
}

#endif

// --- End of File ---
