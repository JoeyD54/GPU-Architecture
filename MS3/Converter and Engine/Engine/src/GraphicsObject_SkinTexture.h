//----------------------------------------------------------------------------
// Copyright 2023, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef GRAPHICS_OBJECT_SKIN_TEXTURE_H
#define GRAPHICS_OBJECT_SKIN_TEXTURE_H

#include "GraphicsObject.h"
#include "TextureMan.h"
#include "WorldCompute.h"

namespace Azul
{

	class GraphicsObject_SkinTexture : public GraphicsObject
	{
	public:
		GraphicsObject_SkinTexture(const Mesh *const _pMesh,
			const ShaderObject *const pShaderObj,
			Texture::Name _name);

		GraphicsObject_SkinTexture() = delete;
		GraphicsObject_SkinTexture(const GraphicsObject_SkinTexture &) = delete;
		GraphicsObject_SkinTexture &operator= (const GraphicsObject_SkinTexture &) = delete;
		virtual ~GraphicsObject_SkinTexture() = default;

		void SetBoneWorld(Mat4 *pBoneWorld);
		void SetWorldCompute(WorldCompute* _pWorldCompute);

		// Rendermaterial contract
		virtual void SetState() override;
		virtual void SetDataGPU() override;
		virtual void Draw() override;
		virtual void RestoreState() override;

		// -------------------------
		// 	   Data
		// -------------------------

		// HACK
		WorldCompute* pWorldCompute;
		Mat4 *pBoneWorld;
		Texture::Name textName;

	};
}

#endif

//--- End of File -------------------------------------------------------------
