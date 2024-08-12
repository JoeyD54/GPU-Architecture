//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------
#include "GraphicsObject_TextureLight.h"
#include "Mesh.h"
#include "TextureMan.h"
#include "Camera.h"
#include "ShaderObject.h"
#include "CameraMan.h"

namespace Azul
{

	GraphicsObject_TextureLight::GraphicsObject_TextureLight(Mesh *_pMesh, ShaderObject *_pShaderObj,
		Texture::Name _name, Vec4 &LightColor, Vec3 &LightPos)
		: GraphicsObject(_pMesh, _pShaderObj),
		textName(_name)
	{
		this->poLightColor = new Vec4(LightColor);
		this->poLightPos = new Vec3(LightPos);
		assert(poLightColor);
		assert(poLightPos);
	}

	GraphicsObject_TextureLight::~GraphicsObject_TextureLight()
	{
		delete this->poLightColor;
		delete this->poLightPos;
	}

	void GraphicsObject_TextureLight::SetState()
	{
		glActiveTexture(GL_TEXTURE0);

		// Bind the texture
		GLuint textureID = TextureMan::FindID(this->textName);
		glBindTexture(GL_TEXTURE_2D, textureID);

		glEnable(GL_CULL_FACE);
		glFrontFace(Mesh::POLY_WINDING);
	}

	void GraphicsObject_TextureLight::SetDataGPU()
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

		Vec3 light = *this->poLightPos;
		Vec4 color = *this->poLightColor;
		glUniform3fv(this->pShaderObj->GetLocation("vLightPos"), 1, (float *)&light);
		glUniform4fv(this->pShaderObj->GetLocation("vColor"), 1, (float *)&color);
	}

	void GraphicsObject_TextureLight::Draw()
	{
		//The starting point of the IBO index buffer object
		glDrawElements(GL_TRIANGLES, 3 * this->GetMesh()->numTris, GL_UNSIGNED_INT, 0);
	}

	void GraphicsObject_TextureLight::RestoreState()
	{
		// undo the states you corrupted
		glEnable(GL_CULL_FACE);
		glFrontFace(Mesh::POLY_WINDING);
	}

}

// ---  End of File ---