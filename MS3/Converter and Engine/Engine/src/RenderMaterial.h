//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef RENDER_MATERIAL_H
#define RENDER_MATERIAL_H

namespace Azul
{

	class RenderMaterial
	{
	protected:
		RenderMaterial() = default;
		RenderMaterial(const RenderMaterial &) = delete;
		RenderMaterial &operator = (const RenderMaterial &) = delete;
		virtual ~RenderMaterial() = default;

		virtual void SetState() = 0;
		virtual void SetDataGPU() = 0;
		virtual void Draw() = 0;
		virtual void RestoreState() = 0;
	};
}

#endif

// --- End of File ---
