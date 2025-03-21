//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef MESH_FILE_HDR_H
#define MESH_FILE_HDR_H


namespace Azul
{
	struct MeshFileHdr
	{
	public:
		static const unsigned int OBJECT_NAME_SIZE = 32;
		static const unsigned int TEXTURE_NAME_SIZE = 32;

	public:
		MeshFileHdr();
		MeshFileHdr(const MeshFileHdr&) = delete;
		MeshFileHdr& operator = (const MeshFileHdr&) = delete;
		~MeshFileHdr() = default;

	public:
		// Data -----------------

		// object name
		char	objName[OBJECT_NAME_SIZE];

		// vertex buffers
		int		numVerts;
		DWORD	vertBufferOffset;
		DWORD	textsBufferOffset;
		DWORD	normsBufferOffset;

		// trilist index 
		int		numTriList;
		DWORD	triListBufferOffset;


		// Future - texture info 
		// char textName[TEXTURE_NAME_SIZE];
		// unsigned int minFilter;
		// unsigned int magFilter;
		// unsigned int horizWrapMode;
		// unsigned int vertWrapMode;

	};


}

#endif

// --- End of File ---
