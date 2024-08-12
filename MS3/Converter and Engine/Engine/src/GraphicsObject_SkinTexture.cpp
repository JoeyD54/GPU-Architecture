//----------------------------------------------------------------------------
// Copyright 2023, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "GraphicsObject_SkinTexture.h"
#include "TextureMan.h"
#include "Mesh.h"
#include "Camera.h"
#include "CameraMan.h"
#include "Anim.h"
#include "WorldCompute.h"

namespace Azul
{

	//extern WorldCompute *pWorldComputeA;

	GraphicsObject_SkinTexture::GraphicsObject_SkinTexture(const Mesh *const _pMesh, const ShaderObject *const _pShaderObj, Texture::Name _name)
		: GraphicsObject(_pMesh, _pShaderObj), textName(_name)
	{
		// check the base class
		assert(this->pMesh);
		assert(this->pShaderObj);
		assert(this->poWorld);

		this->pWorldCompute = nullptr;
		this->pBoneWorld = nullptr;
	}

	void GraphicsObject_SkinTexture::SetBoneWorld(Mat4 *_pBoneWorld)
	{
		assert(_pBoneWorld);
		this->pBoneWorld = _pBoneWorld;
	}

	void GraphicsObject_SkinTexture::SetWorldCompute(WorldCompute* _pWorldCompute)
	{
		assert(_pWorldCompute);
		this->pWorldCompute = _pWorldCompute;
	}

	void GraphicsObject_SkinTexture::SetState()
	{
		glActiveTexture(GL_TEXTURE0);

		// Bind the texture
		GLuint textureID = TextureMan::FindID(this->textName);
		glBindTexture(GL_TEXTURE_2D, textureID);

		glEnable(GL_CULL_FACE);
		glFrontFace(GL_CCW);
	}

	void GraphicsObject_SkinTexture::SetDataGPU()
	{
		// use this shader
		this->pShaderObj->SetActive();

		// set the vao
		glBindVertexArray(this->GetMesh()->vao);

		Camera *pCam = CameraMan::GetCurrent3D();

		//Matrix world = this->GetWorld();
		Mat4 view = pCam->getViewMatrix();
		Mat4 proj = pCam->getProjMatrix();

		// World Matrix array 
		this->pWorldCompute->WorldMat.Bind(0);

		// Send the uniforms
		
		// Pivot is now the world
		glUniformMatrix4fv(this->pShaderObj->GetLocation("pivotWorld"), 1, GL_FALSE, (float *)this->poWorld);

		glUniformMatrix4fv(this->pShaderObj->GetLocation("proj_matrix"), 1, GL_FALSE, (float *)&proj);
		glUniformMatrix4fv(this->pShaderObj->GetLocation("view_matrix"), 1, GL_FALSE, (float *)&view);
	}

	void GraphicsObject_SkinTexture::Draw()
	{
		//The starting point of the IBO index buffer object
		glDrawElements(GL_TRIANGLES, 3 * this->GetMesh()->numTris, GL_UNSIGNED_INT, 0);
	}

	void GraphicsObject_SkinTexture::RestoreState()
	{
		glEnable(GL_CULL_FACE);
		glFrontFace(GL_CCW);
	}

}

//--- End of File -------------------------------------------------------------

