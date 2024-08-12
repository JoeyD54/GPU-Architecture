//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "sb7.h"
#include "MathEngine.h"
#include "Camera2D.h"

namespace Azul
{
	Camera2D::Camera2D()
		: Camera(Camera::Type::ORTHOGRAPHIC_2D)
	{

	}

	Camera2D::~Camera2D()
	{

	}

	// Update everything (make sure it's consistent)
	void Camera2D::updateCamera(void)
	{
		// Use this if you need a Frustum culling for 2D
		//     its the same as the 3D methods
		// Do not delete:
		//    this->privCalcFrustumVerts();
		//    this->privCalcFrustumCollisionNormals();

		// update the projection matrix
		this->privUpdateProjectionMatrix();

		// update the view matrix
		this->proUpdateViewMatrix();
	}

	// The projection matrix (note it's invertable)
	void Camera2D::privUpdateProjectionMatrix(void)
	{
		assert(this->camType == Camera::Type::ORTHOGRAPHIC_2D);

		this->projMatrix[m0] = 2.0f / (xMax - xMin);
		this->projMatrix[m1] = 0.0f;
		this->projMatrix[m2] = 0.0f;
		this->projMatrix[m3] = 0.0f;

		this->projMatrix[m4] = 0.0f;
		this->projMatrix[m5] = 2.0f / (yMax - yMin);
		this->projMatrix[m6] = 0.0f;
		this->projMatrix[m7] = 0.0f;

		this->projMatrix[m8] = 0.0f;
		this->projMatrix[m9] = 0.0f;
		this->projMatrix[m10] = -2.0f / (zMax - zMin);
		this->projMatrix[m11] = 0.0f;

		this->projMatrix[m12] = 0;
		this->projMatrix[m13] = 0;
		this->projMatrix[m14] = -(zMax + zMin) / (zMax - zMin);
		this->projMatrix[m15] = 1.0f;
	};

	void Camera2D::setOrthographic(const float _xMin, const float _xMax, const float _yMin, const float _yMax, const float _zMin, const float _zMax)
	{
		assert(this->camType == Camera::Type::ORTHOGRAPHIC_2D);

		this->xMin = _xMin;
		this->yMin = _yMin;
		this->zMin = _zMin;

		this->xMax = _xMax;
		this->yMax = _yMax;
		this->zMax = _zMax;

		// Use this if you need a Frustum culling for 2D
		// Do not delete:
		//    this->near_height = this->yMax - this->yMin;
		//    this->far_height = this->yMax - this->yMin;
		//    this->far_width = this->xMax - this->xMin;
		//    this->near_width = this->xMax - this->xMin;
		//    this->nearDist = this->zMin;
		//    this->farDist = this->zMax;
	};

}

// --- End of File ---
