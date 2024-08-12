//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "GraphicsObject.h"
#include "MathEngine.h"
#include "Mesh.h"

namespace Azul
{

	GraphicsObject::GraphicsObject(const Mesh *const _pMesh, const ShaderObject *const _pShaderObj)
		: pMesh(_pMesh),
		pShaderObj(_pShaderObj)
	{
		this->poWorld = new Mat4(Mat4::Special::Identity);
		assert(this->poWorld);
		assert(_pMesh);
		assert(_pShaderObj);
		this->poCurrSphere = new Sphere();
		assert(this->poCurrSphere);
	}

	GraphicsObject::~GraphicsObject()
	{
		delete this->poWorld;
		delete this->poCurrSphere;
	}

	void GraphicsObject::Render()
	{
		this->SetState();
		this->SetDataGPU();
		this->Draw();
		this->RestoreState();
	}

	const Mesh *GraphicsObject::GetMesh() const
	{
		return this->pMesh;
	}

	Mat4 &GraphicsObject::GetWorld()
	{
		return *this->poWorld;
	}

	void GraphicsObject::SetWorld(Mat4 &_world)
	{
		*this->poWorld = _world;
	}
}

// --- End of File ---
