//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef CAMERA_MODEL_H
#define CAMERA_MODEL_H

#include "Mesh.h"

namespace Azul
{
	class CameraMesh : public Mesh
	{
	public:
		CameraMesh(const char *const modelFileName);
		CameraMesh(const CameraMesh &) = delete;
		CameraMesh &operator=(const CameraMesh &other) = delete;
		virtual ~CameraMesh();

		void update();

	private:
		void privCreateVAO(const char *const modelFileName);

	};

}

#endif

// --- End of File ---
