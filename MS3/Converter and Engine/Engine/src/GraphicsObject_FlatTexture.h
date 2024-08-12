//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef GRAPHICS_OBJECT_FLAT_TEXTURE_H
#define GRAPHICS_OBJECT_FLAT_TEXTURE_H

#include "GraphicsObject.h"
#include "TextureMan.h"

namespace Azul
{

	class GraphicsObject_FlatTexture :public GraphicsObject
	{
	public:
		GraphicsObject_FlatTexture(const Mesh *const _pMesh, const ShaderObject *const pShaderObj, Texture::Name _name);

		GraphicsObject_FlatTexture() = delete;
		GraphicsObject_FlatTexture(const GraphicsObject_FlatTexture &) = delete;
		GraphicsObject_FlatTexture &operator = (const GraphicsObject_FlatTexture &) = delete;
		virtual ~GraphicsObject_FlatTexture();

		// Rendermaterial contract
		virtual void SetState() override;
		virtual void SetDataGPU() override;
		virtual void Draw() override;
		virtual void RestoreState() override;

		// data:  place uniform instancing here

		Texture::Name textName;

	};
}

#endif

//--- End of File -------------------------------------------------------------
