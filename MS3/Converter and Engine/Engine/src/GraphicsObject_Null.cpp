//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "GraphicsObject_Null.h"

namespace Azul
{

	GraphicsObject_Null::GraphicsObject_Null(const Mesh *const _pMesh, const ShaderObject *const pShaderObj)
		: GraphicsObject(_pMesh, pShaderObj)
	{

	}

	GraphicsObject_Null::~GraphicsObject_Null()
	{

	}

	void GraphicsObject_Null::SetState()
	{

	}

	void GraphicsObject_Null::SetDataGPU()
	{

	}

	void GraphicsObject_Null::Draw()
	{

	}

	void GraphicsObject_Null::RestoreState()
	{

	}
}

// ---  End of File ---
