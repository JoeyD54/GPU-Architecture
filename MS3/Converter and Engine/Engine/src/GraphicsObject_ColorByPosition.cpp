//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "MathEngine.h"
#include "Mesh.h"
#include "GraphicsObject_ColorByPosition.h"
#include "Camera.h"
#include "CameraMan.h"

namespace Azul
{

	GraphicsObject_ColorByPosition::GraphicsObject_ColorByPosition(const Mesh *const _pMesh, const ShaderObject *const pShaderObj)
		: GraphicsObject(_pMesh, pShaderObj)
	{
		assert(pMesh);
		assert(pShaderObj);
		assert(poWorld);
	}

	GraphicsObject_ColorByPosition::~GraphicsObject_ColorByPosition()
	{

	}

	void GraphicsObject_ColorByPosition::SetState()
	{
		glEnable(GL_CULL_FACE);
		glFrontFace(Mesh::POLY_WINDING);
	}

	void GraphicsObject_ColorByPosition::SetDataGPU()
	{
		// use this shader
		this->pShaderObj->SetActive();

		// set the vao
		glBindVertexArray(this->GetMesh()->vao);

		Camera3D *pCam = CameraMan::GetCurrent3D();

		Mat4 world = this->GetWorld();
		Mat4 view = pCam->getViewMatrix();
		Mat4 proj = pCam->getProjMatrix();

		glUniformMatrix4fv(this->pShaderObj->GetLocation("proj_matrix"), 1, GL_FALSE, (float *)&proj);
		glUniformMatrix4fv(this->pShaderObj->GetLocation("view_matrix"), 1, GL_FALSE, (float *)&view);
		glUniformMatrix4fv(this->pShaderObj->GetLocation("world_matrix"), 1, GL_FALSE, (float *)&world);

	}

	void GraphicsObject_ColorByPosition::Draw()
	{
		//The starting point of the IBO index buffer object
		glDrawElements(GL_TRIANGLES, 3 * this->GetMesh()->numTris, GL_UNSIGNED_INT, 0);
	}

	void GraphicsObject_ColorByPosition::RestoreState()
	{
		glEnable(GL_CULL_FACE);
		glFrontFace(Mesh::POLY_WINDING);
	}

}

// --- End of File ---
