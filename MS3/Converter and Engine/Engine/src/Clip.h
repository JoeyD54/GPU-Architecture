//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef CLIP_H
#define CLIP_H

#include "AnimTime.h"
#include "Bone.h"
#include "ClipData.h"
#include "SSBO.h"
#include "Mixer.h"

namespace Azul
{
	class Clip
	{
	public:

		struct FrameBucket
		{
			~FrameBucket()
			{
				delete[] poBone;
			}

			FrameBucket  *nextBucket;
			FrameBucket  *prevBucket;
			AnimTime      KeyTime;
			Bone         *poBone;
			SSBO          sbo;
		};

	public:
		Clip(const char * pName);

		Clip() = delete;
		Clip(const Clip &) = delete;
		Clip &operator = (const Clip &) = delete;
		~Clip();

		AnimTime GetTotalTime();
		
		void AnimateBones(AnimTime tCurr, Bone *pResult);

		void AnimateBones(AnimTime tCurr, Mixer *pMixer);

		int GetNumBones();

	private:

		void privSetAnimationData(ClipData &ClipA);
		FrameBucket *privCreateFrameBucket(ClipData &ClipA, unsigned int FrameIndex);

		AnimTime privFindMaxTime();
		int  privFindNumFrames();

	private:
		int          numBones;
		int          numFrames;
		AnimTime     TotalTime;
		FrameBucket *poHead;
	};
}

#endif

//--- End of File ---
