//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef CAMERA_2D_H
#define CAMERA_2D_H

#include "MathEngine.h"
#include "Camera.h"

namespace Azul
{
	class Camera2D final : public Camera
	{
	
	public:
		Camera2D();
		Camera2D(const Camera &) = delete;
		Camera2D &operator = (const Camera2D &) = delete;
		virtual ~Camera2D();

		virtual void updateCamera() override;
		virtual void privUpdateProjectionMatrix() override;

		void setOrthographic(const float _xMin, const float _xMax, const float _yMin, const float _yMax, const float _zMin, const float _zMax);

	private:

		// Ortho  
		float	xMin;
		float	yMin;
		float	zMin;
		float	xMax;
		float	yMax;
		float	zMax;

	};

}

#endif

// --- End of File ---
