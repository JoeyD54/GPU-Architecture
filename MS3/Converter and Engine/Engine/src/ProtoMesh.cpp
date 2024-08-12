//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "meshData.h"

#include "ProtoMesh.h"
#include "File.h"
#include "MeshFileHdr.h"
#include "TextureMan.h"
#include "ShaderLayout.h"
#include "GameMan.h"

namespace Azul
{
	void ProtoMesh::privCreateVAO(const char *const pMeshFileName, Texture *&pTexture)
	{
		// future proofing it for a file
		assert(pMeshFileName);
		AZUL_UNUSED_VAR(pMeshFileName);

		// Create a VAO
		glGenVertexArrays(1, &this->vao);
		assert(this->vao != 0);
		glBindVertexArray(this->vao);   // <--- Active

		// Create a VBO
		glGenBuffers(1, &this->vbo_verts);
		assert(this->vbo_verts != 0);

		glGenBuffers(1, &this->vbo_norms);
		assert(this->vbo_norms != 0);

		glGenBuffers(1, &this->vbo_uv);
		assert(this->vbo_uv != 0);

		glGenBuffers(1, &this->vbo_color);
		assert(this->vbo_color != 0);

		glGenBuffers(1, &this->vbo_index);
		assert(this->vbo_index != 0);

		glGenBuffers(1, &this->vbo_weight);
		assert(this->vbo_weight != 0);

		glGenBuffers(1, &this->vbo_joint);
		assert(this->vbo_joint != 0);


		// File stuff
		File::Handle fh;
		File::Error  ferror;

		// create a header
		MeshFileHdr meshHdr;

		// ----------------------------------------------
		// READ the data from the file ONLY
		// ----------------------------------------------
		assert(pMeshFileName);
		const char *pPath = "Data\\";
		size_t size = strlen(pPath) + strlen(pMeshFileName) + 1;
		char *pFileName = new char[size]();
		memset(pFileName, 0, size);
		strcat_s(pFileName, size, pPath);
		strcat_s(pFileName, size, pMeshFileName);

		ferror = File::Open(fh, pFileName, File::Mode::READ);
		assert(ferror == File::Error::SUCCESS);

		delete[] pFileName;

		// Get the size
		ferror = File::Seek(fh, File::Position::END, 0);
		assert(ferror == File::Error::SUCCESS);

		DWORD length;
		ferror = File::Tell(fh, length);
		assert(ferror == File::Error::SUCCESS);

		ferror = File::Seek(fh, File::Position::BEGIN, 0);
		assert(ferror == File::Error::SUCCESS);

		char *poBuff = new char[length];
		assert(poBuff);

		ferror = File::Read(fh, poBuff, length);
		assert(ferror == File::Error::SUCCESS);

		ferror = File::Close(fh);
		assert(ferror == File::Error::SUCCESS);


		std::string strIn(poBuff, length);
		meshData_proto mB_proto;

		mB_proto.ParseFromString(strIn);

		meshData mB;
		mB.Deserialize(mB_proto);
		//mB.Print("mB");

		delete[] poBuff;

		// General stuff
		assert(mB.mode == meshData::RENDER_MODE::MODE_TRIANGLES);

		this->numTris = (int)mB.triCount;
		this->numVerts = (int)mB.vertCount;

		assert(this->numTris > 0);
		assert(this->numVerts > 0);

		// safety
		assert(strcmp(mB.pVersion, GameMan::GetGame()->GetProtoVersion()) == 0);

		// Load the verts data: ---------------------------------------------------------

		if(mB.vbo_vert.enabled)
		{
			assert(mB.vbo_vert.targetType == vboData::VBO_TARGET::ARRAY_BUFFER);
			glBindBuffer(GL_ARRAY_BUFFER, this->vbo_verts);

			// load the data to the GPU
			assert(mB.vbo_vert.poData);
			assert(mB.vbo_vert.dataSize > 0);
			assert(mB.vbo_vert.count * sizeof(Vert_xyz) == mB.vbo_vert.dataSize);
			glBufferData(GL_ARRAY_BUFFER, (GLsizeiptr)(mB.vbo_vert.dataSize), mB.vbo_vert.poData, GL_STATIC_DRAW);

			// Vert data is location: ATTRIB_LOCATION_VERT  (used in vertex shader)
			assert(ATTRIB_LOCATION_VERT == mB.vbo_vert.attribIndex);
			assert(mB.vbo_vert.vboType == vboData::VBO_TYPE::VEC3);
			assert(mB.vbo_vert.componentType == vboData::VBO_COMPONENT::FLOAT);
			glVertexAttribPointer(mB.vbo_vert.attribIndex, 3, GL_FLOAT, GL_FALSE, sizeof(Vert_xyz), 0);
			glEnableVertexAttribArray(mB.vbo_vert.attribIndex);
		}

		// Load the norms data: ---------------------------------------------------------

		if(mB.vbo_norm.enabled)
		{
			assert(mB.vbo_norm.targetType == vboData::VBO_TARGET::ARRAY_BUFFER);
			glBindBuffer(GL_ARRAY_BUFFER, this->vbo_norms);

			// load the data to the GPU
			assert(mB.vbo_norm.poData);
			assert(mB.vbo_norm.dataSize > 0);
			assert(mB.vbo_norm.count * sizeof(Vert_nxnynz) == mB.vbo_norm.dataSize);
			glBufferData(GL_ARRAY_BUFFER, (GLsizeiptr)(mB.vbo_norm.dataSize), mB.vbo_norm.poData, GL_STATIC_DRAW);

			// normals data in location ATTRIB_LOCATION_NORM (used in vertex shader)
			assert(ATTRIB_LOCATION_NORM == mB.vbo_norm.attribIndex);
			assert(mB.vbo_norm.vboType == vboData::VBO_TYPE::VEC3);
			assert(mB.vbo_norm.componentType == vboData::VBO_COMPONENT::FLOAT);
			glVertexAttribPointer(mB.vbo_norm.attribIndex, 3, GL_FLOAT, GL_FALSE, sizeof(Vert_nxnynz), 0);
			glEnableVertexAttribArray(mB.vbo_norm.attribIndex);
		}

		// Load the texts data: ---------------------------------------------------------

		if(mB.vbo_uv.enabled)
		{
			assert(mB.vbo_uv.targetType == vboData::VBO_TARGET::ARRAY_BUFFER);
			glBindBuffer(GL_ARRAY_BUFFER, this->vbo_uv);

			// load the data to the GPU
			assert(mB.vbo_uv.poData);
			assert(mB.vbo_uv.dataSize > 0);
			assert(mB.vbo_uv.count * sizeof(Vert_uv) == mB.vbo_uv.dataSize);
			glBufferData(GL_ARRAY_BUFFER, (GLsizeiptr)(mB.vbo_uv.dataSize), mB.vbo_uv.poData, GL_STATIC_DRAW);

			// Texture data is location: ATTRIB_LOCATION_TEXT  (used in vertex shader)
			assert(ATTRIB_LOCATION_TEXT == mB.vbo_uv.attribIndex);
			assert(mB.vbo_uv.vboType == vboData::VBO_TYPE::VEC2);
			assert(mB.vbo_uv.componentType == vboData::VBO_COMPONENT::FLOAT);
			glVertexAttribPointer(mB.vbo_uv.attribIndex, 2, GL_FLOAT, GL_FALSE, sizeof(Vert_uv), 0);
			glEnableVertexAttribArray(mB.vbo_uv.attribIndex);
		}

		// Load the color data: ---------------------------------------------------------

		if(mB.vbo_color.enabled)
		{
			assert(mB.vbo_color.targetType == vboData::VBO_TARGET::ARRAY_BUFFER);
			glBindBuffer(GL_ARRAY_BUFFER, this->vbo_color);

			// load the data to the GPU
			assert(mB.vbo_color.poData);
			assert(mB.vbo_color.dataSize > 0);
			assert(mB.vbo_color.count * sizeof(Vert_color) == mB.vbo_color.dataSize);
			glBufferData(GL_ARRAY_BUFFER, (GLsizeiptr)(mB.vbo_color.dataSize), mB.vbo_color.poData, GL_STATIC_DRAW);

			// color data in location ATTRIB_LOCATION_COLOR (used in vertex shader)
			assert(ATTRIB_LOCATION_COLOR == mB.vbo_color.attribIndex);
			assert(mB.vbo_color.vboType == vboData::VBO_TYPE::VEC4);
			assert(mB.vbo_color.componentType == vboData::VBO_COMPONENT::FLOAT);
			glVertexAttribPointer(mB.vbo_color.attribIndex, 4, GL_FLOAT, GL_FALSE, sizeof(Vert_color), 0);
			glEnableVertexAttribArray(mB.vbo_color.attribIndex);
		}

		// Load the weight data: ---------------------------------------------------------

		if(mB.vbo_weights.enabled)
		{
			assert(mB.vbo_weights.targetType == vboData::VBO_TARGET::ARRAY_BUFFER);
			glBindBuffer(GL_ARRAY_BUFFER, this->vbo_weight);

			// load the data to the GPU
			assert(mB.vbo_weights.poData);
			assert(mB.vbo_weights.dataSize > 0);
			assert(mB.vbo_weights.count * sizeof(Vert_weight) == mB.vbo_weights.dataSize);
			glBufferData(GL_ARRAY_BUFFER, (GLsizeiptr)(mB.vbo_weights.dataSize), mB.vbo_weights.poData, GL_STATIC_DRAW);

			// data in location ATTRIB_LOCATION_WEIGHT(used in vertex shader)
			assert(ATTRIB_LOCATION_WEIGHT == mB.vbo_weights.attribIndex);
			assert(mB.vbo_weights.vboType == vboData::VBO_TYPE::VEC4);
			assert(mB.vbo_weights.componentType == vboData::VBO_COMPONENT::FLOAT);
			glVertexAttribPointer(mB.vbo_weights.attribIndex, 4, GL_FLOAT, GL_FALSE, sizeof(Vert_weight), 0);
			glEnableVertexAttribArray(mB.vbo_weights.attribIndex);
		}

		// Load the Joint data: ---------------------------------------------------------

		if(mB.vbo_joints.enabled)
		{
			assert(mB.vbo_joints.targetType == vboData::VBO_TARGET::ARRAY_BUFFER);
			glBindBuffer(GL_ARRAY_BUFFER, this->vbo_joint);

			// load the data to the GPU
			assert(mB.vbo_joints.poData);
			assert(mB.vbo_joints.dataSize > 0);
			assert(mB.vbo_joints.count * sizeof(Vert_joint) == mB.vbo_joints.dataSize);
			glBufferData(GL_ARRAY_BUFFER, (GLsizeiptr)(mB.vbo_joints.dataSize), mB.vbo_joints.poData, GL_STATIC_DRAW);

			// data in location ATTRIB_LOCATION_JOINT(used in vertex shader)
			assert(ATTRIB_LOCATION_JOINT == mB.vbo_joints.attribIndex);
			assert(mB.vbo_joints.vboType == vboData::VBO_TYPE::VEC4);
			assert(mB.vbo_joints.componentType == vboData::VBO_COMPONENT::UNSIGNED_INT);
			glVertexAttribIPointer(mB.vbo_joints.attribIndex, 4, GL_UNSIGNED_INT, sizeof(Vert_joint), 0);
			glEnableVertexAttribArray(mB.vbo_joints.attribIndex);
		}

		// Load the InverseBind Matrices data: ---------------------------------------------------------

		if(mB.vbo_invBind.enabled)
		{
			assert(mB.vbo_invBind.targetType == vboData::VBO_TARGET::ARRAY_BUFFER);
			//glBindBuffer(GL_ARRAY_BUFFER, this->vbo_invBind);

			// load the data to the GPU
			assert(mB.vbo_invBind.poData);
			assert(mB.vbo_invBind.dataSize > 0);
			assert(mB.vbo_invBind.count * sizeof(Mat4) == mB.vbo_invBind.dataSize);
			//glBufferData(GL_ARRAY_BUFFER, (GLsizeiptr)(mB.vbo_invBind.dataSize), mB.vbo_invBind.poData, GL_STATIC_DRAW);

			// data in location ATTRIB_LOCATION_JOINT(used in vertex shader)
			assert(ATTRIB_LOCATION_INVERSE_BIND == mB.vbo_invBind.attribIndex);
			assert(mB.vbo_invBind.vboType == vboData::VBO_TYPE::MAT4);
			assert(mB.vbo_invBind.componentType == vboData::VBO_COMPONENT::FLOAT);
			//glVertexAttribPointer(mB.vbo_invBind.attribIndex, 4, GL_FLOAT, GL_FALSE, mB.vbo_invBind.count*sizeof(Matrix), 0);
			//glEnableVertexAttribArray(mB.vbo_invBind.attribIndex);
			
			// copy data into buffer
			this->numInverseBind = mB.vbo_invBind.count;
			assert(this->numInverseBind > 0);
			this->poInverseBind = new Mat4[this->numInverseBind]();
			assert(this->poInverseBind);
			memcpy_s(this->poInverseBind, this->numInverseBind * sizeof(Mat4), mB.vbo_invBind.poData, mB.vbo_invBind.dataSize);
		}

		// Load the index data: ---------------------------------------------------------

		if(mB.vbo_index.enabled)
		{
			// Bind our 2nd VBO as being the active buffer and storing index ) 
			assert(mB.vbo_index.targetType == vboData::VBO_TARGET::ELEMENT_ARRAY_BUFFER);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo_index);

			// Copy the index data to our buffer 
			assert(mB.vbo_index.vboType == vboData::VBO_TYPE::SCALAR);
			assert(mB.vbo_index.componentType == vboData::VBO_COMPONENT::UNSIGNED_INT);
			assert(mB.vbo_index.dataSize > 0);
			assert(mB.vbo_index.poData);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, (GLsizeiptr)(mB.vbo_index.dataSize), mB.vbo_index.poData, GL_STATIC_DRAW);
		}

		// ------------------------------------------------------
		// Load the texture - hopefully
		// ------------------------------------------------------

		if(mB.text_color.enabled)
		{
			pTexture = TextureMan::Add(mB);
			assert(pTexture);
		}
		else
		{
			pTexture = nullptr;
		}

	}

	ProtoMesh::ProtoMesh(const char *const pMeshFileName, Texture::Name name)
		: Mesh()
	{
		assert(pMeshFileName);
		Texture *pTexture = nullptr;
		this->privCreateVAO(pMeshFileName, pTexture);
		TextureMan::Add(name, pTexture);
	}

	ProtoMesh::ProtoMesh(const char *const pMeshFileName)
		: Mesh()
	{
		assert(pMeshFileName);
		Texture *pTexture = nullptr;
		this->privCreateVAO(pMeshFileName, pTexture);
		assert(pTexture == nullptr);
	}

	ProtoMesh::~ProtoMesh()
	{
		// remove anything dynamic here
	}

}
// --- End of File ---
