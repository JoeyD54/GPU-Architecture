//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef SHADER_OBJECT_H
#define SHADER_OBJECT_H

#include "sb7.h"
#include "DLink.h"

namespace Azul
{
	class ShaderObject : public DLink
	{
	public:
		enum class Name
		{
			NULL_SHADER,
			COLOR_POSITION,
			COLOR_SINGLE,
			TEXTURE_SIMPLE,
			SPRITE,
			SKIN_TEXTURE,
			TEXTURE_POINT_LIGHT,
			CONST_COLOR,
			COMPUTE_TEST,
			COMPUTE_MIXER,
			COMPUTE_WORLD,
			UNINITIALIZED
		};

		enum class Type
		{
			GRAPHICS,
			COMPUTE,
			UNITINTIALIZED
		};


	public:
		ShaderObject();
		ShaderObject(const ShaderObject &) = delete;
		ShaderObject &operator = (ShaderObject &) = delete;
		virtual ~ShaderObject();


		void Set(ShaderObject::Name name, const char *const pName, const ShaderObject::Type type);
		void SetActive() const;
		GLint GetLocation(const char *const pUniformName) const;

		virtual void Wash() override;
		virtual char *GetName() override;
		virtual bool Compare(DLink *pTargetNode) override;
		virtual void Dump() override;

		void Dispatch(unsigned int groupsize_x, unsigned int groupsize_y, unsigned int groupsize_z);


	private:
		void privClear();
		bool privCreateShader(GLuint &programObject, const char *const pShaderBaseFileName, const ShaderObject::Type type);
		bool privLoadNCompile(GLuint &shaderObject, const char *const pShaderFileName, GLenum shader_type);
		void privLoadFile(const char *const pFileName, char *&pBuff, int &BuffSize);
		void privRemoveVersionLine(char *pBuff, const char *pTok);


	public:
		Name    name;
		GLuint  programObject;
		Type    type;
		GLuint  fs;     // GRAPHICS - fragment shader
		GLuint  vs;     // GRAPHICS - vertex shader
		GLuint  cs;     // COMPUTE shader

	};

}

#endif

// --- End of File ---
