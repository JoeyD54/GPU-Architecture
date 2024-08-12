//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "GameObject.h"
#include "MathEngine.h"
#include "File.h"
#include "ShaderObject.h"
#include "Game.h"
#include "StringThis.h"

namespace Azul
{

	ShaderObject::ShaderObject()
		: name(ShaderObject::Name::UNINITIALIZED),
		programObject(0),
		type(ShaderObject::Type::UNITINTIALIZED),
		fs(0),
		vs(0),
		cs(0)
	{

	}

	void ShaderObject::privClear()
	{
		if(this->programObject)
		{
			glUseProgram(0);
			glDeleteProgram(this->programObject);
			glDeleteShader(this->fs);
			glDeleteShader(this->vs);
			glDeleteShader(this->cs);

			this->name = Name::UNINITIALIZED;
			this->programObject = 0;
			this->type = Type::UNITINTIALIZED;
			this->fs = 0;
			this->vs = 0;
			this->cs = 0;
		}
	}

	ShaderObject::~ShaderObject()
	{
		this->privClear();
	}

	void ShaderObject::Set(ShaderObject::Name _name, const char *const pName, const ShaderObject::Type _type)
	{
		this->name = _name;
		this->type = _type;
		assert(pName);
		this->privCreateShader(this->programObject, pName, _type);
	}

	GLint ShaderObject::GetLocation(const char *const pUniformName) const
	{
		assert(pUniformName);
		GLint loc = glGetUniformLocation(this->programObject, pUniformName);
		assert(loc != -1);

		return loc;
	}

	void ShaderObject::SetActive() const
	{
		// Setup for shader
		glUseProgram(this->programObject);
	}

	void ShaderObject::Dispatch(unsigned int groupsize_x, unsigned int groupsize_y, unsigned int groupsize_z)
	{
		if(this->type == ShaderObject::Type::COMPUTE)
		{
			glDispatchCompute(groupsize_x, groupsize_y, groupsize_z);
		}
	}

	void ShaderObject::privLoadFile(const char *const pName, char *&pBuff, int &BuffSize)
	{
		File::Handle fh;
		File::Error  ferror;

		assert(pName);

		// --------------------------
		// Add path to file name
		// --------------------------

		const char *pPath = "Shaders\\";
		size_t size = strlen(pPath) + strlen(pName) + 1;
		char *pFileName = new char[size]();
		memset(pFileName, 0, size);
		strcat_s(pFileName, size, pPath);
		strcat_s(pFileName, size, pName);

		// --------------------------------------------
		// Ppen/Read the file and store in buffer
		// --------------------------------------------

		ferror = File::Open(fh, pFileName, File::Mode::READ);
		assert(ferror == File::Error::SUCCESS);
		delete[] pFileName;

		ferror = File::Seek(fh, File::Position::END, 0);
		assert(ferror == File::Error::SUCCESS);

		DWORD numBytesInFile;
		ferror = File::Tell(fh, numBytesInFile);
		assert(ferror == File::Error::SUCCESS);

		ferror = File::Seek(fh, File::Position::BEGIN, 0);
		assert(ferror == File::Error::SUCCESS);

		char *data = new char[numBytesInFile + 1];
		memset(data, 0, numBytesInFile + 1);
		assert(data);

		ferror = File::Read(fh, data, numBytesInFile);
		assert(ferror == File::Error::SUCCESS);

		// null termination character
		data[numBytesInFile] = 0;

		ferror = File::Close(fh);
		assert(ferror == File::Error::SUCCESS);

		pBuff = data;
		BuffSize = (int)numBytesInFile;

	}

	void ShaderObject::privRemoveVersionLine(char *pBuff, const char *pTok)
	{
		assert(pBuff);

		size_t BlankSize = strlen(pTok);
		char *pBlank = new char[BlankSize + 1]();
		assert(pBlank);
		memset(pBlank, 0, BlankSize + 1);
		memset(pBlank, ' ', BlankSize);

		char *r = strstr(pBuff, pTok);

		if(r)
		{
			memcpy_s(r, strlen(r) + 1, pBlank, BlankSize);
		}

		delete[] pBlank;
	}


	bool ShaderObject::privLoadNCompile(GLuint &shaderObject, const char *const pShaderFileName, GLenum shader_type)
	{
		assert(pShaderFileName);

		char *pBuffShaderFile = nullptr;
		int BuffShaderFileSize = 0;

		privLoadFile(pShaderFileName, pBuffShaderFile, BuffShaderFileSize);
		assert(pBuffShaderFile);
		assert(BuffShaderFileSize);

		// remove "#version 430 core"        
		privRemoveVersionLine(pBuffShaderFile, "#version 430 core");
		// remove "#include "ShaderLayout.h""   
		privRemoveVersionLine(pBuffShaderFile, "#include \"ShaderLayout.h\"");

		char *pBuffShaderLayout = nullptr;
		int BufferShaderLayoutSize = 0;
		privLoadFile("ShaderLayout.h", pBuffShaderLayout, BufferShaderLayoutSize);
		assert(pBuffShaderLayout);
		assert(BufferShaderLayoutSize);

		const char *pVersionGLSL = "#version 430 core\n\n";
		size_t VersionGLSL_size = strlen(pVersionGLSL);

		size_t dataSize = VersionGLSL_size + BufferShaderLayoutSize + BuffShaderFileSize + 1;

		char *data = new char[dataSize]();
		memset(data, 0, dataSize);

		strcat_s(data, dataSize, pVersionGLSL);
		strcat_s(data, dataSize, pBuffShaderLayout);
		strcat_s(data, dataSize, pBuffShaderFile);

		delete[] pBuffShaderLayout;
		delete[] pBuffShaderFile;

		// clean the
		//char *data = pBuffShaderFile;

		// create a shader object
		shaderObject = glCreateShader(shader_type);
		assert(shaderObject);

		//load shader
		glShaderSource(shaderObject, 1, &data, 0);
		delete[] data;

		glCompileShader(shaderObject);

		// check for errors
		GLint status = 0;
		glGetShaderiv(shaderObject, GL_COMPILE_STATUS, &status);

		// found one
		if(!status)
		{
			char buffer[4096];
			glGetShaderInfoLog(shaderObject, 4096, NULL, buffer);

			Trace::out("Error(ShaderLoadNCompile.cpp) %s: %s\n", pShaderFileName, buffer);

			glDeleteShader(shaderObject);

			assert(false);
			return false;
		}
		else
		{
			return true;
		}
	}

	bool ShaderObject::privCreateShader(GLuint &inProgramObject, const char *const pShaderBaseFileName, const ShaderObject::Type _type)
	{
		bool status;
		char nameBuff[128];

		assert(pShaderBaseFileName);

		if(_type == ShaderObject::Type::GRAPHICS)
		{
			strcpy_s(nameBuff, 128, pShaderBaseFileName);
			strcat_s(nameBuff, 128, ".fs.glsl");

			status = privLoadNCompile(this->fs, nameBuff, GL_FRAGMENT_SHADER);
			assert(status == true);

			strcpy_s(nameBuff, 128, pShaderBaseFileName);
			strcat_s(nameBuff, 128, ".vs.glsl");

			status = privLoadNCompile(this->vs, nameBuff, GL_VERTEX_SHADER);
			assert(status == true);

			// Creates an empty program object
			inProgramObject = glCreateProgram();

			//Attaches a shader object to a program object
			glAttachShader(inProgramObject, this->vs);
			glAttachShader(inProgramObject, this->fs);

			// Links a program object
			glLinkProgram(inProgramObject);

		}
		else
		{
			//  ShaderObject::Type::COMPUTE
			strcpy_s(nameBuff, 128, pShaderBaseFileName);
			strcat_s(nameBuff, 128, ".cs.glsl");

			status = privLoadNCompile(this->cs, nameBuff, GL_COMPUTE_SHADER);
			assert(status == true);

			// Creates an empty program object
			inProgramObject = glCreateProgram();

			//Attaches a shader object to a program object
			glAttachShader(inProgramObject, cs);

			// Links a program object
			glLinkProgram(inProgramObject);
		}

		return true;
	}

	void ShaderObject::Wash()
	{
		this->privClear();
	}

	char *ShaderObject::GetName()
	{
		// todo - Hack understand why is this needed for print and fix...
		static char pTmp[128];
		strcpy_s(pTmp, 128, StringMe(this->name));
		return pTmp;
	}

	bool ShaderObject::Compare(DLink *pTarget)
	{
		// This is used in ManBase.Find() 
		assert(pTarget);

		ShaderObject *pDataB = (ShaderObject *)pTarget;

		bool status = false;

		if(this->name == pDataB->name)
		{
			status = true;
		}

		return status;
	}

	void ShaderObject::Dump()
	{
		Trace::out("      ShaderObject(%p)\n", this);

		// Data:
		Trace::out("      Name: %s \n", StringMe(this->name));


		DLink::Dump();
	}

}

// --- End of File ---
