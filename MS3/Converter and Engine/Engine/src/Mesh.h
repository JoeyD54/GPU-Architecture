//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef MESH_H
#define MESH_H

#include "sb7.h"
#include "MathEngine.h"
#include "DLink.h"
#include "BoundingSphere.h"

namespace Azul
{
	struct Vert_xyzuv
	{
		float x;
		float y;
		float z;
		float u;
		float v;
	};

	struct Vert_xyz
	{
		float x;
		float y;
		float z;
	};

	struct Vert_nxnynz
	{
		float nx;
		float ny;
		float nz;
	};

	struct Vert_uv
	{
		float u;
		float v;
	};

	struct Vert_color
	{
		float r;
		float g;
		float b;
		float a;
	};

	struct Tri_index
	{
		unsigned int v0;
		unsigned int v1;
		unsigned int v2;
	};

	struct Vert_weight
	{
		float wa;
		float wb;
		float wc;
		float wd;
	};

	struct Vert_joint
	{
		float ja;
		float jb;
		float jc;
		float jd;
	};

	class Mesh
	{
	public:
		enum class Name
		{
			CUBE,
			PYRAMID,
			CRATE,
			BONE_2,
			SPHERE,
			CAMERA,
			SPRITE,
			SPACE_FRIGATE,
			R2D2,
			CHICKEN_SKIN,
			MOUSEY_SKIN,
			Bone,
			Bone_001,
			Bone_L,
			Bone_L_001,
			Bone_L_002,
			Bone_R,
			Bone_R_001,
			Bone_R_002,
			NULL_MESH,
			NOT_INITIALIZED
		};

		static const int POLY_WINDING = GL_CCW;

	public:
		Mesh();
		Mesh(Mesh &copyMesh) = delete;
		Mesh &operator = (Mesh &copyMesh) = delete;
		virtual ~Mesh();

		// Data
		int numVerts;
		int numTris;

		GLuint vao;
		GLuint vbo_verts;  // x,y,z      ATTRIB_LOCATION_VERT  0
		GLuint vbo_norms;  // nx,ny,nz	 ATTRIB_LOCATION_NORM  1
		GLuint vbo_uv;     // u,v		 ATTRIB_LOCATION_TEXT  2
		GLuint vbo_color;  // r,g,b,a	 ATTRIB_LOCATION_COLOR 3
		GLuint vbo_index;  // trilist	 ATTRIB_LOCATION_INDEX 4

		// Skin data
		GLuint vbo_weight; // wa,wb,wc,wd   ATTRIB_LOCATION_WEIGHT 5  
		GLuint vbo_joint;  // ja,jb,jc,jd   ATTRIB_LOCATION_JOINT  6  

		// Hack
		Mat4             *poInverseBind;
		unsigned int     numInverseBind;

		// Reference sphere... before any transformations are applied
		Sphere *poRefSphere;

		void Wash();
		bool Compare(DLink *pTarget);
		char *GetName();
		void SetName(Mesh::Name _name);

	protected:



	public:
		Name name;

	};

}
#endif

// --- End of File ---
