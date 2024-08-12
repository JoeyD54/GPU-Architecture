//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "Mesh.h"
#include "GraphicsObject_Wireframe.h"
#include "ShaderObject.h"
#include "Camera.h"
#include "CameraMan.h"

namespace Azul
{

	GraphicsObject_Wireframe::GraphicsObject_Wireframe(const Mesh *const _pMesh, const ShaderObject *const _pShaderObj)
		: GraphicsObject(_pMesh, _pShaderObj)
	{
		assert(pMesh);
		assert(pShaderObj);
		assert(poWorld);
	}

	void GraphicsObject_Wireframe::SetState()
	{
		glEnable(GL_CULL_FACE);
		glFrontFace(Mesh::POLY_WINDING);
	}

	void GraphicsObject_Wireframe::SetDataGPU()
	{
		// use this shader
		this->pShaderObj->SetActive();

		// Draw Me: -----------------------------------------

		// set the vao
		glBindVertexArray(this->GetMesh()->vao);

		// Set state
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glDisable(GL_CULL_FACE);

		Camera3D *pCam = CameraMan::GetCurrent3D();

		Mat4 world = this->GetWorld();
		Mat4 view = pCam->getViewMatrix();
		Mat4 proj = pCam->getProjMatrix();

		Vec4 color(0,0,0.5f, 1.0f);

		glUniform4fv(this->pShaderObj->GetLocation("wire_color"), 1, (float *)&color);
		glUniformMatrix4fv(this->pShaderObj->GetLocation("proj_matrix"), 1, GL_FALSE, (float *)&proj);
		glUniformMatrix4fv(this->pShaderObj->GetLocation("view_matrix"), 1, GL_FALSE, (float *)&view);
		glUniformMatrix4fv(this->pShaderObj->GetLocation("world_matrix"), 1, GL_FALSE, (float *)&world);
	}

	void GraphicsObject_Wireframe::Draw()
	{
		//The starting point of the IBO index buffer object
		glDrawElements(GL_TRIANGLES, 3 * this->GetMesh()->numTris, GL_UNSIGNED_INT, 0);
	}

	void GraphicsObject_Wireframe::RestoreState()
	{
		// Restore state
		glEnable(GL_CULL_FACE);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glFrontFace(Mesh::POLY_WINDING);
	}
}

// ---  End of File ---
