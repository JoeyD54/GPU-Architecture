//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef CAMERA_MANAGER_H
#define CAMERA_MANAGER_H

#include "Camera.h"
#include "Camera2D.h"
#include "Camera3D.h"
#include "CameraNode.h"

namespace Azul
{
	// Singleton
	class CameraMan
	{
	public:
		static void Add(Camera::Name name, Camera *pCamera);
		static Camera3D *Find3D(Camera::Name name);
		static Camera2D *Find2D(Camera::Name name);

		static void SetCurrent2D(Camera::Name name);
		static Camera2D *GetCurrent2D();

		static void SetCurrent3D(Camera::Name name);
		static Camera3D *GetCurrent3D();

		static void Create();
		static void Destroy();

	private:  // methods

		static CameraMan *privGetInstance();
		CameraMan();

		void privAddToFront(CameraLink *node, CameraLink *&head);
		void privRemove(CameraLink *pNode, CameraLink *&poHead);

	private:  // add

		CameraLink *poActive;
	
		Camera2D *pCamOrthographic;
		Camera3D *pCamPerspective;


	};

}

#endif

// --- End of File ---
