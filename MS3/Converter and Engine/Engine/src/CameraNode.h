//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef CAMERA_NODE_H
#define CAMERA_NODE_H

namespace Azul
{
	class Camera;

	class CameraLink
	{
	public:
		CameraLink()
		{
			this->next = nullptr;
			this->prev = nullptr;
		}
		CameraLink(const CameraLink &) = default;
		CameraLink &operator = (const CameraLink &) = default;
		virtual ~CameraLink() = default;

		CameraLink *next;
		CameraLink *prev;
	};

	class CameraNode : public CameraLink
	{
	public:
		CameraNode();
		CameraNode(const CameraNode &) = default;
		CameraNode &operator = (const CameraNode &) = default;
		virtual ~CameraNode();

		void set(Camera *pCamera);

	public:
		Camera *poCamera;

	};

}

#endif

// --- End of File ---
