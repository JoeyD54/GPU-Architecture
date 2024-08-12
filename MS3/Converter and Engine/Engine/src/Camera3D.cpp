//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "sb7.h"
#include "MathEngine.h"
#include "Camera3D.h"

namespace Azul
{
	Camera3D::Camera3D()
		: Camera(Camera::Type::PERSPECTIVE_3D)
	{
		// test alignment - should be 16-byte aligned
		assert(((unsigned int)(&this->projMatrix) & 0xF) == 0x0);
	}

	Camera3D::~Camera3D()
	{

	}

	// Update everything (make sure it's consistent)
	void Camera3D::updateCamera(void)
	{
		// First find the near height/width, far height/width
		this->privCalcPlaneHeightWidth();

		// Find the frustum physical verts
		this->privCalcFrustumVerts();

		// find the frustum collision normals
		this->privCalcFrustumCollisionNormals();

		// update the projection matrix
		this->privUpdateProjectionMatrix();

		// update the view matrix
		this->proUpdateViewMatrix();
	}


	void Camera3D::setPerspective(const float Fovy, const float Aspect, const float NearDist, const float FarDist)
	{
		this->aspectRatio = Aspect;
		this->fovy = Fovy;
		this->nearDist = NearDist;
		this->farDist = FarDist;
	}

	// The projection matrix (note it's invertable)
	void Camera3D::privUpdateProjectionMatrix(void)
	{
		assert(this->camType == Camera::Type::PERSPECTIVE_3D);

		this->projMatrix[m0] = 2.0f * this->nearDist / this->near_width;
		this->projMatrix[m1] = 0.0f;
		this->projMatrix[m2] = 0.0f;
		this->projMatrix[m3] = 0.0f;

		this->projMatrix[m4] = 0.0f;
		this->projMatrix[m5] = 2.0f * this->nearDist / this->near_height;
		this->projMatrix[m6] = 0.0f;
		this->projMatrix[m7] = 0.0f;

		this->projMatrix[m8] = 0.0f;
		this->projMatrix[m9] = 0.0f;
		this->projMatrix[m10] = (this->farDist + this->nearDist) / (this->nearDist - this->farDist);
		this->projMatrix[m11] = -1.0f;

		this->projMatrix[m12] = 0.0f;
		this->projMatrix[m13] = 0.0f;
		this->projMatrix[m14] = (2.0f * this->farDist * this->nearDist) / (this->nearDist - this->farDist);
		this->projMatrix[m15] = 0.0f;

	};

	void Camera3D::privCalcFrustumVerts(void)
	{
		// Top Left corner and so forth.  In this form to see the pattern
		// Might be confusing (remember the picture) vDir goes from screen into your EYE
		// so distance from the eye is "negative" vDir
		this->nearTopLeft = this->vPos - this->vDir * this->nearDist + this->vUp * this->near_height * 0.5f - this->vRight * this->near_width * 0.5f;
		this->nearTopRight = this->vPos - this->vDir * this->nearDist + this->vUp * this->near_height * 0.5f + this->vRight * this->near_width * 0.5f;
		this->nearBottomLeft = this->vPos - this->vDir * this->nearDist - this->vUp * this->near_height * 0.5f - this->vRight * this->near_width * 0.5f;
		this->nearBottomRight = this->vPos - this->vDir * this->nearDist - this->vUp * this->near_height * 0.5f + this->vRight * this->near_width * 0.5f;
		this->farTopLeft = this->vPos - this->vDir * this->farDist + this->vUp * this->far_height * 0.5f - this->vRight * this->far_width * 0.5f;
		this->farTopRight = this->vPos - this->vDir * this->farDist + this->vUp * this->far_height * 0.5f + this->vRight * this->far_width * 0.5f;
		this->farBottomLeft = this->vPos - this->vDir * this->farDist - this->vUp * this->far_height * 0.5f - this->vRight * this->far_width * 0.5f;
		this->farBottomRight = this->vPos - this->vDir * this->farDist - this->vUp * this->far_height * 0.5f + this->vRight * this->far_width * 0.5f;
	};

	void Camera3D::privCalcFrustumCollisionNormals(void)
	{
		// Normals of the frustum around nearTopLeft
		Vec3 A = this->nearBottomLeft - this->nearTopLeft;
		Vec3 B = this->nearTopRight - this->nearTopLeft;
		Vec3 C = this->farTopLeft - this->nearTopLeft;

		this->frontNorm = A.cross(B);
		this->frontNorm.norm();

		this->leftNorm = C.cross(A);
		this->leftNorm.norm();

		this->topNorm = B.cross(C);
		this->topNorm.norm();

		// Normals of the frustum around farBottomRight
		A = this->farBottomLeft - this->farBottomRight;
		B = this->farTopRight - this->farBottomRight;
		C = this->nearBottomRight - this->farBottomRight;

		this->backNorm = A.cross(B);
		this->backNorm.norm();

		this->rightNorm = B.cross(C);
		this->rightNorm.norm();

		this->bottomNorm = C.cross(A);
		this->bottomNorm.norm();
	};

	// Goal, calculate the near height / width, same for far plane 
	void Camera3D::privCalcPlaneHeightWidth(void)
	{

		this->near_height = 2.0f * tanf((this->fovy * MATH_PI / 180.0f) * .5f) * this->nearDist;
		this->near_width = this->near_height * this->aspectRatio;

		this->far_height = 2.0f * tanf((this->fovy * MATH_PI / 180.0f) * .5f) * this->farDist;
		this->far_width = this->far_height * this->aspectRatio;

	};

	void Camera3D::getNearDist(float &Value) const
	{
		Value = this->nearDist;
	}

	void Camera3D::setNearDist(const float Value)
	{
		this->nearDist = Value;
	}

	void Camera3D::getFieldOfView(float &Value) const
	{
		Value = this->fovy;
	};

	void Camera3D::setFieldOfView(const float Value)
	{
		this->fovy = Value;
	};

	void Camera3D::getNearTopLeft(Vec3 &vOut) const
	{
		vOut = this->nearTopLeft;
	}
	void Camera3D::getNearTopRight(Vec3 &vOut) const
	{
		vOut = this->nearTopRight;
	}
	void Camera3D::getNearBottomLeft(Vec3 &vOut)const
	{
		vOut = this->nearBottomLeft;
	}
	void Camera3D::getNearBottomRight(Vec3 &vOut) const
	{
		vOut = this->nearBottomRight;
	}
	void Camera3D::getFarTopLeft(Vec3 &vOut) const
	{
		vOut = this->farTopLeft;
	}
	void Camera3D::getFarTopRight(Vec3 &vOut) const
	{
		vOut = this->farTopRight;
	}
	void Camera3D::getFarBottomLeft(Vec3 &vOut) const
	{
		vOut = this->farBottomLeft;
	}
	void Camera3D::getFarBottomRight(Vec3 &vOut)const
	{
		vOut = this->farBottomRight;
	}


	Camera::CullResult Camera3D::CullTest(const Sphere &Sphere)
	{
		CullResult result = Camera::CullResult::CULL_INSIDE;

		// first test
		Vec3 A = Sphere.cntr - this->nearTopLeft;

		if((A.dot(this->topNorm) > Sphere.rad) ||
			(A.dot(this->leftNorm) > Sphere.rad) ||
			(A.dot(this->frontNorm) > Sphere.rad))
		{
			result = Camera::CullResult::CULL_OUTSIDE;
		}
		else
		{
			Vec3 B = Sphere.cntr - this->farBottomRight;
			if((B.dot(this->backNorm) > Sphere.rad) ||
				(B.dot(this->rightNorm) > Sphere.rad) ||
				(B.dot(this->bottomNorm) > Sphere.rad))
			{
				result = Camera::CullResult::CULL_OUTSIDE;
			}
		}

		return result;
	}
}

// --- End of File ---
