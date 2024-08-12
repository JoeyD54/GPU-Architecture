//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef CAMERA_H
#define CAMERA_H

#include "MathEngine.h"
#include "BoundingSphere.h"

namespace Azul
{
	class Camera : public Align16
	{
	public:

		enum class Type
		{
			PERSPECTIVE_3D,
			ORTHOGRAPHIC_2D
		};

		enum class Name
		{
			CAMERA_0,
			CAMERA_1,
			CAMERA_2,
			CAMERA_3,
			NOT_INITIALIZED
		};

		enum class CullResult
		{
			CULL_INSIDE,
			CULL_OUTSIDE
		};

	public:
		Camera(Camera::Type type);

		Camera() = delete;
		Camera(const Camera &) = delete;
		Camera &operator = (const Camera &) = delete;
		virtual ~Camera();

		void setViewport(const int inX, const int inY, const int width, const int height);
		void setOrientAndPosition(const Vec3 &Up_vect, const Vec3 &inLookAt_pt, const Vec3 &pos_pt);

		// update camera system
		virtual void updateCamera() = 0;

		// Get the matrices for rendering
		Mat4 &getViewMatrix();
		Mat4 &getProjMatrix();

		// Why no SETS?  Pos,Dir,Up,LookAt, Right
		//   They have to be adjust together in setOrientAndPosition()
		void getPos(Vec3 &outPos) const;
		void getDir(Vec3 &outDir) const;
		void getUp(Vec3 &outUp) const;
		void getLookAt(Vec3 &outLookAt) const;
		void getRight(Vec3 &outRight) const;

		int getScreenWidth() const;
		int getScreenHeight() const;

		Camera::Type getType() const;

		Name getName() const;
		void setName(Camera::Name name);

		// helper functions
		void GetHelper(Vec3 &up, Vec3 &tar, Vec3 &pos, Vec3 &upNorm, Vec3 &forwardNorm, Vec3 &rightNorm);
		void SetHelper(Vec3 &up, Vec3 &tar, Vec3 &pos);


	private:  // methods should never be public
		void privSetViewState(void);
		virtual void privUpdateProjectionMatrix() = 0;

	protected:
		void proUpdateViewMatrix(void);

	protected:  

		// -------------------------------------------------------
		// 16-bit aligned data below this point:
		// -------------------------------------------------------
	
		// Projection Matrix
		Mat4	projMatrix;
		Mat4	viewMatrix;

		// Camera unit vectors (up, dir, right)
		Vec3	vUp;      // Up vector
		Vec3	vDir;
		Vec3	vRight;   // derived by up and dir
		Vec3	vPos;     // pos pt

		Vec3	vLookAt;  // target pt

		// -------------------------------------------------------
		// unaligned data below this point:
		// -------------------------------------------------------

		Camera::Type camType;

		// viewports
		int		viewport_x;
		int		viewport_y;
		int		viewport_width;
		int		viewport_height;

		// Name
		Camera::Name name;
	};

}

#endif

// --- End of File ---
