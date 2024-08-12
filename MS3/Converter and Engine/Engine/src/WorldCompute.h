//----------------------------------------------------------------------------
// Copyright 2023, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef WORLD_COMPUTE_H
#define WORLD_COMPUTE_H

#include "Mixer.h"
#include "SSBO.h"

namespace Azul
{

	class WorldCompute
	{
	public:
		WorldCompute(Mixer *pMixer, const char *pHierarchyName, const char *pInvBindName);

		WorldCompute() = delete;
		WorldCompute(const WorldCompute &) = delete;
		WorldCompute &operator = (const WorldCompute &) = delete;
		~WorldCompute() = default;

	public:
		SSBO   LocalBone;
		SSBO   Hierarchy;
		SSBO   WorldMat;
		SSBO   InvBind;
		int    boneCount;
		int    hierarchyDepth;
	};
}

#endif

// --- End of File ---
