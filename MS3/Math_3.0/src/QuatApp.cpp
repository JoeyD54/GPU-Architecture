//-----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

#include "MathEngine.h"
#include "MathApp.h"

//----------------------------------------------------------------------------- 
// Mutates result to be a slerp between the source and target by the
// specified factor.
// For a factor of 0.0, result == source.
// For a factor of 1.0, result == target.
//----------------------------------------------------------------------------- 

namespace Azul
{
	void QuatApp::Slerp(Quat& result, const Quat& source, const Quat& target, const float slerpFactor)
	{
		Quat src = source;
		Quat tgt = target;

		float dot = src.dot(tgt);
		
		if (dot < 0.0f)
		{
			dot = -dot;
			tgt = -tgt;
		}
		else if (dot == 1.0f)
		{
			result = tgt;
			return;
		}

		float angle = acosf(dot);

		Quat srcSection = src * (sinf((1.0f - slerpFactor) * angle) / sinf(angle));
		Quat tgtSection = tgt * (sinf(slerpFactor * angle) / sinf(angle));

		result = (srcSection + tgtSection);
	}

	void QuatApp::SlerpArray(Quat* result, const Quat* source, const Quat* target, const float slerpFactor, const int numQuats)
	{
		for (int i = 0; i < numQuats; i++)
		{
			Slerp(result[i], source[i], target[i], slerpFactor);
		}
	}
}

// ---  End of File ---------------
