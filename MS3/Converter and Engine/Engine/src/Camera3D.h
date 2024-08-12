//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef CAMERA_3D_H
#define CAMERA_3D_H

#include "MathEngine.h"
#include "BoundingSphere.h"
#include "Camera.h"

namespace Azul
{
	class Camera3D final : public Camera
	{
	public:
		Camera3D();
		Camera3D(const Camera3D &) = delete;
		Camera3D &operator = (const Camera3D &) = delete;
		virtual ~Camera3D();

		virtual void updateCamera() override;
		virtual void privUpdateProjectionMatrix() override;

		void setPerspective(const float FieldOfView_Degs, const float AspectRatio, const float NearDist, const float FarDist);

		void getFieldOfView(float &Value) const;
		void setFieldOfView(const float Value);

		void getNearDist(float &Value) const;
		void setNearDist(const float Value);

		void getNearTopLeft(Vec3 &vOut) const;
		void getNearTopRight(Vec3 &vOut) const;
		void getNearBottomLeft(Vec3 &vOut) const;
		void getNearBottomRight(Vec3 &vOut) const;
		void getFarTopLeft(Vec3 &vOut) const;
		void getFarTopRight(Vec3 &vOut) const;
		void getFarBottomLeft(Vec3 &vOut) const;
		void getFarBottomRight(Vec3 &vOut) const;

		CullResult CullTest(const Sphere &Sphere);

	private:
		void privCalcPlaneHeightWidth(void);
		void privCalcFrustumVerts(void);
		void privCalcFrustumCollisionNormals(void);

	private:

		// -------------------------------------------------------
		// 16-bit aligned data below this point:
		// -------------------------------------------------------

		// world space coords for viewing frustum
		Vec3	nearTopLeft;
		Vec3	nearTopRight;
		Vec3	nearBottomLeft;

		Vec3	nearBottomRight;
		Vec3	farTopLeft;
		Vec3	farTopRight;
		Vec3	farBottomLeft;

		Vec3	farBottomRight;

		// Normals of the frustum
		Vec3	frontNorm;
		Vec3	backNorm;
		Vec3	rightNorm;

		Vec3	leftNorm;
		Vec3	topNorm;
		Vec3	bottomNorm;

		// Define the frustum inputs
		float	fovy;
		float	aspectRatio;

		// Define the frustum inputs
		float	nearDist;
		float	farDist;

		// Screen size in world space
		float	near_height;
		float	near_width;
		float	far_height;
		float	far_width;

	};

}

#endif

// --- End of File ---
