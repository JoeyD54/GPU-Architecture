//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "MeshNull.h"

namespace Azul
{
	MeshNull::MeshNull(const char *const MeshFileName)
		: Mesh()
	{
		AZUL_UNUSED_VAR(MeshFileName);
	}

	MeshNull::MeshNull()
		: Mesh()
	{
	}

	MeshNull::~MeshNull()
	{
		// remove anything dynamic here
	}

	void MeshNull::privCreateVAO(const char *const MeshFileName)
	{
		AZUL_UNUSED_VAR(MeshFileName);
	}
}

// --- End of File ---
