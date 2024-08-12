//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "Mesh.h"
#include "StringThis.h"

namespace Azul
{
	Mesh::Mesh()
		: numVerts(0),
		numTris(0),
		vao(0),
		vbo_verts(0),
		vbo_norms(0),
		vbo_uv(0),
		vbo_color(0),
		vbo_index(0),	
		vbo_weight(0),
		vbo_joint(0),
		poInverseBind(nullptr),
		numInverseBind(0),
		poRefSphere(new Sphere())
	{
	}

	Mesh::~Mesh()
	{
		delete this->poRefSphere;
		delete[] this->poInverseBind;
	}

	void Mesh::Wash()
	{
		this->numVerts = 0;
		this->numTris = 0;
		vao = 0;
		vbo_verts = 0;
		vbo_norms = 0;
		vbo_uv = 0;
		vbo_index = 0;
		vbo_color = 0;
		vbo_weight = 0;
		vbo_joint = 0;
	}

	bool Mesh::Compare(DLink *pTarget)
	{
		// This is used in ManBase.Find() 
		assert(pTarget != nullptr);

		Mesh *pDataB = (Mesh *)pTarget;

		bool status = false;

		if(this->name == pDataB->name)
		{
			status = true;
		}

		return status;
	}

	void Mesh::SetName(Mesh::Name _name)
	{
		this->name = _name;
	}

	char *Mesh::GetName()
	{
		// todo - Hack understand why is this needed for print and fix...
		static char pTmp[128];
		strcpy_s(pTmp, 128, StringMe(this->name));
		return pTmp;
	}

}

// --- End of File ---
