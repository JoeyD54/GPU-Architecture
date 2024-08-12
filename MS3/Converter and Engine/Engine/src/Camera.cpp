//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "sb7.h"
#include "MathEngine.h"
#include "Camera.h"

namespace Azul
{

	Camera::Camera(Camera::Type _camType)
	{
		//out("Camera(): ---------\n");
		this->name = Camera::Name::NOT_INITIALIZED;
		this->camType = _camType;
	}

	Camera::~Camera()
	{

	}

	void Camera::GetHelper(Vec3 &up, Vec3 &tar, Vec3 &pos,
		Vec3 &upNorm, Vec3 &forwardNorm, Vec3 &pRightNorm)
	{
		this->getPos(pos);
		this->getLookAt(tar);
		this->getUp(upNorm);
		up = pos + upNorm;

		forwardNorm = tar - pos;
		forwardNorm.norm();

		this->getRight(pRightNorm);
	}

	void Camera::SetHelper(Vec3 &up_pt, Vec3 &tar_pt, Vec3 &pos_pt)
	{
		Vec3 upVect = up_pt - pos_pt;
		this->setOrientAndPosition(upVect, tar_pt, pos_pt);
	}

	Camera::Name Camera::getName() const
	{
		return this->name;
	}

	void Camera::setName(Camera::Name inName)
	{
		this->name = inName;
	}

	int Camera::getScreenWidth() const
	{
		return this->viewport_width;
	}

	int Camera::getScreenHeight() const
	{
		return this->viewport_height;
	}

	// Just a pass through to setup the view port screen sub window
	void Camera::setViewport(const int inX, const int inY, const int width, const int height)
	{
		this->viewport_x = inX;
		this->viewport_y = inY;
		this->viewport_width = width;
		this->viewport_height = height;

		this->privSetViewState();
	};

	// Simple wrapper
	void Camera::privSetViewState(void)
	{
		glViewport(this->viewport_x, this->viewport_y, this->viewport_width, this->viewport_height);
	};

	void Camera::setOrientAndPosition(const Vec3 &inUp, const Vec3 &inLookAt, const Vec3 &inPos)
	{
		// Remember the up, lookAt and right are unit, and are perpendicular.
		// Treat lookAt as king, find Right vect, then correct Up to insure perpendiculare.
		// Make sure that all vectors are unit vectors.

		this->vLookAt = inLookAt;

		// Point out of the screen into your EYE
		this->vDir = inPos - inLookAt;
		this->vDir.norm();

		// Clean up the vectors (Right hand rule)
		this->vRight = inUp.cross(this->vDir);
		this->vRight.norm();

		this->vUp = this->vDir.cross(this->vRight);
		this->vUp.norm();

		this->vPos = inPos;
	};

	void Camera::proUpdateViewMatrix(void)
	{
		// This functions assumes the your vUp, vRight, vDir are still unit
		// And perpendicular to each other
		//  view = Rot(orient) * trans(-(eye.basis) )

		this->viewMatrix[m0] = this->vRight[x];
		this->viewMatrix[m1] = this->vUp[x];
		this->viewMatrix[m2] = this->vDir[x];
		this->viewMatrix[m3] = 0.0f;

		this->viewMatrix[m4] = this->vRight[y];
		this->viewMatrix[m5] = this->vUp[y];
		this->viewMatrix[m6] = this->vDir[y];
		this->viewMatrix[m7] = 0.0f;

		this->viewMatrix[m8] = this->vRight[z];
		this->viewMatrix[m9] = this->vUp[z];
		this->viewMatrix[m10] = this->vDir[z];
		this->viewMatrix[m11] = 0.0f;

		// Change of basis (dot with the basis vectors)
		this->viewMatrix[m12] = -vPos.dot(vRight);
		this->viewMatrix[m13] = -vPos.dot(vUp);
		this->viewMatrix[m14] = -vPos.dot(vDir);
		this->viewMatrix[m15] = 1.0f;
	};

	Camera::Type Camera::getType() const
	{
		return this->camType;
	}

	Mat4 &Camera::getViewMatrix(void)
	{
		return this->viewMatrix;
	}

	Mat4 &Camera::getProjMatrix(void)
	{
		return this->projMatrix;
	}

	void Camera::getPos(Vec3 &outPos) const
	{
		outPos = this->vPos;
	}

	void  Camera::getDir(Vec3 &outDir) const
	{
		outDir = this->vDir;
	}

	void  Camera::getUp(Vec3 &outUp) const
	{
		outUp = this->vUp;
	}

	void Camera::getLookAt(Vec3 &outLookAt) const
	{
		outLookAt = this->vLookAt;
	}

	void Camera::getRight(Vec3 &outRight) const
	{
		outRight = this->vRight;
	}

}

// --- End of File ---
